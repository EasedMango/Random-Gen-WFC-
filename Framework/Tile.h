#pragma once
#include <tuple>
#include <string>

struct tile
{
	bool mountain, land, coast, sea;
	int entropy;
	char type;
	//const std::tuple<char, char, std::string> ruleOne ();


	tile* adjacent[4];
	inline tile() : mountain(1), land(1), coast(1), sea(1), entropy(4) {
		adjacent[0] = 0;
		adjacent[1] = 0;
		adjacent[2] = 0;
		adjacent[3] = 0;
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

	//void AdjactentGen()

	void AdjactentGen();

};