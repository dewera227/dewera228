#include "Game.h"
#include <iostream>

Game::Game() : window(nullptr), renderer(nullptr) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        std::cerr << "Ошибка создания рендерера: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    player = new Player(64, 64, &maze, renderer);
}

Game::~Game() {
    delete player;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run() {
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        const Uint8* state = SDL_GetKeyboardState(NULL);
        player->handleInput(state);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        maze.draw(renderer);
        player->draw(renderer);

        SDL_RenderPresent(renderer);

        if (player->hasReachedExit()) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Congratulations!", "You've reached the exit!", window);
            running = false;
        }
    }
}