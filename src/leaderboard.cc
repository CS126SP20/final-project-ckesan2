// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/leaderboard.h>
#include <sqlite_modern_cpp.h>

namespace mylibrary {

LeaderBoard::LeaderBoard(const std::string& db_path) : db_{db_path} {
  db_ << "CREATE TABLE if not exists leaderboard (\n"
         "  name  TEXT NOT NULL,\n"
         "  score INTEGER NOT NULL\n"
         ");";
}
void LeaderBoard::AddScoreToLeaderBoard(const User& user) {
  db_ << "INSERT INTO leaderboard (name, score) VALUES (?,?);"
      << user.name
      << user.score;
}

}  // namespace mylibrary
