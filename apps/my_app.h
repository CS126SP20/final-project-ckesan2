// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/leaderboard.h>
#include "mylibrary/circle.h"

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown( cinder::app::MouseEvent) override;

 private:
  void drawBlocks();
  void loadData();


 private:

  mylibrary::LeaderBoard leaderboard;
  const std::string player_name;
  mylibrary::Circle first;
  mylibrary::Circle second;
  int first_x = first.getX();
  int first_y = first.getY();
  int second_x = second.getX();
  int second_y = second.getY();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
