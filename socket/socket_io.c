/*********************************************************************************************/
/*						socket_io.c Create by xuli on 2017/06/10                             */
/*	               	���ڷ��ͽ�������, ������Ӧ�����Լ�����������                           */
/*********************************************************************************************/

#include "socket_io.h"

int socket_read(struct tcp_socket *tsocket, char *buff, int len, int timeout)
{
	int cnt = 0;				/* ��ȡ�����ֽ��� */
	int bytes = 0;				/* ���ζ�ȡ���ֽ��� */
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
			return -1; /* fdΪ������ģʽ ��ȡ���� */ 
		}
		else if ( bytes == 0 )
		{
		//	printf("�Զ��ѹر�Socket.\n");
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
					tsocket->error = ETIMEDOUT;
				else
					tsocket->error = errno;
				return -1;
			}
		}

	}while ( timeout > 0 || timeout == -1 );

	tsocket->error = EAGAIN; /* ��������ȡ����  ����δ���� */

	return -1;
}

int socket_send(struct tcp_socket *tsocket, const char *buff, int len, int timeout)
{
	int cnt = 0;				/* �ѷ��͵����ֽ��� */
	int bytes = 0;				/* ���η��͵��ֽ��� */
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
					tsocket->error = ETIMEDOUT;
				else
					tsocket->error = errno;
				return -1;
			}
		}

	}while ( timeout > 0 || timeout == -1 );

	tsocket->error = EAGAIN; /* �Ƕ����������ݣ�����δ������  */

	return -1;
}
