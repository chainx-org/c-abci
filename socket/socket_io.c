/*********************************************************************************************/
/*						socket_io.c Create by xuli on 2017/06/10                             */
/*	               	用于发送接收数据, 发送响应报文以及接收请求报文                           */
/*********************************************************************************************/

#include "socket_io.h"

int socket_read(struct tcp_socket *tsocket, char *buff, int len, int timeout)
{
	int cnt = 0;				/* 读取的总字节数 */
	int bytes = 0;				/* 本次读取的字节数 */
	struct timeval start = {};	
	struct timeval end = {};
	struct pollfd fds = {tsocket->fd, POLLIN};

	if ( tsocket->stat != FD_INIT || buff == NULL || len <= 0 )
	{
		tsocket->error = EINVAL;
		return -1;
	}

	if ( timeout > 0 )
		gettimeofday(&start, NULL);

	do 
	{
		bytes = read(tsocket->fd, &buff[cnt], len-cnt);
		if ( bytes < 0 && (errno != EAGAIN || errno != EWOULDBLOCK) )
		{
			tsocket->error = errno;
			return -1; /* fd为非阻塞模式 读取出错 */ 
		}
		else if ( bytes == 0 )
		{
		//	printf("对端已关闭Socket.\n");
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
					tsocket->error = ETIMEDOUT;
				else
					tsocket->error = errno;
				return -1;
			}
		}

	}while ( timeout > 0 || timeout == -1 );

	tsocket->error = EAGAIN; /* 非阻塞读取数据  数据未读完 */

	return -1;
}

int socket_send(struct tcp_socket *tsocket, const char *buff, int len, int timeout)
{
	int cnt = 0;				/* 已发送的总字节数 */
	int bytes = 0;				/* 本次发送的字节数 */
	struct timeval start = {};
	struct timeval end = {};
	struct pollfd fds = {tsocket->fd, POLLOUT};

	if ( tsocket->stat != FD_INIT || buff == NULL || len <= 0 )
	{
		tsocket->error = EINVAL;
		return -1;
	}

	if ( timeout > 0 )
		gettimeofday(&start, NULL);
	
	do 
	{
		bytes = write(tsocket->fd, &buff[cnt], len-cnt);
		if ( bytes < 0 && (errno != EAGAIN || errno != EWOULDBLOCK) )
		{
			tsocket->error = errno;
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
					tsocket->error = ETIMEDOUT;
				else
					tsocket->error = errno;
				return -1;
			}
		}

	}while ( timeout > 0 || timeout == -1 );

	tsocket->error = EAGAIN; /* 非堵塞发送数据，数据未发送完  */

	return -1;
}
