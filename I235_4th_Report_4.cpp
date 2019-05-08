#include <iostream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#define WIDTH (4+2)
#define LOOPCOUNT 1000
#define LOOP 100
#define DEPTH 20
enum
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};
static class MATH {
public:
	static int getX(int i) { return i % WIDTH; }
	static int getY(int i) { return i / WIDTH; }
	static int getI(int x, int y) { return y * WIDTH + x; }
	static int getNext(int next, int i)
	{
		switch (next)
		{
		case UP:return i - WIDTH; break;
		case DOWN:return i + WIDTH; break;
		case LEFT:return i - 1; break;
		case RIGHT:return i + 1; break;
		}
	}
	static std::vector<int>* getMoveableList(std::vector<int>& v)
	{
		auto vv = new std::vector<int>();
		for (int i = UP; i <= RIGHT; i++)
		{
			if (isMoveable(i, v))vv->push_back(i);
		}
		return vv;
	}
	static bool isMoveable(int direction, std::vector<int>& v)
	{
		if (v[getNext(direction, -v[0])] < 0)return false;
		return true;
	}
	static std::vector<int>* move(int direction, std::vector<int> & v)
	{
		int lin = v[getNext(direction, -v[0])];
		v[getNext(direction, -v[0])] = 0;
		v[-v[0]] = lin;
		v[0] = -getNext(direction, -v[0]);
		return &v;
	}
};
void print(std::vector<int> pazuru)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (pazuru[i * WIDTH + j] > 9) { std::cout << pazuru[i * WIDTH + j] << " "; }
			else if (pazuru[i * WIDTH + j] < 0) {
				std::cout << "■ ";
			}
			else
			{
				std::cout << pazuru[i * WIDTH + j] << "  ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
int main()
{
	std::vector<int> pazuru;
	for (int i = 0, wallCount = 0; i < WIDTH * WIDTH; i++)
	{
		if (MATH::getX(i) == 0 || MATH::getX(i) == WIDTH - 1 ||
			MATH::getY(i) == 0 || MATH::getY(i) == WIDTH - 1)
		{
			pazuru.push_back(-1);
			wallCount++;
		}
		else if (MATH::getX(i) == WIDTH - 2 && MATH::getY(i) == WIDTH - 2) {
			pazuru.push_back(0);
			pazuru[0] = -i;
		}
		else
		{
			pazuru.push_back(i - wallCount + 1);
		}
	}
	print(pazuru);//正しく並んだ状態
	auto s_a = pazuru;//s_a=正しく並んだ状態
	MATH::move(UP, pazuru);//20回適当に行動をとること(ここは10回)
	MATH::move(LEFT, pazuru);
	MATH::move(DOWN, pazuru);
	MATH::move(LEFT, pazuru);
	MATH::move(UP, pazuru);
	MATH::move(LEFT, pazuru);
	MATH::move(RIGHT, pazuru);
	MATH::move(RIGHT, pazuru);
	MATH::move(RIGHT, pazuru);
	MATH::move(UP, pazuru);
	MATH::move(LEFT, pazuru);
	MATH::move(LEFT, pazuru);
	//MATH::move(LEFT, pazuru);
	//MATH::move(DOWN, pazuru);
	//MATH::move(DOWN, pazuru);
	//MATH::move(RIGHT, pazuru);
	//MATH::move(UP, pazuru);
	//MATH::move(UP, pazuru);
	//MATH::move(UP, pazuru);
	//MATH::move(RIGHT, pazuru);
	auto s_b = pazuru; //初期盤面Bを作れ
	print(pazuru);
	srand((unsigned int)time(NULL));
	int successCount = 0;
	std::cout << "Random run " << LOOPCOUNT << " times\n";
	for (int i = 0; i < LOOPCOUNT; i++)//「Bから100回ランダムに行動」LOOPCOUNT=1000回を繰り返すこと
	{
		pazuru = s_b;
		auto output = new std::vector<int>();
		for (int j = 0; j < LOOP; j++)//BからLOOP=100回ランダムに行動
		{
			auto ml = MATH::getMoveableList(pazuru);
			int direction = rand() % (ml->size());
			MATH::move((*ml)[direction], pazuru);
			output->push_back((*ml)[direction]);//手数を示せ
			if (pazuru == s_a)//Aに到達する解を何個か見つけて
			{
				successCount++;//個数を表示
				for (auto k : *output)//手数を示せ
				{
					switch (k)
					{
					case UP:std::cout << "↑"; break;
					case DOWN:std::cout << "↓"; break;
					case LEFT:std::cout << "←"; break;
					case RIGHT:std::cout << "→"; break;
					default:break;
					}
				}
				std::cout << "Success!\n";
				break;
			}
			delete(ml);
		}
		delete(output);
	}
	std::cout << successCount << " times succeeded\n";
	//BからAに到達する最短手順を，反復深化法で求め
	std::vector<std::pair<std::vector<int>, std::vector<int>>> search;
	std::vector<std::pair<std::vector<int>, std::vector<int>>> nextSearch;
	search.push_back({ s_b,*(new std::vector<int>) });
	unsigned long accessedNodeCount = 0;//探索したノード数
	for (int i = 0, isFound = 0; i < DEPTH; i++)
	{
		for (auto& j : search)
		{
			auto k = MATH::getMoveableList(j.first);
			for (auto& l : *k)
			{
				auto jClong = *(new std::pair<std::vector<int>, std::vector<int>>());
				jClong = j;
				MATH::move(l, jClong.first);
				jClong.second.push_back(l);
				nextSearch.push_back(jClong);
			}
			delete(k);
		}
		for (auto& j : nextSearch)
		{
			accessedNodeCount++;
			if (j.first == s_a)
			{
				isFound = 1;
				std::cout << "found! depth=" << i + 1 << " accessedNodeCount=" << accessedNodeCount << "\n";
				for (auto& k : j.second)//手数
				{
					switch (k)
					{
					case UP:std::cout << "↑"; break;
					case DOWN:std::cout << "↓"; break;
					case LEFT:std::cout << "←"; break;
					case RIGHT:std::cout << "→"; break;
					default:break;
					}
				}
				break;
			}
			if (isFound == 1)break;
		}
		if (isFound == 1)break;
		search = nextSearch;
		nextSearch.clear();
	}
	return 0;
}
/*////////////実行結果/////////////////
■ ■ ■ ■ ■ ■
■ 1  2  3  4  ■
■ 5  6  7  8  ■
■ 9  10 11 12 ■
■ 13 14 15 0  ■
■ ■ ■ ■ ■ ■

■ ■ ■ ■ ■ ■
■ 1  2  3  4  ■
■ 5  0  6  7  ■
■ 9  15 11 8  ■
■ 13 10 14 12 ■
■ ■ ■ ■ ■ ■

Random run 1000 times
↑↓←→→→↑←↓↑→↓↑←↓↑↓↓←↓→↑↑↑←→→←→↓↓↑↓↓Success!
1 times succeeded
found!depth = 10 accessedNodeCount = 217219
→↓←↓→↑↑→↓↓
*//////////////////////////////////////