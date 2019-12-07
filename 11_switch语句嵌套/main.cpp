
//½áÂÛ£º
#define CPP 0

#if CPP
#include <iostream>
#else
#include <stdio.h>
#endif

typedef enum _xing {
	zhao = 1,
	qian = 2,
	sun = 3,
	li = 4,
};

typedef enum _ming {
	yi = 1,
	er = 2,
	san = 3,
	si = 4,
};

int main()
{
#if CPP
	using namespace std;
#endif
	_xing xing = li;
	_ming ming = si;

	switch (xing)
	{
	case zhao:
		break;
	case qian:
		break;
	case sun:
		break;
	case li:
		printf("test start!");
		break;
	default:
		break;
	}
	char a = getchar();
	return 0;
}