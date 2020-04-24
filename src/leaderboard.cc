// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/leaderboard.h>
#include <sqlite_modern_cpp.h>

namespace mylibrary {

using std::string;
using std::vector;

LeaderBoard::LeaderBoard(const std::string& db_path) : db_{db_path} {

  db_ << "CREATE TABLE if not exists easyleaderboard (\n"
         "  name  TEXT NOT NULL,\n"
         "  score INTEGER NOT NULL\n"
         ");";

  db_ << "CREATE TABLE if not exists medleaderboard (\n"
         "  name  TEXT NOT NULL,\n"
         "  score INTEGER NOT NULL\n"
         ");";

  db_ << "CREATE TABLE if not exists hardleaderboard (\n"
         "  name  TEXT NOT NULL,\n"
         "  score INTEGER NOT NULL\n"
         ");";
}

void LeaderBoard::AddScoreToEasyBoard(const User& user) {
  db_ << "INSERT INTO easyleaderboard (name, score) VALUES (?,?);"
      << user.name
      << user.score;
}

void LeaderBoard::AddScoreToMediumBoard(const User& user) {
  db_ << "INSERT INTO medleaderboard (name, score) VALUES (?,?);"
      << user.name
      << user.score;
}

void LeaderBoard::AddScoreToHardBoard(const User& user) {
  db_ << "INSERT INTO hardleaderboard (name, score) VALUES (?,?);"
      << user.name
      << user.score;
}

//citation: got this method from snake assignment
vector<User> GetUsers(sqlite::database_binder* rows) {
  vector<User> Users;

  for (auto&& row : *rows) {
    string name;
    int score;
    row >> name >> score;
    User User = {name, score};
    Users.push_back(User);
  }
  return Users;
}

std::vector<User> LeaderBoard::GetTopEasyScores(const int limit) {

  auto rows = db_ << "SELECT name,score FROM easyleaderboard ORDER BY "
                     "score DESC LIMIT ?;"
                  << limit;

  return GetUsers(&rows);
}

std::vector<User> LeaderBoard::GetTopMedScores(const int limit) {

  auto rows = db_ << "SELECT name,score FROM medleaderboard ORDER BY "
                     "score DESC LIMIT ?;"
                  << limit;

  return GetUsers(&rows);
}

std::vector<User> LeaderBoard::GetTopHardScores(const int limit) {

  auto rows = db_ << "SELECT name,score FROM hardleaderboard ORDER BY "
                     "score DESC LIMIT ?;"
                  << limit;

  return GetUsers(&rows);
}

}  // namespace mylibrary
