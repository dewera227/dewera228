#include "maze.h"
#include "dewera228.cpp"

maze::maze() {
    maze = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
      {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
      {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
      {1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
      {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
      {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
      {1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
      {1, 0, 1, 1, 1, 1, 1, 1, 2, 1}, // Финиш в правом верхнем углу
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
}

bool maze::isWall(int x, int y) {
    return maze[y][x] == 1;
}

bool maze::isExit(int x, int y) {
    return maze[y][x] == 2;
}

void maze::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 123, 032, 145); // Background color
    SDL_RenderClear(renderer); // Clear the renderer

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            SDL_Rect cellRect = { j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE };

            if (maze[i][j] == 1) { // Draw walls
                SDL_SetRenderDrawColor(renderer, 255, 120, 034, 213); // Wall color
                SDL_RenderFillRect(renderer, &cellRect);
            }
            else if (maze[i][j] == 2) { // Draw exit
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Exit color
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
    }
}