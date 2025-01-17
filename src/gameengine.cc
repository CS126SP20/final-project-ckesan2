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
  if (abs(mouse_x - center_x) <= kSmallXSize/2
  && abs(mouse_y - (center_y + kYsize)) <= kYsize/2) {
    return "easy";
  } else if (abs(mouse_x - center_x) <= kMediumXsize/2
  && abs(mouse_y - (center_y + (2*kYsize))) <= kYsize/2) {
    return "medium";
  } else if (abs(mouse_x - center_x) <= kSmallXSize/2
  && abs(mouse_y - (center_y + (3*kYsize))) <= kYsize/2) {
    return "hard";
  }
  //if a game mode has not been clicked yet, string will be empty
  return "";
}

bool GameEngine::ClickedItem(int mouse_x, int mouse_y, int item_centerx,
    int item_centery, int item_width, int item_height) {

  //if the item was clicked, returns true
  return abs(mouse_x - item_centerx) <= (item_width / 2) &&
         abs(mouse_y - item_centery) <= (item_height / 2);
}
}