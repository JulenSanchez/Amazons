#include "statement.h"

using namespace std;
int currBotColor = 1;
int gridInfo[GRIDSIZE][GRIDSIZE] = { 0 }; 
int dx[] = { -1,-1,-1,0,0,1,1,1 };
int dy[] = { -1,0,1,-1,1,-1,0,1 };
int Sx[4] = { 0 }, Sy[4] = { 0 }, Rx[4] = { 0 }, Ry[4] = { 0 }, cnt1 = 0, cnt2 = 0;
int turnID = 1;
int poscount = 0;
double alpha = -10000;
//棋子是否在棋盘内
inline bool inMap(int x, int y)
{
	if (x < 0 || x >= GRIDSIZE || y < 0 || y >= GRIDSIZE)
		return false;
	return true;
}
//检查是否已经无路可走
bool Zugzwang()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (gridInfo[i][j] != -currBotColor)continue;
			for (int k = 0; k < 8; k++) {
				if (!inMap(i + dx[k], j + dy[k]))continue;
				if (gridInfo[i + dx[k]][j + dy[k]] == 0)return false;
			}
		}
	}
	return true;
}
// 在坐标处落子，检查是否合法或模拟落子
bool ProcStep(int x0, int y0, int x1, int y1, int x2, int y2, int color, bool check_only)
{
	if ((!inMap(x0, y0)) || (!inMap(x1, y1)) || (!inMap(x2, y2)))//是否在棋盘内
		return false;
	if (gridInfo[x0][y0] != color || gridInfo[x1][y1] != 0)//起始点是否有棋，落脚点有没有其它棋子挡住
		return false;
	if ((gridInfo[x2][y2] != 0) && !(x2 == x0 && y2 == y0))//能不能设置障碍
		return false;
	int flag = 0;
	for (int k = 0; k < 8; k++)
	{
		for (int h = 1; h < 8; h++)
		{
			int xx = x0 + dx[k] * h, yy = y0 + dy[k] * h;
			if (xx == x1 && yy == y1) { flag = 1; break; }
			else if (gridInfo[xx][yy] != 0)continue;
		}
		if (flag == 1)break;
	}

	if (flag == 1)
	{
		for (int k = 0; k < 8; k++)
		{
			for (int h = 1; h < 8; h++)
			{
				int xxx = x1 + dx[k] * h, yyy = y1 + dy[k] * h;
				if (xxx == x2 && yyy == y2) { flag = 2; break; }
				else if (gridInfo[xxx][yyy] != 0)continue;
			}
			if (flag == 2)break;
		}
	}
	if (flag == 2)return true;
	return false;
}
//最大最小
double max(double a, double b)
{
	if (a > b)return a;
	return b;
}
double min(double a, double b)
{
	if (a < b)return a;
	return b;
}