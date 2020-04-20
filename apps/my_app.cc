// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <gflags/gflags.h>
#include "nlohmann/json.hpp"
#include <cinder/gl/gl.h>

namespace myapp {

std::vector<std::string> names;
std::vector<int> scores;

using cinder::app::KeyEvent;
DECLARE_string(name);

MyApp::MyApp() { }

void MyApp::setup() {

  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  loadData();

}

void MyApp::update() {


}

void MyApp::draw() {


}

void MyApp::keyDown(KeyEvent event) {


}


void MyApp::drawBlocks() {


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
    std::cout << event.getPos();
  }
}

}  // namespace myapp
