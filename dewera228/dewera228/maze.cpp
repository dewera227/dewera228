#include "Maze.h"

Maze::Maze() {
    maze = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 2}, // 2 - выход
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
}

bool Maze::isWall(int x, int y) {
    return maze[y][x] == 1;
}

bool Maze::isExit(int x, int y) {
    return maze[y][x];
}

void Maze::draw(SDL_Renderer* renderer) {
    SDL_Rect cellRect;
    cellRect.w = 64;
    cellRect.h = 64;

    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            cellRect.x = col * 64;
            cellRect.y = row * 64;

            if (maze[row][col] == 1) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Синие стены
            }
            else if (maze[row][col] == 2) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Зеленый выход
            }
            else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Белый проход
            }
            SDL_RenderFillRect(renderer, &cellRect);
        }
    }
}