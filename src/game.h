#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include <unistd.h>
#include <condition_variable>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  std::thread wallCheckThread;

 private:
  Snake snake;
 bool running = true;

  SDL_Point food, spl_food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  

  void PlaceFood();
  void Update();
  void WallCheck();
};

#endif