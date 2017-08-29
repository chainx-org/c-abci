/*********************************************************************************************/
/*                    message.h Created by xuli on 2017/08/20                                */
/*                           ���ļ����������Ӧ����                                        */
/*********************************************************************************************/
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <stdlib.h>
#include <string.h>
#include "types.pb-c.h"
#include "response_struct.h"

/************************************************************************************************
 * ���Echo����ķ���ֵ
 * @
 * @
 * @return:�ɹ�����0 ʧ�ܷ���-1
 ************************************************************************************************/
int ToResponseEcho(const Types__Request *request, Types__Response *response);

int ToResponseFlush(const Types__Request *request, Types__Response *response);

int ToResponseInfo(const Types__Request *request, Types__Response *response);

int ToResponseSetOption(const Types__Request *request, Types__Response *response);

int ToResponseDeliverTx(const Types__Request *request, Types__Response *response);

int ToResponseCheckTx(const Types__Request *request, Types__Response *response);

int ToResponseCommit(const Types__Request *request, Types__Response *response);

int ToResponseQuery(const Types__Request *request, Types__Response *response);

int ToResponseInitChain(const Types__Request *request, Types__Response *response);

int ToResponseBeginBlock(const Types__Request *request, Types__Response *response);

int ToResponseEndBlock(const Types__Request *request, Types__Response *response);

int ToResponseException(const Types__Request *request, Types__Response *response);

#endif
