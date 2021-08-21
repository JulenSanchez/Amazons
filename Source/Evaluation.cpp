#include "statement.h"

using namespace std;

//S��ʾ�ҷ������ӣ�Soldier��,R��ʾ�Է������ӣ�Rival��
int s1[8][8] = { 0 }, s2[8][8] = { 0 }, r1[8][8] = { 0 }, r2[8][8] = { 0 };
//�Լ���soldier���ͶԷ���rival��ͨ���ƶ�1��queen move��/2(king move)��ÿ���յص���С����
int step = 0;//̽���͵ݹ������ڱ��̽��������scale��
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


bool Scoguard[8][8] = { 0 }, Rcoguard[8][8] = { 0 };//��¼һ��յ��Ƿ�ͬʱ�ܱ��ҷ�������ӵ���
int Smark[8][8] = { 0 }, Rmark[8][8] = { 0 };//��¼���num�������ܹ��������յ�
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
			else if (Smark[x][y] != num)    Scoguard[x][y] = true;//������mark��=0��coguard==0��
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
			else if (Rmark[x][y] != num)    Rcoguard[x][y] = true;//������mark��=0��coguard==0��
		}
		Rkingmove(a, x, y, num);
	}
	step--;
}

//��������ֵ������ֵ��������һ�����ĳЩ�յض��п���Ȩ�����Թر�����ͨ����Ȧס�Լ�����أ�
//��һ���������������ͨ�����ԣ���ʱ��������أ�Ȼ�������ƶ������ӵ��ƶ��Ϸ�������
//�ֱ�����������ֵ��ȡmin��Ϊ����ֵ�Ա�֤�����ܾ����������������
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

//����ָ����ԤʾǱ�ڵı���ס�Ŀ��������ж϶����Ƿ�������Χ���ҷ���ĳ�����ӣ��ͷ�����������������ת�Ƴ������ľ���
double Strapindex(int a[8][8], int i, int j)
{
	int indexf = 0, indexs = 0;
	for (int k = 0; k < 8; k++) {
		if (!inMap(i + dx[k], j + dy[k]) || (a[i + dx[k]][j + dy[k]] != 0) || r1[i + dx[k]][j + dy[k]] < 3)
			indexf++;
		else if (!inMap(i + dx[k] * 2, j + dy[k] * 2) || (a[i + dx[k] * 2][j + dy[k] * 2] != 0))
			indexs++;
	}
	if (indexf >= 4 && (indexf + indexs == 8))return 10;//��ֹ���
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

//�ƶ���
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

//flag��ʾ���������һ�����ҷ����ǶԷ����ں���t1,t2��������������ͬ
int flag = 1;
double E(int a[8][8])
{
	double t1 = 0, t2 = 0, c1 = 0, c2 = 0, m1[4] = { 0 }, m2[4] = { 0 }, m = 0, g1 = 0, g2 = 0;//������Ҫ�ĸ����Ӻ���
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
			else if (r1[i][j] < s1[i][j])                                        t1--;//����1
			c1 = c1 + pow(2, 1 - s1[i][j]) - pow(2, 1 - r1[i][j]);                    //����2
			if (r2[i][j] > s2[i][j])                                             t2++;
			else if (r2[i][j] == s2[i][j] && r2[i][j] < 20 && flag == 1)t2 = t2 - 0.2;
			else if (r2[i][j] == s2[i][j] && r2[i][j] < 20 && flag == 2)t2 = t2 + 0.2;
			else if (r2[i][j] < s2[i][j])                                        t2--;//����4
			c2 = c2 + min(1, max(-1, ((double)r2[i][j] - (double)s2[i][j]) / 6));     //����5
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

//�����ڶ��㣻���־�����̫����������ֱ�ӵ��³�ʱ�������趨���ܾ�����<300ʱ�����ã�
//���衰���֡����ӡ��͡����������ʹ�ҷ������ֵ��С�Ĳ��������ü�������������³�����
//���ǡ����ӡ��͡������ǰ�Ϳ��Էֱ���һ�μ�֦�������˶Խڵ�ķ����������ⳬʱ
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
				beta = min(beta, evaluate);//ȡ��Сֵ
				if (beta <= alpha)
					return beta;
				for (int l = 0; l < 8; l++) {
					for (int delta2 = 1; delta2 < 8; delta2++) {
						int xxx = xx + dx[l] * delta2;
						int yyy = yy + dy[l] * delta2;
						if (!inMap(xxx, yyy))//����������
							break;
						if (a[xxx][yyy] != 0 && !(i == xxx && j == yyy))//���ǿյػ���ʼ��
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
							if (evaluate < beta)beta = evaluate;//ȡ��Сֵ
							if (beta <= alpha)return beta;
						}
					}
				}
			}
		}
	}
	return beta;
}
