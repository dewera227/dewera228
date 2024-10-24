#pragma once
#include <SDL.H>
#include <vector>
using namespace std;
class maze {
private:
	vector<vector<int>> Maze;
public:
	maze();
	bool isWall(int x, int y);
	bool isExit(int x, int y);
	void draw(SDL_Renderer* renderer);
};

