#pragma once
#include <SDL.h>
#include <vector>

using namespace std;

class Maze {
private:
	vector<vector<int>> maze;

public:
	Maze();
	bool isWall(int x, int y);
	bool isExit(int x, int y);
	void draw(SDL_Renderer* render);
};