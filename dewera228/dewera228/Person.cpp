#include "Person.h"
#include <iostream>

Player::Player(int x, int y, Maze* maze, SDL_Renderer* renderer)
    : maze(maze), renderer(renderer) {
    rect = { x, y, CELL_SIZE, CELL_SIZE };

    // Загрузка текстуры
    SDL_Surface* tempSurface = SDL_LoadBMP("character.bmp");
    if (!tempSurface) {
        std::cerr << "Ошибка загрузки изображения: " << SDL_GetError() << std::endl;
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
    }
}

void Player::handleInput(const Uint8* state) {
    SDL_Rect newRect = rect;
    if (state[SDL_SCANCODE_UP]) newRect.y -= SPEED;
    if (state[SDL_SCANCODE_DOWN]) newRect.y += SPEED;
    if (state[SDL_SCANCODE_LEFT]) newRect.x -= SPEED;
    if (state[SDL_SCANCODE_RIGHT]) newRect.x += SPEED;

    if (!maze->checkCollision(newRect)) {
        rect = newRect;
    }
}

void Player::draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

bool Player::hasReachedExit() {
    return maze->reachedExit(rect);
}