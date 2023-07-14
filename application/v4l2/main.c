#include <stdio.h>
#include <stdlib.h>
#include "v4l2.h"

int main(int argc, char *argv[])
{
    if(2 != argc)
    {
        fprintf(stderr, "usage : %s<video_dev>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*初始化LCD*/
   if(0 > fb_dev_init())
   {
        printf("LCD init fail");
        exit(EXIT_FAILURE);
   }

    /*初始化摄像头*/
    if(0 > v4l2_dev_init(argv[1]))
    {
        printf("device init fail");
        exit(EXIT_FAILURE);
    }

    /*枚举所有格式并打印摄像头支持的分辨率及帧率*/
    if(0 > v4l2_enum_formats())
    {
        printf("enum formats fail");
        exit(EXIT_FAILURE);
    }
    if(0 > v4l2_print_formats())
    {
        printf("print formats fail");
        exit(EXIT_FAILURE);
    }

    /*设置格式*/
    if(0 > v4l2_set_format())
    {
        printf("set format fail");
        exit(EXIT_FAILURE);
    }

    /*初始化帧缓冲：申请、内存映射、入队*/
    if(0 > v4l2_init_buffer())
    {
        printf("init buffer fail");
        exit(EXIT_FAILURE);
    }

    /*开启视频采集*/
    if(0 > v4l2_stream_on())
    {
        printf("stream on fail");
        exit(EXIT_FAILURE);
    }

    /*读取数据：出队,在循环内采集数据将其显示在LCD*/
    if(0 > v4l2_read_data())
    {
        printf("read data fail");
        exit(EXIT_FAILURE);
    }

    exit(0);    
}