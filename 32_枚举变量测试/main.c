#include <stdio.h>

#define HW_VERSION_GS_NO_IPD_STA       0x01030101
#define HW_VERSION_GS_NO_IPD_STA_3P    0x01020101   //cco is same as this

#define HW_VERSION_BRMT_I3C_V1         0X480A0104   //72.10.01.04
#define HW_VERSION_BRMT_I3C_V1_3       0x480D0304   //72.13.03.04
#define HW_VERSION_BRMT_I3C_V1_5       0x480F0104   //72.15.01.04
#define HW_VERSION_BRMT_I3C_V2_0       0x48140104   //72.20.01.04

/* define the hardware version number of the old version of PW CCO module,
 * the module has stopped production. The definition here is only for
 * compatibility consideration
 */
#define HW_VERSION_CCO_PW_V1           0x4B0B0204   //75.11.02.04
#define HW_VERSION_CCO_PW_V2           0x4B0C0104   //75.12.01.04
#define HW_VERSION_CCO_PW_V3           0x4B0D0104   //75.13.01.04
/* The hardware version number of 6 pass zero detection GPIO . */
#define HW_VERSION_CCO_6_ZC            0x330A0100   //51.10.01.00
/* define the hardware version number of new CCO V1 version of USB (FT232) */
#define HW_VERSION_CCO_USB_V1          0x1F0A0100   //31.10.01.00

/* define iic (psram) hardware version */
#define HW_VERSION_IIC_PSRAM           0x3D0A0108   //61.10.01.08
/* define iic (extern flash) hardware version */
#define HW_VERSION_IIC_FLASH_EXT       0x3E140200   //62.20.02.00

typedef enum {
    MODEL_NORMAL = 0,
    MODEL_WAKEUP,
    MODEL_LOW_POWER,
    MODEL_SLEEP
} module_model;

enum {
    ACTION_SET = 0,
    ACTION_SEND = 8,
    ACTION_REC = 7,
    ACTION_MAX = 5
} action_num;

int main()
{
    uint32_t model = 0xff;
    uint32_t act = 0xff;
    printf("1: model:%d, act:%d \n",model,act);
    model = MODEL_SLEEP;
    act = ACTION_MAX;
    printf("2: model:%d, act:%d \n",model,act);

    getchar();
    return 0;
}