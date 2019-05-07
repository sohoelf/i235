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
/*////////////実行結果*2///////////////
3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
3 1 1 1 3 0 0 0 0 0 3 0 0 0 3
3 3 3 1 3 0 3 3 3 0 3 0 3 3 3
3 1 1 1 3 0 0 0 3 0 3 0 0 0 3
3 1 3 3 3 3 3 3 3 0 3 0 3 3 3
3 1 1 1 1 1 1 1 0 0 0 0 3 2 3
3 0 3 3 3 0 3 1 3 3 3 3 3 2 3
3 0 3 0 3 0 3 1 1 1 1 2 2 2 3
3 0 3 0 3 0 3 3 3 3 1 3 3 3 3
3 0 0 0 3 0 3 1 1 1 1 0 0 0 3
3 3 3 0 3 0 3 1 3 3 3 3 3 3 3
3 0 0 0 3 0 3 1 1 1 1 1 0 0 3
3 0 3 3 3 0 3 3 3 3 3 1 3 3 3
3 0 0 0 3 0 3 0 0 0 0 1 1 1 3
3 3 3 3 3 3 3 3 3 3 3 3 3 3 3

3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
3 1 1 1 3 0 0 0 0 0 3 0 0 0 3
3 3 3 1 3 0 3 3 3 0 3 0 3 3 3
3 1 1 1 3 0 0 0 3 0 3 0 0 0 3
3 1 3 3 3 3 3 3 3 0 3 0 3 3 3
3 1 1 1 1 1 1 1 0 0 0 0 3 2 3
3 2 3 3 3 0 3 1 3 3 3 3 3 2 3
3 2 3 2 3 0 3 1 1 1 1 2 2 2 3
3 2 3 2 3 0 3 3 3 3 1 3 3 3 3
3 2 2 2 3 0 3 1 1 1 1 0 0 0 3
3 3 3 2 3 0 3 1 3 3 3 3 3 3 3
3 2 2 2 3 0 3 1 1 1 1 1 2 2 3
3 2 3 3 3 0 3 3 3 3 3 1 3 3 3
3 2 2 2 3 0 3 2 2 2 2 1 1 1 3
3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
*//////////////////////////////////////