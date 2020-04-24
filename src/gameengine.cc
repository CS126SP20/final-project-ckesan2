//
// Created by CHANDRACHUR KESANA on 4/22/20.
//

#include "mylibrary/gameengine.h"
#include <cstdlib>

namespace mylibrary {

void GameEngine::ResetGame() {

  score = 0;
}

void GameEngine::IncreaseScore() {

  score++;
}

int GameEngine::GetScore() {

  return score;
}

bool GameEngine::ClickedCircle(int mouse_x, int mouse_y, int circle_x,
                               int circle_y) {

  return abs(mouse_x - circle_x) <= 20 && abs(mouse_y - circle_y) <= 20;
}

std::string GameEngine::GetGameMode(int mouse_x, int mouse_y, int center_x,
                                 int center_y) {

  if (abs(mouse_x - center_x) <= 48
  && abs(mouse_y - (center_y + 50)) <= 25) {
    return "easy";
  } else if (abs(mouse_x - center_x) <= 55
  && abs(mouse_y - (center_y + 100)) <= 25) {
    return "medium";
  } else if (abs(mouse_x - center_x) <= 48
  && abs(mouse_y - (center_y + 150)) <= 25) {
    return "hard";
  }
  return "";
}

}