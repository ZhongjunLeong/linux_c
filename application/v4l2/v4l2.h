#ifndef __V4L2_H__
#define __V4L2_H__

#define FB_DEV  "/dev/fb0"  //LCD设备节点
#define FRAMEBUFFER_COUNT   3   //帧缓冲数量

/*初始化LCD*/
int fb_dev_init(void);

/*初始化摄像头*/
int v4l2_dev_init(const char *);

/*枚举所有格式并打印摄像头支持的分辨率及帧率*/
int v4l2_enum_formats(void);
int v4l2_print_formats(void);

/*设置格式*/
int v4l2_set_format(void);

/*初始化帧缓冲：申请、内存映射、入队*/
int v4l2_init_buffer(void);

/*开启视频采集*/
int v4l2_stream_on(void);

/*读取数据：出队,在循环内采集数据将其显示在LCD*/
int v4l2_read_data(void);

#endif // !V4L2_H__
