#include <iostream>
#include <vector>
#include <algorithm>
#define WIDTH 15
enum NEXT
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};
std::vector <int> maze{//15×15の配列にループのない迷路
	'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',
	'X',' ',' ',' ','X',' ',' ',' ',' ',' ','X',' ',' ',' ','X',
	'X','X','X',' ','X',' ','X','X','X',' ','X',' ','X','X','X',
	'X',' ',' ',' ','X',' ',' ',' ','X',' ','X',' ',' ',' ','X',
	'X',' ','X','X','X','X','X','X','X',' ','X',' ','X','X','X',
	'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ','X',
	'X',' ','X','X','X',' ','X',' ','X','X','X','X','X',' ','X',
	'X',' ','X',' ','X',' ','X',' ',' ',' ',' ',' ',' ',' ','X',
	'X',' ','X',' ','X',' ','X','X','X','X',' ','X','X','X','X',
	'X',' ',' ',' ','X',' ','X',' ',' ',' ',' ',' ',' ',' ','X',
	'X','X','X',' ','X',' ','X',' ','X','X','X','X','X','X','X',
	'X',' ',' ',' ','X',' ','X',' ',' ',' ',' ',' ',' ',' ','X',
	'X',' ','X','X','X',' ','X','X','X','X','X',' ','X','X','X',
	'X',' ',' ',' ','X',' ','X',' ',' ',' ',' ',' ',' ',' ','X',
	'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'
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
};
int main()
{
	for (auto& i : maze)
	{
		i == 'X' ? i = -2 : i = -1;
	}
	int now = MATH::getI(1, 1);//(1,1)からスタート
	int goal = MATH::getI(WIDTH - 2, WIDTH - 2);//(13,13)をゴール点と設定
	maze[now] = 0;//(1,1)は 1（進入済）にしておく
	std::vector<int> * searchList = new std::vector<int>();
	searchList->push_back(now);
	while (maze[goal] == -1)
	{
		std::vector<int>* lin = new std::vector<int>();
		for (auto& i : *searchList)
		{
			for (int j = UP; j <= RIGHT; j++)
			{
				if (maze[MATH::getNext(j, i)] == -1)
				{
					maze[MATH::getNext(j, i)] = maze[i]+1; //進んだ先を1（進入済）にする
					lin->push_back(MATH::getNext(j, i));
				}
			}
		}
		delete(searchList);
		searchList = lin;
	}
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if(maze[i * WIDTH + j]<0)std::cout << " * ";
			else
			{
				if (maze[i * WIDTH + j] > 9)std::cout << maze[i * WIDTH + j] << " ";
				else std::cout << " " << maze[i * WIDTH + j] << " ";
			}
			
		}
		std::cout << "\n";
	}
	now = goal;
	std::vector<int> output;
	while (maze[now] != 0)
	{
		for (int i = UP; i <= RIGHT; i++)
		{
			if (maze[MATH::getNext(i, now)] == maze[now]-1)
			{
				now = MATH::getNext(i, now);
				output.push_back(now);
				break;
			}
		}
	}
	std::for_each(output.rbegin(), output.rend(), [](auto&& s) {
		std::cout << "(" << MATH::getX(s) << "," << MATH::getY(s) << ")->";
		});
	std::cout << "(" << MATH::getX(goal) << "," << MATH::getY(goal) << ")";
	return 0;
}
/*////////////実行結果/////////////////
 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
 *  0  1  2  * 24 23 22 21 20  * 22 23 24  *
 *  *  *  3  * 25  *  *  * 19  * 21  *  *  *
 *  6  5  4  * 26 27 28  * 18  * 20 21 22  *
 *  7  *  *  *  *  *  *  * 17  * 19  *  *  *
 *  8  9 10 11 12 13 14 15 16 17 18  * 24  *
 *  9  *  *  * 13  * 15  *  *  *  *  * 23  *
 * 10  * 16  * 14  * 16 17 18 19 20 21 22  *
 * 11  * 15  * 15  *  *  *  * 20  *  *  *  *
 * 12 13 14  * 16  * 24 23 22 21 22 23 24  *
 *  *  * 15  * 17  * 25  *  *  *  *  *  *  *
 * 18 17 16  * 18  * 26 27 28 29 30 31 32  *
 * 19  *  *  * 19  *  *  *  *  * 31  *  *  *
 * 20 21 22  * 20  *  *  * 34 33 32 33 34  *
 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
(1,1)->(2,1)->(3,1)->(3,2)->(3,3)->(2,3)->(1,3)->(1,4)->(1,5)->(2,5)->(3,5)->(4,5)->(5,5)->(6,5)->(7,5)->(7,6)->(7,7)->(8,7)->(9,7)->(10,7)->(10,8)->(10,9)->(9,9)->(8,9)->(7,9)->(7,10)->(7,11)->(8,11)->(9,11)->(10,11)->(11,11)->(11,12)->(11,13)->(12,13)->(13,13)
*//////////////////////////////////////
