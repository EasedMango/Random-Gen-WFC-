#include "WaveCollapse.h"
#include <random>



void WaveCollapse::FindCommon(std::vector<char>& vec1, std::vector<char>& vec2, std::vector<char>& vec3)
{
	std::vector<int> v(vec1.size() + vec2.size());
	std::vector<int>::iterator it, bt, at, st;
	std::sort(vec1.begin(), vec1.end());
	std::sort(vec2.begin(), vec2.end());
	//printf("common: ");
	if (vec1.size() != 0 && vec2.size() != 0) {

		it = set_intersection(vec1.begin(),
			vec1.end(),
			vec2.begin(),
			vec2.end(),
			v.begin());

		for (st = v.begin(); st != it; ++st) {
			vec3.push_back(*st);
			//std::cout << char(*st) << " ";
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

	std::cout << "\n";
}

void WaveCollapse::OnCreate()
{
	int h = 0;
	for (size_t y = 0; y < HEIGHT; y++)
	{


		for (size_t x = 0; x < WIDTH; x++)
		{

			tiles[y][x] = new tile();
			tiles[y][x]->type = 'e';
			tiles[y][x]->x = x;
			tiles[y][x]->y = y;
		}
	}

	srand(time(0));


}



void WaveCollapse::Generate()
{


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
			CheckRules(y, x);
			++x;

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


			std::cout << ((char)tiles[i][j]->type) << " ";




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
	tiles[y][x]->entropy = 0;

	tile* l, * r, * t, * b;
	if (InBounds(y, x + 1)) {
		l = tiles[y][x + 1];
		if (tiles[y][x + 1]->type == 'e') {
			tiles[y][x]->entropy++;
		}
	}
	else
	{
		l = nullptr;
	}
	if (InBounds(y, x - 1)) {
		b = tiles[y][x - 1];
		if (tiles[y][x - 1]->type == 'e') {
			tiles[y][x]->entropy++;
		}
	}
	else
	{
		b = nullptr;
	}
	if (InBounds(y + 1, x)) {
		r = tiles[y + 1][x];
		if (tiles[y + 1][x]->type == 'e') {
			tiles[y][x]->entropy++;
		}
	}
	else
	{
		r = nullptr;
	}
	if (InBounds(y - 1, x)) {
		t = tiles[y - 1][x];
		if (tiles[y - 1][x]->type == 'e') {
			tiles[y][x]->entropy++;
		}
	}
	else {
		t = nullptr;
	}
	//}
	tiles[y][x]->SetAdjacent(l, r, t, b);





}

void WaveCollapse::GetRules()
{
	//gets best results 
	char examplwe[HEIGHT][WIDTH] = {
		{'m','m','l','l','l','l'},
		{'m','l','l','l','l','c'},
		{'l','l','l','l','c','s'},
		{'l','l','l','c','s','s'},
		{'l','l','c','s','s','s'},
		{'l','c','s','s','s','s'}
	};

	char examplje[HEIGHT][WIDTH] = {
		{'s','s','s','s','s','c'},
		{'s','c','c','c','c','l'},
		{'s','c','l','l','l','m'},
		{'s','c','l','c','c','l'},
		{'s','c','l','c','s','c'},
		{'c','l','m','l','c','s'}
	};

	char example[HEIGHT][WIDTH] = {
	{'m','m','l','l','l','l','m','m','l','l','l','l'},
	{'m','l','l','l','l','l','l','l','l','l','l','l'},
	{'l','l','l','l','c','c','l','l','l','l','l','l'},
	{'l','l','l','c','s','s','c','l','l','l','l','l'},
	{'l','l','c','s','s','s','s','c','l','l','l','l'},
	{'l','c','s','s','c','c','s','s','c','l','l','l'},
	{'l','c','s','s','c','l','c','s','s','c','l','l'},
	{'l','l','c','s','s','c','s','s','c','l','l','l'},
	{'l','l','l','c','s','s','s','c','l','l','l','l'},
	{'l','l','l','l','c','s','c','l','l','m','m','l'},
	{'l','l','l','l','l','c','l','l','l','m','m','l'},
	{'l','l','l','l','l','l','l','l','l','l','l','l'}
	};

	bool lc, rc, tc, bc;

	for (size_t y = 0; y < HEIGHT; y++)
	{
		for (size_t x = 0; x < WIDTH; x++)
		{
			lc = rc = tc = bc = 0;
			TILEPT(y, x, example[y][x]);
			bool checkFlag = false;

			if (isalpha(example[y][x])) {

				for (weight& w : weights) {
					if (w.type == example[y][x]) {
						checkFlag = true;
						w.weigh+=1;
						std::cout << w.type << " " << w.weigh << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
					}

				}
				if (checkFlag == false) {
					weights.push_back(weight(example[y][x], 0));
				}
				for (weight& w : weightsHold) {
					if (w.type == example[y][x]) {
						checkFlag = true;
						w.weigh += 1;
						std::cout << w.type << " " << w.weigh << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
					}

				}
				if (checkFlag == false) {
					weightsHold.push_back(weight(example[y][x], 0));
				}
				weightSum++;
				std::cout << example[y][x] << "\n";
			}
			/*	for (std::map<char, int>::iterator it = tileTypes.begin(); it != tileTypes.end(); ++it) {
					if (example[y][x] == it->first) {
						tileTypes[example[y][x]]++;
						checkFlag = true;
					}
				}
				if (checkFlag == false) {
					std::cout << example[y][x] << "\n";
					tileTypes[example[y][x]] == 1;
				}*/

			if (InBounds(y, x + 1)) {
				bool exist = false;
				for (std::tuple<char, char, lrt> w : ruleListR) {
					if ((std::get<0>(w) == example[y][x] && std::get<1>(w) == example[y][x + 1] && std::get<2>(w) == RIGHT)) {
						rc = true;
					}
				}
				if (rc == false) {
					ruleListR.push_back(std::tuple<char, char, lrt>(example[y][x], example[y][x + 1], RIGHT));
				}

			}
			else
			{

			}
			if (InBounds(y, x - 1)) {
				bool exist = false;
				for (std::tuple<char, char, lrt> w : ruleListL) {
					if ((std::get<0>(w) == example[y][x] && std::get<1>(w) == example[y][x - 1] && std::get<2>(w) == LEFT)) {
						lc = true;
					}
				}
				if (lc == false) {
					ruleListL.push_back(std::tuple<char, char, lrt>(example[y][x], example[y][x - 1], LEFT));

				}
			}
			else
			{

			}
			if (InBounds(y + 1, x)) {
				//printf("MM BUG");
				TILEPT(y + 1, x, example[y][x]);
				bool exist = false;
				for (std::tuple<char, char, lrt> w : ruleListB) {
					if ((std::get<0>(w) == example[y][x] && std::get<1>(w) == example[y + 1][x] && std::get<2>(w) == BOTTOM)) {
						bc = true;
						break;
					}
				}
				if (bc == false) {
					ruleListB.push_back(std::tuple<char, char, lrt>(example[y][x], example[y + 1][x], BOTTOM));

				}

			}
			else
			{

			}
			if (InBounds(y - 1, x)) {
				bool exist = false;
				for (std::tuple<char, char, lrt> w : ruleListT) {
					if ((std::get<0>(w) == example[y][x] && std::get<1>(w) == example[y - 1][x] && std::get<2>(w) == TOP)) {
						tc = true;
					}
				}
				if (tc == false) {
					ruleListT.push_back(std::tuple<char, char, lrt>(example[y][x], example[y - 1][x], TOP));

				}
			}
			else {

			}
			for (weight w : weights) {
				std::cout << "type: " << w.type << " weight: " << w.weigh << "\n";
			}
			//}

		}
	}
	for (std::tuple<char, char, lrt> w : ruleListL) {
		std::cout << std::get<0>(w) << " is next to " << std::get<1>(w) << " direction ";
		switch (std::get<2>(w)) {
		case 1:
			std::cout << "left\n";
			break;
		case 2:
			std::cout << "right\n";
			break;
		case 3:
			std::cout << "top\n";
			break;
		case 4:
			std::cout << "bottom\n";
			break;
		default:
			break;
		}
	}
	for (std::tuple<char, char, lrt> w : ruleListR) {
		std::cout << std::get<0>(w) << " is next to " << std::get<1>(w) << " direction ";
		switch (std::get<2>(w)) {
		case 1:
			std::cout << "left\n";
			break;
		case 2:
			std::cout << "right\n";
			break;
		case 3:
			std::cout << "top\n";
			break;
		case 4:
			std::cout << "bottom\n";
			break;
		default:
			break;
		}
	}
	for (std::tuple<char, char, lrt> w : ruleListT) {
		std::cout << std::get<0>(w) << " is next to " << std::get<1>(w) << " direction ";
		switch (std::get<2>(w)) {
		case 1:
			std::cout << "left\n";
			break;
		case 2:
			std::cout << "right\n";
			break;
		case 3:
			std::cout << "top\n";
			break;
		case 4:
			std::cout << "bottom\n";
			break;
		default:
			break;
		}
	}
	for (std::tuple<char, char, lrt> w : ruleListB) {
		std::cout << std::get<0>(w) << " is next to " << std::get<1>(w) << " direction ";
		switch (std::get<2>(w)) {
		case 1:
			std::cout << "left\n";
			break;
		case 2:
			std::cout << "right\n";
			break;
		case 3:
			std::cout << "top\n";
			break;
		case 4:
			std::cout << "bottom\n";
			break;
		default:
			break;
		}
	}
	for (weight t : weights) {
		printf("map: ");
		std::cout << t.type << " => " << t.weigh << '\n';


	}

}

void WaveCollapse::CheckRules(int& y, int& x)
{
	GetAdjactent(y, x);
	std::vector<char> starting;
	std::vector<char> allowedL;
	std::vector<char> allowedR;
	std::vector<char> allowedT;
	std::vector<char> allowedB;
	std::vector<char> allowed;
	std::vector<char> notAllowed;
	for (weight w : weights) {
		allowed.push_back(w.type);
		starting.push_back(w.type);
	}
	bool check = 0;

	bool lc, rc, tc, bc;
	lc = rc = tc = bc = 0;
	do {
		
		//start of adjacent check
		for (size_t i = 0; i < 4; i++)
		{
			//checks if adjacent if null 
			if (tiles[y][x]->adjacent[i] != nullptr) {
				switch (i)
				{
					//checks 0 of the adjacent array(left hopefully)
				case 0:
					//makes sure that the tile isn't 'e'
					if ((tiles[y][x]->adjacent[i]->type != 'e')) {

						for (std::tuple<char, char, lrt> l : ruleListL) {

							if (tiles[y][x]->adjacent[i]->type == std::get<1>(l)) {
								//adds all tiles allowed on the left of the adjacent tile type
								allowedL.push_back(std::get<0>(l));
								lc = 1;
							}
						}
					}
					//if lc isn't true
					else if (lc != true) {
						for (char w : allowed) {
							allowedL.push_back(w);
						}
						lc = true;
					}
					break;
				case 1:
					//makes sure that the tile isn't 'e'
					if ((tiles[y][x]->adjacent[i]->type != 'e')) {

						for (std::tuple<char, char, lrt> l : ruleListR) {

							if (tiles[y][x]->adjacent[i]->type == std::get<1>(l)) {
								//adds all tiles allowed on the left of the adjacent tile type
								allowedR.push_back(std::get<0>(l));
								rc = 1;
							}
						}
					}
					//if lc isn't true
					else if (rc != true) {
						for (char w : allowed) {
							allowedR.push_back(w);
						}
						rc = true;
					}
					break;
				case 2:
					//makes sure that the tile isn't 'e'
					if ((tiles[y][x]->adjacent[i]->type != 'e')) {

						for (std::tuple<char, char, lrt> l : ruleListT) {

							if (tiles[y][x]->adjacent[i]->type == std::get<1>(l)) {
								//adds all tiles allowed on the left of the adjacent tile type
								allowedT.push_back(std::get<0>(l));
								tc = 1;
							}
						}
					}
					//if lc isn't true
					else if (tc != true) {
						for (char w : allowed) {
							allowedT.push_back(w);
						}
						tc = true;
					}
					break;
				case 3:
					//makes sure that the tile isn't 'e'
					if ((tiles[y][x]->adjacent[i]->type != 'e')) {

						for (std::tuple<char, char, lrt> l : ruleListB) {

							if (tiles[y][x]->adjacent[i]->type == std::get<1>(l)) {
								//adds all tiles allowed on the left of the adjacent tile type
								allowedB.push_back(std::get<0>(l));
								bc = 1;
							}
						}
					}
					//if lc isn't true
					else if (bc != true) {
						for (char w : allowed) {
							allowedB.push_back(w);
						}
						bc = true;
					}
					break;
				default:
					break;
				}
			}
			else {
				switch (i)
				{
				case 0:
					lc = 1;
					break;
				case 1:
					rc = 1;
					break;
				case 2:
					tc = 1;
					break;
				case 3:
					bc = 1;
					break;

				default:
					break;
				}
			}
		}

	} while ((lc == false || rc == false || bc == false || tc == false));




	std::vector<char> choices;
	std::vector<char> choicesTB;
	std::vector<char> choicesLR;
	FindCommon(allowedL, allowedR, choicesLR);
	FindCommon(allowedT, allowedB, choicesTB);
	FindCommon(choicesLR, choicesTB, choices);
	int ran;
	//std::cout << "L: " << allowedL.size() << "R: " << allowedR.size() << "T: " << allowedT.size() << "B: " << allowedB.size() << "\n";
	char rn;
	//int weight = 0;
	//int ran = 





	
	if (weightCheck) {
		//std::vector<int> weights;
		std::map<char, int>::iterator it;
		int tWeight = 0;
		std::vector<weight> localWeights;
		std::vector<int> sorted;
		for (weight t : weights) {
			for (char c : choices) {
				if (t.type == c) {

					tWeight += t.weigh;
					localWeights.push_back(weight(c, tWeight));
				}
			}

		}

		std::sort(localWeights.begin(), localWeights.end(), [](const weight& w1, const weight& w2) {
			return w1.weigh < w2.weigh; });
		//	std::cout << " choices: ";
			//for (char c : choices) {

			//	std::cout << c << " ";
			//}
		for (weight c : localWeights) {
			std::cout << "choice: " << c.type << " weight: " << c.weigh << " ";
		}
		printf("\n");
		std::cout << " weights: ";

		printf("\n");
		if (tWeight <= 0) {
			tWeight = 1;
		}
		 ran = rand() % tWeight;
		WATCH(tWeight);
		for (weight w : localWeights) {
			std::cout << "ran: " << ran << " < " << w.weigh << "\n";
			if (ran < w.weigh) {
				rn = w.type;
				std::cout << "tile: " << rn << " \n";
				break;
			}
		}
	}
	else {
		ran = rand() % choices.size();
		rn = choices[ran];
	}


	//for (char c : choices) {
	//	tileTypes[c]
	//		if (c > w) {

	//		}
	//}
	
	

	tiles[y][x]->type = rn;
	Print();

	tileCount++;

	if (weightSub == true &&  isalpha(tiles[y][x]->type)) {
		for (weight &t : weights) {
			for (weight tt : weightsHold) {
				if (tiles[y][x]->type == t.type && (t.type == tt.type) && (t.weigh == tt.weigh)  ) {
					t.weigh --;
				}
			}
		}; weightSum--;
	}
}

