#include <SDL.h>
#include <iostream>
using namespace std;

const int CELL_SIZE = 64; // Размер клетки лабиринта
const int SCREEN_WIDTH = 640; // Ширина экрана
const int SCREEN_HEIGHT = 640; // Высота экрана
const int SPEED = 4; // Скорость персонажа

// Определение лабиринта (1 - стена, 0 - проход, 2 - финиш, 3 - проигрыш)
int maze[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 3, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 2, 1}, // Финиш в правом верхнем углу
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
//{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
//{ 1, 0, 1, 0, 1, 0, 1, 1, 0, 1 },
//{ 1, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
//{ 1, 3, 1, 1, 1, 3, 1, 0, 1, 1 },
//{ 1, 0, 3, 0, 1, 0, 3, 0, 0, 1 },
//{ 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
//{ 1, 0, 0, 0, 0, 3, 1, 1, 0, 1 },
//{ 1, 3, 1, 1, 1, 1, 1, 1, 2, 1 }, // игра с ловушкой
//{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }

// Функция для проверки столкновения с стеной
bool checkCollision(SDL_Rect playerRect) {
    // Получаем все четыре угла персонажа
    int left = playerRect.x;
    int right = playerRect.x + playerRect.w - 1;
    int top = playerRect.y;
    int bottom = playerRect.y + playerRect.h - 1;

    // Преобразуем координаты углов в индексы клеток
    int gridX1 = left / CELL_SIZE;
    int gridY1 = top / CELL_SIZE;

    int gridX2 = right / CELL_SIZE;
    int gridY2 = top / CELL_SIZE;

    int gridX3 = left / CELL_SIZE;
    int gridY3 = bottom / CELL_SIZE;

    int gridX4 = right / CELL_SIZE;
    int gridY4 = bottom / CELL_SIZE;

    // Проверка выхода за пределы лабиринта
    if (gridX1 < 0 || gridX1 >= 10 || gridY1 < 0 || gridY1 >= 10 ||
        gridX2 < 0 || gridX2 >= 10 || gridY2 < 0 || gridY2 >= 10 ||
        gridX3 < 0 || gridX3 >= 10 || gridY3 < 0 || gridY3 >= 10 ||
        gridX4 < 0 || gridX4 >= 10 || gridY4 < 0 || gridY4 >= 10) {
        return true; // Выйти за границы
    }

    // Проверка каждого угла на столкновение со стеной
    if (maze[gridY1][gridX1] == 1 ||
        maze[gridY2][gridX2] == 1 ||
        maze[gridY3][gridX3] == 1 ||
        maze[gridY4][gridX4] == 1) {
        return true; // Столкновение со стеной
    }

    return false; // Нет столкновения
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "RU");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Ошибка инициализации SDL: " << SDL_GetError() << endl;
        return -1;
    }
    SDL_Window* window = SDL_CreateWindow("Лабиринт с персонажем",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Ошибка создания окна: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "Ошибка создания рендера: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
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
    SDL_Rect playerRect = { CELL_SIZE, CELL_SIZE, 56, 56 };
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        SDL_Rect oldPosition = playerRect;
        if (keystate[SDL_SCANCODE_W]) {
            playerRect.y -= SPEED;
            if (checkCollision(playerRect)) {
                playerRect.y += SPEED;
            }
        }
        if (keystate[SDL_SCANCODE_S]) {
            playerRect.y += SPEED;
            if (checkCollision(playerRect)) {
                playerRect.y -= SPEED;
            }
        }
        if (keystate[SDL_SCANCODE_A]) {
            playerRect.x -= SPEED;
            if (checkCollision(playerRect)) {
                playerRect.x += SPEED;
            }
        }
        if (keystate[SDL_SCANCODE_D]) {
            playerRect.x += SPEED;
            if (checkCollision(playerRect)) {
                playerRect.x -= SPEED;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 123, 032, 145);
        SDL_RenderClear(renderer);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                SDL_Rect cellRect = { j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE };
                if (maze[i][j] == 1) {
                    SDL_SetRenderDrawColor(renderer, 255, 120, 034, 213);
                    SDL_RenderFillRect(renderer, &cellRect);
                }
                else if (maze[i][j] == 2) {
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Зеленый цвет для финиша
                    SDL_RenderFillRect(renderer, &cellRect);
                }
                else if (maze[i][j] == 3) {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Красный цвет для проигрыша
                    SDL_RenderFillRect(renderer, &cellRect);
                }
            }
        }
        SDL_RenderCopy(renderer, characterTexture, NULL, &playerRect);

        // Проверка достижения финиша
        int gridX = playerRect.x / CELL_SIZE;
        int gridY = playerRect.y / CELL_SIZE;
        if (maze[gridY][gridX] == 2) {
            cout << "Вы победили!" << endl;
            isRunning = false; // Завершаем игру
        }
        // Проверка достижения проигрыша
        if (maze[gridY][gridX] == 3) {
            cout << "Вы проиграли!" << endl;
            isRunning = false; // Завершаем игру
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(characterTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}