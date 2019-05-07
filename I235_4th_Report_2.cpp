#include <iostream>
#include <stdio.h>
#include <time.h>
#include <vector>
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
		i == 'X' ? i = 3 : i = 0;//0が空所，3が壁を表すことにする．
	}
	srand((unsigned int)time(NULL));
	std::vector<int> randomNumers;
	int now = MATH::getI(1, 1);//(1,1)からスタート
	int goal = MATH::getI(WIDTH - 2, WIDTH - 2);//(13,13)をゴール点と設定
	maze[now] = 1;//(1,1)は 1（進入済）にしておく
	while (now != goal)//(13, 13)に到達すればゴール
	{
		randomNumers.clear();
		while (randomNumers.size() <= RIGHT)//今いる場所から上下左右に0があればランダムにそこに進み
		{
			int i;
			std::vector<int>::iterator ret;
			do
			{
				i = rand() % (RIGHT + 1);
				ret = std::find(randomNumers.begin(), randomNumers.end(), i);

			} while (ret != randomNumers.end());
			randomNumers.push_back(i);
		}
		bool found = false;
		for (int i = UP; i <= RIGHT; i++)
		{
			if (maze[MATH::getNext(randomNumers[i], now)] == 0)
			{
				maze[MATH::getNext(randomNumers[i], now)] = 1; //進んだ先を1（進入済）にする
				now = MATH::getNext(randomNumers[i], now);
				found = true;
				break;
			}
		}
		if (!found)//上下左右に0がなければ
		{
			for (int i = UP; i <= RIGHT; i++)
			{
				if (maze[MATH::getNext(randomNumers[i], now)] == 1)
				{
					maze[now] = 2;//今の場所を2（希望なし）にして
					now = MATH::getNext(randomNumers[i], now); //上下左右の１のうちどれかをランダムに選んで進む
					break;
				}
			}
		}
	}
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			std::cout << maze[i * WIDTH + j] << " ";
		}
		std::cout << "\n";
	}
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