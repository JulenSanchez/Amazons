#include "statement.h"

using namespace std;

//S表示我方的棋子（Soldier）,R表示对方的棋子（Rival）
int s1[8][8] = { 0 }, s2[8][8] = { 0 }, r1[8][8] = { 0 }, r2[8][8] = { 0 };
//自己（soldier）和对方（rival）通过移动1（queen move）/2(king move)到每个空地的最小步数
int step = 0;//探索型递归中用于标记探索层数（scale）
void Squeenmove(int a[8][8], int i, int j)
{
	step++;
	for (int k = 0; k < 8; k++) {
		if (step > 8)break;
		for (int h = 1; h < 8; h++) {
			int x = i + dx[k] * h, y = j + dy[k] * h;
			if (!inMap(x, y) || step >= s1[x][y] || a[x][y] != 0)
				break;
			s1[x][y] = step;
			Squeenmove(a, x, y);
		}
	}
	step--;
}

void Rqueenmove(int a[8][8], int i, int j)
{
	step++;
	for (int k = 0; k < 8; k++) {
		if (step > 8)break;
		for (int h = 1; h < 8; h++) {
			int x = i + dx[k] * h, y = j + dy[k] * h;
			if (!inMap(x, y) || step >= r1[x][y] || a[x][y] != 0)
				break;
			r1[x][y] = step;
			Rqueenmove(a, x, y);
		}
	}
	step--;
}


bool Scoguard[8][8] = { 0 }, Rcoguard[8][8] = { 0 };//记录一块空地是否同时能被我方多个棋子到达
int Smark[8][8] = { 0 }, Rmark[8][8] = { 0 };//记录编号num的棋子能够到达这块空地
void Skingmove(int a[8][8], int i, int j, int num)
{
	step++;
	for (int k = 0; k < 8; k++) {
		if (step > 15)break;
		int x = i + dx[k], y = j + dy[k];
		if (!inMap(x, y) || step >= s2[x][y] || a[x][y] != 0)
			continue;
		s2[x][y] = step;
		if (Scoguard[x][y] == false) {
			if (Smark[x][y] == 0)  Smark[x][y] = num;
			else if (Smark[x][y] != num)    Scoguard[x][y] = true;//守卫：mark！=0且coguard==0；
		}
		Skingmove(a, x, y, num);
	}
	step--;
}

void Rkingmove(int a[8][8], int i, int j, int num)
{
	step++;
	for (int k = 0; k < 8; k++) {
		if (step > 15)break;
		int x = i + dx[k], y = j + dy[k];
		if (!inMap(x, y) || step >= r2[x][y] || a[x][y] != 0)
			continue;
		r2[x][y] = step;
		if (Rcoguard[x][y] == false) {
			if (Rmark[x][y] == 0)  Rmark[x][y] = num;
			else if (Rmark[x][y] != num)    Rcoguard[x][y] = true;//守卫：mark！=0且coguard==0；
		}
		Rkingmove(a, x, y, num);
	}
	step--;
}

//守卫附加值（守卫值）：守卫一方面对某些空地独有控制权，可以关闭外来通道来圈住自己的领地，
//另一方面仍与外界相连通，可以（暂时）放弃领地，然后在限制对手棋子的移动上发挥作用
//分别对两个方面估值，取min作为返回值以保证棋子能均衡两个方面的利益
double Sguard(int a[8][8], int num)
{
	int n1 = 0, n2 = 0;
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (Scoguard[r][c] == false && Smark[r][c] == num) {
				if (r2[r][c] == 30)n1++;
				else if (s1[r][c] == 1 && r1[r][c] == 1)n2++;
			}
		}
	}
	return min((double)n1, (double)n2);
}

double Rguard(int a[8][8], int num)
{
	int n1 = 0, n2 = 0;
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (Rcoguard[r][c] == false && Rmark[r][c] == num) {
				if (s2[r][c] == 30)n1++;
				else if (s1[r][c] == 1 && r1[r][c] == 1)n2++;
			}
		}
	}
	return min((double)n1, (double)n2);
}

//受限指数，预示潜在的被堵住的可能性来判断对手是否在有意围困我方的某个棋子，惩罚“不将这样的棋子转移出来”的决策
double Strapindex(int a[8][8], int i, int j)
{
	int indexf = 0, indexs = 0;
	for (int k = 0; k < 8; k++) {
		if (!inMap(i + dx[k], j + dy[k]) || (a[i + dx[k]][j + dy[k]] != 0) || r1[i + dx[k]][j + dy[k]] < 3)
			indexf++;
		else if (!inMap(i + dx[k] * 2, j + dy[k] * 2) || (a[i + dx[k] * 2][j + dy[k] * 2] != 0))
			indexs++;
	}
	if (indexf >= 4 && (indexf + indexs == 8))return 10;//禁止玩火！
	return 0;
}

double Rtrapindex(int a[8][8], int i, int j)
{
	int indexf = 0, indexs = 0;
	for (int k = 0; k < 8; k++) {
		if (!inMap(i + dx[k], j + dy[k]) || (a[i + dx[k]][j + dy[k]] != 0))
			indexf++;
		else if (!inMap(i + dx[k] * 2, j + dy[k] * 2) || (a[i + dx[k] * 2][j + dy[k] * 2] != 0))
			indexs++;
	}
	if (indexf >= 4 && (indexf + indexs == 8))return 10;
	return 0;
}

//移动性
double mobility(int a[8][8], int i, int j)
{
	int N = 0;
	for (int k = 0; k < 8; k++) {
		for (int h = 1; h < 8; h++) {
			int x = i + dx[k] * h, y = j + dy[k] * h;
			if (!inMap(x, y) || a[x][y] != 0) break;
			N++;
		}
	}
	return N;
}

//flag表示搜索的最后一层是我方还是对方，在函数t1,t2的评估上有所不同
int flag = 1;
double E(int a[8][8])
{
	double t1 = 0, t2 = 0, c1 = 0, c2 = 0, m1[4] = { 0 }, m2[4] = { 0 }, m = 0, g1 = 0, g2 = 0;//评估需要的各个子函数
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			r1[i][j] = r2[i][j] = s1[i][j] = s2[i][j] = 20;
	for (int cnt = 0; cnt < 4; cnt++) {
		Squeenmove(a, Sx[cnt], Sy[cnt]);
		Skingmove(a, Sx[cnt], Sy[cnt], cnt);
		Rqueenmove(a, Rx[cnt], Ry[cnt]);
		Rkingmove(a, Rx[cnt], Ry[cnt], cnt);
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (r1[i][j] > s1[i][j])                                             t1++;
			else if (r1[i][j] == s1[i][j] && r1[i][j] < 20 && flag == 1)t1 = t1 - 0.2;
			else if (r1[i][j] == s1[i][j] && r1[i][j] < 20 && flag == 2)t1 = t1 + 0.2;
			else if (r1[i][j] < s1[i][j])                                        t1--;//函数1
			c1 = c1 + pow(2, 1 - s1[i][j]) - pow(2, 1 - r1[i][j]);                    //函数2
			if (r2[i][j] > s2[i][j])                                             t2++;
			else if (r2[i][j] == s2[i][j] && r2[i][j] < 20 && flag == 1)t2 = t2 - 0.2;
			else if (r2[i][j] == s2[i][j] && r2[i][j] < 20 && flag == 2)t2 = t2 + 0.2;
			else if (r2[i][j] < s2[i][j])                                        t2--;//函数4
			c2 = c2 + min(1, max(-1, ((double)r2[i][j] - (double)s2[i][j]) / 6));     //函数5
		}
	}
	for (int i = 0; i < 4; i++) {
		m1[i] = mobility(a, Sx[i], Sy[i]) - 5 / (mobility(a, Sx[i], Sy[i]) + 1);
		m2[i] = mobility(a, Rx[i], Ry[i]) - 5 / (mobility(a, Rx[i], Ry[i]) + 1);
		m = m + m1[i] - m2[i];
		g1 = g1 + Sguard(a, i);
		g2 = g2 + Rguard(a, i);
	}
	if (turnID < 13)return 0.14*t1 + 0.13*c1 + 0.12*c2 + 0.36*t2 + 0.2*m + 0.05*(g1 - g2);
	else if (turnID < 32)return 0.23*t1 + 0.2*c1 + 0.19*c2 + 0.23*t2 + 0.05*m + 0.1*(g1 - g2);
	else  return 0.8*t1 + 0.1*c1 + 0.05*c2 + 0.05*t2;
}

//搜索第二层；开局局面数太多搜索二层直接导致超时，于是设定可能局面数<300时再启用；
//假设“对手‘落子’和‘射箭’都是使我方局面估值变小的操作”（该假设绝大多数情况下成立）
//于是“落子”和“射箭”前就可以分别做一次剪枝，减少了对节点的访问数，避免超时
double EE(int a[8][8])
{
	flag = 1;
	double e = E(a);
	if (turnID < 8 || poscount > 300 || e < alpha)return e;
	flag = 2;
	double beta = 10000;
	double evaluate = 0;
	for (int cnt = 0; cnt < 4; cnt++) {
		int i = Rx[cnt], j = Ry[cnt];
		for (int k = 0; k < 8; k++) {
			for (int delta1 = 1; delta1 < 8; delta1++) {
				int xx = i + dx[k] * delta1;
				int yy = j + dy[k] * delta1;
				if (a[xx][yy] != 0 || !inMap(xx, yy))
					break;
				a[i][j] = 0;
				a[xx][yy] = -currBotColor;
				Rx[cnt] = xx;
				Ry[cnt] = yy;
				evaluate = E(a);
				Rx[cnt] = i;
				Ry[cnt] = j;
				a[xx][yy] = 0;
				a[i][j] = -currBotColor;
				beta = min(beta, evaluate);//取最小值
				if (beta <= alpha)
					return beta;
				for (int l = 0; l < 8; l++) {
					for (int delta2 = 1; delta2 < 8; delta2++) {
						int xxx = xx + dx[l] * delta2;
						int yyy = yy + dy[l] * delta2;
						if (!inMap(xxx, yyy))//不在棋盘内
							break;
						if (a[xxx][yyy] != 0 && !(i == xxx && j == yyy))//不是空地或起始点
							break;
						if (ProcStep(i, j, xx, yy, xxx, yyy, -currBotColor, true)) {
							a[i][j] = 0;
							a[xx][yy] = -currBotColor;
							a[xxx][yyy] = 2;
							Rx[cnt] = xx;
							Ry[cnt] = yy;
							evaluate = E(a);
							Rx[cnt] = i;
							Ry[cnt] = j;
							a[xxx][yyy] = 0;
							a[xx][yy] = 0;
							a[i][j] = -currBotColor;
							if (evaluate < beta)beta = evaluate;//取最小值
							if (beta <= alpha)return beta;
						}
					}
				}
			}
		}
	}
	return beta;
}
