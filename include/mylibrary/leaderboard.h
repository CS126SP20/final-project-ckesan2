// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_LEADERBOARD_H_
#define FINALPROJECT_MYLIBRARY_LEADERBOARD_H_

#include <sqlite_modern_cpp.h>
#include "user.h"
namespace mylibrary {


class LeaderBoard {

 public:
  // Creates a new leaderboard table if it doesn't already exist.
  explicit LeaderBoard(const std::string& db_path);
  //adds name and score of the player to easyleaderboard table
  void AddScoreToEasyBoard(const User&);
  //adds name and score of the player to medleaderboard table
  void AddScoreToMediumBoard(const User&);
  //adds name and score of the player to hardleaderboard table
  void AddScoreToHardBoard(const User&);
  //gets the vector of players with the highest scores in the easy leaderboard
  std::vector<User> GetTopEasyScores(const int limit);
  //gets the vector of players with the highest scores in the medium leaderboard
  std::vector<User> GetTopMedScores(const int limit);
  //gets the vector of players with the highest scores in the hard leaderboard
  std::vector<User> GetTopHardScores(const int limit);

 private:
  sqlite::database db_;
};
}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_LEADERBOARD_H_
