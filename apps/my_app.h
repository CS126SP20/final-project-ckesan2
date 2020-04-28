// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/gameengine.h>
#include <mylibrary/leaderboard.h>

#include "mylibrary/circle.h"

namespace myapp {

using std::string;

class MyApp : public cinder::app::App {

 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown( cinder::app::MouseEvent) override;

 private:
  //draws the two circles on the screen
  void DrawBlocks();
  //displays the front screen asking user to pick game mode
  void DrawModeScreen();
  //displays the timer on the screen
  void DrawTimer(double seconds);
  //draws after the game is over and displays scores
  void DrawEndScreen();

  void DrawItems();

 private:

  mylibrary::LeaderBoard leaderboard;
  const std::string user_name;
  mylibrary::Circle first;
  mylibrary::Circle second;
  int first_x = first.getX();
  int first_y = first.getY();
  int second_x = second.getX();
  int second_y = second.getY();
  mylibrary::GameEngine engine;
  string mode = "";
  int timer = 15;
  std::vector<mylibrary::User> top_users;
  int radius = first.GetRadius();

  int poison_centerx;
  int poison_centery;
  int slow_centerx;
  int slow_centery;
  int slow_height;
  int slow_width;
  int poison_height;
  int poison_width;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
