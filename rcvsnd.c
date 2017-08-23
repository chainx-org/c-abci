/*********************************************************************************************/
/*						rcvsnd.c Create by XuLi on 2017/03/09                                */
/*	               	用于发送接收数据, 发送响应报文以及接收请求报文                           */
/*********************************************************************************************/
#include "rcvsnd.h"

int recv_data(int fd, char *buff, int len, int timeout)
{
	int cnt = 0;				/* 读取的总字节数 */
	int bytes = 0;				/* 本次读取的字节数 */
	struct timeval start = {};	
	struct timeval end = {};
	struct pollfd fds = {fd, POLLIN};

	if ( buff == NULL || fd <= 0 || len <= 0 )
		return -1;

	if ( timeout > 0 )
		gettimeofday(&start, NULL);

	do 
	{
		bytes = read(fd, &buff[cnt], len-cnt);
		if ( bytes < 0 && (errno != EAGAIN || errno != EWOULDBLOCK) )
		{
			printf("receive data error:%d error message:%s\n", errno, strerror(errno));
			return -1; /* fd为非阻塞模式 读取出错 */ 
		}
		else if ( bytes == 0 )
		{
			printf("对端已关闭Socket.\n");
			return 0; /* 对端已关闭 */
		}
		
		if ( bytes > 0 ) /* 成功读取到数据 */
		{
			if ( (cnt += bytes) == len ) /* 判断数据是否已经接受完毕 */
				return cnt;
		}

		if ( timeout > 0 )
		{
			gettimeofday(&end, NULL);
			timeout -= ((end.tv_sec - start.tv_sec) * 1000) +  ((end.tv_usec - start.tv_usec) / 1000);
		}

		/* 数据未接收完毕且未超时 则poll等待读事件被触发 */
		if ( timeout > 0 || timeout == -1 )
		{
			if ( poll(&fds, 1, timeout) <= 0 ) /* 超时或出错返回 */
			{
				if ( errno == 0 )
					printf("receive data error timeout.\n");
				else
					printf("receive data error: %d error message:%s\n", errno, strerror(errno));
				return -1;
			}
		}

	}while ( timeout > 0 || timeout == -1 );

	return -1;
}

int send_data(int fd, const char *buff, int len, int timeout)
{
	int cnt = 0;				/* 已发送的总字节数 */
	int bytes = 0;				/* 本次发送的字节数 */
	struct timeval start = {};
	struct timeval end = {};
	struct pollfd fds = {fd, POLLOUT};

	if ( buff == NULL || fd <= 0 || len <= 0 )
		return -1;

	if ( timeout > 0 )
		gettimeofday(&start, NULL);
	
	do 
	{
		bytes = write(fd, &buff[cnt], len-cnt);
		if ( bytes < 0 && (errno != EAGAIN || errno != EWOULDBLOCK) )
		{
			printf("send data error:%d error message:%s\n", errno, strerror(errno));
			return -1; /* fd为非阻塞模式 写数据出错 */ 
		}
		
		if ( bytes > 0 )/* 成功发送数据 */
		{
			/* 数据发送完毕 */
			if ( (cnt += bytes) == len )
				return cnt; 
		}

		if ( timeout > 0 )
		{
			gettimeofday(&end, NULL);
			timeout -= ((end.tv_sec - start.tv_sec) * 1000) +  ((end.tv_usec - start.tv_usec) / 1000);
		}

		/* 数据未接收完毕且未超时 则poll等待写事件被触发 */
		if ( timeout > 0 || timeout == -1 )
		{
			if (  poll(&fds, 1, timeout) <= 0 )
			{
				if ( errno ==  0)
					printf("send data error timeout.\n");
				else
					printf("send data error:%d error message:%s\n", errno, strerror(errno));
				return -1;
			}
		}

	}while ( timeout > 0 || timeout == -1 );

	return -1;
}
