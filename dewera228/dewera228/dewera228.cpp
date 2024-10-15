#include <SDL.h>
#include <iostream>
using namespace std;

// Функция для проверки столкновений
bool checkCollision(SDL_Rect rect1, SDL_Rect rect2) {
    if (rect1.x + rect1.w > rect2.x &&
        rect1.x < rect2.x + rect2.w &&
        rect1.y + rect1.h > rect2.y &&
        rect1.y < rect2.y + rect2.h) {
        return true;
    }
    return false;
}

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

    SDL_Rect characterRect = { 100, 100, 20, 20 }; // Положение и размер персонажа
    const int speed = 1; // Скорость перемещения

    // Загрузка изображения карты
    SDL_Surface* mapSurface = SDL_LoadBMP("map.bmp");
    if (!mapSurface) {
        cout << "Ошибка загрузки изображения карты: " << SDL_GetError() << endl;
        SDL_DestroyTexture(characterTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    SDL_Texture* mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurface);
    SDL_FreeSurface(mapSurface);

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

        // Получаем состояние клавиатуры
        const Uint8* keystate = SDL_GetKeyboardState(NULL);

        // Сохраняем старое положение персонажа
        SDL_Rect oldCharacterRect = characterRect;

        // Обрабатываем нажатия клавиш для перемещения персонажа
        if (keystate[SDL_SCANCODE_W] && characterRect.y > 0) {
            characterRect.y -= speed;
            if (checkCollision(characterRect, { 0, 0, 800, 600 })) {
                characterRect.y = oldCharacterRect.y;  
                }
        }
        if (keystate[SDL_SCANCODE_S] && characterRect.y + characterRect.h < 600) {
            characterRect.y += speed;
            if (checkCollision(characterRect, { 0, 0, 800, 600 })) {
                characterRect.y = oldCharacterRect.y;
            }
        }
        if (keystate[SDL_SCANCODE_A] && characterRect.x > 0) {
            characterRect.x -= speed;
            if (checkCollision(characterRect, { 0, 0, 800, 600 })) {
                characterRect.x = oldCharacterRect.x; 
            }
        }
        if (keystate[SDL_SCANCODE_D] && characterRect.x + characterRect.w < 800) {
            characterRect.x += speed;
            if (checkCollision(characterRect, { 0, 0, 800, 600 })) {
                characterRect.x = oldCharacterRect.x; 
            }
        }
 

        // Проверяем столкновение с картой
        if (checkCollision(characterRect, { 0, 0, 800, 600 })) {
            // Если персонаж столкнулся с краем карты, возвращаем его в прежнее положение
            characterRect = oldCharacterRect;
        }

        // Очищаем экран
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Черный фон
        SDL_RenderClear(renderer);

        // Отрисовка карты
        SDL_RenderCopy(renderer, mapTexture, NULL, NULL);

        // Отрисовка персонажа
        SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect);

        // Обновляем экран
        SDL_RenderPresent(renderer);
    }

    // Очищаем ресурсы
    SDL_DestroyTexture(characterTexture);
    SDL_DestroyTexture(mapTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}