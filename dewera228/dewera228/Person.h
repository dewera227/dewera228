#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "Maze.h"

const int SPEED = 4;

class Player {
public:
    Player(int x, int y, Maze* maze, SDL_Renderer* renderer);
    void handleInput(const Uint8* state);
    void draw(SDL_Renderer* renderer);
    bool hasReachedExit();

private:
    SDL_Rect rect;
    SDL_Texture* texture;
    Maze* maze;
    SDL_Renderer* renderer;
};

#endif // PLAYER_H