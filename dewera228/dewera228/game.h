#pragma once
#include <SDL.h>
#include "maze.h"
#include "Person.h"

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Maze maze;
    Player player;
public:
    Game();
    ~Game();
    void run();
};