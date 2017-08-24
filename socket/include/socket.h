/*********************************************************************************************/
/*                   socket.h Created by xuli on 2017/05/10                                  */
/*          ע:���е�socket fd���Ѿ����ó��˷�����ģʽ[���ļ���������tcp socket]             */
/*********************************************************************************************/

#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <netdb.h>
#include <unistd.h>
#include <poll.h>
#include <errno.h>
#include <fcntl.h>

#define MAXIPADDRLEN	128     	/* ����IP��ַ���ĳ��� */
#define LISTENFDS	   (1024*10)   	/* �����ȴ����е���󳤶� */
#define CONNECTTIMEOUT (1000*5)     /* Ĭ�ϵ����ӳ�ʱʱ�� ��λ:ms */


/* �׽��������Ϣ�ṹ�� */
struct tcp_socket
{
	int      fd;						/* socket fd */	
	uint16_t localport;					/* ���ض˿� */	
	uint16_t peerport;					/* �Զ˶˿� */	
	char     localaddr[MAXIPADDRLEN];	/* ����IP��ַ */
	char     peeraddr[MAXIPADDRLEN];	/* �Զ�IP��ַ */
	enum
	{
		TCP_CONNECT = 0x01,
		TCP_BIND,
		TCP_ACCEPT
	}type;		/* socket������ */	
	enum
	{
		FD_INIT = 0x01,
		FD_READ,
		FD_WRITE,
		FD_CLOSE
	}stat;		/* socket״̬ */
	int error;	/* socketִ��ʧ�ܴ�����(��Linuxϵͳ������һ��) */
};


/************************************************************************************************
 * �󶨺ͼ���һ��IP��ַ�˿�
 * @tsocket:����������ɱ��������ṹ��ֵ
 * @ipaddr:���󶨼����ı���IP��ַ(NULL����󶨵ĵ�ַΪINADDR_ANY)
 * @port:���󶨼����ı���IP�˿�
 * @return: �ɹ�����0��ʧ�ܷ���-1(����������tsocket->error)
 ************************************************************************************************/
int socket_listen(struct tcp_socket *tsocket, const char *ipaddr, const char *port);


/************************************************************************************************
 * ���ӵ�һ��IP��ַ�˿�,ʹ�÷������ķ�ʽconnect�Զˣ������ó�ʱʱ��
 * @tsocket:����������ɱ��������ṹ��ֵ
 * @ipaddr:Ҫ���ӵĶԶ�IP��ַ
 * @port:Ҫ���ӵĶԶ�IP�˿�
 * @timeout:���ӶԶ˳�ʱ���� <0:ʹ��Ĭ�ϳ�ʱʱ�� 0:���������ӶԶ� >0:���ó�ʱ���� [��λ:ms]
 * @return: �ɹ�����0��ʧ�ܷ���-1(����������tsocket->error)
 ************************************************************************************************/
int socket_connect(struct tcp_socket *tsocket, const char *ipaddr, const char *port, int timeout);


/************************************************************************************************
 * �ڼ�����socket�Ͻ����¿ͻ��˵�����
 * @lsocket:�����������������socket								[l:listen]
 * @csocket:������������յ����¿ͻ���socket���ɱ��������ṹ��ֵ  [c:client]
 * @return: �ɹ�����0��ʧ�ܷ���-1(����������csocket->error)
 ************************************************************************************************/
int socket_accept(const struct tcp_socket *lsocket, struct tcp_socket *csocket);


/************************************************************************************************
 * �ر�һ���׽���
 * @tsocket:���ر��׽��ֵĽṹ��
 * @return: �ɹ�����0��ʧ�ܷ���-1(����������tsocket->error)
 ************************************************************************************************/
int socket_close(struct tcp_socket *tsocket);

/************************************************************************************************
 * ����fd�ı�־
 * @fd:�����õ�fd
 * @flag:�����õı�־ֵ
 * @return: �ɹ�����0��ʧ�ܷ���-1
 ************************************************************************************************/
static inline int fd_setopt(int fd, int flag)
{
	int retval = -1;

	retval = fcntl(fd, F_GETFL, NULL);
	if ( retval !=  -1 )
	{
		retval |= flag;
		retval = fcntl(fd, F_SETFL, retval);
	}
	return retval;
}

#endif	/* ifndef __TCP_H__ */
