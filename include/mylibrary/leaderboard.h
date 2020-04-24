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

  // Adds a player to the leaderboard.
  void AddScoreToLeaderBoard(const User&);

  void AddScoreToEasyBoard(const User&);

  void AddScoreToMediumBoard(const User&);

  void AddScoreToHardBoard(const User&);

  std::vector<User> GetTopEasyScores(const int limit);

  std::vector<User> GetTopMedScores(const int limit);

  std::vector<User> GetTopHardScores(const int limit);

 private:
  sqlite::database db_;
};
}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_LEADERBOARD_H_
