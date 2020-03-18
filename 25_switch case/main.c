//测试后case中能否包含逻辑语句

//结论：不能包含逻辑语句

#include "stdint.h"
#include "stdio.h"

typedef struct _tcsr_table_t {
    /* upper limit of the temperature range */
    int8_t t_upper;
    /* lower limit of temperature range */
    int8_t t_lower;
    /* the compensation value corresponding to the temperature range */
    int16_t value;
} tcsr_table_t;

/* define number of temperature ranges */
#define IOT_PLC_HW_TSFM_TEMPERATURE_RANGE_NUM   15

/* temperature compensation table */
const static tcsr_table_t g_tcsr_table[IOT_PLC_HW_TSFM_TEMPERATURE_RANGE_NUM] = {
    //t-u t_l value
    {127, 85, 160},
    {85, 70, 150},
    {70, 65, 125},
    {65, 55, 100},
    {55, 50, 75},
    {50, 40, 50},
    {40, 25, 25},
    {25, 5, 0},
    {5, -5, -15},
    {-5, -15, -30},
    {-15, -20, -50},
    {-20, -30, -70},
    {-30, -35, -120},
    {-35, -40, -170},
    {-40, -127, -180}
};

void main()
{
    uint8_t test_num = 0;
    int32_t tpsd = 0;
    int16_t result = 0;
    uint8_t i = 0;
    while (1)
    {
        printf("enter test_num value:");

        // scanf("%d", &test_num);
        // printf("test_num is:%d \n", test_num);
        // switch (test_num)
        // {
        // case 45 <= test_num < 50:
        //     printf("45<= test_num < 50 \n");
        //     break;
        // case 35 <= test_num < 40:
        //     printf("35<= test_num < 40 \n");
        //     break;
        // case 25 <= test_num < 30:
        //     printf("25<= test_num < 30 \n");
        //     break;
        // case 15 <= test_num < 20:
        //     printf("15<= test_num < 20 \n");
        //     break;
        // case 5 <= test_num < 10:
        //     printf("5<= test_num < 10 \n");
        //     break;
        // default:
        //     printf("default\n");
        //     break;
        // }

        scanf("%d", &tpsd);
        printf("tpsd is:%d \n", tpsd);
        // if (85 <= tpsd) {
        //     result = 160;
        // } else if (70 <= tpsd && tpsd < 85) {
        //     result = 150;
        // } else if (65 <= tpsd && tpsd < 70) {
        //     result = 125;
        // } else if (55 <= tpsd && tpsd < 65) {
        //     result = 100;
        // } else if (50 <= tpsd && tpsd < 55) {
        //     result = 75;
        // } else if (40 <= tpsd && tpsd < 50) {
        //     result = 50;
        // } else if (25 <= tpsd && tpsd < 40) {
        //     result = 25;
        // } else if (5 <= tpsd && tpsd < 25) {
        //     result = 0;
        // } else if (-5 <= tpsd && tpsd < 5) {
        //     result = -15;
        // } else if (-15 <= tpsd && tpsd < -5) {
        //     result = -30;
        // } else if (-20 <= tpsd && tpsd < -15) {
        //     result = -50;
        // } else if (-30 <= tpsd && tpsd < -20) {
        //     result = -70;
        // } else if (-35 <= tpsd && tpsd < -30) {
        //     result = -120;
        // } else if (-40 <= tpsd && tpsd < -35) {
        //     result = -170;
        // } else if (tpsd < -40) {
        //     result = -180;
        // }
        for (i = 0; i < IOT_PLC_HW_TSFM_TEMPERATURE_RANGE_NUM; i++) {
            if (tpsd < g_tcsr_table[i].t_upper && tpsd >= g_tcsr_table[i].t_lower) {
                result = g_tcsr_table[i].value;
                break;
            }
        }
        if (i == IOT_PLC_HW_TSFM_TEMPERATURE_RANGE_NUM) {
            printf("error\n");
        }
        printf("get delta:%d\n", result);
    }

    getchar();
    return;
}
