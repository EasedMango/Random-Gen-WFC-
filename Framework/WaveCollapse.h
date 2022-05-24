#pragma once
#include <iostream>
#include <vector>
#include "Tile.h"

#include <map>

const enum lrt {
	LEFT = 1, RIGHT, TOP, BOTTOM
};
#define HEIGHT 16
#define WIDTH 16
#define WATCH(w)(std::cout << #w << " is " << w << std::endl)
#define TILEPT(y,x,t)(std::cout<<"y: " << y << " x: " << x << " t: " << t << "\n" )
class WaveCollapse
{
private:


	void FindCommon(std::vector<char>& vec1, std::vector<char>& vec2, std::vector<char>& vec3);


public:
	bool weightCheck = false;
	bool weightSub = false;
	//std::map<char, int> tileTypes;
	//std::map<char, int> tileEntropy;
	int tileCount;
	int weightSum;
	struct weight {
		weight(char t, int w) {
			type = t;
			weigh = w;
		}
		char type;
		int weigh;
	};
	//inline bool compare(const std::vector<weight>& w1,const  weight& w2) {
	//	return w1.weigh < w2.weigh;
	//}
	std::vector<weight> weights;
	std::vector<weight> weightsHold;
	tile* tiles[HEIGHT][WIDTH];
	int starty, startx, startt;
	std::vector<std::tuple<char, char, lrt>> ruleListL;
	std::vector<std::tuple<char, char, lrt>> ruleListR;
	std::vector<std::tuple<char, char, lrt>> ruleListT;
	std::vector<std::tuple<char, char, lrt>> ruleListB;
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

