#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

class scoreManager {
    public:
        scoreManager(std::string&& pname, int cscore, std::string filePath);  
        // Handles the score          
        void saveScore();   
        // Writes the player name and score to a text file                
        void saveToFile();                                     
    private:
        std::string _name;                                      // name of the player
        int _score;                                             // score of the player
        int _maxScores = 5;                                     // counter to decide how many scores will be saved(top 5)
        std::string scorefile;
        std::vector<std::unique_ptr<std::pair<std::string, int>>> scoreHistory;  // Vector of pairs to hold the player name along with their score
};

#endif