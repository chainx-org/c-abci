/*********************************************************************************************/
/*						rcvsnd.c Create by XuLi on 2017/03/09                                */
/*	               	���ڷ��ͽ�������, ������Ӧ�����Լ�����������                           */
/*********************************************************************************************/
#include "rcvsnd.h"

int recv_data(int fd, char *buff, int len, int timeout)
{
	int cnt = 0;				/* ��ȡ�����ֽ��� */
	int bytes = 0;				/* ���ζ�ȡ���ֽ��� */
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
			return -1; /* fdΪ������ģʽ ��ȡ���� */ 
		}
		else if ( bytes == 0 )
		{
			printf("�Զ��ѹر�Socket.\n");
			return 0; /* �Զ��ѹر� */
		}
		
		if ( bytes > 0 ) /* �ɹ���ȡ������ */
		{
			if ( (cnt += bytes) == len ) /* �ж������Ƿ��Ѿ�������� */
				return cnt;
		}

		if ( timeout > 0 )
		{
			gettimeofday(&end, NULL);
			timeout -= ((end.tv_sec - start.tv_sec) * 1000) +  ((end.tv_usec - start.tv_usec) / 1000);
		}

		/* ����δ���������δ��ʱ ��poll�ȴ����¼������� */
		if ( timeout > 0 || timeout == -1 )
		{
			if ( poll(&fds, 1, timeout) <= 0 ) /* ��ʱ������� */
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
	int cnt = 0;				/* �ѷ��͵����ֽ��� */
	int bytes = 0;				/* ���η��͵��ֽ��� */
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
			return -1; /* fdΪ������ģʽ д���ݳ��� */ 
		}
		
		if ( bytes > 0 )/* �ɹ��������� */
		{
			/* ���ݷ������ */
			if ( (cnt += bytes) == len )
				return cnt; 
		}

		if ( timeout > 0 )
		{
			gettimeofday(&end, NULL);
			timeout -= ((end.tv_sec - start.tv_sec) * 1000) +  ((end.tv_usec - start.tv_usec) / 1000);
		}

		/* ����δ���������δ��ʱ ��poll�ȴ�д�¼������� */
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
