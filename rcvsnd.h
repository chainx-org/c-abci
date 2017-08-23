#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <sys/time.h>


int recv_data(int fd, char *buff, int len, int timeout);

int send_data(int fd, const char *buff, int len, int timeout);
