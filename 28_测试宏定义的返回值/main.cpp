//结论：a为假，直接return。

#include <iostream>

using namespace std;

#define gpio_mix_check(a)	if(!a){cout<<"enter gpio_mix_check"<<endl;return;}
void main()
{
	int a = 1;
	int b = 2;
	gpio_mix_check((a > 3));
	gpio_mix_check((b < 3));
	getchar();
}