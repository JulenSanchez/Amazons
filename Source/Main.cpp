#include "statement.h"

using namespace std;

int main()
{
	int n = 0;
	while (n != 3)
	{system("cls");
		cout << "���������������������������������� \n";
		cout << "��  ��ӭʹ��     �� \n";
		cout << "�� 1.�¿�ʼ      �� \n";
		cout << "�� 2.��ȡ�浵    �� \n";
		cout << "�� 3.�˳�        �� \n";
		cout << "��               �� \n";
		cout << "���������������������������������� \n";
		cout << "������1/2/3ѡ��" << endl;
		cin >> n; cin.get();
		switch (n)
		{case 1:Game(1); break;
		case 2:Game(2); break;
		default:break;
		}
	}
}