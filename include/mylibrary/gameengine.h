//
// Created by CHANDRACHUR KESANA on 4/22/20.
//

#ifndef FINALPROJECT_GAMEENGINE_H
#define FINALPROJECT_GAMEENGINE_H

namespace mylibrary {

class GameEngine {

 public:
  void ResetGame();
  int GetScore();
  void IncreaseScore();
  bool ClickedCircle(int mouse_x, int mouse_y, int circle_x, int circle_y);

 private:
  int score = 0;

};
}

#endif  // FINALPROJECT_GAMEENGINE_H