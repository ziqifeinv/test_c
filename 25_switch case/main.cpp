//结论:如果没有break，将会顺序执行之后的case，直到遇到下一个break

#include <iostream>

int main()
{
	using namespace std;

	int num = 0;
	int input = 0;
	for (int i = 0; i < 10; i++)
	{
		cin >> input;
		cout << "input is:" << input << endl;
		switch (input)
		{
		case  1:
			cout << "shu ru shi: 1" << endl;
			break;
		case 2:
			cout << "shu ru shi: 2" << endl;
			break;
		case 3:
		case 4:
			cout << "shu ru shi: 4" << endl;
		case 5:
			cout << "shu ru shi: 5" << endl;
		default:
			break;
		}
	}
		getchar();
	return 0;
}