// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <mylibrary/gameengine.h>
#include <mylibrary/circle.h>
#include <catch2/catch.hpp>

TEST_CASE("Getting the correct score", "[game score]") {

  //makes sure the score is 0 at the start of the game
  mylibrary::GameEngine engine;
  REQUIRE(engine.GetScore() == 0);

  //makes sure score updated after increasing it
  SECTION("Add to the score") {
    engine.IncreaseScore();
    REQUIRE(engine.GetScore() == 1);
  }

  //checks that score goes back to 0 after resetting the game
  SECTION("Reset score") {
    engine.IncreaseScore();
    engine.IncreaseScore();
    REQUIRE(engine.GetScore() == 2);
    engine.ResetGame();
    REQUIRE(engine.GetScore() == 0);
  }
}

TEST_CASE("Accuracy of X Coordinates", "[coordinates]") {

  //checks that x coordinate changes after every call of getX
  mylibrary::Circle circle;
  int x = circle.getX();
  int x2 = circle.getX();
  REQUIRE(x != x2);
}

TEST_CASE("Accuracy of Y Coordinates", "[coordinates]") {

  //checks that y coordinate changes after every call of getY
  mylibrary::Circle circle;
  int y = circle.getY();
  int y2 = circle.getY();
  REQUIRE(y != y2);
}

TEST_CASE("X of Circle center is on screen", "[coordinates]") {

  //checks that the x coordinate is not off screen
  mylibrary::Circle circle;
  int x = circle.getX();
  REQUIRE(!circle.XIsInWindow(1000));
  REQUIRE(!circle.XIsInWindow(-1));
  REQUIRE(x >= 0);
  REQUIRE(x <= 800);
  REQUIRE(circle.XIsInWindow(x));
}

TEST_CASE("Y of Circle center is on screen", "[coordinates]") {

  //checks that the y coordinate is not off screen
  mylibrary::Circle circle;
  int y = circle.getY();
  REQUIRE(!circle.YIsInWindow(800));
  REQUIRE(!circle.YIsInWindow(-1));
  REQUIRE(y >= 0);
  REQUIRE(y <= 680);
  REQUIRE(circle.YIsInWindow(y));
}

TEST_CASE("Circle Not Clicked", "[location]") {

  //checks that the circle is not clicked if click is outside the radius
  mylibrary::GameEngine engine;
  int radius = 20;
  REQUIRE(!engine.ClickedCircle(20,20,200,200, radius));

  SECTION("Off by 21 in x and y") {
    REQUIRE(!engine.ClickedCircle(20,20,41,41, radius));
  }

  SECTION("Off by 21 in x") {
    REQUIRE(!engine.ClickedCircle(20,20,41,40, radius));
  }

  SECTION("Off by 21 in y") {
    REQUIRE(!engine.ClickedCircle(20,20,40,41, radius));
  }
}

TEST_CASE("Circle Is Clicked", "[location]") {

  //checks that the circle is clicked if click is inside the radius
  mylibrary::GameEngine engine;
  int radius = 20;
  REQUIRE(engine.ClickedCircle(20,20,20,20, radius));

  SECTION("Click In range") {
    REQUIRE(engine.ClickedCircle(20,20,40,40, radius));
    REQUIRE(engine.ClickedCircle(20,20,0,0, radius));
    REQUIRE(engine.ClickedCircle(10,20,9,19, radius));
    REQUIRE(engine.ClickedCircle(0,0,0,0, radius));
  }

  SECTION("Circle partially off screen") {
    REQUIRE(engine.ClickedCircle(10,10,-1,-1, radius));
  }

}

TEST_CASE("Picked Easy Game Mode", "[easy]") {

  //checks that inputted coordinates means that user clicked the easy mode
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

  //checks that inputted coordinates means that user clicked the medium mode
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

  //checks that inputted coordinates means that user clicked the hard mode
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

  //checks that these coordinates mean that the user has not clicked on a game
  //mode's coordinates
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

TEST_CASE("Clicked on Item", "[picked item]") {

  //makes sure it returns true when the click is on the center of the image
  mylibrary::GameEngine engine;
  int mouse_x = 400;
  int mouse_y = 360;
  int item_centerx = 400;
  int item_centery = 360;
  int width = 100;
  int height = 100;
  REQUIRE(engine.ClickedItem(mouse_x, mouse_y, item_centerx, item_centery,
      width, height));
  //make sure it returns true when the click is on the image but just not its
  //center
  SECTION("Not same coordinates") {
    REQUIRE(engine.ClickedItem(401, 361, 400, 360, 100, 100));
  }
  //makes sure method returns true when the click is on the edge of the image
  SECTION("Edge of the item")  {
    REQUIRE(engine.ClickedItem(200, 200, 250, 250, 100, 100));
    REQUIRE(engine.ClickedItem(200, 200, 250, 200, 100, 100));
    REQUIRE(engine.ClickedItem(200, 200, 300, 250, 200, 100));
    REQUIRE(engine.ClickedItem(250, 350, 275, 375, 50, 50));
    REQUIRE(engine.ClickedItem(0, 0, 0, 0, 0, 0));
  }
}

TEST_CASE("Item Is Not Clicked", "[normal click]") {

  //checks that the method return false when the mouse does not click in the
  //image range
  mylibrary::GameEngine engine;
  int mouse_x = 400;
  int mouse_y = 360;
  int item_centerx = 1000;
  int item_centery = 1000;
  int width = 100;
  int height = 100;
  REQUIRE(!engine.ClickedItem(mouse_x, mouse_y, item_centerx,
      item_centery, width, height));
  //checks that the method returns false when the click x and y coordinates
  //are both one off the edges of the image
  SECTION("Off By One") {
    REQUIRE(!engine.ClickedItem(100, 250, 201, 351, 200, 200));
    REQUIRE(!engine.ClickedItem(400, 400, 299, 299, 200, 200));
  }
}










