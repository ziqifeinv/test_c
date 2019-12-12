

#include <stdio.h>

void user_print()
{
	char i = 0, j = 0;
	for (j = 0; j < 10; j++)
	{
		for (i = 0; i < 10; i++)
		{
			if (i == 5)
			{
				printf("user_print func break\n");
				break;
			}
			printf("user print i is %d\n", i);
		}
		if (i == 5)
			break;
		printf("user print j is %d\n", j);
		if (j == 5)
		{
			printf("user_print func return\n");
			return;
		}
	}
}

int main()
{
	//int j = 0;
	user_print();
	getchar();
	return 0;
}