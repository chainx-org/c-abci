
#include "dummy.h"
#include <signal.h>


void kill_signal(int sig)
{
	destroy_dummy();
	server_stop();
	printf("Exit From C-ABCI Server\n");
	exit( 1 );
}

int main(int argc, char *argv[])
{
	char port[16] = {};
	char ipaddr[256] = {};

	signal(SIGTERM, kill_signal);   /* Ω” ’killall–≈∫≈ */

	if ( argc < 3 )
	{
		strcpy(ipaddr, "127.0.0.1");
		strcpy(port, "46658");
	}
	else
	{
		strcpy(ipaddr, argv[1]);
		strcpy(port, argv[2]);
	}

	init_dummy();

	server_init(ipaddr, port);

	Application app = ABCIApplication;

	server_start(app);

	server_stop();
}

