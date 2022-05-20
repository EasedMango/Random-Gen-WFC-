#pragma once
#include <iostream>
#include <vector>
#include "Tile.h"


const enum lrt {
	LEFT = 1, RIGHT, TOP, BOTTOM
};
#define HEIGHT 12
#define WIDTH 12
class WaveCollapse
{
private:





public:
	tile* tiles[HEIGHT][WIDTH];
	int starty, startx, startt;
	std::vector<std::tuple<char, char, lrt>> ruleList;
	inline bool InBounds(int y, int x) {
		//ruleList.push_back(std::tuple<int, int, lrt>(1, 1, LEFT));
		return ((y >= 0) && (y < HEIGHT) && (x >= 0) && (x < WIDTH)) ? true : false;
	}

	void OnCreate();

	void Generate();

	void Print();

	void GetAdjactent(int y, int x);

	void GetRules();

	void CheckRules(int& x, int& y);
};

