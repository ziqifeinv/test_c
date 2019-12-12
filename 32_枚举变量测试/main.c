#include <stdio.h>

typedef enum {
    MODEL_NORMAL = 0,
    MODEL_WAKEUP,
    MODEL_LOW_POWER,
    MODEL_SLEEP
} module_model;

enum {
    ACTION_SET = 0,
    ACTION_SEND,
    ACTION_REC
} action_num;

int main()
{
    uint32_t model = 0xff;
    uint32_t act = 0xff;
    printf("1: model:%d, act:%d \n",model,act);
    model = MODEL_SLEEP;
    act = ACTION_REC;
    printf("2: model:%d, act:%d \n",model,act);
    
    getchar();
    return 0;
}