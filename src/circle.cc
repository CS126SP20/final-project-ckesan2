//
// Created by CHANDRACHUR KESANA on 4/21/20.
//

#include "mylibrary/circle.h"

namespace mylibrary {

int Circle::getX() {

  //sets the x coordinate to a random position
  x = std::rand() % 100 * 7;
  //changes the position again if it is off screen
  if (!XIsInWindow(x)) {
    x = std::rand() % 100 * 7;
  }
  return x;
}

int Circle::getY() {

  //sets the y coordinate to a random position
  y = std::rand() % 100 * 7;
  //changes the position again if it is off screen
  if (!YIsInWindow(y)) {
    y = std::rand() % 100 * 7;
  }
  return y;
}

bool Circle::XIsInWindow(int x_value) {

  //bounds for x coordinates
  return x_value <= 800 && x_value >= 0;
}

bool Circle::YIsInWindow(int y_value) {

  //bounds for y coordinates
  return y_value >= 0 && y_value <= 680;
}

}