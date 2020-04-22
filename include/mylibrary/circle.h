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
  int getX();
  int getY();
  bool XIsInWindow(int x_value);
  bool YIsInWindow(int y_value);

};

}
#endif  // FINALPROJECT_CIRCLE_H
