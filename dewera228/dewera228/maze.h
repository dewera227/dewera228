#ifndef MAZE_H
#define MAZE_H

#include <SDL.h>

const int CELL_SIZE = 64;

class Maze {
public:
    Maze();
    void draw(SDL_Renderer* renderer);
    bool checkCollision(SDL_Rect playerRect);
    bool reachedExit(SDL_Rect playerRect);

private:
    int maze[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 2},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
};

#endif // MAZE_H