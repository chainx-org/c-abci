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
 * ���Echo����Ӧ����
 * @request:������
 * @response:��Ӧ���ģ��������������������
 * @return:�ɹ�����0 ʧ�ܷ���-1
 ************************************************************************************************/
int ToResponseEcho(const Types__Request *request, Types__Response *response);


/************************************************************************************************
 * ���Flush����Ӧ����
 * @request:������
 * @response:��Ӧ���ģ������Ӧ�����е�Flush�ṹ��
 * @return:�ɹ�����0 ʧ�ܷ���-1
 ************************************************************************************************/
int ToResponseFlush(const Types__Request *request, Types__Response *response);


/************************************************************************************************
 * ���Info����Ӧ����
 * @request:������
 * @response:��Ӧ���ģ���Ӧ�ó��򷵻ص�Info�ṹ�帳ֵ����Ӧ�����е�Info�ṹ��
 * @info:Ӧ�ó��򷵻ص�Info�ṹ��
 * @return:�ɹ�����0 ʧ�ܷ���-1
 ************************************************************************************************/
int ToResponseInfo(const Types__Request *request, Types__Response *response, Types__ResponseInfo *info);


/************************************************************************************************
 * ���SetOption����Ӧ����
 * @request:������
 * @response:��Ӧ���ģ���Ӧ�ó��򷵻ص�SetOption��ֵ����Ӧ�����е�SetOption�ṹ��
 * @setoption:Ӧ�ó��򷵻ص�setoption�ṹ��
 * @return:�ɹ�����0 ʧ�ܷ���-1
 ************************************************************************************************/
int ToResponseSetOption(const Types__Request *request, Types__Response *response, Types__ResponseSetOption *setoption);


/************************************************************************************************
 * ���DeliverTx����Ӧ����
 * @request:������
 * @response:��Ӧ���ģ���Ӧ�ó��򷵻ص�DeliverTx��ֵ����Ӧ�����е�DeliverTx�ṹ��
 * @delivertx:Ӧ�ó��򷵻ص�delivertx�ṹ��
 * @return:�ɹ�����0 ʧ�ܷ���-1
 ************************************************************************************************/
int ToResponseDeliverTx(const Types__Request *request, Types__Response *response, Types__ResponseDeliverTx *delivertx);


/************************************************************************************************
 * ���CheckTx����Ӧ����
 * @request:������
 * @response:��Ӧ���ģ���Ӧ�ó��򷵻ص�CheckTx��ֵ����Ӧ�����е�CheckTx�ṹ��
 * @checktx:Ӧ�ó��򷵻ص�checktx�ṹ��
 * @return:�ɹ�����0 ʧ�ܷ���-1
 ************************************************************************************************/
int ToResponseCheckTx(const Types__Request *request, Types__Response *response, Types__ResponseCheckTx *checktx);


/************************************************************************************************
 * ���Commit����Ӧ����
 * @request:������
 * @response:��Ӧ���ģ���Ӧ�ó��򷵻ص�Commit��ֵ����Ӧ�����е�Commit�ṹ��
 * @commit:Ӧ�ó��򷵻ص�commit�ṹ��
 * @return:�ɹ�����0 ʧ�ܷ���-1
 ************************************************************************************************/
int ToResponseCommit(const Types__Request *request, Types__Response *response, Types__ResponseCommit *commit);


/************************************************************************************************
 * ���Query����Ӧ����
 * @request:������
 * @response:��Ӧ���ģ���Ӧ�ó��򷵻ص�Query��ֵ����Ӧ�����е�Query�ṹ��
 * @query:Ӧ�ó��򷵻ص�query�ṹ��
 * @return:�ɹ�����0 ʧ�ܷ���-1
 ************************************************************************************************/
int ToResponseQuery(const Types__Request *request, Types__Response *response, Types__ResponseQuery *query);


/************************************************************************************************
 * ���InitChain����Ӧ����
 * @request:������
 * @response:��Ӧ���ģ���Ӧ�ó��򷵻ص�InitChain��ֵ����Ӧ�����е�InitChain�ṹ��
 * @initchain:Ӧ�ó��򷵻ص�initchain�ṹ��
 * @return:�ɹ�����0 ʧ�ܷ���-1
 ************************************************************************************************/
int ToResponseInitChain(const Types__Request *request, Types__Response *response, Types__ResponseInitChain *initchain);


/************************************************************************************************
 * ���BeginBlock����Ӧ����
 * @request:������
 * @response:��Ӧ���ģ���Ӧ�ó��򷵻ص�BeginBlock��ֵ����Ӧ�����е�BeginBlock�ṹ��
 * @beginblock:Ӧ�ó��򷵻ص�beginblcok�ṹ��
 * @return:�ɹ�����0 ʧ�ܷ���-1
 ************************************************************************************************/
int ToResponseBeginBlock(const Types__Request *request, Types__Response *response, Types__ResponseBeginBlock *beginblock);


/************************************************************************************************
 * ���EndBlock����Ӧ����
 * @request:������
 * @response:��Ӧ���ģ���Ӧ�ó��򷵻ص�EndBlock��ֵ����Ӧ�����е�EndBlock�ṹ��
 * @endblock:Ӧ�ó��򷵻ص�endblcok�ṹ��
 * @return:�ɹ�����0 ʧ�ܷ���-1
 ************************************************************************************************/
int ToResponseEndBlock(const Types__Request *request, Types__Response *response, Types__ResponseEndBlock *endblock);


/************************************************************************************************
 * ���Exception����Ӧ����
 * @request:������
 * @response:��Ӧ���ģ������쳣�������Ӧ�������е�Exception�ṹ��
 * @return:�ɹ�����0 ʧ�ܷ���-1
 ************************************************************************************************/
int ToResponseException(const Types__Request *request, Types__Response *response);

#endif
