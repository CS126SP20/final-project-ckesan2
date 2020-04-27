// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/Vector.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>
#include <cinder/Font.h>
#include <cinder/Text.h>

#include "mylibrary/circle.h"
#include "nlohmann/json.hpp"

namespace myapp {

const char kDbPath[] = "final.db";
double previous_time = 0.0;
double timer_previous_time = 0.0;
const int kLimit = 3;
bool is_mode_screen = true;

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


DECLARE_string(name);

MyApp::MyApp() :

    leaderboard{cinder::app::getAssetPath(kDbPath).string()},
    user_name{FLAGS_name}
{}

void MyApp::setup() {

  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  is_mode_screen = true;
  //loads my 3 background images into the textures
  auto picture = loadImage(
      loadAsset( "spacepic.jpeg" ) );
  front_image = cinder::gl::Texture2d::create( picture);
  auto game_pic = loadImage(loadAsset("earth.jpg"));
  game_image = cinder::gl::Texture2d::create( game_pic);
  auto ending_pic = loadImage(loadAsset("endingpic.jpg"));
  end_image = cinder::gl::Texture2d::create(ending_pic);
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
      .font(cinder::Font("Arial", 30))
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

void MyApp::keyDown(KeyEvent event) {

}

void MyApp::DrawModeScreen() {

  //locations for the text to be printed
  const cinder::ivec2 size = {400, 50};
  const cinder::ivec2 medium_size = {110, 50};
  const cinder::ivec2 small_size = {96, 50};
  const Color color = Color::white();
  const cinder::vec2 center = getWindowCenter();
  //prints the game mode options on the screen for the user to click
  PrintText("Choose your Game Mode!", color, size, center);
  //loc parameter = center of the text box
  PrintText("Easy", color, small_size,
      {center.x, center.y + 50});
  PrintText("Medium", color, medium_size,
      {center.x, center.y + 100});
  PrintText("Hard", color, small_size,
      {center.x, center.y + 150});
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
  const cinder::ivec2 size = {100, 50};
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
    } else if (engine.ClickedCircle(event.getX(), event.getY(), first_x,
        first_y, radius) || engine.ClickedCircle(event.getX(), event.getY(),
            second_x, second_y, radius)) {
      //if the game is not over yet, add to the score
      if (timer != 0) {
        engine.IncreaseScore();
      }
      cout << engine.GetScore() << endl;
    }
  }
}

void MyApp::DrawEndScreen() {

  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  //print's the current player's score in white
  PrintText(user_name + "'s score: " +
  std::to_string(engine.GetScore()),
  color, size, {center.x, center.y - 250});
  //citation: snake assignment
  //prints the top scores of the leaderboard depending on game mode
  int row = 1;
  PrintText("Top Scores!", color, size, {center.x,
                                         center.y + (++row)*50});
  for (const mylibrary::User& user : top_users) {
    std::stringstream ss;
    ss << user.name << " - " << user.score;
    PrintText(ss.str(), color, size, {center.x,
                                      center.y + (++row) * 50});
  }
}
}  // namespace myapp
