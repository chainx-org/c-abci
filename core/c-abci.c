
#include "c-abci.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


static struct socket_tcp LSOCKET;

static void wait_child(int sig);

int server_init(const char *ipaddr, const char *port)
{
	if ( socket_listen(&LSOCKET, ipaddr, port) == -1 )
	{
		printf("server initialization failed.error message:%s\n", strerror(LSOCKET.error));
		return -1;
	}

	printf("ABCI-Server Initialized Okay\n");

	return 0;
}


int server_start(Application app)
{
	pid_t  pid = 0;
	struct pollfd pollfd =  {};
	struct socket_tcp csocket = {};

	signal(SIGCHLD, wait_child);    /* 捕捉子进程退出信号 */

	pollfd.fd = LSOCKET.fd;
	pollfd.events = POLLIN;

	 while ( 1 )
    {
		if ( poll(&pollfd, 1, POLLTIMEOUT) <= 0 )
            continue ;

        if ( !(pollfd.revents & POLLIN) )
            continue ;

        if ( socket_accept(&LSOCKET, &csocket) == -1 )
			continue ;

		if ( (pid = fork()) < 0 ) /* 创建子进程失败 */
		{
			socket_close(&csocket);
			continue ;
		}

		if ( pid == 0 ) /* 子进程 */
		{
			socket_close(&LSOCKET);
			dispose_connect(&csocket, app);
			socket_close(&csocket);
			exit ( 0 );
		}

		/* 主进程 */
		printf("new 'ipaddress:%s port:%d' connected. fd:%d pid:%d to deal it\n", csocket.peeraddr, csocket.peerport, csocket.fd, pid);
		socket_close(&csocket);
	}
}

void server_stop()
{
	socket_close(&LSOCKET);
	printf("ABCI-Server Stopped Okay\n");
	return ;
}

static void wait_child(int sig)
{
	pid_t pid = 0;

	do{

		pid = waitpid(-1, NULL, WNOHANG);

	}while( pid > 0);
}
