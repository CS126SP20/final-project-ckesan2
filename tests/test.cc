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






