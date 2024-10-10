#include <SDL.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    // Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Создаем окно
    SDL_Window* window = SDL_CreateWindow("Простая игра на SDL2",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Ошибка создания окна: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Создаем рендер
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Ошибка создания рендера: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Загрузка изображения персонажа
    SDL_Surface* tempSurface = SDL_LoadBMP("character.bmp");
    if (!tempSurface) {
        cout << "Ошибка загрузки изображения: " << SDL_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    SDL_Texture* characterTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    SDL_Rect characterRect = { 100, 100, 500, 500 }; // Положение и размер персонажа
    const int speed = 1; // Скорость перемещения

    // Основной цикл игры
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // Обрабатываем события
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        int windowHeight = 800;
        int windowWidht = 600;
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_W] && characterRect.y > 0) {
            characterRect.y -= speed;
        }
        if (keystate[SDL_SCANCODE_S] && characterRect.y + characterRect.h < windowHeight) {
            characterRect.y += speed;
        }
        if (keystate[SDL_SCANCODE_A] && characterRect.x > 0) {
            characterRect.x -= speed;
        }
        if (keystate[SDL_SCANCODE_D] && characterRect.x + characterRect.w < windowWidht) {
            characterRect.x += speed;
        }
            //if (event.type == SDL_KEYDOWN) {
            //    switch (event.key.keysym.sym) {
            //    case SDLK_UP:
            //        characterRect.y -= speed;
            //        break;
            //    case SDLK_DOWN:
            //        characterRect.y += speed;
            //        break;
            //    case SDLK_LEFT:
            //        characterRect.x -= speed;
            //        break;
            //    case SDLK_RIGHT:
            //        characterRect.x += speed;
            //        break;
            //    }
            //}

        // Очищаем экран
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Черный фон
        SDL_RenderClear(renderer);

        // Отрисовка персонажа
        SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect);

        // Обновляем экран
        SDL_RenderPresent(renderer);
    }

    // Очищаем ресурсы
    SDL_Delay(5000);
    SDL_DestroyTexture(characterTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}