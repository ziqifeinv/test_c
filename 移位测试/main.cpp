
#include <iostream>

int main()
{
	using namespace std;
	uint32_t test = 0x01030050;
	cout << hex << test << endl;
	cout << hex << (test << 6) << endl;
	cout << hex << (test << 24) << endl;
	cout << hex << (test & 0xff) << endl;
	getchar();
	return 0;
}