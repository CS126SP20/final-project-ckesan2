//
// Created by CHANDRACHUR KESANA on 4/22/20.
//

#ifndef FINALPROJECT_GAMEENGINE_H
#define FINALPROJECT_GAMEENGINE_H

#include <string>
namespace mylibrary {

const int kYsize = 50;
const int kMediumXsize = 110;
const int kSmallXSize = 96;

class GameEngine {

 public:
  //resets the score of the game
  void ResetGame();
  //returns the score of the game
  int GetScore();
  //increases the game score by 1
  void IncreaseScore();
  //takes in the mouse click coordinates and the circle center
  // coordinates and checks if the click was on the circle. Returns true/false
  bool ClickedCircle(int mouse_x, int mouse_y, int circle_x, int circle_y,
      int radius);
  //takes in the mouse click coordinates and the screen center coordinates and
  // checks which game mode the user picked. Returns the name of the game mode
  std::string GetGameMode(int mouse_x, int mouse_y, int center_x, int center_y);
  //takes in mouse click coordinates and returns whether the user clicker on
  //an item or not
  bool ClickedItem(int mouse_x, int mouse_y, int item_centerx, int item_centery,
      int item_width, int item_height);

 private:
  int score = 0;
};
}

#endif  // FINALPROJECT_GAMEENGINE_H