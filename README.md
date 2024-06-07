# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

![](Snake.gif)

<!-- The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features. -->

## Structure of the code

One additional class has been added to the project to manage the highscores of players and save the 5 highest scores in a text file ("highscores.txt"). 

## Features added

1. Added highscores saving where the top 5 scores are saved in a text file in the repository
2. Added a wall in the game which when touched by the snake, kills the game
3. Added a functionality to pause the game using the Space Bar

## How my code satisfies the project rubric

1. Loops, Functions, I/O
    * The project reads data from a file and process the data, or the program writes data to a file - Scores are saved to a text file in the repository("highscores.txt").
    * The project accepts user input and processes the input - Added a case SDLK_SPACE which switches a pause variable of the Snake class (isSnakePaused). A check has been added in the Update() of Snake class to reflect the same.
2. Object Oriented Programming
    * One or more classes are added to the project with appropriate access specifiers for class members - scoreManager class was added to the project with suitable attributes and methods set as private and public members of the class respectively.
    * Class constructors utilize member initialization lists - Constructor of the class takes in parameters(username and score) and sets the attributes of the class to the same using initialization lists
    * Classes abstract implementation details from their interfaces - The class has two methods which implements their functionalities in the definitions and is abstracted from their interfaces. The code is also well commented
3. Memory Management
    * The project uses move semantics to move data instead of copying it, where possible - The user name is sent to scoreManager object as a rvalue reference by utilizing move semantics
    * The project uses smart pointers instead of raw pointers - The scoreManager has a vector of unique_ptr to std::pair<std::string, int> which is used to read and write the name of the user and their score.
    * The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate - The scoreManager class uses shared_ptrs to implement RAII. Additionally, as two filestream objects are required for reading and writing to the file in different functions, we leverage scope to create and destroy the two objects efficiently.
4. Concurrency
    * The project uses multithreading - A std::thread object was used to run the Game::WallCheck() in parallel to the Game::Run(). The WallCheck() basically keeps checking if the snake has collided with any of the walls(while the game is running) and kills the snake if it collides with the wall. The thread is joined in the Destructor(created) of the Game class.
    * A mutex or lock is used in the project - WallCheck() uses a unique_lock and mutex to lock shared resources (snake in this case) before it can set snake.alive = false.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
