#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uart.h"

int main(int argc, char *argv[])
{
    uart_cfg_t cfg = {0};
    char *device = NULL;
    int rw_flag = -1;
    unsigned char w_buf[10] = {0x11, 0x22, 0x33, 0x44,
                0x55, 0x66, 0x77, 0x88};    //通过串口发送出去的数据
    int n;

    /* 解析出参数 */
    for (n = 1; n < argc; n++) {

        if (!strncmp("--dev=", argv[n], 6))
            device = &argv[n][6];
        else if (!strncmp("--brate=", argv[n], 8))
            cfg.baudrate = atoi(&argv[n][8]);
        else if (!strncmp("--dbit=", argv[n], 7))
            cfg.dbit = atoi(&argv[n][7]);
        else if (!strncmp("--parity=", argv[n], 9))
            cfg.parity = argv[n][9];
        else if (!strncmp("--sbit=", argv[n], 7))
            cfg.sbit = atoi(&argv[n][7]);
        else if (!strncmp("--type=", argv[n], 7)) {
            if (!strcmp("read", &argv[n][7]))
                rw_flag = 0;        //读
            else if (!strcmp("write", &argv[n][7]))
                rw_flag = 1;        //写
        }
        else if (!strcmp("--help", argv[n])) {
            show_help(argv[0]); //打印帮助信息
            exit(EXIT_SUCCESS);
        }
    }

    if (NULL == device || -1 == rw_flag) {
        fprintf(stderr, "Error: the device and read|write type must be set!\n");
        show_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    /* 串口初始化 */
    if (uart_init(device))
        exit(EXIT_FAILURE);

    /* 串口配置 */
    if (uart_cfg(&cfg)) {
        tcsetattr(fd, TCSANOW, &old_cfg);   //恢复到之前的配置
        close(fd);
        exit(EXIT_FAILURE);
    }

    /* 读|写串口 */
    switch (rw_flag) {
    case 0:  //读串口数据
        async_io_init();	//我们使用异步I/O方式读取串口的数据，调用该函数去初始化串口的异步I/O
        for ( ; ; )
            sleep(1);   	//进入休眠、等待有数据可读，有数据可读之后就会跳转到io_handler()函数
        break;
    case 1:   //向串口写入数据
        for ( ; ; ) {   		//循环向串口写入数据
            write(fd, w_buf, 8); 	//一次向串口写入8个字节
            sleep(1);       		//间隔1秒钟
        }
        break;
    }

    /* 退出 */
    tcsetattr(fd, TCSANOW, &old_cfg);   //恢复到之前的配置
    close(fd);
    exit(EXIT_SUCCESS);
}
