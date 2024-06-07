#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

Game::~Game() {
  wallCheckThread.join();
}

void Game::WallCheck() {
  while(snake.alive && running)  {
  // std::cout << "WallCheck" << std::endl;
  // std::cout << "Snake head y "<< snake.head_y << " x " << snake.head_x<< "\n";
  if( ((snake.head_y <= 1) || (snake.head_y >= 31)) && (snake.head_x >=7 && snake.head_x < 25)) {
    std::mutex mut;
    std::unique_lock lck(mut);
    snake.alive = false;
    std::cout << "Killed!\n";
    return;
  }
  if( ((snake.head_x <= 1) || (snake.head_x >= 31)) && (snake.head_y >=7 && snake.head_y < 25)) { 
    std::mutex mut;
    std::unique_lock lck(mut);
    snake.alive = false;
    std::cout << "Killed!\n";
    return;
  }
  usleep(5000);
  }
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  
  wallCheckThread = std::thread(&Game::WallCheck, this);

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();

    renderer.Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is not occupied by a snake item before placing
    // food.
    if( ((y <= 1) || (y >= 31)) && (x >=7 && x < 25)) { 
      continue;
    }
    if( ((x <= 1) || (x >= 31)) && (y >=7 && y < 25)) { 
      continue;
    }
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }

  }
}

// void Game::PlaceSpecialFood(Renderer &renderer) {
//   int x_, y_;
//   while (true) {
//     x_ = random_w(engine);
//     y_ = random_h(engine);

//     // Check that the location is not occupied by a snake item before placing
//     // food.
//     if (!snake.SnakeCell(x_, y_)) {
//       if(x_ != food.x && y_ != food.y) {
//         spl_food.x = x_;
//         spl_food.y = y_;
//         renderer.food_rendered = false;
//         return;
//       }
//     }

//   }
// }

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
      score++;
    
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }