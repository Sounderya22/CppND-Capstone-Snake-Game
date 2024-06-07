#include <iostream>
#include "controller.h"
#include <fstream>
#include <algorithm>
#include <utility>
#include <string>
#include <sstream>
#include "game.h"
#include "renderer.h"
#include "scoreManager.h"

int main() {

  std::string name;
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Enter your name: ";
  std::cin >> name;
  scoreManager sm(std::move(name), game.GetScore(), FILE_PATH);               // class object to save the score along with the player name in a text file
  sm.saveScore();
  return 0;
}