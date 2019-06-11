
//½áÂÛ£º

#include <iostream>

uint8_t wdata[100] = { 0 };
uint8_t wdata_1[100] = { 0 };
uint8_t rdata[100] = { 0 };

int main()
{
	using namespace std;

	uint8_t test_data[100] = { 0 };
	std::cout << sizeof(test_data) << std::endl;

	for (uint8_t i = 0; i < 100; i++)
	{
		wdata[i] = 0x5a;
		wdata_1[i] = wdata[i] ^ i;
	}
	cout << hex << wdata << endl;
	cout << hex << wdata_1 << endl;

	getchar();
	return 0;
}