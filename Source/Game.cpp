#include "statement.h"
using namespace std;

int x0[60] = { 0 }, z0[60] = { 0 }, x1[60] = { 0 };
int z1[60] = { 0 }, x2[60] = { 0 }, z2[60] = { 0 };
void Game(int a)
{
	system("cls");
    if(a==1)NewStart();
	else Load();
	Output();
	//检查玩家是否已经无路可走
	while(!Zugzwang()){
		if (!(turnID == 1 && currBotColor == 1))
		{
			if (currBotColor == 1)cout << "您现在是 白棋 " << endl;
			else cout << "您现在是 黑棋 " << endl;
			cout << "请按以下操作输入：" << endl;
			cout<<" a b c d e f：移动您的棋子(字母均为0~7的整数)" << endl;
			cout << " -1：存档" << endl;
			cout << " -2：悔棋" << endl;
			cout << " -3：中途退出游戏" << endl;
			int move=0;
			//输入
			while(1)
			{
				cin >> move;
				if ( move== -1){
					int a[8][8];
					for (int i = 0; i < 8; i++)
						for (int j = 0; j < 8; j++)
							a[i][j] = gridInfo[i][j];
					Save(a,currBotColor);
					cout << "存档成功！" << endl;
					continue;//存档
				}
				else if (move == -2) {
					turnID--;
					gridInfo[x2[turnID]][z2[turnID]] = 0;
					gridInfo[x1[turnID]][z1[turnID]] = 0;
					gridInfo[x0[turnID]][z0[turnID]] = currBotColor;
					turnID--;
					gridInfo[x2[turnID]][z2[turnID]] = 0;
					gridInfo[x1[turnID]][z1[turnID]] = 0;
					gridInfo[x0[turnID]][z0[turnID]] = -currBotColor;
					Output();
					cout << "对手棋步 (" << x0[turnID-1] << " " << z0[turnID-1] << ") (" << x1[turnID-1] << 
						" " <<z1[turnID-1] << ") (" << x2[turnID-1] << " " << z2[turnID-1] << ")" << endl;
					if (currBotColor == 1)cout << "您现在是 白棋 " << endl;
					else cout << "您现在是 黑棋 " << endl;
					cout << "请按以下操作输入：" << endl;
					cout << " a b c d e f：移动您的棋子(字母均为0~7的整数)" << endl;
					cout << " -1：存档" << endl;
					cout << " -2：悔棋" << endl;
					cout << " -3：中途退出游戏" << endl;
					continue;//悔棋
				}
				else if (move== -3)return;//中途退出游戏
				else {
					x0[turnID] = move;
					cin >> z0[turnID] >> x1[turnID]>> z1[turnID] >> x2[turnID] >> z2[turnID];
					if (ProcStep(x0[turnID], z0[turnID], x1[turnID], z1[turnID], x2[turnID], z2[turnID], -currBotColor, false))
					{break;}//正常输入
				}
				cout << "非法棋步！警告一次!       （╯#-_-)╯╧═╧" << endl << endl;
				cout << "请按以下操作输入：" << endl;
				cout << " a b c d e f：移动您的棋子(字母均为0~7的整数)" << endl;
				cout << " -1：存档" << endl;
				cout << " -2：悔棋" << endl;
				cout << " -3：中途退出游戏" << endl;
			}

			//玩家落子
			gridInfo[x0[turnID]][z0[turnID]] = 0;
			gridInfo[x1[turnID]][z1[turnID]] = -currBotColor;
			gridInfo[x2[turnID]][z2[turnID]] = 2;
			turnID++;
			Output();
		}
		//我方落子........................................................................
		int a[8][8] = { 0 };
		poscount = 0;
		int cnt1 = 0, cnt2 = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				a[i][j] = gridInfo[i][j];
				if (a[i][j] == currBotColor) {
					Sx[cnt1] = i;
					Sy[cnt1++] = j;
				}
				else if (a[i][j] == -currBotColor) {
					Rx[cnt2] = i;
					Ry[cnt2++] = j;
				}
			}
		}//把所有的Amazon找到
		int beginx[3000],beginy[3000], terminalx[3000],
			terminaly[3000], obstaclex[3000],obstacley[3000], num[3000];
		double evaluate = 0;
		for (int cnt = 0; cnt < 4; cnt++)
		{
			int i = Sx[cnt], j = Sy[cnt];
			for (int k = 0; k < 8; k++)
			{
				for (int delta1 = 1; delta1 < 8; delta1++)
				{
					int xx = i + dx[k] * delta1,yy = j + dy[k] * delta1;
					if (a[xx][yy] != 0 || !inMap(xx, yy))break;
					for (int l = 0; l < 8; l++) 
					{
						for (int delta2 = 1; delta2 < 8; delta2++) 
						{
							int xxx = xx + dx[l] * delta2,yyy = yy + dy[l] * delta2;
							if (!(inMap(xxx, yyy) && (a[xxx][yyy] == 0 || (i == xxx && j == yyy))))break;
							beginx[poscount] = i;
							beginy[poscount] = j;
							terminalx[poscount] = xx;
							terminaly[poscount] = yy;
							obstaclex[poscount] = xxx;
							obstacley[poscount] = yyy;
							num[poscount++] = cnt;
						}
					}
				}
			}
		}
		//记录可能的局面数，以判断是否能在不超时的情况下调用第二层的搜索
		//判断是否已无路可走
		if (poscount == 0)
		{
			cout << "You Win!" << endl;
			Replay();
			return;
		}
		else
		{
			alpha = -10000;
			for (int i = 0; i < poscount; i++) {
				a[beginx[i]][beginy[i]] = 0;
				a[terminalx[i]][terminaly[i]] = currBotColor;
				a[obstaclex[i]][obstacley[i]] = 2;
				Sx[num[i]] = terminalx[i];
				Sy[num[i]] = terminaly[i];
				evaluate = E(a);
				Sx[num[i]] = beginx[i];
				Sy[num[i]] = beginy[i];
				a[obstaclex[i]][obstacley[i]] = 0;
				a[terminalx[i]][terminaly[i]] = 0;
				a[beginx[i]][beginy[i]] = currBotColor;
				if (evaluate > alpha) 
				{
					alpha = evaluate;
					x0[turnID] = beginx[i];
					z0[turnID] = beginy[i];
					x1[turnID] = terminalx[i];
					z1[turnID] = terminaly[i];
					x2[turnID] = obstaclex[i];
					z2[turnID] = obstacley[i];
				}
			}
			gridInfo[x0[turnID]][z0[turnID]] = 0;
			gridInfo[x1[turnID]][z1[turnID]] = currBotColor;
			gridInfo[x2[turnID]][z2[turnID]] = 2;
			
			Output();
			cout << "对手棋步 ("<<x0[turnID] << " " << z0[turnID] << ") (" << x1[turnID] << " " <<
				z1[turnID] << ") (" << x2[turnID] << " " << z2[turnID] <<")"<< endl;
			turnID++;
		}
	}
	cout << "You Lose..." << endl;
	Replay();
	return;
}