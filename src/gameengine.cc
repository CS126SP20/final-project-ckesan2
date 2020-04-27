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
                               int circle_y, int radius) {

  //checks that the difference between mouse coordinates and the center
  //coordinates are less than or equal to the radius of the circle
  return abs(mouse_x - circle_x) <= radius && abs(mouse_y - circle_y) <= radius;
}

std::string GameEngine::GetGameMode(int mouse_x, int mouse_y, int center_x,
                                 int center_y) {

  //if the mouse click is in range of one of the game mode buttons, method
  // returns that game mode
  //48 is half of 96, which is the x size for the easy and hard text boxes
  //25 is half of 50, which is y size for all 3 text boxes
  if (abs(mouse_x - center_x) <= 48
  && abs(mouse_y - (center_y + 50)) <= 25) {
    return "easy";
    //55 is half of 110, which is the x size of the medium mode text box
  } else if (abs(mouse_x - center_x) <= 55
  && abs(mouse_y - (center_y + 100)) <= 25) {
    return "medium";
  } else if (abs(mouse_x - center_x) <= 48
  && abs(mouse_y - (center_y + 150)) <= 25) {
    return "hard";
  }
  //if a game mode has not been clicked yet, string will be empty
  return "";
}

}