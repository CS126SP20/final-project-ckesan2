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

  auto picture = loadImage(
      loadAsset( "spacepic.jpeg" ) );
  front_image = cinder::gl::Texture2d::create( picture);

  auto game_pic = loadImage(loadAsset("earth.jpg"));
  game_image = cinder::gl::Texture2d::create( game_pic);

  auto ending_pic = loadImage(loadAsset("endingpic.jpg"));
  end_image = cinder::gl::Texture2d::create(ending_pic);
}

void MyApp::update() {

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

  cinder::gl::clear();
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();
  cinder::gl::enableAlphaBlending();
  cinder::gl::color( Color::white());

  if (timer == 0) {
    cinder::gl::draw(end_image, getWindowBounds());
    DrawEndScreen();
    return;
  }

  if (is_mode_screen) {
    cinder::gl::draw( front_image, getWindowBounds());
    DrawModeScreen();
  }

  if (!is_mode_screen) {
    cinder::gl::draw( game_image, getWindowBounds());
    DrawBlocks();
  }

}

//citation: from snake assignment
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

  const cinder::ivec2 size = {400, 50};
  const cinder::ivec2 small_size = {110, 50};
  const Color color = Color::white();
  const cinder::vec2 center = getWindowCenter();
  PrintText("Choose your Game Mode!", color, size, center);
  PrintText("Easy", color, small_size,
      {center.x, center.y + 50});
  PrintText("Medium", color, small_size,
      {center.x, center.y + 100});
  PrintText("Hard", color, small_size,
      {center.x, center.y + 150});
}

void MyApp::DrawBlocks() {

  cinder::gl::color( Color( 1, 0, 0 ) );
  double seconds = cinder::app::getElapsedSeconds();
  double threshold = 0.0;
  if (mode == "easy") {
    threshold = 1.5;
  } else if (mode == "medium") {
    threshold = .8;
  } else if (mode == "hard") {
    threshold = .5;
  }
  if (seconds - previous_time >= threshold) {
    first_x = first.getX();
    first_y = first.getY();
    second_x = second.getX();
    second_y = second.getY();
    previous_time = getElapsedSeconds();
  }
  cinder::gl::drawSolidCircle({first_x,first_y},20);
  cinder::gl::color( Color( .25, .25, .5) );
  cinder::gl::drawSolidCircle({second_x,second_y},20);
  DrawTimer(seconds);
}

void MyApp::DrawTimer(double seconds) {

  if (seconds - timer_previous_time >= 1) {
    timer--;
    timer_previous_time = seconds;
  }
  const string text = std::to_string(timer);
  const Color color = {1, 0, 0};
  const cinder::ivec2 size = {100, 50};
  const cinder::vec2 loc = {50, 50};
  PrintText(text, color, size, loc);
}

void MyApp::mouseDown(cinder::app::MouseEvent event) {

  if (event.isLeft()) {

    if (is_mode_screen) {
      const cinder::vec2 center = getWindowCenter();
      mode = engine.GetGameMode(event.getX(), event.getY(), center.x, center.y);
      if (!mode.empty()) {
        is_mode_screen = false;
      }
    } else if (engine.ClickedCircle(event.getX(), event.getY(), first_x, first_y)
    || engine.ClickedCircle(event.getX(), event.getY(), second_x, second_y)) {

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

  PrintText(user_name + "'s score: " +
  std::to_string(engine.GetScore()),
  color, size, {center.x, center.y - 250});

  //citation: snake assignment
  int row = 1;
  PrintText("Top Scores!", color, size, {center.x, center.y + (++row)*50});
  for (const mylibrary::User& user : top_users) {
    std::stringstream ss;
    ss << user.name << " - " << user.score;
    PrintText(ss.str(), color, size, {center.x,
                                      center.y + (++row) * 50});
  }
}

}  // namespace myapp
