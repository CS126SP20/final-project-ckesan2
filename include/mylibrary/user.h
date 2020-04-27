//
// Created by CHANDRACHUR KESANA on 4/20/20.
//

#ifndef FINALPROJECT_USER_H
#define FINALPROJECT_USER_H

#include <string>

namespace mylibrary {

struct User {

  //each user has a name and a score value
  User(const std::string& name, int score) : name(name), score(score) {}
  std::string name;
  int score;
};

}

#endif  // FINALPROJECT_USER_H
