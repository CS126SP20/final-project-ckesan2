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

}