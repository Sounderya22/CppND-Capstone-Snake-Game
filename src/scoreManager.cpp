#include "scoreManager.h"
#include <iostream>

scoreManager::scoreManager(std::string&& pname, int cscore, std::string filePath) : _name(std::move(pname)), _score(cscore), scorefile(filePath){}

void scoreManager::saveScore() {

  std::ifstream scores(scorefile);
  if(!scores.is_open())
  {
    std::cout << "File couldn't be opened\n";
  }
  std::string line, name;
  int score;

  // Gets the score from the file and loads it in the vector
  while (std::getline(scores, line)) {
    std::stringstream ss(line);

    ss >> name >> score;
    scoreHistory.emplace_back(std::make_unique<std::pair<std::string, int>>(name, score));
  }
  scores.close();
  // Checks for player name and score redundancy
  for(const auto &pairVec : scoreHistory)
  {
    if(pairVec->first == _name && pairVec->second == _score)
    {
      std::cout << "Not unique\n";
      return;
    }
  }
  scoreHistory.emplace_back(std::make_unique<std::pair<std::string, int>>(_name, _score));

  // Sort the vector in descending order of scores
  std::sort(scoreHistory.begin(), scoreHistory.end(), [](const std::unique_ptr<std::pair<std::string, int>> &a, const std::unique_ptr<std::pair<std::string, int>> &b) {
        return a->second > b->second; 
    });

  saveToFile();
}

void scoreManager::saveToFile() {
  std::ofstream scores_(scorefile);
  if(!scores_.is_open())
  {
    std::cout << "Error opening!\n";
    return;
  }
  // Writes to "highscores.txt" file
  for (auto &pairVec : scoreHistory) {
    if(_maxScores > 0)
    {
      scores_ << pairVec->first << " " << pairVec->second << "\n";
      _maxScores--;
    }
    else
      break;
  }
  scores_.close();
}