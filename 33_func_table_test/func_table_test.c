#include <stdio.h>
#include <stdlib.h>
#include "func_table_test.h"

int func_init(int pib);
int func_ready();
int func_ready();
void func_timer_handle(int timer_id);
int func_write(char *buf, int length);
int func_read(char *buf, int length);

iot_cus_ports_api_t g_func_table = {
    .pid = 22,
    .p_init = func_init,
    .p_ready = func_ready,
    .p_timer = func_timer_handle,
    .p_write = func_write,
    .p_read = func_read,
};

int func_init(int pib)
{
    printf("enter %s \n", __FUNCTION__);
    printf("%s, pib1:%d \n", __FUNCTION__, g_func_table.pid);
    g_func_table.pid = pib;
    printf("%s, pib2:%d \n", __FUNCTION__, g_func_table.pid);
    return pib;
}

int func_ready()
{
    printf("enter %s \n", __FUNCTION__);
    return 1;
}

void func_timer_handle(int timer_id)
{
    printf("enter %s \n", __FUNCTION__);
    printf("%s, timer id:%d \n", __FUNCTION__, timer_id);
}

int func_write(char *buf, int length)
{
    printf("enter %s \n", __FUNCTION__);
    (void)buf;
    (void)length;
    return 1;
}

int func_read(char *buf, int length)
{
    printf("enter %s \n", __FUNCTION__);
    (void)buf;
    (void)length;
    return 1;
}

int main()
{
    char test[100] = {0};
    int length = 50;
    g_func_table.p_init(11);
    g_func_table.p_read(test,length);
    g_func_table.p_ready();
    g_func_table.p_timer(22);
    g_func_table.p_write(test,length);
    printf("pib:%d \n",g_func_table.pid);
    getchar();
    return 1;
}