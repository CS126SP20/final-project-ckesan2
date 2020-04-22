// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/Vector.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>

#include "mylibrary/circle.h"
#include "nlohmann/json.hpp"

namespace myapp {

std::vector<std::string> names;
std::vector<int> scores;
const char kDbPath[] = "final.db";
double previous_time = 0.0;

using cinder::Color;
using cinder::app::KeyEvent;
using std::cout;
using std::endl;
DECLARE_string(name);

MyApp::MyApp() :

    leaderboard{cinder::app::getAssetPath(kDbPath).string()},
    player_name{FLAGS_name}
{}

void MyApp::setup() {

  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  //leaderboard.AddScoreToLeaderBoard({player_name, 6});
  //loadData();
}

void MyApp::update() {


}

void MyApp::draw() {

  cinder::gl::clear();
  drawBlocks();

}

void MyApp::keyDown(KeyEvent event) {

}

void MyApp::drawBlocks() {

  cinder::gl::color( Color( 1, 0, 0 ) );
  //cinder::gl::drawSolidCircle( getWindowCenter(), 20);

  double seconds = cinder::app::getElapsedSeconds();

  if (seconds - previous_time >= .7) {
    first_x = first.getX();
    first_y = first.getY();
    second_x = second.getX();
    second_y = second.getY();
    previous_time = getElapsedSeconds();
  }

  cinder::gl::drawSolidCircle({first_x,first_y},20);

  //float coord = 100;
  cinder::gl::color( Color( .25, .25, .5) );
  //cinder::gl::drawSolidCircle( getWindowCenter() + coord, 20);
  cinder::gl::drawSolidCircle({second_x,second_y},20);
}

void MyApp::loadData() {

  names.push_back("chan");
  names.push_back(FLAGS_name);
  scores.push_back(6);
  scores.push_back(7);
  nlohmann::json j;
  j["names"] = names;
  j["scores"] = scores;

  std::cout << j.dump(4) << std::endl;
  std::ofstream o("/Users/ckesana/Downloads/cinder_0.9.2_mac"
                  "/my-projects/126final-project/resources/scoredata.json");
  o << std::setw(4) << j << std::endl;
}

void MyApp::mouseDown(cinder::app::MouseEvent event) {
  if (event.isLeft()) {
    std::cout << event.getPos()<<std::endl;
    //check if the clicks location is the same as the block's
    //if its the same add 1 point to the score
  }
}

}  // namespace myapp
