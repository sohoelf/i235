#include <iostream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <algorithm>
class Board
{
public:
	int board[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int whoseTurn = 1;
	int turnSum = 0;
	int winner = 0;
	std::vector <int>* actionList;
	Board()
	{
		actionList = new std::vector <int>();
	}
	Board(Board* b)
	{
		actionList = new std::vector <int>();
		for (int i = 0; i < 9; i++)
		{
			board[i] = b->board[i];
		}
		whoseTurn = b->whoseTurn;
		turnSum = b->turnSum;
		winner = b->winner;
		//*actionList = *(b->actionList);
	}
	~Board()
	{
		delete(actionList);
	}
	void refreshActionList()
	{
		actionList->clear();
		for (int i = 0; i < 9; i++)
		{
			if (board[i] == 0)
				actionList->push_back(i);
		}
	}
	void doAction(int a)
	{
		board[a] = whoseTurn;
		whoseTurn = -whoseTurn;
		turnSum++;
	}
	int randomAction()
	{
		refreshActionList();
		if (actionList->size() > 0)
		{
			int a = (*actionList)[rand() % (actionList->size())];
			doAction(a);
			return a;
		}
		else
		{
			return -1;
		}
	}
	int isGoal()
	{
		int winner = 0;
		int goalRule[][3]{ {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
		for (auto& i : goalRule)
		{
			int sum = 0;
			for (auto& j : i)
			{
				sum += board[j];
			}
			if (sum == 3)
			{
				winner = 1;
				break;
			}
			else if (sum == -3)
			{
				winner = -1;
				break;
			}
		}
		this->winner = winner;
		return winner;
	}
	void print()
	{
		int n = 0;
		for (auto& i : board)
		{
			if (i == 0)
			{
				std::cout << "- ";
			}
			else if (i == 1)
			{
				std::cout << "O ";
			}
			else
			{
				std::cout << "X ";
			}
			n++;
			if (n == 3)
			{
				n = 0;
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;
	}
};
Board* simulation(std::vector<Board*> simulationList, int simulationNumber, int whoseBestAction, bool isShow)//モンテカルロシミュレーション
{
	int maxWinCount = -1;
	int minWinCount = -1;
	Board* maxBoard = nullptr;//勝率最大手
	Board* minBoard = nullptr;//勝率最小手
	for (auto& i : simulationList)
	{
		if (isShow)i->print();
		int winCount = 0;
		for (int j = 0; j < simulationNumber; j++)
		{
			Board* b = new Board(i);
			while (b->randomAction() != -1 && b->isGoal() == 0);
			if (b->winner == 1)
			{
				winCount += 2;
			}
			else if (b->winner == 0)
			{
				winCount += 1;
			}
			delete(b);
		}
		if (maxWinCount == -1)
		{
			maxWinCount = winCount;
			minWinCount = winCount;
			maxBoard = i;
			minBoard = i;
		}
		else
		{
			if (winCount > maxWinCount)
			{
				maxWinCount = winCount;
				maxBoard = i;
			}
			if (winCount < minWinCount)
			{
				minWinCount = winCount;
				minBoard = i;
			}
		}
		float winRate = winCount / (float)(simulationNumber * 2);//勝率
		if (isShow)std::cout << "WinRate=" << winRate << std::endl << std::endl;
	}
	if (whoseBestAction == 1)return maxBoard;
	else return minBoard;
}
int main()
{
	srand((unsigned int)time(NULL));
	std::vector<Board*> simulationList;
	Board* b0 = new Board();//先手は本質的には３通りある
	b0->doAction(0);
	Board* b1 = new Board();
	b1->doAction(1);
	Board* b4 = new Board();
	b4->doAction(4);
	simulationList.push_back(b0);
	simulationList.push_back(b1);
	simulationList.push_back(b4);
	simulation(simulationList, 10000, 1, true);//10000シミュレーションし
	//以下は発展の部分
	int winCount = 0;
	for (int match = 0; match < 100; match++)
	{
		Board* b_ = new Board();
		if (match >= 50)b_->whoseTurn = -1;
		while (b_->isGoal() == 0 && b_->turnSum < 9)
		{
			b_->refreshActionList();
			simulationList.clear();
			for (auto& i : (*b_->actionList))
			{
				Board* b_next = new Board(b_);
				b_next->doAction(i);
				simulationList.push_back(b_next);
			}
			b_ = simulation(simulationList, b_->whoseTurn == 1 ? 1000 : 30, b_->whoseTurn, false);//自分のターンだったら勝率最大手を選択し、相手のターンだったら勝率最小手を選択すること
		}
		if (b_->winner == 1) { winCount += 2; }
		else if (b_->winner == 0) { winCount += 1; }
		std::cout << "Match-" << match << ":" << b_->winner << "| ";
		//b_->print();
	}
	float winRate = winCount / (100.0f * 2.0f);
	std::cout << std::endl << "WinRate=" << winRate << std::endl;
}

/*////////出力//////////////
O - -
- - -
- - -

WinRate=0.669

- O -
- - -
- - -

WinRate=0.6031

- - -
- O -
- - -

WinRate=0.7527

Match-0:0| Match-1:0| Match-2:0| Match-3:1| Match-4:1| Match-5:0| Match-6:1| Match-7:0| Match-8:1| Match-9:0| Match-10:0| Match-11:0| Match-12:0| Match-13:0| Match-14:1| Match-15:0| Match-16:1| Match-17:1| Match-18:1| Match-19:0| Match-20:1| Match-21:1| Match-22:1| Match-23:0| Match-24:0| Match-25:1| Match-26:1| Match-27:0| Match-28:1| Match-29:0| Match-30:0| Match-31:0| Match-32:0| Match-33:0| Match-34:1| Match-35:0| Match-36:1| Match-37:1| Match-38:0| Match-39:1| Match-40:1| Match-41:0| Match-42:1| Match-43:1| Match-44:0| Match-45:1| Match-46:0| Match-47:0| Match-48:1| Match-49:0| Match-50:-1| Match-51:-1| Match-52:0| Match-53:0| Match-54:0| Match-55:-1| Match-56:0| Match-57:-1| Match-58:-1| Match-59:-1| Match-60:0| Match-61:-1| Match-62:0| Match-63:0| Match-64:-1| Match-65:0| Match-66:-1| Match-67:0| Match-68:-1| Match-69:-1| Match-70:0| Match-71:0| Match-72:0| Match-73:0| Match-74:0| Match-75:0| Match-76:0| Match-77:0| Match-78:0| Match-79:0| Match-80:0| Match-81:0| Match-82:0| Match-83:-1| Match-84:0| Match-85:0| Match-86:-1| Match-87:-1| Match-88:0| Match-89:0| Match-90:0| Match-91:0| Match-92:0| Match-93:0| Match-94:0| Match-95:-1| Match-96:-1| Match-97:-1| Match-98:0| Match-99:0|
WinRate=0.53

*///////////////////////////
