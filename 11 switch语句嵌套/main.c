
//结论：

#include <stdio.h>
#include "main.h"

typedef enum _xing {
	zhao = 1,
	qian = 2,
	sun = 3,
	li = 4,
}xing;

typedef enum _ming {
	yi = 1,
	er = 2,
	san = 3,
	si = 4,
}ming;

int main()
{

	xing xing1 = li;
	ming ming1 = si;

	switch (xing1)
	{
	case zhao:
		break;
	case qian:
		break;
	case sun:
		break;
	case li:
		switch (ming1)
		{
		case yi:
			break;
		case er:
			break;
		case san:
			break;
		case si:
			printf("测试成功，switch能嵌套！");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	getchar();
	return 0;
}