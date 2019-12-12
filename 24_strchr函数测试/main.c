#include <stdio.h>
#include <string.h>

int main()
{
	const char str[] = " pm_12v ch1";
	const char ch = 'h';
	char* ret;

	ret = strchr(str, ch);

	printf("|%c| 之后的字符串是 - |%s|\n", ch, ret);

	getchar();
	return(0);
}