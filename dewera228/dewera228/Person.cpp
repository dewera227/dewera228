#include "Person.h"
#include "maze.h"
#include "game.h"

Person::person(int startX, int startY, Maze* m) {
    Player::rect = { startX, startY, 64, 64 };
    Maze::maze = m;
}

void Player::Person(int startX, int startY, Maze* m)
{
}

void Player::move(int dx, int dy) {
    SDL_Rect newRect = rect;
    newRect.x += dx * 4;
    newRect.y += dy * 4;

    int gridX = newRect.x / 64;
    int gridY = newRect.y / 64;

    if (!maze->isWall(gridX, gridY)) {
        rect = newRect;
    }
}

bool Player::hasReachedExit() {
    int gridX = rect.x / 64;
    int gridY = rect.y / 64;
    return maze->isExit(gridX, gridY);
}

void Player::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}