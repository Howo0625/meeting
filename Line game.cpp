#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
using namespace std;

//全域變數
int ansx, ansy;
int minimumsum = 10000000;
int tempDist = 0;


struct Point { double x,y; };
struct Vector { double x, y; };	// 二維向量的資料結構

// 內積運算
double dot(Vector v1, Vector v2)
{
	// 沒有除法，儘量避免誤差。
	return v1.x * v2.x + v1.y * v2.y;
}

// 外積運算，回傳純量（除去方向）
double cross(Vector v1, Vector v2)
{
	// 沒有除法，儘量避免誤差。
	return v1.x * v2.y - v1.y * v2.x;
}

double length(Vector v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

//計算角度是否為鈍角
double angle(Vector v1, Vector v2, Vector v3)
{
	if (v3.x * v3.x + v3.y * v3.y - v1.x * v1.x - v1.y * v1.y - v2.x * v2.x - v2.y * v2.y > 0) return 1;
	if (v1.x * v1.x + v1.y * v1.y - v3.x * v3.x - v3.y * v3.y - v2.x * v2.x - v2.y * v2.y > 0) return 1;
	else return 0;
}

void minDis(int* arr,int x,int y)
{
	Point p = { x, y };
	Point p1 = { arr[0], arr[1] };
	Point p2 = { arr[2], arr[3] };


	Vector v1 = { p1.x - p.x,p1.y - p.y };
	Vector v2 = { p2.x - p1.x,p2.y - p1.y };
	Vector v3 = { p2.x - p.x,p2.y - p.y };

	if (angle(v1, v2, v3) == 0)//不是鈍角直接求高
	{
		tempDist += fabs(cross(v1, v2)) / length(v2);
	}
	else //鈍角要去算到線段兩個端點的最小距離
	{
		if (fabs(p.x - p1.x) + fabs(p.y - p1.y) < fabs(p.x - p2.x) + fabs(p.y - p2.y)) tempDist += fabs(p.x - p1.x) + fabs(p.y - p1.y);
		else tempDist += fabs(p.x - p2.x) + fabs(p.y - p2.y);
	}
}

int main()
{
	constexpr  int m = 4, n = 4;
	int line[n][m] = { {2,4,2,0},{2,1,0,1},{4,3,4,4},{5,5,4,5} };
	int minx = 1000000000;
	int miny = 1000000000;
	int maxx = -1000000000;
	int maxy = -1000000000;
	

	//找最小的(x1,y1)跟最大的(x2,y2)
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (j % 2 == 1)
			{
				if (miny > line[i][j]) miny = line[i][j];
				else if(maxy < line[i][j]) maxy = line[i][j];
			}
			else
			{
				if (minx > line[i][j]) minx = line[i][j];
				else if (maxx < line[i][j]) maxx = line[i][j];
			}
		}
	}

	//確定找出的大最大最小有無錯
	printf("(%d,%d,%d,%d)\n", minx, miny, maxx, maxy);

	//迭代框出的長方形中的所有點找出距離各線段總和最短的點
	for (double axisx = minx; axisx < maxx; ++axisx)
	{
		for (double axisy = miny; axisy < maxy; ++axisy)
		{
			//每條線段輪流代入計算minDis
			for (int i = 0; i < n; i++)
			{
				minDis(line[i],axisx,axisy);
			}

			if (minimumsum > tempDist)
			{
				minimumsum = tempDist;
				ansx = axisx;
				ansy = axisy;
			}

			//reset每個點的最短距離
			tempDist = 0;
		}
	}

	printf("(%d,%d)  %d\n", ansx, ansy, minimumsum);
	return 0;
}
