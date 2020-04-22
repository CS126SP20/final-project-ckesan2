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






