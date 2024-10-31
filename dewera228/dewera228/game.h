#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Maze.h"
#include "Person.h"

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Maze maze;
    Player* player;
};

#endif // GAME_H