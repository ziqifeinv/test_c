//验证读写指针重叠时，buffer满和空判断

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define ERR_OK 0
#define ERR_FAIL 1
#define RING_SIZE 20
#define R_W_BUF_SIZE 5
#define WRITE_FLAG 0
#define READ_FLAG 1

typedef struct _ring_t
{
    uint8_t *data;
    uint32_t size; //real length
    uint32_t r;
    uint32_t w;
} ring_t;

ring_t g_ring = {0};
uint8_t data_buffer[RING_SIZE] = {0};

uint8_t ring_init(ring_t *ring)
{
    // uint8_t *temp = malloc(RING_SIZE + 1);
    // if (temp == NULL)
    // {
    //     printf("%s malloc memory failen \n", __FUNCTION__);
    //     return ERR_FAIL;
    // }
    // ring->data = temp;
    ring->data = data_buffer;
    ring->r = ring->w = 0;
    ring->size = RING_SIZE;
    return ERR_OK;
}

uint32_t ring_remain(ring_t *ring, uint8_t flag)
{
    assert(ring);
    uint32_t remain_len = 0;
    printf("atc:%s, ",(flag == READ_FLAG ? "read" : "write"));
    if (ring->w >= ring->r)
    {
        remain_len = ring->size - (ring->w - ring->r);
        printf("%s, remain len:%d, w >= r, w:%d, r:%d \n", __FUNCTION__, remain_len, ring->w, ring->r);
    }
    else
    {
        remain_len = ring->r - ring->w;
        printf("%s, remain len:%d, w < r, w:%d, r:%d \n", __FUNCTION__, remain_len, ring->w, ring->r);
    }
    return remain_len;
}

uint32_t write(ring_t *ring, uint8_t *data, uint32_t len)
{
    assert(ring && data);
    uint32_t remain_len = ring_remain(ring, WRITE_FLAG) - 1;
    if (remain_len < len)
    {
        printf("%s, buffer is full, remain len:%d w:%d, r:%d \n",
               __FUNCTION__, remain_len, ring->w, ring->r);
        return ERR_FAIL;
    }

    uint32_t temp_len = ring->size - ring->w;
    if (temp_len >= len)
    {
        memcpy(&ring->data[ring->w], data, len);
        ring->w += len;
        if (ring->w == ring->size)
        {
            ring->w = 0;
        }
    }
    else
    {
        memcpy(&ring->data[ring->w], data, temp_len);
        memcpy(&ring->data[0], &data[temp_len], len - temp_len);
        ring->w = len - temp_len;
    }
    return ERR_OK;
}

uint32_t read(ring_t *ring, uint8_t *data, uint32_t len)
{
    assert(ring && data);
    uint32_t remain_len = ring_remain(ring, READ_FLAG);
    uint32_t buffer_used = ring->size - remain_len;
    if (buffer_used == 0) {
        printf("%s, buffer is empty, remain len:%d w:%d, r:%d \n",
               __FUNCTION__, remain_len, ring->w, ring->r);
    }
    uint32_t read_len = buffer_used >= len ? len : buffer_used;
    if (ring->r + read_len <= ring->size)
    {
        memcpy(data, &ring->data[ring->r], read_len);
        ring->r += read_len;
        if (ring->r == ring->size)
        {
            ring->r = 0;
        }
    }
    else
    {
        uint32_t temp_len = ring->size - ring->r;
        memcpy(data, &ring->data[ring->r], temp_len);
        memcpy(&data[temp_len], &ring->data[0], read_len - temp_len);
        ring->r = read_len - temp_len;
    }
}

void data_dump(uint8_t *data, uint32_t len, uint8_t flag)
{
    printf("%s data, len:%d: ", (flag ? "read" : "write"), len);
    for (uint32_t i = 0; i < len; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int main()
{
    uint8_t ret = ERR_FAIL;
    uint8_t buffer_w[R_W_BUF_SIZE] = {0x1, 0x2, 0x3, 0x4, 0x5};
    uint8_t buffer_r[R_W_BUF_SIZE] = {0};

    ret = ring_init(&g_ring);
    printf("init ring %s \n", (ret == ERR_OK) ? "succeed" : "failed");

    for (uint32_t i = 0; i < 10000; i++)
    {
        for(uint8_t w = 0; w < 3; w++) 
        {
            write(&g_ring, buffer_w, R_W_BUF_SIZE);
        }
        for(uint8_t w = 0; w < 1; w++) 
        {
            read(&g_ring, buffer_r, R_W_BUF_SIZE);
        }
        
        
        // data_dump(buffer_r,R_W_BUF_SIZE,READ_FLAG);
    }
    getchar();
    return 0;
}