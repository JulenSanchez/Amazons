#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include<math.h>
#include <iostream>
#include <fstream>

#define GRIDSIZE 8
#define OBSTACLE 2
#define judge_black 0
#define judge_white 1
#define grid_black 1
#define grid_white -1

extern int currBotColor; // 我所执子颜色（1为黑，-1为白，棋盘状态亦同）
extern int gridInfo[GRIDSIZE][GRIDSIZE] ; // 先x后y，记录棋盘状态
extern int dx[] ;
extern int dy[] ;
extern int Sx[4], Sy[4], Rx[4], Ry[4], cnt1, cnt2;
extern int turnID;
extern int poscount;
extern double alpha;
extern int x0[60],z0[60],x1[60],z1[60],x2[60],z2[60];

inline bool inMap(int x, int y);
double min(double a, double b);
double max(double a, double b);
bool ProcStep(int x0, int y0, int x1, int y1, int x2, int y2, int color, bool check_only);
bool Zugzwang();

double E(int a[8][8]);
double EE(int a[8][8]);

void NewStart();
void Load();
void Save(int a[8][8],int b);
void Game(int i);
void Output();
void Replay();

