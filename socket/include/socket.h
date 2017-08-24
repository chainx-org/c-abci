/*********************************************************************************************/
/*                   socket.h Created by xuli on 2017/05/10                                  */
/*          注:所有的socket fd都已经设置成了非阻塞模式[本文件仅适用于tcp socket]             */
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

#define MAXIPADDRLEN	128     	/* 允许IP地址最大的长度 */
#define LISTENFDS	   (1024*10)   	/* 监听等待队列的最大长度 */
#define CONNECTTIMEOUT (1000*5)     /* 默认的连接超时时间 单位:ms */


/* 套接字相关信息结构体 */
struct tcp_socket
{
	int      fd;						/* socket fd */	
	uint16_t localport;					/* 本地端口 */	
	uint16_t peerport;					/* 对端端口 */	
	char     localaddr[MAXIPADDRLEN];	/* 本地IP地址 */
	char     peeraddr[MAXIPADDRLEN];	/* 对端IP地址 */
	enum
	{
		TCP_CONNECT = 0x01,
		TCP_BIND,
		TCP_ACCEPT
	}type;		/* socket的类型 */	
	enum
	{
		FD_INIT = 0x01,
		FD_READ,
		FD_WRITE,
		FD_CLOSE
	}stat;		/* socket状态 */
	int error;	/* socket执行失败错误码(与Linux系统错误码一致) */
};


/************************************************************************************************
 * 绑定和监听一个IP地址端口
 * @tsocket:输出参数，由本函数填充结构体值
 * @ipaddr:待绑定监听的本端IP地址(NULL代表绑定的地址为INADDR_ANY)
 * @port:待绑定监听的本端IP端口
 * @return: 成功返回0，失败返回-1(错误码存放在tsocket->error)
 ************************************************************************************************/
int socket_listen(struct tcp_socket *tsocket, const char *ipaddr, const char *port);


/************************************************************************************************
 * 连接到一个IP地址端口,使用非阻塞的方式connect对端，可设置超时时间
 * @tsocket:输出参数，由本函数填充结构体值
 * @ipaddr:要连接的对端IP地址
 * @port:要连接的对端IP端口
 * @timeout:连接对端超时设置 <0:使用默认超时时间 0:不阻塞连接对端 >0:设置超时连接 [单位:ms]
 * @return: 成功返回0，失败返回-1(错误码存放在tsocket->error)
 ************************************************************************************************/
int socket_connect(struct tcp_socket *tsocket, const char *ipaddr, const char *port, int timeout);


/************************************************************************************************
 * 在监听的socket上接收新客户端的请求
 * @lsocket:输入参数，待监听的socket								[l:listen]
 * @csocket:输出参数，接收到的新客户端socket，由本函数填充结构体值  [c:client]
 * @return: 成功返回0，失败返回-1(错误码存放在csocket->error)
 ************************************************************************************************/
int socket_accept(const struct tcp_socket *lsocket, struct tcp_socket *csocket);


/************************************************************************************************
 * 关闭一个套接字
 * @tsocket:待关闭套接字的结构体
 * @return: 成功返回0，失败返回-1(错误码存放在tsocket->error)
 ************************************************************************************************/
int socket_close(struct tcp_socket *tsocket);

/************************************************************************************************
 * 设置fd的标志
 * @fd:待设置的fd
 * @flag:需设置的标志值
 * @return: 成功返回0，失败返回-1
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
