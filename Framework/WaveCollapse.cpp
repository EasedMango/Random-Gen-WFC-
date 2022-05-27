#include "WaveCollapse.h"
#include <random>



void WaveCollapse::FindCommon(std::vector<char>& vec1, std::vector<char>& vec2, std::vector<char>& vec3)
{
	std::vector<char> v(vec1.size() + vec2.size());
	std::vector<char>::iterator it, bt, at, st;
	std::sort(vec1.begin(), vec1.end());
	std::sort(vec2.begin(), vec2.end());
	printf("common: ");
	//if (vec1.size() != 0 && vec2.size() != 0) {
	//	for (tile t1 : vec1) {
	//		for (tile t2 : vec2) {
	//			if (t1.types[0] == t2.types[0]) {
	//				vec3.push_back(t1.types[0]);
	//			}
	//		}
	//	}

	//}

	if (vec1.size() != 0 && vec2.size() != 0) {

		it = set_intersection(vec1.begin(),
			vec1.end(),
			vec2.begin(),
			vec2.end(),
			v.begin());

		for (st = v.begin(); st != it; ++st) {
			vec3.push_back(*st);
			std::cout << char(*st) << " ";
		}
	}
	else {
		if (vec1.size() != 0) {
			for (char w : vec1) {
				vec3.push_back(w);
				//	std::cout << w << " ";
			}
		}
		else if (vec2.size() != 0) {
			for (char w : vec2) {
				vec3.push_back(w);
				//std::cout << w << " ";
			}
		}
	}
	for (char c : vec3) {
		std::cout << c << " ";
	}
	std::cout << "\n";
}

WaveCollapse::WaveCollapse(const std::vector<std::vector<char>>& input) : HEIGHT(input.size()), WIDTH(input[0].size())
{

	GetRules(input);
	OnCreate();
	//OnCreate();


}

WaveCollapse::WaveCollapse() : WIDTH(0), HEIGHT(1)
{
}

void WaveCollapse::OnCreate()
{
	weightSum = 0;
	int h = 0;
	for (size_t y = 0; y < HEIGHT; y++)
	{
		std::vector<tile> temp;
		output.push_back(temp);

		for (size_t x = 0; x < WIDTH; x++)
		{

			output.at(y).push_back(tile(y, x, 'e'));

		}
	}
	for (tile* t : tiles) {
		weightSum += t->weight;
		weightChecks.push_back(tile(t->types[0], weightSum));
	}
	weightSum += 4;

	srand(time(0));


}



void WaveCollapse::Generate()
{

	//OnCreate();

	std::random_device rseed;
	std::mt19937 rng(rseed());
	std::uniform_int_distribution<int> dist(0, WIDTH);

	int amountOne = 0, amountTwo = 0, amountThree = 0;

	int currenty = dist(rng), currentx = dist(rng), startt = dist(rng);
	static int y = 0;

	//std::cout << "i: " << i << "\n";
	static int x = 0;



	//std::sort(entropyArray.begin(), entropyArray.end(), std::greater<>());


	if (y < HEIGHT) {
		if (x < WIDTH) {
			tile temp = output[y][x];
			CheckRules(temp);
			for (char c : temp.types) {
				std::cout << c << " ";
			}
			printf("\n");
			char rn='e';
			int weightT=0;
			int randy=0;
			std::vector<tile> weight;
			
			if (weightCheck) {
				for (tile t : weightChecks) {
					for(tile c : output[y][x].types)
						if (t.types[0] == c.types[0]) {
							printf("yo");
							weightT += t.weight;
							weight.push_back(tile(t.types[0],weightT));

						}

				}
				randy = rand() % weightT;
				for (tile t : weight) {
					if (randy < t.weight) {
						rn = t.types[0];
						break;
					}
				}
				for (tile* t : tiles) {
					if (rn == t->types[0]) {
						--t->weight;
						--weightSum;
					}
				}
				//rn = temp.types[rand() % weightT];
			}
			else {
				rn = temp.types[rand() % temp.types.size()];
			}




			 




			std::cout << "rn: " << rn << "\n";
			output[y][x] = (tile(y, x, rn));
			++x;
			Print();
			//std::cout << i << " " << j;
		}
		else if (y < WIDTH) { ++y; x = 0; 		std::cout << "//////////////////////////////////////////////////////////////////\n"; };
	}

}


void WaveCollapse::Print()
{
	for (size_t i = 0; i < HEIGHT; i++)
	{

		for (size_t j = 0; j < WIDTH; j++)
		{


			std::cout << (output[i][j].types[0]) << " ";




		}
		std::cout << "y\n";
	}
	for (size_t i = 0; i < WIDTH; i++)
	{
		std::cout << "x ";
	}
	std::cout << "\n";
	std::cout << "\n";

}

void WaveCollapse::GetAdjactent(int y, int x)
{
	output[y][x].entropy = 0;
	std::cout << "y: " << y << " x: " << x << "\n";
	tile* l, * r, * t, * b;
	if (InBounds(y, x + 1)) {
		l = &output[y][x + 1];
		printf("bounds right\n");
	}
	else
	{
		printf("bounds right null\n");
		l = nullptr;
	}
	if (InBounds(y, x - 1)) {
		b = &output[y][x - 1];
		printf("bounds left\n");
	}
	else
	{
		printf("bounds left null\n");
		b = nullptr;
	}
	if (InBounds(y + 1, x)) {
		r =& output[y + 1][x];
		printf("bounds bottom\n");
	}
	else
	{
		printf("bounds bottom null\n");
		r = nullptr;
	}
	if (InBounds(y - 1, x)) {
		t = &output[y - 1][x];
		printf("bounds top\n");
	}
	else {
		printf("bounds top null\n");
		t = nullptr;
	}

	//std::cout << char(l->types[0]) << " " << char(r->types[0]) << " " << t->types[0] << " " << b->types[0] << "\n";
	//}
	output[y][x].SetAdjacent(l, r, t, b);
	/*delete l;
	delete r;
	delete t;
	delete b;*/




}



void WaveCollapse::GetRules(const std::vector< std::vector<char> >& input)
{
	//gets best results 
	//char examplwe[HEIGHT][WIDTH] = {
	//	{'m','m','l','l','l','l'},
	//	{'m','l','l','l','l','c'},
	//	{'l','l','l','l','c','s'},
	//	{'l','l','l','c','s','s'},
	//	{'l','l','c','s','s','s'},
	//	{'l','c','s','s','s','s'}
	//};

	//char examplje[HEIGHT][WIDTH] = {
	//	{'s','s','s','s','s','c'},
	//	{'s','c','c','c','c','l'},
	//	{'s','c','l','l','l','m'},
	//	{'s','c','l','c','c','l'},
	//	{'s','c','l','c','s','c'},
	//	{'c','l','m','l','c','s'}
	//};



	bool lc = 0, rc = 0, tc = 0, bc = 0;


	for (size_t y = 0; y < HEIGHT; y++)
	{
		for (size_t x = 0; x < WIDTH; x++)
		{
			bool flagCheck = false;
			for (tile*& t : tiles) {

				if (input[y][x] == t->types[0]) {
					++t->weight;
					flagCheck = true;
				}

			}
			if (!flagCheck) {
				tiles.push_back(new tile(input[y][x]));
			}



			if (InBounds(y, x + 1)) {
				bool exist = false;
				for (rule& r : ruleListR) {

					if (((r.origin.types[0] == input[y][x]) && (r.adjacent.types[0] == input[y][x + 1]) && (r.direction == RIGHT))) {
						++r.weight;
						exist = true;
						//std::cout << r.origin.types[0] << " is next to " << r.adjacent.types[0] << " direction RIGHT\n";
					}
				}
				if (exist == false) {
					ruleListR.push_back(rule(tile(input[y][x]), tile(input[y][x + 1]), RIGHT));
					std::cout << ruleListR.back().origin.types[0] << " is next to " << ruleListR.back().adjacent.types[0] << " direction RIGHT\n";
				}

			}
			else
			{

			}
			if (InBounds(y, x - 1)) {
				bool exist = false;
				for (rule& r : ruleListL) {
					if ((r.origin.types[0] == input[y][x] && r.adjacent.types[0] == input[y][x - 1] && r.direction == LEFT)) {
						++r.weight;
						exist = true;
					}
				}
				if (exist == false) {
					ruleListL.push_back(rule(tile(input[y][x]), tile(input[y][x - 1]), LEFT));
					std::cout << ruleListL.back().origin.types[0] << " is next to " << ruleListL.back().adjacent.types[0] << " direction LEFT\n";
				}

			}
			else
			{

			}
			if (InBounds(y + 1, x)) {
				//printf("MM BUG");
				//TILEPT(y + 1, x, input[y][x]);
				bool exist = false;
				for (rule& r : ruleListB) {
					if ((r.origin.types[0] == input[y][x] && r.adjacent.types[0] == input[y + 1][x] && r.direction == BOTTOM)) {
						++r.weight;
						exist = true;
					}
				}
				if (exist == false) {
					ruleListB.push_back(rule(tile(input[y][x]), tile(input[y + 1][x]), BOTTOM));
					std::cout << ruleListB.back().origin.types[0] << " is next to " << ruleListB.back().adjacent.types[0] << " direction BOTTOM\n";
				}

			}
			else
			{

			}
			if (InBounds(y - 1, x)) {
				bool exist = false;
				for (rule& r : ruleListT) {
					if ((r.origin.types[0] == input[y][x] && r.adjacent.types[0] == input[y - 1][x] && r.direction == BOTTOM)) {
						exist = true;
						++r.weight;
					}
				}
				if (exist == false) {
					ruleListT.push_back(rule(tile(input[y][x]), tile(input[y - 1][x]), BOTTOM));
					std::cout << ruleListT.back().origin.types[0] << " is next to " << ruleListT.back().adjacent.types[0] << " direction RIGHT\n";
				}
			}
			else {

			}

			//}

		}
	}
	std::cout << "tiles: ";
	for (tile* t : tiles) {

		std::cout << t->types[0] << " ";
	}
	std::cout << "\n";
	//for (rule r : ruleListR) {

	//	std::cout << r.origin.types[0] << " is next to " << r.adjacent.types[0] << " direction RIGHT\n";
	//}
	//for (rule r : ruleListL) {
	//	std::cout << r.origin.types[0] << " is next to " << r.adjacent.types[0] << " direction LEFT\n";
	//}
	//for (rule r : ruleListT) {
	//	std::cout << r.origin.types[0] << " is next to " << r.adjacent.types[0] << " direction TOP\n";
	//}
	//for (rule r : ruleListB) {
	//	std::cout << r.origin.types[0] << " is next to " << r.adjacent.types[0] << " direction BOTTOM\n";
	//}



}

void WaveCollapse::CheckRules(tile& temp)
{
	GetAdjactent(temp.y, temp.x);
	std::vector<tile> starting;
	std::vector<char> allowedL;
	std::vector<char> allowedR;
	std::vector<char> allowedT;
	std::vector<char> allowedB;
	std::vector<tile> allowed;
	std::vector<char> notAllowed;
	for (tile* w : tiles) {
		allowed.push_back(*w);
		starting.push_back(*w);
		std::cout << "tiles: " << w->types[0] << " ";
	}
	std::cout << "\n";
	bool check = 0;

	bool lc, rc, tc, bc;
	lc = rc = tc = bc = 0;




	for (size_t i = 0; i < 4; i++)
	{
		if (output[temp.y][temp.x].adjacent[i] != nullptr && output[temp.y][temp.x].adjacent[i]->types[0] != 'e')
		{
			bool collapsed = true;
			switch (i)
			{
			case 0:

				for (rule r : ruleListL) {
					if (r.adjacent.types[0] == output[temp.y][temp.x].adjacent[i]->types[0]) {
						allowedL.push_back(r.origin.types[0]);
						collapsed = false;
					}
				}
				if (collapsed) {
					//	for (tile* t : tiles) {
					//		allowedL.push_back(t->types[0]);
					//	}
				}
				break;

			case 1:

				for (rule r : ruleListR) {
					if (r.adjacent.types[0] == output[temp.y][temp.x].adjacent[i]->types[0]) {
						allowedR.push_back(r.origin.types[0]);
						collapsed = false;
					}
				}
				if (collapsed) {
					//	for (tile* t : tiles) {
					//		allowedR.push_back(t->types[0]);
					//	}
				}
				break;

			case 2:

				for (rule r : ruleListT) {
					if (r.adjacent.types[0] == output[temp.y][temp.x].adjacent[i]->types[0]) {
						allowedT.push_back(r.origin.types[0]);
						collapsed = false;
					}
				}
				if (collapsed) {
					//	for (tile* t : tiles) {
					//		allowedT.push_back(t->types[0]);
					//	}
				}
				break;

			case 3:

				for (rule r : ruleListB) {
					if (r.adjacent.types[0] == output[temp.y][temp.x].adjacent[i]->types[0]) {
						allowedB.push_back(r.origin.types[0]);
						collapsed = false;
					}
				}
				if (collapsed) {
					//	for (tile* t : tiles) {
					//		allowedB.push_back(t->types[0]);
					//	}
				}
				break;

			default:
				break;
			}
		}
	}
	printf("allowedL: ");
	for (char c : allowedL) {
		std::cout << c << " ";
	}
	printf("\n");
	printf("allowedL: ");
	for (char c : allowedR) {
		std::cout << c << " ";
	}
	printf("\n");
	printf("allowedL: ");
	for (char c : allowedT) {
		std::cout << c << " ";
	}
	printf("\n");
	printf("allowedL: ");
	for (char c : allowedB) {
		std::cout << c << " ";
	}
	printf("\n");
	std::vector<char> choices;
	std::vector<char> choicesTB;
	std::vector<char> choicesLR;
	FindCommon(allowedL, allowedR, choicesLR);
	FindCommon(allowedT, allowedB, choicesTB);
	FindCommon(choicesLR, choicesTB, choices);
	temp.types.clear();
	if (choices.size() != 0) {
		for (tile t : choices) {
			temp.types.push_back(t.types[0]);
		}
	}
	else {
		//temp.types.push_back('m');
		for (tile t : starting) {
			temp.types.push_back(t.types[0]);
		}
	}

	int ran;
	//std::cout << "L: " << allowedL.size() << "R: " << allowedR.size() << "T: " << allowedT.size() << "B: " << allowedB.size() << "\n";
	char rn;
	//int weight = 0;
	//int ran = 






	//if (weightCheck) {
	//	//std::vector<int> weights;
	//	std::map<char, int>::iterator it;
	//	int tWeight = 0;
	//	std::vector<weight> localWeights;
	//	std::vector<int> sorted;
	//	for (weight t : weights) {
	//		for (char c : choices) {
	//			if (t.type == c) {

	//				tWeight += t.weigh;
	//				localWeights.push_back(weight(c, tWeight));
	//			}
	//		}

	//	}

	//	std::sort(localWeights.begin(), localWeights.end(), [](const weight& w1, const weight& w2) {
	//		return w1.weigh < w2.weigh; });
	//	//	std::cout << " choices: ";
	//		//for (char c : choices) {

	//		//	std::cout << c << " ";
	//		//}
	//	for (weight c : localWeights) {
	//		std::cout << "choice: " << c.type << " weight: " << c.weigh << " ";
	//	}
	//	printf("\n");
	//	std::cout << " weights: ";

	//	printf("\n");
	//	if (tWeight <= 0) {
	//		tWeight = 1;
	//	}
	//	ran = rand() % tWeight;
	//	WATCH(tWeight);
	//	for (weight w : localWeights) {
	//		std::cout << "ran: " << ran << " < " << w.weigh << "\n";
	//		if (ran < w.weigh) {
	//			rn = w.type;
	//			std::cout << "tile: " << rn << " \n";
	//			break;
	//		}
	//	}
	//}
	//else {
	//	ran = rand() % choices.size();
	//	rn = choices[ran];
	//}


	////for (char c : choices) {
	////	tileTypes[c]
	////		if (c > w) {

	////		}
	////}



	//output[temp.y][temp.x]->type = rn;
	//Print();

	//tileCount++;

	//if (weightSub == true && isalpha(output[temp.y][temp.x]->type)) {
	//	for (weight& t : weights) {
	//		for (weight tt : weightsHold) {
	//			if (output[temp.y][temp.x]->type == t.type && (t.type == tt.type) && (t.weigh == tt.weigh)) {
	//				t.weigh--;
	//			}
	//		}
	//	}; weightSum--;
	//}
}

