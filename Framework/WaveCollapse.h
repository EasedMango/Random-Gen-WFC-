#pragma once
#include <iostream>
#include <vector>
#include "Tile.h"

#include <map>

const enum lrt {
	LEFT = 1, RIGHT, TOP, BOTTOM
};
//#define HEIGHT 16
//#define WIDTH 16
#define WATCH(w)(std::cout << #w << " is " << w << std::endl)
#define TILEPT(y,x,t)(std::cout<<"y: " << y << " x: " << x << " t: " << t << "\n" )
class WaveCollapse
{
private:
	const int HEIGHT;
	const int WIDTH;
	struct tile
	{
		//types allowed
		//char type;
		int weight;
		int entropy;
		int x, y;

		std::vector<tile*> adjacent;
		std::vector<char> types;

		inline tile(char type_, int weight_) : weight(weight_) {
			types.push_back(type_);
		}

		inline tile() : y(0), x(0), weight(0) {

		};
		inline tile(int y_, int x_, const char c) : y(y_), x(x_), weight(0) {
			types.push_back(c);
		}
		inline tile(const char c) : y(0), x(0), weight(0) {
			types.push_back(c);
		}

		//inline tile(int& type_, int& l, int& r, int& t, int& b) {
		//	type = type_;
		//	adjacent[0] = l;
		//	adjacent[1] = r;
		//	adjacent[2] = t;
		//	adjacent[3] = b;
		//}

		//inline bool operator==(const tile& t) {
		//	if()
		//};

		inline void SetAdjacent(tile* l, tile* r, tile* t, tile* b) {
			if (adjacent.size() == 0) {
				adjacent.push_back(l);
				adjacent.push_back(r);
				adjacent.push_back(t);
				adjacent.push_back(b);
			}
			else
			{
				adjacent.at(0) = l;
				adjacent.at(1) = r;
				adjacent.at(2) = t;
				adjacent.at(3) = b;
			}
		}

		inline void Print() {
			//std::cout << "y: " << y << " x: " << x << " type: "<< types[0] << " entropy: " << entropy << "\n";
		}


	};
	void FindCommon(std::vector<char>& vec1, std::vector<char>& vec2, std::vector<char>& vec3);


public:

	bool weightCheck = false;
	bool weightSub = false;

	int tileCount;
	int weightSum;

	std::vector<tile*> tiles;



	std::vector< std::vector<tile> > output;

	std::vector<tile> weightChecks;

	int starty, startx, startt;
	struct rule {

		tile origin;
		tile adjacent;
		lrt direction;
		int weight;
		inline rule(tile t, tile a, lrt d) : origin(t), adjacent(a), direction(d), weight(0) {
			origin.weight = weight;
			adjacent.weight = weight;
		};


	};
	std::vector<rule> ruleListL;
	std::vector<rule> ruleListR;
	std::vector<rule> ruleListT;
	std::vector<rule> ruleListB;
	inline bool InBounds(int y, int x) {
		//ruleList.push_back(std::tuple<int, int, lrt>(1, 1, LEFT));
		return ((y >= 0) && (y < HEIGHT) && (x >= 0) && (x < WIDTH)) ? true : false;
	}

	WaveCollapse(const std::vector< std::vector<char> >& input);
	WaveCollapse();

	void OnCreate();

	void Generate();

	void Print();

	void GetAdjactent(int y, int x);

	void GetRules(const std::vector< std::vector<char> > & input);

	void CheckRules(tile& temp);
};

