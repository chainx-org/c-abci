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
 * 填充Echo的响应报文
 * @request:请求报文
 * @response:响应报文，根据请求报文填充请求报文
 * @return:成功返回0 失败返回-1
 ************************************************************************************************/
int ToResponseEcho(const Types__Request *request, Types__Response *response);


/************************************************************************************************
 * 填充Flush的响应报文
 * @request:请求报文
 * @response:响应报文，填充响应报文中的Flush结构体
 * @return:成功返回0 失败返回-1
 ************************************************************************************************/
int ToResponseFlush(const Types__Request *request, Types__Response *response);


/************************************************************************************************
 * 填充Info的响应报文
 * @request:请求报文
 * @response:响应报文，将应用程序返回的Info结构体赋值给响应报文中的Info结构体
 * @info:应用程序返回的Info结构体
 * @return:成功返回0 失败返回-1
 ************************************************************************************************/
int ToResponseInfo(const Types__Request *request, Types__Response *response, Types__ResponseInfo *info);


/************************************************************************************************
 * 填充SetOption的响应报文
 * @request:请求报文
 * @response:响应报文，将应用程序返回的SetOption赋值给响应报文中的SetOption结构体
 * @setoption:应用程序返回的setoption结构体
 * @return:成功返回0 失败返回-1
 ************************************************************************************************/
int ToResponseSetOption(const Types__Request *request, Types__Response *response, Types__ResponseSetOption *setoption);


/************************************************************************************************
 * 填充DeliverTx的响应报文
 * @request:请求报文
 * @response:响应报文，将应用程序返回的DeliverTx赋值给响应报文中的DeliverTx结构体
 * @delivertx:应用程序返回的delivertx结构体
 * @return:成功返回0 失败返回-1
 ************************************************************************************************/
int ToResponseDeliverTx(const Types__Request *request, Types__Response *response, Types__ResponseDeliverTx *delivertx);


/************************************************************************************************
 * 填充CheckTx的响应报文
 * @request:请求报文
 * @response:响应报文，将应用程序返回的CheckTx赋值给响应报文中的CheckTx结构体
 * @checktx:应用程序返回的checktx结构体
 * @return:成功返回0 失败返回-1
 ************************************************************************************************/
int ToResponseCheckTx(const Types__Request *request, Types__Response *response, Types__ResponseCheckTx *checktx);


/************************************************************************************************
 * 填充Commit的响应报文
 * @request:请求报文
 * @response:响应报文，将应用程序返回的Commit赋值给响应报文中的Commit结构体
 * @commit:应用程序返回的commit结构体
 * @return:成功返回0 失败返回-1
 ************************************************************************************************/
int ToResponseCommit(const Types__Request *request, Types__Response *response, Types__ResponseCommit *commit);


/************************************************************************************************
 * 填充Query的响应报文
 * @request:请求报文
 * @response:响应报文，将应用程序返回的Query赋值给响应报文中的Query结构体
 * @query:应用程序返回的query结构体
 * @return:成功返回0 失败返回-1
 ************************************************************************************************/
int ToResponseQuery(const Types__Request *request, Types__Response *response, Types__ResponseQuery *query);


/************************************************************************************************
 * 填充InitChain的响应报文
 * @request:请求报文
 * @response:响应报文，将应用程序返回的InitChain赋值给响应报文中的InitChain结构体
 * @initchain:应用程序返回的initchain结构体
 * @return:成功返回0 失败返回-1
 ************************************************************************************************/
int ToResponseInitChain(const Types__Request *request, Types__Response *response, Types__ResponseInitChain *initchain);


/************************************************************************************************
 * 填充BeginBlock的响应报文
 * @request:请求报文
 * @response:响应报文，将应用程序返回的BeginBlock赋值给响应报文中的BeginBlock结构体
 * @beginblock:应用程序返回的beginblcok结构体
 * @return:成功返回0 失败返回-1
 ************************************************************************************************/
int ToResponseBeginBlock(const Types__Request *request, Types__Response *response, Types__ResponseBeginBlock *beginblock);


/************************************************************************************************
 * 填充EndBlock的响应报文
 * @request:请求报文
 * @response:响应报文，将应用程序返回的EndBlock赋值给响应报文中的EndBlock结构体
 * @endblock:应用程序返回的endblcok结构体
 * @return:成功返回0 失败返回-1
 ************************************************************************************************/
int ToResponseEndBlock(const Types__Request *request, Types__Response *response, Types__ResponseEndBlock *endblock);


/************************************************************************************************
 * 填充Exception的响应报文
 * @request:请求报文
 * @response:响应报文，请求异常，填充响应报文体中的Exception结构体
 * @return:成功返回0 失败返回-1
 ************************************************************************************************/
int ToResponseException(const Types__Request *request, Types__Response *response);

#endif
