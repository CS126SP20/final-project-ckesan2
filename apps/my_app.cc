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
bool is_mode_screen = true;

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using std::cout;
using std::endl;
using std::string;

DECLARE_string(name);

MyApp::MyApp() :

    leaderboard{cinder::app::getAssetPath(kDbPath).string()},
    player_name{FLAGS_name}
{}

void MyApp::setup() {

  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  is_mode_screen = true;
  //drawModeScreen();

  //leaderboard.AddScoreToLeaderBoard({player_name, 6});
}

void MyApp::update() {

}

void MyApp::draw() {

  cinder::gl::clear();
  //do a while loop for the game mode screen (while is_mode_screen)
  //DrawModeScreen() in the while loop

  //DrawModeScreen();
  //only draw blocks if is_mode_screen = false
  DrawBlocks();

}

//citation: from snake assignment
void PrintText(const string& text, const Color& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font("Arial", 30))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::keyDown(KeyEvent event) {

}

void MyApp::DrawModeScreen() {

  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  const cinder::vec2 center = getWindowCenter();
  PrintText("Choose your Game Mode!", color, size, center);
  PrintText("Easy", color, size, {center.x, center.y + 50});
  PrintText("Medium", color, size, {center.x, center.y + 100});
  PrintText("Hard", color, size, {center.x, center.y + 150});
  //cout << center.x << endl;
  //cout << center.y << endl;
}

void MyApp::DrawBlocks() {

  cinder::gl::color( Color( 1, 0, 0 ) );
  double seconds = cinder::app::getElapsedSeconds();
  if (seconds - previous_time >= .7) {
    first_x = first.getX();
    first_y = first.getY();
    second_x = second.getX();
    second_y = second.getY();
    previous_time = getElapsedSeconds();
  }
  cinder::gl::drawSolidCircle({first_x,first_y},20);
  cinder::gl::color( Color( .25, .25, .5) );
  cinder::gl::drawSolidCircle({second_x,second_y},20);
}

void MyApp::mouseDown(cinder::app::MouseEvent event) {

  if (event.isLeft()) {
    //check if the clicks location is the same as the block's
    //if its the same add 1 point to the score
    if (engine.ClickedCircle(event.getX(), event.getY(), first_x, first_y)
    || engine.ClickedCircle(event.getX(), event.getY(), second_x, second_y)) {
      engine.IncreaseScore();
      cout << engine.GetScore() << endl;
    }
  }
}

}  // namespace myapp
