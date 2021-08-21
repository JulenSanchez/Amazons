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
	//�������Ƿ��Ѿ���·����
	while(!Zugzwang()){
		if (!(turnID == 1 && currBotColor == 1))
		{
			if (currBotColor == 1)cout << "�������� ���� " << endl;
			else cout << "�������� ���� " << endl;
			cout << "�밴���²������룺" << endl;
			cout<<" a b c d e f���ƶ���������(��ĸ��Ϊ0~7������)" << endl;
			cout << " -1���浵" << endl;
			cout << " -2������" << endl;
			cout << " -3����;�˳���Ϸ" << endl;
			int move=0;
			//����
			while(1)
			{
				cin >> move;
				if ( move== -1){
					int a[8][8];
					for (int i = 0; i < 8; i++)
						for (int j = 0; j < 8; j++)
							a[i][j] = gridInfo[i][j];
					Save(a,currBotColor);
					cout << "�浵�ɹ���" << endl;
					continue;//�浵
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
					cout << "�����岽 (" << x0[turnID-1] << " " << z0[turnID-1] << ") (" << x1[turnID-1] << 
						" " <<z1[turnID-1] << ") (" << x2[turnID-1] << " " << z2[turnID-1] << ")" << endl;
					if (currBotColor == 1)cout << "�������� ���� " << endl;
					else cout << "�������� ���� " << endl;
					cout << "�밴���²������룺" << endl;
					cout << " a b c d e f���ƶ���������(��ĸ��Ϊ0~7������)" << endl;
					cout << " -1���浵" << endl;
					cout << " -2������" << endl;
					cout << " -3����;�˳���Ϸ" << endl;
					continue;//����
				}
				else if (move== -3)return;//��;�˳���Ϸ
				else {
					x0[turnID] = move;
					cin >> z0[turnID] >> x1[turnID]>> z1[turnID] >> x2[turnID] >> z2[turnID];
					if (ProcStep(x0[turnID], z0[turnID], x1[turnID], z1[turnID], x2[turnID], z2[turnID], -currBotColor, false))
					{break;}//��������
				}
				cout << "�Ƿ��岽������һ��!       ���s#-_-)�s�k�T�k" << endl << endl;
				cout << "�밴���²������룺" << endl;
				cout << " a b c d e f���ƶ���������(��ĸ��Ϊ0~7������)" << endl;
				cout << " -1���浵" << endl;
				cout << " -2������" << endl;
				cout << " -3����;�˳���Ϸ" << endl;
			}

			//�������
			gridInfo[x0[turnID]][z0[turnID]] = 0;
			gridInfo[x1[turnID]][z1[turnID]] = -currBotColor;
			gridInfo[x2[turnID]][z2[turnID]] = 2;
			turnID++;
			Output();
		}
		//�ҷ�����........................................................................
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
		}//�����е�Amazon�ҵ�
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
		//��¼���ܵľ����������ж��Ƿ����ڲ���ʱ������µ��õڶ��������
		//�ж��Ƿ�����·����
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
			cout << "�����岽 ("<<x0[turnID] << " " << z0[turnID] << ") (" << x1[turnID] << " " <<
				z1[turnID] << ") (" << x2[turnID] << " " << z2[turnID] <<")"<< endl;
			turnID++;
		}
	}
	cout << "You Lose..." << endl;
	Replay();
	return;
}