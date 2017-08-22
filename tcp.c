/*********************************************************************************************/
/*						tcp.c Create by XuLi on 2017/03/15                                   */
/*	         socket����ش�����������,��ָ��IP��ַ�˿��Լ�����������                     */
/*********************************************************************************************/
#include "tcp.h"

/* ����fd��ȡ���ص�IP��ַ�Ͷ˿���Ϣ */
static int _get_local_addrinfo(int fd, char *addr, size_t addrlen, uint16_t* port);

/* ����fd��ȡ�Զ˵�IP��ַ�Ͷ˿���Ϣ */
static int _get_peer_addrinfo(int fd, char *addr, size_t addrlen, uint16_t* port);

/* ����IP��ַ�Ͷ˿ڻ�ȡ��ַ����Ϣ bind: 'B'�����ȡ�ĵ�ַ�����ڶ˿ڰ󶨣�'C'�����ȡ�ĵ�ַ����Ϣ�������� */
static struct addrinfo *_get_family_addrinfo(const char *addr, const char *port, char bind);

/* �жϷ�����connect�Զ�ʱ�Ƿ����������ӳɹ� */
static int _is_connected(int fd, int timeout);


int socket_listen(struct tcp_socket *tsocket, const char *ipaddr, const char *port)
{
	int optval = SO_REUSEADDR;
	struct addrinfo *ai = NULL;
	struct addrinfo *aiptr = NULL;

	if ( tsocket == NULL || port == NULL )
		return -1;

	memset(tsocket, 0, sizeof(*tsocket));

	if ( (ai = _get_family_addrinfo(ipaddr, port, 'B')) == NULL)
	{
		tsocket->error = errno;
		return -1;
	}

	for ( aiptr = ai; aiptr != NULL; aiptr = aiptr->ai_next )
	{
		tsocket->fd = socket(aiptr->ai_family, aiptr->ai_socktype, aiptr->ai_protocol);
		if ( tsocket->fd == -1 )
			continue ;

		/* ����IP��ַ���ظ�ʹ�ñ�־ */
		if ( setsockopt(tsocket->fd, SOL_SOCKET, SO_REUSEADDR, &optval, (socklen_t)sizeof(int)) == 0 )
		{
			/* ��IP��ַ�˿� */
			if ( bind(tsocket->fd, aiptr->ai_addr, aiptr->ai_addrlen) == 0 )
			{
				if ( listen(tsocket->fd, LISTENFDS) == 0 )/* ����IP��ַ�˿� */
				{
					if ( fd_setopt(tsocket->fd, O_NONBLOCK) == 0 )/* ��fd����Ϊ������ģʽ */
						break ; /* �ɹ��˳� */
				}
				close(tsocket->fd);
				tsocket->fd = -1;
				break ; /* ʧ���˳� */
			}
		}
		/* ����IP��ַ��־ʧ�ܻ��IP��ַʧ��,������һ��IP��ַ */
		close(tsocket->fd);
		tsocket->fd = -1;
	}

	freeaddrinfo(ai);
	if ( tsocket->fd != -1 )
	{
		if ( _get_local_addrinfo(tsocket->fd, tsocket->localaddr, sizeof(tsocket->localaddr), &tsocket->localport) == 0 )
		{
			tsocket->type = TCP_BIND;
			tsocket->stat = FD_INIT;
			return 0 ;
		}
		else
		{
			close(tsocket->fd);
			tsocket->fd = -1;
		}
	}
	tsocket->error = errno;
	return -1;
}

int socket_connect(struct tcp_socket *tsocket, const char *ipaddr, const char *port, int timeout)
{
	struct addrinfo *ai = NULL;
	struct addrinfo *aiptr = NULL;
	struct timeval  start = {};
	struct timeval  end = {};

	if (tsocket == NULL || ipaddr == NULL || port == NULL )
		return -1;

	if ( timeout < 0 )
		timeout = CONNECTTIMEOUT;

	gettimeofday(&start, NULL);

	memset(tsocket, 0, sizeof(*tsocket));
	memcpy(tsocket->peeraddr, ipaddr, strlen(ipaddr));
	tsocket->peerport = atoi(port);

	if ( (ai = _get_family_addrinfo(ipaddr, port, 'C')) == NULL )
	{
		tsocket->error = errno;
		return -1;
	}

	for ( aiptr = ai; aiptr != NULL; aiptr = aiptr->ai_next )
	{
		tsocket->fd = socket(aiptr->ai_family, aiptr->ai_socktype, aiptr->ai_protocol);
		if ( tsocket->fd == -1 )
			continue ;

		if ( fd_setopt(tsocket->fd, O_NONBLOCK) == 0 )	/* ��tsocket fd����Ϊ������ģʽ����connect */
		{
			if ( connect(tsocket->fd, aiptr->ai_addr, aiptr->ai_addrlen) == 0 )
				break ; /* ���ӳɹ� */

			if (errno == EINPROGRESS || errno == EALREADY)/* �������ڽ����� �ж��Ƿ����ӳɹ� */
			{
				gettimeofday(&end, NULL);
				timeout -= ((end.tv_sec - start.tv_sec) * 1000) +  ((end.tv_usec - start.tv_usec) / 1000);
				if ( _is_connected(tsocket->fd, timeout) == 0 )
					break ; /* ���ӳɹ� */
			}
		}
		/* ���÷�����ģʽ������ʧ�ܣ���������һ����ַ */
		close(tsocket->fd);
		tsocket->fd = -1;
		gettimeofday(&end, NULL);
		timeout -= ((end.tv_sec - start.tv_sec) * 1000) +  ((end.tv_usec - start.tv_usec) / 1000);
		if ( timeout < 0 ) 
		{
			errno = ETIMEDOUT;
			close(tsocket->fd);
			tsocket->fd = -1;
			break ;/* ���ӳ�ʱʧ�ܷ��� */
		}
	}
	freeaddrinfo(ai);
	if ( tsocket->fd != -1 )
	{
		if ( _get_local_addrinfo(tsocket->fd, tsocket->localaddr, sizeof(tsocket->localaddr), &tsocket->localport) == 0 )
		{
			tsocket->type = TCP_CONNECT;
			tsocket->stat = FD_INIT;
			return 0 ;
		}
		else
		{
			close(tsocket->fd);
			tsocket->fd = -1;
		}
	}
	tsocket->error = errno;
	return -1;
}

int socket_accept(const struct tcp_socket *lsocket, struct tcp_socket *csocket)
{
	if ( lsocket == NULL || lsocket->stat != FD_INIT || csocket == NULL )
		return -1;

	memset(csocket, 0, sizeof(*csocket));
	csocket->fd = accept(lsocket->fd, NULL, NULL);
	if ( csocket->fd > 0 ) 
	{
		if ( fd_setopt(csocket->fd, O_NONBLOCK) == 0 )
		{
			if ( _get_local_addrinfo(csocket->fd, csocket->localaddr, sizeof(csocket->localaddr), &csocket->localport) == 0 )
			{
				if ( _get_peer_addrinfo(csocket->fd, csocket->peeraddr, sizeof(csocket->peeraddr), &csocket->peerport) == 0 )
				{
					csocket->type = TCP_ACCEPT;
					csocket->stat = FD_INIT;
					return 0;
				}
			}
		}
		close(csocket->fd);
		csocket->fd = -1;
	}
	csocket->error = errno;
	return -1;
}

int socket_close(struct tcp_socket *tsocket)
{
	int ret = 0;

	if ( tsocket == NULL || tsocket->stat != FD_INIT )
		return -1;

	ret = close(tsocket->fd);
	memset(tsocket, 0, sizeof(*tsocket));
	tsocket->fd = -1;

	if ( ret != 0 )
		tsocket->error = errno;

	return ret;
}

static int _get_local_addrinfo(int fd, char *addr, size_t addrlen, uint16_t *port)
{
	const char *pointer = NULL;
	struct sockaddr sockaddr = {};
	socklen_t skaddrlen = sizeof(sockaddr);

	if ( fd <= 0 || addr == NULL || port == NULL )
		return -1;
	
	if ( getsockname(fd, &sockaddr, &skaddrlen) == -1 )
		return -1;

	switch (sockaddr.sa_family)
	{
		case AF_INET:
		{
			struct sockaddr_in *inaddr = (struct sockaddr_in *)&sockaddr;
			pointer = inet_ntop(AF_INET, &inaddr->sin_addr, addr, addrlen);
			*port = ntohs(inaddr->sin_port);
		}
			break;
		case AF_INET6:
		{
			struct sockaddr_in6 *inaddr6 = (struct sockaddr_in6 *)&sockaddr;
			pointer = inet_ntop(AF_INET6, &inaddr6->sin6_addr, addr, addrlen);
			*port = ntohs(inaddr6->sin6_port);
		}
			break;
		case AF_UNIX:
		{
			struct sockaddr_un *unaddr = (struct sockaddr_un *)&sockaddr;
			sprintf(addr,  "%s", unaddr->sun_path);
			pointer = addr;
		}
			break;
		default:
			break;
	}

	return pointer != NULL ? 0 : -1;
}

static int _get_peer_addrinfo(int fd, char *addr, size_t addrlen, uint16_t *port)
{
	const char *pointer = NULL;
	struct sockaddr sockaddr = {};
	socklen_t skaddrlen = sizeof(sockaddr);

	if ( fd <= 0 || addr == NULL || port == NULL )
		return -1;

	if ( getpeername(fd, &sockaddr, &skaddrlen) == -1 )
		return -1;

	switch (sockaddr.sa_family)
	{
		case AF_INET:
		{
			struct sockaddr_in *inaddr = (struct sockaddr_in *)&sockaddr;
			pointer = inet_ntop(AF_INET, &inaddr->sin_addr, addr, addrlen);
			*port = ntohs(inaddr->sin_port);
		}
			break;
		case AF_INET6:
		{
			struct sockaddr_in6 *inaddr6 = (struct sockaddr_in6 *)&sockaddr;
			pointer = inet_ntop(AF_INET6, &inaddr6->sin6_addr, addr, addrlen);
			*port = ntohs(inaddr6->sin6_port);
		}
			break;
		case AF_UNIX:
		{
			struct sockaddr_un *unaddr = (struct sockaddr_un *)&sockaddr;
			sprintf(addr, "%s", unaddr->sun_path);
			pointer = addr;
		}
			break;
		default:
			break;
	}

	return pointer != NULL ? 0 : -1;
}

static struct addrinfo*  _get_family_addrinfo(const char *ipaddr, const char *port, char bind)
{
	int retval = -1;
	struct addrinfo *ai = NULL;
	struct addrinfo hints = {};

	if ( port == NULL )
		return NULL;

	if ( bind == 'B' )
		hints.ai_flags = AI_PASSIVE;
	else
		hints.ai_flags = AI_CANONNAME; /* ������������������ */

	hints.ai_family = AF_UNSPEC;	/* ����IPv4��IPv6����Э�� */
	hints.ai_socktype = SOCK_STREAM;/* TCPЭ�� */

	do 
	{
		retval = getaddrinfo(ipaddr, port, &hints, &ai);
		if ( retval == 0 )
			return ai;
		else if ( retval == EAI_AGAIN )
			continue;
		else 
			return NULL;
	} while (1);
}

static int _is_connected(int fd, int timeout)
{
	int    error = 0;
	int    errlen = 0;
	int    retval = -1;
	struct pollfd pollfd = {};

	if ( fd <= 0 )
		return -1;

	pollfd.fd = fd;
	pollfd.events = POLLIN | POLLOUT;

	retval = poll(&pollfd, 1, timeout);
	if ( retval > 0 )
	{
		if ( pollfd.revents & POLLERR ) /* ����ʱ�������� */
		{
			errno = EHOSTUNREACH;
			return -1;
		}

		retval = getsockopt(pollfd.fd, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&errlen);
		if ( retval == 0 && error == 0 )
			return 0;
		else if ( error == EHOSTUNREACH || errno == EHOSTUNREACH )
			errno = EHOSTUNREACH;
	}
	return -1;
}
