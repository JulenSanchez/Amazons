#include "statement.h"

using namespace std;

int main()
{
	int n = 0;
	while (n != 3)
	{system("cls");
		cout << "┍━━━━━━━━━━━━━━━┓ \n";
		cout << "┃  欢迎使用     ┃ \n";
		cout << "┃ 1.新开始      ┃ \n";
		cout << "┃ 2.读取存档    ┃ \n";
		cout << "┃ 3.退出        ┃ \n";
		cout << "┃               ┃ \n";
		cout << "┕━━━━━━━━━━━━━━━┛ \n";
		cout << "请输入1/2/3选择：" << endl;
		cin >> n; cin.get();
		switch (n)
		{case 1:Game(1); break;
		case 2:Game(2); break;
		default:break;
		}
	}
}