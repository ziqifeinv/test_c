#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* 数据重叠大小 */
#define OVERLAP_LEN         0
/* 每次fft计算的点数 */
#define FFT_NUM             256
/* 每一个bit持续时间 */
#define BIT_DURATION        600 //ms
/* adc采样频率 */
#define SAMPLING_FREQUENCY  12800
/* 重叠后每一段中新包含的数据大小 */
#define PER_SEGMENT_NUM     (FFT_NUM - OVERLAP_LEN)
/* 每次多送给算法的数据 */
#define REDUNDANT_DATA      (5 + 256)
/* 定义能量值最小阈值 */
#define DATA_MIN_LEN        2
#define SUM_BUFFER_SIZE     (30 * 4)

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

void sum_move(uint32_t *sample_data, uint16_t data_len,
    uint16_t moveLen, uint32_t *res)
{
    int32_t buff[moveLen];
    uint16_t idx = 0;
    int32_t sum = 0;

    for (uint16_t i = 0; i < moveLen; i++) {
        buff[i] = sample_data[i];
        sum += buff[i];
    }
    res[0] = sum;
    for (uint16_t j = moveLen; j < data_len; j++) {
        idx = j % (moveLen);
        sum += sample_data[j] - buff[idx];
        buff[idx] = sample_data[j];
        res[j - moveLen] = sum;
    }
}

uint32_t decision(uint32_t *data, uint32_t len, uint8_t *result)
{
    uint32_t sliding_window = BIT_DURATION * SAMPLING_FREQUENCY / PER_SEGMENT_NUM / 1000;
    static uint32_t sliding_win_buffer[30];
    uint32_t flag = 0;
    static uint32_t index = 0;
    static uint32_t energy_max = 0, energy_min = 0;
    static uint8_t bit_counter = {0};
    static uint8_t start_sum_move_flag = 0;
    uint32_t sum_move_value = 0;
//    uint32_t sum_buffer[sliding_window * 16];
    static uint32_t threshold = 0, threshold_last = 0, threshold_ave;
    uint32_t i = 0, j = 0;
    static uint32_t sum_buffer[SUM_BUFFER_SIZE] = {0};
    static uint8_t index_sum = 0;
    static uint32_t sum_max_temp = 0;
    static uint8_t start_find_bit = 0;
    static uint8_t index_focus = 0;
    static uint8_t curr_bit = 1, next_bit = 0;

//    os_mem_set(sliding_win_buffer, 0, sliding_window * 4);
    // printf("sliding window:%d\n", sliding_window);

    for (i = 0; i < len; i++) {
        // printf("%d, ", data[i]);
        if (start_sum_move_flag == 0) {
            sliding_win_buffer[index] = data[i];
            index++;
            if (index == (sliding_window - 1)) {
                start_sum_move_flag = 1;
            }
        } else {
            //sum move
            sliding_win_buffer[index] = data[i];
            index++;
            if (index == sliding_window) {
                index = 0;
            }
            sum_move(sliding_win_buffer, sliding_window, sliding_window, &sum_move_value);
            // printf("decision sum move value:%d\t, threshold:%d\n", sum_move_value, threshold);
            // printf("%d, ", sum_move_value);

            if (start_find_bit == 0) {
                sum_buffer[index_sum] = sum_move_value;
                index_sum++;
                if (index_sum == (SUM_BUFFER_SIZE)) {
                    for (j = 0; j < (SUM_BUFFER_SIZE - 1); j++) {
                        energy_max = max(sum_buffer[j], sum_buffer[j+1]);
                        // energy_min = min(sum_buffer[j], sum_buffer[j+1]);
                    }
                    // threshold = (energy_max - energy_min) / 2;
                    threshold = (energy_max - threshold_ave) / 2;
                    if (threshold == 0) {
                        index_sum = 0;
                        continue;
                    }
                    if (threshold >= 2 * threshold_last) {
                        start_find_bit = 1;
                        for (j = 0; j < (SUM_BUFFER_SIZE); j++) {
                            if (sum_buffer[j] <= threshold && sum_buffer[j + 1] >= threshold) {
                                printf("\nfind first focus, threshold:%d, sum:%d - %d\n",
                                    threshold, sum_buffer[j], sum_buffer[j +1]);
                                curr_bit = 1;
                                next_bit = 0;
                                break;
                            }
                        }
                        memcpy(sum_buffer, &sum_buffer[j], ((SUM_BUFFER_SIZE - j) * 4));
                        index_sum = SUM_BUFFER_SIZE - j;
                    } else {
                        threshold_last = threshold;
                        threshold_ave = (threshold_ave + threshold) / 2;
                        index_sum = 0;
                    }
                }
            } else {
                sum_buffer[index_sum] = sum_move_value;
                index_sum++;
                if (index_sum == SUM_BUFFER_SIZE) {
                    for (j = 2; j < SUM_BUFFER_SIZE; j++) {
                        if (next_bit) { //next bit is 0
                            if (sum_buffer[j] <= threshold && sum_buffer[j + 1] >= threshold) {
                                index_focus = j;
                            } else {
                                continue;
                            }
                        } else {
                            if (sum_buffer[j] >= threshold && sum_buffer[j + 1] <= threshold) {
                                index_focus = j;
                            } else {
                                continue;
                            }
                        }

                        uint8_t delta = index_focus;
                        //判断有多少个bit
                        uint8_t bit_num = delta / 30 + ((delta % 30 > 15) ? 1 : 0);
                        if (bit_num == 0) {
                            printf("\nfind bad focus\n");
                            continue;
                        }
                        while (bit_num)
                        {
                            result[bit_counter / 8] = (result[bit_counter / 8] << 1) | curr_bit;
                            bit_counter++;
                            bit_num--;
                        }
                        printf("\nfind focus, delta:%d, bit_num:%d, data:%x, %x, %x\n",
                            delta, bit_num, result[0], result[1], result[2]);
                        curr_bit = (curr_bit == 0) ? 1 : 0;
                        next_bit = (next_bit == 0) ? 1 : 0;
                        break;
                    }
                    memcpy(sum_buffer, &sum_buffer[j], (SUM_BUFFER_SIZE - j) * 4);
                    index_sum = SUM_BUFFER_SIZE - j;

                    if (bit_counter >= DATA_MIN_LEN * 8) {
                        flag = 1;
                        printf("get complete data, and reset buffer\n");
                        memset(sum_buffer, 0, SUM_BUFFER_SIZE * 4);
                        index_sum = 0;
                    }
                }
            }
        }
    }

    return flag;
}

#define G_ENERGY_NUM    (22 + 12)
uint32_t g_energy_value[G_ENERGY_NUM][26] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //附加一组无效数据
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //附加一组无效数据
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //附加一组无效数据
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //附加一组无效数据
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //附加一组无效数据
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //附加一组无效数据
    {0, 0, 0, 0, 40, 0, 0, 0, 0, 0, 20, 20, 0, 0, 0, 0, 0, 40, 60, 40, 40, 40, 40, 40, 60, 60},
    {40, 60, 60, 40, 20, 60, 40, 60, 20, 20, 20, 60, 60, 0, 40, 20, 40, 60, 60, 0, 40, 40, 20, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 0, 0, 0, 20, 0, 0, 0, 0, 0, 20, 0, 0, 0},
    {0, 20, 40, 40, 60, 60, 0, 40, 40, 60, 40, 60, 60, 40, 40, 0, 40, 40, 60, 60, 40, 0, 60, 40, 40, 40},
    {60, 60, 40, 60, 60, 40, 40, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 0, 0, 20, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 40, 40, 60, 60, 60, 40, 40, 60, 40, 40, 40, 20, 0, 0},
    {40, 60, 40, 40, 20, 40, 20, 60, 0, 40, 40, 60, 40, 60, 40, 60, 60, 40, 0, 0, 0, 0, 20, 40, 0, 0},
    {40, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 20, 0, 40, 40},
    {40, 60, 40, 60, 0, 0, 0, 60, 40, 40, 40, 40, 40, 40, 40, 40, 40, 0, 20, 0, 0, 60, 60, 40, 60, 60},
    {60, 40, 40, 0, 0, 20, 0, 0, 0, 0, 0, 0, 20, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 40},
    {0, 0, 0, 20, 0, 0, 20, 40, 40, 40, 40, 40, 60, 40, 0, 40, 40, 0, 60, 60, 40, 60, 40, 60, 60, 60},
    {60, 40, 60, 40, 0, 0, 40, 60, 40, 60, 0, 20, 60, 40, 40, 60, 60, 20, 60, 40, 60, 60, 0, 0, 40, 60},
    {40, 60, 60, 40, 60, 60, 40, 60, 0, 60, 60, 60, 40, 40, 60, 40, 0, 60, 0, 40, 40, 60, 40, 60, 60, 40},
    {40, 0, 0, 0, 0, 60, 60, 60, 40, 60, 60, 60, 40, 60, 60, 60, 60, 40, 60, 20, 60, 40, 40, 0, 0, 0},
    {0, 0, 0, 0, 0, 40, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 40, 40, 40, 40, 40, 0, 40, 40, 60, 60, 60, 0, 40, 40, 60, 40, 60, 40, 0, 0, 0, 0, 20, 0, 0},
    {40, 60, 40, 20, 40, 40, 60, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 40, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 40, 40, 60, 60, 40, 60, 60, 40, 20},
    {40, 60, 60, 0, 0, 0, 60, 40, 40, 0, 0, 0, 60, 60, 40, 60, 0, 0, 40, 40, 20, 40, 20, 0, 0, 0},
    {0, 20, 0, 0, 0, 0, 0, 0, 20, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 40, 0, 0, 0, 40, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //附加一组无效数据
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //附加一组无效数据
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //附加一组无效数据
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //附加一组无效数据
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //附加一组无效数据
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //附加一组无效数据
};
uint32_t g_energy_value_2[G_ENERGY_NUM][25] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //附加一组无效数据
    {0, 0, 0, 0, 40, 0, 0, 0, 0, 0, 20, 20, 0, 0, 0, 0, 0, 40, 60, 40, 40, 40, 40, 40, 60},
    {40, 60, 60, 40, 20, 60, 40, 60, 20, 20, 20, 60, 60, 0, 40, 20, 40, 60, 60, 0, 40, 40, 20, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 0, 0, 0, 20, 0, 0, 0, 0, 0, 20, 0, 0},
    {0, 20, 40, 40, 60, 60, 0, 40, 40, 60, 40, 60, 60, 40, 40, 0, 40, 40, 60, 60, 40, 0, 60, 40, 40},
    {60, 60, 40, 60, 60, 40, 40, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 0, 0, 20, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 40, 40, 60, 60, 60, 40, 40, 60, 40, 40, 40, 20, 0},
    {40, 60, 40, 40, 20, 40, 20, 60, 0, 40, 40, 60, 40, 60, 40, 60, 60, 40, 0, 0, 0, 0, 20, 40, 0},
    {40, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 20, 0, 40},
    {40, 60, 40, 60, 0, 0, 0, 60, 40, 40, 40, 40, 40, 40, 40, 40, 40, 0, 20, 0, 0, 60, 60, 40, 60},
    {60, 40, 40, 0, 0, 20, 0, 0, 0, 0, 0, 0, 20, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20},
    {0, 0, 0, 20, 0, 0, 20, 40, 40, 40, 40, 40, 60, 40, 0, 40, 40, 0, 60, 60, 40, 60, 40, 60, 60},
    {60, 40, 60, 40, 0, 0, 40, 60, 40, 60, 0, 20, 60, 40, 40, 60, 60, 20, 60, 40, 60, 60, 0, 0, 40}
};
int main(void)
{
    uint8_t data_valid[5] = {0};
    uint32_t segment = 26;

    for (uint8_t j = 0; j < G_ENERGY_NUM; j++) {
        decision(g_energy_value[j], segment, data_valid);
    }

    return 0;
}