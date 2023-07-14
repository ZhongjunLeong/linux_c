#ifndef __UART_H__
#define __UART_H__
#define _GNU_SOURCE     //在源文件开头定义_GNU_SOURCE宏

typedef struct uart_hardware_cfg {
    unsigned int baudrate;      /* 波特率 */
    unsigned char dbit;         /* 数据位 */
    char parity;                /* 奇偶校验 */
    unsigned char sbit;         /* 停止位 */
} uart_cfg_t;

/**
 ** 串口初始化操作
 ** 参数device表示串口终端的设备节点
 **/
int uart_init(const char *device);

/**
 ** 串口配置
 ** 参数cfg指向一个uart_cfg_t结构体对象
 **/
int uart_cfg(const uart_cfg_t *cfg);

/***
--dev=/dev/ttymxc2
--brate=115200
--dbit=8
--parity=N
--sbit=1
--type=read
***/
/**
 ** 打印帮助信息
 **/
void show_help(const char *app);

/**
 ** 信号处理函数，当串口有数据可读时，会跳转到该函数执行
 **/
void io_handler(int sig, siginfo_t *info, void *context);

/**
 ** 异步I/O初始化函数
 **/
void async_io_init(void);


#endif // !__UART_H__
