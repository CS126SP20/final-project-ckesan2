//
// Created by CHANDRACHUR KESANA on 4/21/20.
//

#include "mylibrary/circle.h"

namespace mylibrary {

int Circle::getX() {

  x = std::rand() % 100 * 7;
  if (!XIsInWindow(x)) {
    x = std::rand() % 100 * 7;
  }
  return x;
}

int Circle::getY() {

  y = std::rand() % 100 * 7;
  if (!YIsInWindow(y)) {
    y = std::rand() % 100 * 7;
  }
  return y;
}

bool Circle::XIsInWindow(int x_value) {

  return x_value <= 800 && x_value >= 0;
}

bool Circle::YIsInWindow(int y_value) {

  return y_value >= 0 && y_value <= 680;
}

}