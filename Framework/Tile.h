#pragma once
#include <tuple>
#include <string>
#include <iostream>

struct tile
{

	char type;
	int x, y;
	//const std::tuple<char, char, std::string> ruleOne ();


	tile* adjacent[4];
	inline tile()  {
		adjacent[0] = 0;
		adjacent[1] = 0;
		adjacent[2] = 0;
		adjacent[3] = 0;
		x = 0;
		y = 0;
	};
	//inline tile(int& type_, int& l, int& r, int& t, int& b) {
	//	type = type_;
	//	adjacent[0] = l;
	//	adjacent[1] = r;
	//	adjacent[2] = t;
	//	adjacent[3] = b;
	//}
	inline void SetAdjacent(tile* l, tile* r, tile* t, tile* b) {
		adjacent[0] = l;
		adjacent[1] = r;
		adjacent[2] = t;
		adjacent[3] = b;
	}

	inline void Print() {
		std::cout << "y: " << y << " x: " << x << " type: "<< type << " entropy: " << entropy << "\n";
	}
	//void AdjactentGen()

	void AdjactentGen();

};