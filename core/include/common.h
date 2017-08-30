
#ifndef __COMMON_H__
#define __COMMON_H__

#include "message.h"
#include "bits.h"
#include "bigEndian.h"
#include "socket_tcp.h"
#include "socket_io.h"
#include "response_struct.h"

#define POLLTIMEOUT  5000   /* 单位:ms */
#define READTIMEOUT  1000   /* 单位:ms */
#define SENDTIMEOUT  1000   /* 单位:ms*/

typedef void* (*Application)(Types__Request *);

size_t readsize(struct socket_tcp *tsocket, int timeout);

size_t sendsize(struct socket_tcp *tsocket, size_t length, int timeout);

int dispose_connect(struct socket_tcp *tsocket, Application app);

#endif
