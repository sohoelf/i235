#include <iostream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <map>
#define MAPSIZE 20
#define LOOP 10
std::map<short, short> nnMap;
std::map<short, bool> pointMap;
short MAPSIZE2 = MAPSIZE * MAPSIZE;
void run(short LEARNINGDATA)
{
	float avg = 0.0f;
	for (short l = 0; l < LOOP; l++)
	{
		nnMap.clear();
		pointMap.clear();
		for (short i = 0; i < LEARNINGDATA; i++)
		{
			short j;
			if (i < LEARNINGDATA / 2)
			{
				do {
					j = rand() % MAPSIZE2;
				} while (pointMap.find(j) != pointMap.end()
					|| j % MAPSIZE >= MAPSIZE / 2);
				pointMap.insert({ j,true });
			}
			else
			{
				do {
					j = rand() % MAPSIZE2;
				} while (pointMap.find(j) != pointMap.end()
					|| j % MAPSIZE < MAPSIZE / 2);
				pointMap.insert({ j,false });
			}
		}
		for (short i = 0; i < MAPSIZE2; i++)
		{
			short minPoint = -1, minDistance = MAPSIZE2 + MAPSIZE2;
			short x = i % MAPSIZE;
			short y = i / MAPSIZE;
			for (auto& j : pointMap)
			{
				short x_ = j.first % MAPSIZE;
				short y_ = j.first / MAPSIZE;
				short x_x = x_ - x; short y_y = y_ - y;
				short x_xy_y = x_x * x_x + y_y * y_y;
				if (x_xy_y <= minDistance)
				{
					minDistance = x_xy_y;
					minPoint = j.first;
				}
			}
			nnMap.insert({ i,pointMap[minPoint] });
		}
		for (auto& i : pointMap)
		{
			nnMap[i.first] = i.second + 2;
		}
		short correctCount = 0;
		for (short i = MAPSIZE - 1; i >= 0; i--)
		{
			for (short j = 0; j < MAPSIZE; j++)
			{
				short k = nnMap[i * MAPSIZE + j];
				if (j < MAPSIZE / 2)
				{
					if (k % 2 == 1)correctCount++;
				}
				else
				{
					if (k % 2 == 0)correctCount++;
				}
				switch (k)
				{
				case 0:std::cout << "x "; break;
				case 1:std::cout << ". "; break;
				case 2:std::cout << "X "; break;
				case 3:std::cout << "o "; break;
				default:break;

				}
			}
			std::cout << "\n";
		}
		std::cout << "Generalization Performance="
			<< (float)correctCount / MAPSIZE2 << "\n\n";
		avg += (float)correctCount / MAPSIZE2 / LOOP;
	}
	std::cout << "-------------Avg=" << avg
		<< "---------------\n\n";
}
int main()
{
	srand((unsigned int)time(NULL));
	run(7 * 2);//○と×をランダムに7個ずつ選んだ場合
	run(2 * 2);//○と×をランダムに2個ずつ選んだ場合
	return 0;
}
/*/////////////実行結果////////////////

. . . . . . . . x x x x x x x x x x x x
. . . . . o . . x x x x x x X x x x x x
. . . . . . . . x x X x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . . . x x x x x x
. . . . . . . . o . . . . x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . x x x x x x x X x x x x x
. o . . . . x x x x x x x x x x x x x x
. . . . . . . x x x X X x x x x x x x x
. . . . . . . . x x x x x X x X x x x x
o . . . . . . . . . . x x x x x x x x x
. . . . . . . o . o . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . o . . . . . . . . x x x x x x x
Generalization Performance=0.89

. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. o . . . . . . . . . x x x x X x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . o . . x x x x x x x x x x
o . . . . . . . . . x x X x x X x x x x
. . o . . o . . . x x X x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
o . . . . . . . x x x x x x x X x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . . x x x X x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . . x x x x x x x X x
. . . . . . . . o . . . x x x x x x x x
Generalization Performance=0.9425

. . . . . . . . o . . . . . x x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . x x x x x x x x X x x x x
. . o . . . . x x x x X x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . o o . . . . . x x x x x x x x X x x
. . . . o . . . . x x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . o . . . . . x x x x x x x x X x x
. . . . . . . . . x x x x x X x x x x x
. . . . . . . . . x x x x x x x x x x X
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . o x X x x x x x x x x x
Generalization Performance=0.925

. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x X x x
. . . . . o . . . . x x x x x x x x x x
. . . . . . . . . x x x x X x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . o . . . . . x x x x x x x x x
. . . . . . . . . . . x x x X x x x x x
. . . . . . o . . . . x x x x x x x x x
. . . . . . . . o . . . x x x x x x x X
. . . o . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . o . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x X x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x X x x x x x
. . . . . o . . . . x x x x x x X x x x
Generalization Performance=0.955

. . . . . . . . . . . . x x x x x x x x
. . . . o o . . . . . . . x x x X x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . o . . x x x x x x x x
. . . . . . . . . . . . x x X x x x x X
. . . . . . . . o . . . x x x x x X x x
. . o . . . . . . . . . x x x x x x x x
. . . . . . . . o . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x X x
. . . . . . . . . o . x x x x x x x x x
. . . . . . . . . . . x X x x x x x x x
. . . . . . . . . . . x x X x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
Generalization Performance=0.9225

. . . . . . x x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . . x x x x x x x x x X x x
. . . . . . . . . x X x x x x x x x x x
. . . . . . . . . o x x x x x x x x X x
. . . o . . . . . . . x x x x x x x x x
. . o . . . o . . . x x X x x X x x x x
. o . . . . . . . x x X x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . o . . . . . x x x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . . . . . . . . . . . x x x x X x x
. . . . . . . . . . . . . x x x x x x x
. . . . . . . . o . . . . x x x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . . . . . . . . . . . . x x x x x x
. . . . . . . . . . . . . . x x x x x x
Generalization Performance=0.8975

. . . o . . . . . . . . . x x x x x x X
. . . . . . . . o . . . . x x x x x x x
. o . . . . . . . . . . x x x x x X x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . o . . . x x x x X x x x x x x x x x
. . . . . . x x x x x x x x x x x x x x
o . . . . . . x x x x x x x x x x x x x
. . o . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x X X x x x
. . o . . . . . x x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x X x
. . . . . . x x x x x x x x x x x x x x
. . . . . x x x x x x x x x x x x x x x
. . . . x x x x x x X x x x x x x x x x
. . . . x x x x x x x x x x x x x x x x
. . . x x x x x x x x x x x x x x x x x
. . x x x x x x x x x x x x x x x x x x
Generalization Performance=0.8175

. . . o . . . . . x x x x x x x x X x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . . x x X x x x x x x x
. . . o . . . . . . x x x x x x x x x x
. . . . . . . o . . x x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . o . . . x x x X x x x x X x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . . x X x x x x x x x x
. . . . . . . . o . x x x x x x x x X x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
o . o . . . . x x x x x X x x x x x x x
. . . . . . . x x x x x x x x x x x x x
Generalization Performance=0.955

. . . . . . . . . . . . . x x x x X x x
. . . . . . . . o . . . . x x x x x x x
. . . o . . . . . . . . . x x x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x X
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x X x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . . . x x x x X x x x
. . . . . . . . . o . . x x x x x x x x
. o . . . . . . . . . x x X x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . o . o . x X x x x x x x x
. . . . . . . . . . . x X x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . o . . . x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
Generalization Performance=0.9325

. . . . . . . . . . . . x x x x X x x x
. . . . . . . o . . . . x x x x x x x x
. . . . . . o . . . . x x x x x x x x x
. . . o . . . . . . . x x x x x x x x x
. . . . . . . . . . x x x x X x x x x x
. . . . . . . . . x x x x X x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . x x x x X x x x x x x X
. . . . . . . . x x x x x x x x x x x x
. . . o . . . . x x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x X x
. . . . . . . . . . . x x x x x x x x x
. . . o . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
o . . . . . . o . . . . x x x x x X x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
Generalization Performance=0.9175

-------------Avg=0.9155---------------

. . . . . o . . . . . . . x x x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x X
. . . . . o . . . . . . . x x x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x X
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
Generalization Performance=0.9125

. . . . x x x x x x x x x x x x x x x x
. . . . x x x x x x x x x x x x x x x x
. . . . . x x x x x x x x x x x x x x x
. . . . . x x x x x x x x x x x x x x x
. . . . . x x x x x x x x x x x x x x x
. . . . . . x x x x x x x x x x x x x x
. . . . . . x x x x x x x x x x x x x x
. . . . . . . x x x x x x X x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . o . . . . . . x x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . x x x x x x X x x x x
. . . o . . . . . . x x x x x x x x x x
Generalization Performance=0.87

. . . . . . . . x x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x X
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . o . . . . . . x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x X x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . o . . . . . x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
Generalization Performance=0.9575

. . . . x x x x x x x x x x x x x x x x
. . . . . x x x x x x x x x x x x x x x
. . . . . x x x x x x x x x x x x x x x
. . . . . . x x x x x x x x x x x x X x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . o . . . x x x X x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . o . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
Generalization Performance=0.83

. . x x x x x x x x x x x x x x x x x x
. . . x x x x x x x x x x x x x x x x x
. . . . x x x x x x x x x x x x x x x x
. . . . . x x x x x x x x x x x x x x x
. . . . . . x x x x x x x x x x X x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . . x x X x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . o . x x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . o . . . . . . . . x x x x x x x
. . . . . . . . . . . . . . x x x x x x
. . . . . . . . . . . . . . . x x x x x
. . . . . . . . . . . . . . . . x x x x
. . . . . . . . . . . . . . . . . x x x
. . . . . . . . . . . . . . . . . x x x
. . . . . . . . . . . . . . . . . . x x
. . . . . . . . . . . . . . . . . . x x
. . . . . . . . . . . . . . . . . . . x
Generalization Performance=0.76

. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . . . x x X x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . o . . x x x x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . . . . . . . . . . . . x x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . . . o . . . . . . x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x X x x x x
. . . . . . . . . x x x x x x x x x x x
Generalization Performance=0.93

. . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . x
. . . . . . . . . o . . . . . . . . . x
. . . . . . . . . . . . . . . . . . x x
. . . . . . . . . . . . . . . . . x x x
. . . . . . . . . o . . . . . . x x x x
. . . . . . . . . . . . . . . . x x x x
. . . . . . . . . . . . . . x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . x x x x x x x x x x x x x x x
. . x x x x x x x x x X x x x x x x x X
x x x x x x x x x x x x x x x x x x x x
x x x x x x x x x x x x x x x x x x x x
x x x x x x x x x x x x x x x x x x x x
Generalization Performance=0.6125

. . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . .
. . . . . . . . o . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . x x
. . . . . . . . . . . . . . . . . x x x
. . . . . . . . . . . . . . . x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . o . . . . . . . . x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . x x x x x x X x x x x x
. . . . . . . x x x x x x x x x X x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
Generalization Performance=0.725

. . . . . . . . . . . . . . . . . . x x
. . . . . . . . . . . . . . . . . x x x
. . . . . . . . . . . . . . . . x x x x
. . . . . . . . . o . . . . . x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . x x x x x X x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . . . x x x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . . . . x x x x x x x X x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . . . . . o . . . . . x x x x x x x
. . . . . . . . . . . . . . x x x x x x
. . . . . . . . . . . . . . x x x x x x
. . . . . . . . . . . . . . x x x x x x
Generalization Performance=0.845

. . . . . . . . . . . . . x x x x x x x
. . . . . . . . . . . . . x x x x x x x
. . . . . . . . o . . . x x x x x x x x
. . . . . . . . . . . . x x x x x x x x
. . . . . . . . . . . x x x x x x x x x
. . . . . . . . . . . x x x X x x x x x
. . . . o . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . . x x x x x x x x x x
. . . . . . . . . x x x x x x x x x x x
. . . . . . . x x x x x x x x x x x x x
. . . . . . x x x x x x x x x x x x x x
. . . . x x x x x x x x x x x x x x x x
. . . x x x x x x x x x x x x x x x x x
. x x x x x x x x x x x x x x x x x x x
x x x x x x x x x x x X x x x x x x x x
x x x x x x x x x x x x x x x x x x x x
x x x x x x x x x x x x x x x x x x x x
Generalization Performance=0.82

-------------Avg=0.82625---------------

*//////////////////////////////////////