
#ifndef __C_ABCI_H__
#define __C_ABCI_H__

#include "common.h"

/* �ص�Ӧ�õĺ���ԭ�� */
//typedef int (*Application)(Types__Request *, Types__Response *);

int server_init(const char *ipaddr, const char *port);

int server_start(Application app);

void server_stop();

#endif
