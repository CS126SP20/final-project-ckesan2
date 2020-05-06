// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/Vector.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <mylibrary/circle.h>
#include <cinder/audio/Voice.h>

namespace myapp {

const char kDbPath[] = "final.db";
double previous_time = 0.0;
double timer_previous_time = 0.0;
const int kLimit = 3;
const int kFontSize = 30;
const int kModeXSize = 400;
const int kTimerXSize = 100;
const int kEndXSize = 500;
const int kItemTime = 10;
bool is_mode_screen = true;
bool no_poison = true;
bool not_slow = true;

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using std::cout;
using std::endl;
using std::string;

cinder::gl::Texture2dRef front_image;
cinder::gl::Texture2dRef game_image;
cinder::gl::Texture2dRef end_image;
cinder::gl::Texture2dRef poison_image;
cinder::gl::Texture2dRef slow_image;
cinder::audio::VoiceRef mVoice;

DECLARE_string(name);

MyApp::MyApp() :

    leaderboard{cinder::app::getAssetPath(kDbPath).string()},
    user_name{FLAGS_name}
{}

void MyApp::setup() {

  cinder::audio::SourceFileRef sourceFile = cinder::audio::load(
      cinder::app::loadAsset(
          "Elevators_Need_Rock_Too.mp3" ) );
  mVoice = cinder::audio::Voice::create( sourceFile );
  mVoice->start();
  is_mode_screen = true;
  //loads my 3 background images into the textures
  auto picture = loadImage(
      loadAsset( "space.jpg" ) );
  front_image = cinder::gl::Texture2d::create( picture);
  auto game_pic = loadImage(loadAsset("earthcrater.jpg"));
  game_image = cinder::gl::Texture2d::create( game_pic);
  auto ending_pic = loadImage(loadAsset("endingpic.jpg"));
  end_image = cinder::gl::Texture2d::create(ending_pic);
  //loads 2 item images into textures
  auto poison_pic = loadImage(loadAsset( "poison.png" ) );
  poison_image = cinder::gl::Texture2d::create(poison_pic);
  auto slow_pic = loadImage(loadAsset( "slow.png" ) );
  slow_image = cinder::gl::Texture2d::create(slow_pic);
}

void MyApp::update() {

  //if the game has ended, add the scores to the correct leaderboard and
  //get the top scores
  if (timer == 0) {
    if (top_users.empty()) {
      if (mode == "easy") {
        leaderboard.AddScoreToEasyBoard({user_name, engine.GetScore()});
        top_users = leaderboard.GetTopEasyScores(kLimit);
      } else if (mode == "medium") {
        leaderboard.AddScoreToMediumBoard({user_name, engine.GetScore()});
        top_users = leaderboard.GetTopMedScores(kLimit);
      } else if (mode == "hard") {
        leaderboard.AddScoreToHardBoard({user_name, engine.GetScore()});
        top_users = leaderboard.GetTopHardScores(kLimit);
      }
    }
  }
}

void MyApp::draw() {

  //these five lines are necessary to make sure the background image color is
  //not affected by my circle colors
  cinder::gl::clear();
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();
  cinder::gl::enableAlphaBlending();
  cinder::gl::color( Color::white());
  //if game is over, draw the game over picture and screen
  if (timer == 0) {
    mVoice->stop();
    cinder::gl::draw(end_image, getWindowBounds());
    DrawEndScreen();
    return;
  }
  //if a mode has not been picked, stay on the front screen
  if (is_mode_screen) {
    cinder::gl::draw( front_image, getWindowBounds());
    DrawModeScreen();
    //otherwise draw the game image and game screen
  } else if (!is_mode_screen) {
    cinder::gl::draw( game_image, getWindowBounds());
    if (timer <= kItemTime) {
      DrawItems();
    }
    DrawBlocks();
  }
}

//citation: from snake assignment
//prints text on the app screen
void PrintText(const string& text, const Color& color,
    const cinder::ivec2& size, const cinder::vec2& loc) {

  cinder::gl::color(color);
  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font("Arial", kFontSize))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2,
                             loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawModeScreen() {

  //sizes for the text boxes to be printed
  const cinder::ivec2 size = {kModeXSize, mylibrary::kYsize};
  const cinder::ivec2 medium_size = {mylibrary::kMediumXsize, mylibrary::kYsize};
  const cinder::ivec2 small_size = {mylibrary::kSmallXSize, mylibrary::kYsize};
  const Color color = Color::white();
  const cinder::vec2 center = getWindowCenter();
  //prints the game mode options on the screen for the user to click
  PrintText("Choose your Game Mode!", color, size, center);
  //loc parameter = center of the text box
  PrintText("Easy", color, small_size,
      {center.x, center.y + mylibrary::kYsize});
  PrintText("Medium", color, medium_size,
      {center.x, center.y + (2*mylibrary::kYsize)});
  PrintText("Hard", color, small_size,
      {center.x, center.y + (3*mylibrary::kYsize)});
}

void MyApp::DrawBlocks() {

  double seconds = cinder::app::getElapsedSeconds();
  //depending on game mode, this sets how fast the blocks switch position
  double threshold = 0.0;
  if (mode == "easy") {
    threshold = 1.5;
  } else if (mode == "medium") {
    threshold = .8;
  } else if (mode == "hard") {
    threshold = .5;
  }
  if (!no_poison) {
    threshold = .2;
  } else if (!not_slow) {
    threshold = 2;
  }
  //if the time to switch has reached, the coordinates become random spots
  //on the screen
  if (seconds - previous_time >= threshold) {
    first_x = first.getX();
    first_y = first.getY();
    second_x = second.getX();
    second_y = second.getY();
    //after the switch, this updates the time the position switch happened
    previous_time = getElapsedSeconds();
  }
  //draws the two circles with the coordinates as their centers
  cinder::gl::color( Color( 1, 0, 0 ) );
  cinder::gl::drawSolidCircle({first_x,first_y},radius);
  cinder::gl::color( Color( .25, .25, .5) );
  cinder::gl::drawSolidCircle({second_x,second_y},radius);
  //draws the timer for the game taking in the elapsed time
  DrawTimer(seconds);
}

void MyApp::DrawTimer(double seconds) {

  //every second, subtract the time by 1
  if (seconds - timer_previous_time >= 1) {
    timer--;
    //update the time to use in next computation
    timer_previous_time = seconds;
  }
  //prints the time left on the upper left corner of the screen
  const string text = std::to_string(timer);
  const Color color = {1, 0, 0};
  const cinder::ivec2 size = {kTimerXSize, mylibrary::kYsize};
  const cinder::vec2 loc = {50, 50};
  PrintText(text, color, size, loc);
}

void MyApp::mouseDown(cinder::app::MouseEvent event) {

  //if the left mouse button is clicked
  if (event.isLeft()) {
    //if the screen is the beginning screen to pick modes, checks to see
    //if the user clicked on a game mode and updates that a mode has been picked
    if (is_mode_screen) {
      const cinder::vec2 center = getWindowCenter();
      mode = engine.GetGameMode(event.getX(), event.getY(), center.x, center.y);
      if (!mode.empty()) {
        is_mode_screen = false;
      }
      //if a mode has already been picked, check to see if the user clicked
      //on one of the circles
    } else if (engine.ClickedCircle(event.getX(), event.getY(),
        first_x, first_y, radius) || engine.ClickedCircle(event.getX(),
            event.getY(), second_x, second_y, radius)) {
      //if the game is not over yet, add to the score
      if (timer != 0) {
        engine.IncreaseScore();
      }
      //if neither item has been picked yet check to see if the click is one of
      //the items.
    } else if (no_poison && not_slow && timer <= kItemTime) {
        if (engine.ClickedItem(event.getX(), event.getY(), poison_centerx,
                               poison_centery, poison_width, poison_height)) {
          no_poison = false;
        } else if (engine.ClickedItem(event.getX(), event.getY(), slow_centerx,
                                      slow_centery, slow_width, slow_height)) {
          not_slow = false;
        }
    }
  }
}

void MyApp::DrawEndScreen() {

  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {kEndXSize, mylibrary::kYsize};
  const Color color = Color::white();
  //print's the current player's score in white
  PrintText(user_name + "'s score: " +
  std::to_string(engine.GetScore()),
  color, size, {center.x, center.y - 250});
  //citation: snake assignment
  //prints the top scores of the leaderboard depending on game mode
  int row = 1;
  PrintText("Top Scores!", color, size, {center.x,center.y +
  (++row)*mylibrary::kYsize});
  for (const mylibrary::User& user : top_users) {
    std::stringstream ss;
    ss << user.name << " - " << user.score;
    PrintText(ss.str(), color, size, {center.x,center.y +
    (++row) * mylibrary::kYsize});
  }
  //notifies player which item they clicked on
  if (!no_poison) {
    PrintText("You picked the poison potion!", color, size,
              {center.x, center.y - 180});
  } else if (!not_slow) {
    PrintText("You picked the slowing potion!", color, size,
              {center.x, center.y - 180});
  }
}

void MyApp::DrawItems() {

  //draws poison item and stores its coordinates and dimensions into variables
  const cinder::vec2 center = getWindowCenter();
  if (no_poison && not_slow) {
    Rectf poison_rect( center.x - 50, center.y - 50,
        center.x + 50,center.y + 50);
    cinder::gl::draw( poison_image, poison_rect);
    poison_centerx = poison_rect.getCenter().x;
    poison_centery = poison_rect.getCenter().y;
    poison_height = poison_rect.getHeight();
    poison_width = poison_rect.getWidth();
  }
  //draws slowing potion item and stores its coordinates and dimensions
  // into variables
  if (no_poison && not_slow && mode == "hard") {
    Rectf slow_rect( center.x - 50, center.y + 70, center.x + 50,
                    center.y + 210);
    cinder::gl::draw( slow_image, slow_rect);
    slow_centerx = slow_rect.getCenter().x;
    slow_centery = slow_rect.getCenter().y;
    slow_height = slow_rect.getHeight();
    slow_width = slow_rect.getWidth();
  }
}
}  // namespace myapp
