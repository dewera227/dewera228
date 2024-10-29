#pragma once
#include <SDL.h>
#include "Maze.h"  

class Player {
public:
    void Person(int startX, int startY, Maze* m);
    void move(int dx, int dy);
    bool hasReachedExit();
    void draw(SDL_Renderer* renderer);

    SDL_Rect rect;

private:
    Maze* maze;
};