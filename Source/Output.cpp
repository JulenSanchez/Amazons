#include "statement.h"
using namespace std;

void Output()
{
	system("cls");
	cout << "     0   1   2   3   4   5   6   7   " << endl;
	cout << "  ���������ש������ש������ש������ש������ש������ש������ש�������" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << i<<" ";
		for (int j = 0; j < 8; j++)
		{
			cout <<"��";
			switch (gridInfo[i][j])
			{
			case -1:cout << " ��"; break;
			case 1:cout << " ��"; break;
			case 0:cout << "   "; break;
			case 2:cout << " �w "; break;
			}
		}
		cout << "��" <<" "<<i<< endl;
		if (i < 7)cout << "  �ǩ������贈�����贈�����贈�����贈�����贈�����贈�����贈������" << endl;
	}

	cout << "  ���������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�������" << endl;
	cout << "     0   1   2   3   4   5   6   7   " << endl;
	return;
}