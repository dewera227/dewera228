#include "Game.h"

Game::Game() : player(64, 64, &maze) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Game::~Game() {
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
        if (state[SDL_SCANCODE_UP]) player.move(0, -1);
        if (state[SDL_SCANCODE_DOWN]) player.move(0, 1);
        if (state[SDL_SCANCODE_LEFT]) player.move(-1, 0);
        if (state[SDL_SCANCODE_RIGHT]) player.move(1, 0);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        maze.draw(renderer);
        player.draw(renderer);

        SDL_RenderPresent(renderer);

        if (player.hasReachedExit()) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Congratulations!", "You've reached the exit!", window);
            running = false;
        }
    }
}