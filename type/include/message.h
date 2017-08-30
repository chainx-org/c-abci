/*********************************************************************************************/
/*                    message.h Created by xuli on 2017/08/20                                */
/*                           本文件处理请求和应答报文                                        */
/*********************************************************************************************/
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <stdlib.h>
#include <string.h>
#include "types.pb-c.h"
#include "response_struct.h"

/************************************************************************************************
 * 填充Echo请求的返回值
 * @
 * @
 * @return:成功返回0 失败返回-1
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
