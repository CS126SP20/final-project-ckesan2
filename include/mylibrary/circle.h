//
// Created by CHANDRACHUR KESANA on 4/21/20.
//

#ifndef FINALPROJECT_CIRCLE_H
#define FINALPROJECT_CIRCLE_H

#include <string>

namespace mylibrary {

class Circle {

 private:
  int x = 1;
  int y = 1;

 public:
  Circle() {

    x = std::rand() % 100 * 8;
    y = std::rand() % 100 * 8;
  }
  //changes the position of the x coordinate and returns its position
  int getX();
  //changes the position of the y coordinate and returns its position
  int getY();
  //checks that the x coordinate is in the screen
  bool XIsInWindow(int x_value);
  //checks that the y coordinate is in the screen
  bool YIsInWindow(int y_value);

};

}
#endif  // FINALPROJECT_CIRCLE_H
