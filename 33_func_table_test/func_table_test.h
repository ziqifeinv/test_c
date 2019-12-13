/**
 * @brief fn_init() - Initialize the port.
 * @param pid: port id.
 * @return ERR_FAIL -- Operation failed.
 * @return ERR_OK -- Operation Successful.
 */
typedef int (*fn_init)(int pid);

/**
 * @brief fn_ready() - Get status of port.
 * @return 1 -- port is ready.
 * @return 0 -- port is not ready.
 */
typedef  int (*fn_ready)(void);

/**
 * @brief fn_timer() - every XXX ms, this handler will be called.
 * @param t_time: delta time in ms.
 */
typedef  void (*fn_timer)(int t_time);

/**
 * @brief fn_write() - write data to the port.
 * @param buf: pointer of buffer.
 * @param length: count of bytes to write.
 * @return -- count of bytes was written.
 */
typedef int (*fn_write)(char *buf, int length);

/**
 * @brief fn_read() - read data from the port.
 * @param buf: pointer of buffer.
 * @param length: count of bytes to read.
 * @return -- count of bytes was read.
 */
typedef int (*fn_read)(char *buf, int length);

/**
 * @brief iot_cus_ports_event_post() - post events to cus-task.
 * @param pid: pid of this port.
 * @param events: event to post.
 */
void iot_cus_ports_event_post(int pid, int events);

/**
 * @brief struct _iot_cus_ports_api_t - APIs defination for port driver.
 */
typedef struct _iot_cus_ports_api_t {
    int         pid;
    fn_init     p_init;
    fn_ready    p_ready;
    fn_timer    p_timer;
    fn_write    p_write;
    fn_read     p_read;
} iot_cus_ports_api_t;