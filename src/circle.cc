//
// Created by CHANDRACHUR KESANA on 4/21/20.
//

#include "mylibrary/circle.h"

namespace mylibrary {

int Circle::getX() {

  x = std::rand() % 100 * 7;
  return x;
}

int Circle::getY() {

  y = std::rand() % 100 * 7;
  return y;
}

}