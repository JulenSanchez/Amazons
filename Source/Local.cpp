#include "statement.h"
using namespace std;

void Load()
{
	ofstream outfile("data");
	outfile << currBotColor<<endl;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			outfile << gridInfo[i][j] << " ";
	outfile.close();

}

void Save(int a[8][8],int b)
{
	ifstream infile("data");
	infile >> b;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			infile >> a[i][j];
	infile.close();

}

void NewStart()
{
	cout << "��ܰ��ʾ���浵���Ḳ��ԭ�м�¼��" << endl;
	cout << "������1/2������ѡ���������ɫ��1 ��ɫ�����֣� 2 ��ɫ" << endl;
	int t;
	cin >> t;
	if (t == 1)currBotColor = -1;
	else if (t == 2)currBotColor = 1;
	memset(gridInfo, 0, sizeof(gridInfo));
	gridInfo[2][0] = gridInfo[0][2] = gridInfo[0][5] = gridInfo[2][7] = grid_black;
	gridInfo[5][0] = gridInfo[7][2] = gridInfo[7][5] = gridInfo[5][7] = grid_white;
	turnID = 1;
}

void Replay()
{
	int endgame;
	do
	{
		cout << "�������Ӧ�غ����Ը��̣����롰0���ص�������" << endl;
		cin >> endgame;
		memset(gridInfo, 0, sizeof(gridInfo));
		gridInfo[2][0] = gridInfo[0][2] = gridInfo[0][5] = gridInfo[2][7] = grid_black;
		gridInfo[5][0] = gridInfo[7][2] = gridInfo[7][5] = gridInfo[5][7] = grid_white;
		for (int i = 1; i <= endgame; i++)
		{
			gridInfo[x1[i]][z1[i]] = gridInfo[x0[i]][z0[i]];
			gridInfo[x0[i]][z0[i]] = 0;
			gridInfo[x2[i]][z2[i]] = 2;
		}
		Output();
	} while (endgame != 0);
	return;
}