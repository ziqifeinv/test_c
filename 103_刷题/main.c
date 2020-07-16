#include <stdio.h>

int func_1()
{
    char str1[] = "12345";
    char str2[] = "67";
    char *p1 = str1, *p2 = str2;
    while (*p1++ = *p2++) //先赋值，再判断左值
    {
        printf("%s", str1); //打印整个字符串
    }
    printf("\n");
    return 0;
}

 int func_2()
 {
     union a
     {
         int i;
         char ch[2];
     };

     union a u;
     u.ch[0] = 3;
     u.ch[1] = 2;
     printf("ch0:%d, ch1:%d, i:%d\n", u.ch[0],u.ch[1], u.i);
     return 0;
 }

int main()
{
    func_2();

    return 0;
}