// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <mylibrary/leaderboard.h>
#include "mylibrary/gameengine.h"
#include "mylibrary/circle.h"

#include <catch2/catch.hpp>

TEST_CASE("Getting the correct score", "[game score]") {

  mylibrary::GameEngine engine;
  REQUIRE(engine.GetScore() == 0);

  SECTION("Add to the score") {
    engine.IncreaseScore();
    REQUIRE(engine.GetScore() == 1);
  }

  SECTION("Reset score") {
    engine.IncreaseScore();
    engine.IncreaseScore();
    REQUIRE(engine.GetScore() == 2);
    engine.ResetGame();
    REQUIRE(engine.GetScore() == 0);
  }
}

TEST_CASE("Accuracy of X Coordinates", "[coordinates]") {

  mylibrary::Circle circle;
  int x = circle.getX();
  int x2 = circle.getX();
  REQUIRE(x != x2);
}

TEST_CASE("Accuracy of Y Coordinates", "[coordinates]") {

  mylibrary::Circle circle;
  int y = circle.getY();
  int y2 = circle.getY();
  REQUIRE(y != y2);
}

TEST_CASE("X of Circle center is on screen", "[coordinates]") {

  mylibrary::Circle circle;
  int x = circle.getX();
  REQUIRE(!circle.XIsInWindow(1000));
  REQUIRE(!circle.XIsInWindow(-1));
  REQUIRE(x >= 0);
  REQUIRE(x <= 800);
  REQUIRE(circle.XIsInWindow(x));
}

TEST_CASE("Y of Circle center is on screen", "[coordinates]") {

  mylibrary::Circle circle;
  int y = circle.getY();
  REQUIRE(!circle.YIsInWindow(800));
  REQUIRE(!circle.YIsInWindow(-1));
  REQUIRE(y >= 0);
  REQUIRE(y <= 680);
  REQUIRE(circle.YIsInWindow(y));
}

TEST_CASE("Circle Not Clicked", "[location]") {

  mylibrary::GameEngine engine;
  REQUIRE(!engine.ClickedCircle(20,20,200,200));

  SECTION("Off by 21 in x and y") {
    REQUIRE(!engine.ClickedCircle(20,20,41,41));
  }

  SECTION("Off by 21 in x") {
    REQUIRE(!engine.ClickedCircle(20,20,41,40));
  }

  SECTION("Off by 21 in y") {
    REQUIRE(!engine.ClickedCircle(20,20,40,41));
  }
}

TEST_CASE("Circle Is Clicked", "[location]") {

  mylibrary::GameEngine engine;
  REQUIRE(engine.ClickedCircle(20,20,20,20));

  SECTION("Click In range") {
    REQUIRE(engine.ClickedCircle(20,20,40,40));
    REQUIRE(engine.ClickedCircle(20,20,0,0));
    REQUIRE(engine.ClickedCircle(10,20,9,19));
    REQUIRE(engine.ClickedCircle(0,0,0,0));
  }

  SECTION("Circle partially off screen") {
    REQUIRE(engine.ClickedCircle(10,10,-1,-1));
  }

}

TEST_CASE("Picked Easy Game Mode", "[easy]") {

  mylibrary::GameEngine engine;
  //assigned variables for numbers to just it have be more intuitive with the
  //coordinates going into the function
  int mouse_x = 400;
  int mouse_y = 400;
  int center_x = 400;
  int center_y = 350;
  REQUIRE(engine.GetGameMode(mouse_x, mouse_y, center_x, center_y) == "easy");

  SECTION("Different x coordinates but in range of easy button") {
    mouse_x = 360;
    REQUIRE(engine.GetGameMode(mouse_x, mouse_y, center_x, center_y) == "easy");
  }
}

TEST_CASE("Picked Medium Game Mode", "[medium]") {

  mylibrary::GameEngine engine;
  int mouse_x = 200;
  int mouse_y = 400;
  int center_x = 200;
  int center_y = 300;
  REQUIRE(engine.GetGameMode(mouse_x, mouse_y, center_x, center_y) == "medium");

  SECTION("Different x coordinate but in range of medium button") {
    mouse_x = 145;
    REQUIRE(engine.GetGameMode(mouse_x, mouse_y,
        center_x, center_y) == "medium");
  }
}

TEST_CASE("Picked Hard Game Mode", "[hard]") {

  mylibrary::GameEngine engine;
  int mouse_x = 400;
  int mouse_y = 400;
  int center_x = 400;
  int center_y = 250;
  REQUIRE(engine.GetGameMode(mouse_x, mouse_y, center_x, center_y) == "hard");

  SECTION("Different x coordinates but in range of hard button") {
    mouse_x = 448;
    REQUIRE(engine.GetGameMode(mouse_x, mouse_y, center_x, center_y) == "hard");
  }
}

TEST_CASE("No Game Mode Picked", "[no game mode]") {

  mylibrary::GameEngine engine;
  int mouse_x = 0;
  int mouse_y = 0;
  int center_x = 0;
  int center_y = 0;
  REQUIRE(engine.GetGameMode(mouse_x, mouse_y, center_x, center_y).empty());

  SECTION("Different x coordinates and no game mode picked") {
    mouse_x = 400;
    REQUIRE(engine.GetGameMode(mouse_x, mouse_y, center_x, center_y).empty());
  }

  SECTION("Different y coordinates and no game mode picked") {
    mouse_y = 200;
    REQUIRE(engine.GetGameMode(mouse_x, mouse_y, center_x, center_y).empty());
  }

  SECTION("All same coordinates other than 0") {
    mouse_x = 100;
    mouse_y = 100;
    center_x = 100;
    center_y = 100;
    REQUIRE(engine.GetGameMode(mouse_x, mouse_y, center_x, center_y).empty());
  }

  SECTION("All different coordinates") {
    mouse_x = 100;
    mouse_y = 200;
    center_x = 300;
    center_y = 400;
    REQUIRE(engine.GetGameMode(mouse_x, mouse_y, center_x, center_y).empty());
  }
}








