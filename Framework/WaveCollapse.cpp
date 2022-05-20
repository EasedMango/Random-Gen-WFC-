#include "WaveCollapse.h"
#include <random>


void WaveCollapse::OnCreate()
{
	int h = 0;
	for (size_t i = 0; i < HEIGHT; i++)
	{


		for (size_t j = 0; j < WIDTH; j++)
		{

			tiles[j][i] = new tile();
			tiles[j][i]->type = 'e';
		}
	}

	srand(time(0));


}



void WaveCollapse::Generate()
{


	std::random_device rseed;
	std::mt19937 rng(rseed());
	std::uniform_int_distribution<int> dist(-1, 1);
	std::uniform_int_distribution<int> distType(1, 4);
	std::uniform_int_distribution<int> distAd(0, 5);
	std::uniform_int_distribution<int> distLC(1, 2);
	std::uniform_int_distribution<int> distSC(2, 3);
	static int i = 0;

	//std::cout << "i: " << i << "\n";
	static int j = 0;
	std::cout << "\n";

	for (int k = 0; k < HEIGHT; k++)
	{
		for (int h = 0; h < WIDTH; h++)
		{
			std::cout << "k: " << k << " h: " << h << "\n";
			CheckRules(k, h);
		}
		std::cout << "\n";
	}
	//if (i < WIDTH-1) {
	//	if (j < HEIGHT-1) {
	//		++j;
	//		//std::cout << i << " " << j;
	//	}
	//	else if(i < WIDTH-1) { ++i; j = 0; 		/*std::cout << "\n";*/ };

	//}
	int amountOne = 0, amountTwo = 0, amountThree = 0;

	int currenty = distAd(rng), currentx = distAd(rng), startt = distType(rng);

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


	tile* l, * r, * t, * b;
	if (InBounds(y, x + 1)) {
		l = tiles[y][x + 1];
	}
	else
	{
		l = nullptr;
	}
	if (InBounds(y, x - 1)) {
		b = tiles[y][x - 1];
	}
	else
	{
		b = nullptr;
	}
	if (InBounds(y + 1, x)) {
		r = tiles[y + 1][x];
	}
	else
	{
		r = nullptr;
	}
	if (InBounds(y - 1, x)) {
		t = tiles[y - 1][x];
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
	char exampleOG[HEIGHT][WIDTH] = {
		{'m','m','l','l','l','l'},
		{'m','l','l','l','l','c'},
		{'l','l','l','l','c','s'},
		{'l','l','l','c','s','s'},
		{'l','l','c','s','s','s'},
		{'l','c','s','s','s','s'}
	};

	char examplewe[HEIGHT][WIDTH] = {
		{'l','l','l','l','l','l'},
		{'l','l','m','l','l','l'},
		{'l','m','c','m','l','l'},
		{'l','m','c','m','l','l'},
		{'l','m','c','m','l','l'},
		{'l','l','m','l','l','l'}
	};
	char example[12][12] = {
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
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{

			if (InBounds(i, j + 1)) {
				bool exist = false;
				for (std::tuple<char, char, lrt> x : ruleList) {
					if ((std::get<0>(x) == example[i][j] && std::get<1>(x) == example[i][j + 1] && std::get<2>(x) == RIGHT)) {
						exist = true;
					}
				}
				if (!exist) {
					ruleList.push_back(std::tuple<char, char, lrt>(example[i][j], example[i][j + 1], RIGHT));
				}
			}
			else
			{

			}
			if (InBounds(i, j - 1)) {
				bool exist = false;
				for (std::tuple<char, char, lrt> x : ruleList) {
					if ((std::get<0>(x) == example[i][j] && std::get<1>(x) == example[i][j - 1] && std::get<2>(x) == LEFT)) {
						exist = true;
					}
				}
				if (!exist) {
					ruleList.push_back(std::tuple<char, char, lrt>(example[i][j], example[i][j - 1], LEFT));
				}
			}
			else
			{

			}
			if (InBounds(i + 1, j)) {
				bool exist = false;
				for (std::tuple<char, char, lrt> x : ruleList) {
					if ((std::get<0>(x) == example[i][j] && std::get<1>(x) == example[i + 1][j] && std::get<2>(x) == BOTTOM)) {
						exist = true;
					}
				}
				if (!exist) {
					ruleList.push_back(std::tuple<char, char, lrt>(example[i][j], example[i + 1][j], BOTTOM));
				}
			}
			else
			{

			}
			if (InBounds(i - 1, j)) {
				bool exist = false;
				for (std::tuple<char, char, lrt> x : ruleList) {
					if ((std::get<0>(x) == example[i][j] && std::get<1>(x) == example[i - 1][j] && std::get<2>(x) == TOP)) {
						exist = true;
					}
				}
				if (!exist) {
					ruleList.push_back(std::tuple<char, char, lrt>(example[i][j], example[i - 1][j], TOP));
				}
			}
			else {

			}
			//}

		}
	}
	for (std::tuple<char, char, lrt> x : ruleList) {
		std::cout << std::get<0>(x) << " is next to " << std::get<1>(x) << " direction ";
		switch (std::get<2>(x)) {
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
}

void WaveCollapse::CheckRules(int& x, int& y)
{
	GetAdjactent(y, x);
	std::vector<char> allowed = { 'm', 'l', 'c', 's' };
	std::vector<char> backup = { 'm', 'l', 'c', 's' };
	int sideCheck = 0;
	bool check = true;
	bool checkAgain = false;
	if (tiles[y][x]->type != 'e') {
		checkAgain = true;
	}
	bool lCheck = 0, rCheck = 0, tCheck = 0, bCheck = 0;
	char lastCheck;
	char randomT = allowed[rand() % allowed.size()];

	//	int ki = 0;
	do {

		Print();
		if (!checkAgain) {
			lastCheck = randomT;
			std::cout << "alowed size" << int(allowed.size()) << "\n";
			while (randomT == lastCheck) {
				randomT = allowed[rand() % allowed.size()];
			}
		}
		else {
			randomT = tiles[y][x]->type;
		}
		std::cout << "tile CHOOSEN: " << randomT << "\n";
		for (std::tuple<char, char, lrt> w : ruleList) {
			//std::cout << ki<< "\n";
			//ki++;

			//sideCheck = 0;
			switch (std::get<2>(w))
			{
			case LEFT:
				if (tiles[y][x]->adjacent[0] != nullptr) {
					if (tiles[y][x]->adjacent[0]->type == std::get<1>(w) && randomT == std::get<0>(w)) {
						lCheck = 1;
						++sideCheck;
					}
					else if (tiles[y][x]->adjacent[0]->type == 'e') {
						++sideCheck;
						lCheck = 1;
					}
					std::cout << "LEFT: " << tiles[y][x]->adjacent[0]->type << " " << std::get<0>(w) << "\n";
				}
				else { lCheck = 1; }

				break;
			case RIGHT:
				if (tiles[y][x]->adjacent[1] != nullptr) {
					if (tiles[y][x]->adjacent[1]->type == std::get<1>(w) && randomT == std::get<0>(w)) {
						rCheck;
						++sideCheck;
					}
					else if (tiles[y][x]->adjacent[1]->type == 'e') {
						++sideCheck;
						rCheck = 1;
					}
					std::cout << "RIGHT: " << tiles[y][x]->adjacent[1]->type << " " << std::get<0>(w) << "\n";
				}
				else { rCheck = 1; }
				break;
			case TOP:
				if (tiles[y][x]->adjacent[2] != nullptr) {
					if (tiles[y][x]->adjacent[2]->type == std::get<1>(w) && randomT == std::get<0>(w)) {
						++sideCheck;
						tCheck = 1;
					}
					else if (tiles[y][x]->adjacent[2]->type == 'e') {
						++sideCheck;
						tCheck = 1;
					}
					std::cout << "TOP: " << tiles[y][x]->adjacent[2]->type << " " << std::get<0>(w) << "\n";
				}
				else { tCheck = 1; }
				break;
			case BOTTOM:
				if (tiles[y][x]->adjacent[3] != nullptr) {
					if (tiles[y][x]->adjacent[3]->type == std::get<1>(w) && randomT == std::get<0>(w)) {
						++sideCheck;
						bCheck = 1;

					}
					else if (tiles[y][x]->adjacent[3]->type == 'e') {
						++sideCheck;
						bCheck = 1;
					}
					std::cout << "BOTTOM: " << tiles[y][x]->adjacent[3]->type << " " << std::get<0>(w) << "\n";

				}
				else { bCheck = 1; }
				break;
			default:
				break;
			}
			checkAgain = false;
			if (lCheck && rCheck && tCheck && bCheck) {
				check = false;
			}
			//else if (sideCheck > 20) {
			//	x = 0;
			//	y = 0;
			//}
			//for (int g = 0; g < allowed.size(); ++g) {
			//	if (allowed[g] = randomT) {
			//		printf("deleting\n");
			//		allowed.erase(allowed.begin() + g);
			//	}
			//}
			/*			std::vector<char>::iterator it;
						it = std::find(allowed.begin(), allowed.end(), randomT);
						allowed.erase(it)*/;
						//printf(" \n");
						//	std::cout << sideCheck << "\n";

		}
	} while (check);
	//if (sideCheck == 0) {
	//	char random = backup[rand() % backup.size()];
	//	std::cout << "tile: " << random << "\n";
	//	tiles[y][x]->type = random;
	//}
	//else {

	tiles[y][x]->type = randomT;
	//}
	//else {
	//	if (tiles[y][x]->type == 'e') {
	//		char random = backup[rand() % backup.size()];
	//		std::cout << "tile: " << random << "\n";
	//		tiles[y][x]->type = random;
	//	}

	//}
	//printf("Available:\n");
	//for (char h : allowed) {
	//	std::cout << h << " ";
	//}
	printf("\n");
	//for (std::tuple<int, int, lrt> j : ruleList) {							 -
	//	if ((std::get<0>(j) == tiles[y][x]->type && std::get<1>(j) == tiles[y + 1][x]->type && std::get<2>(j) == BOTTOM))
	//	{

	//	}
	//}

}

