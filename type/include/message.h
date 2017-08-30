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

int ToResponseInfo(const Types__Request *request, Types__Response *response, Types__ResponseInfo *info);

int ToResponseSetOption(const Types__Request *request, Types__Response *response, Types__ResponseSetOption *setoption);

int ToResponseDeliverTx(const Types__Request *request, Types__Response *response, Types__ResponseDeliverTx *delivertx);

int ToResponseCheckTx(const Types__Request *request, Types__Response *response, Types__ResponseCheckTx *checktx);

int ToResponseCommit(const Types__Request *request, Types__Response *response, Types__ResponseCommit *commit);

int ToResponseQuery(const Types__Request *request, Types__Response *response, Types__ResponseQuery *query);

int ToResponseInitChain(const Types__Request *request, Types__Response *response, Types__ResponseInitChain *initchain);

int ToResponseBeginBlock(const Types__Request *request, Types__Response *response, Types__ResponseBeginBlock *beginblock);

int ToResponseEndBlock(const Types__Request *request, Types__Response *response, Types__ResponseEndBlock *endblock);

int ToResponseException(const Types__Request *request, Types__Response *response);

#endif
