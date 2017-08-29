/*********************************************************************************************/
/*                    message.c Created by xuli on 2017/08/20                                */
/*                        本文件用于处理请求和应答报文                                       */
/*********************************************************************************************/
#include "message.h"

#if 0
int ToRequestEcho(const Types__Request *request)
{
}

int ToRequestFlush(const Types__Request *request, Types)
{
}

int ToRequestFlush(Types__Request *request)
{
}
#endif


int ToResponseEcho(const Types__Request *request, Types__Response *response)
{
	size_t size = 0;

	if ( request == NULL || response == NULL )
		return -1;

	response->value_case = TYPES__RESPONSE__VALUE_ECHO;
	response->echo = response_malloc_echo();
	if ( response->echo == NULL )
	{
		return -1;
	}

	size = types__request_echo__get_packed_size((const Types__RequestEcho*)response->echo);

	response->echo->message = (char *)malloc(size);

	if ( response->echo->message == NULL )
	{
		return -1;
	}
	memset(response->echo->message, 0, size);
	memcpy(response->echo->message, request->echo->message, size);

	return 0;
}

int ToResponseFlush(const Types__Request *request, Types__Response *response)
{
	if ( request == NULL || response == NULL )
		return -1;

	response->value_case = TYPES__RESPONSE__VALUE_FLUSH;
	response->flush = response_malloc_flush();
	if ( response->flush == NULL )
	{
		return -1;
	}

	return 0;
}

int ToResponseInfo(const Types__Request *request, Types__Response *response)
{
	if ( request == NULL || response == NULL )
		return -1;

	response->value_case = TYPES__RESPONSE__VALUE_INFO;
	response->info = response_malloc_info();
	if ( response->info == NULL )
	{
		return -1;
	}

	return 0;
}

int ToResponseSetOption(const Types__Request *request, Types__Response *response)
{
	if ( request == NULL || response == NULL )
		return -1;

	response->value_case = TYPES__RESPONSE__VALUE_SET_OPTION;
	response->set_option = response_malloc_setoption();
	if ( response->set_option == NULL )
	{
		return -1;
	}

	return 0;
}

int ToResponseDeliverTx(const Types__Request *request, Types__Response *response)
{
	if ( request == NULL || response == NULL )
		return -1;

	response->value_case = TYPES__RESPONSE__VALUE_DELIVER_TX;
	response->deliver_tx = response_malloc_delivertx();
	if ( response->deliver_tx == NULL )
	{
		return -1;
	}

	return 0;
}

int ToResponseCheckTx(const Types__Request *request, Types__Response *response)
{
	if ( request == NULL || response == NULL )
		return -1;

	response->value_case = TYPES__RESPONSE__VALUE_CHECK_TX;
	response->check_tx = response_malloc_checktx();
	if ( response->check_tx == NULL )
	{
		return -1;
	}

	return 0;
}

int ToResponseCommit(const Types__Request *request, Types__Response *response)
{
	if ( request == NULL || response == NULL )
		return -1;

	response->value_case = TYPES__RESPONSE__VALUE_COMMIT;
	response->commit = response_malloc_commit();
	if ( response->commit == NULL )
	{
		return -1;
	}

	return 0;
}

int ToResponseQuery(const Types__Request *request, Types__Response *response)
{
	if ( request == NULL || response == NULL )
		return -1;

	response->value_case = TYPES__RESPONSE__VALUE_QUERY;
	response->query = response_malloc_query();
	if ( response->query == NULL )
	{
		return -1;
	}

	return 0;
}

int ToResponseInitChain(const Types__Request *request, Types__Response *response)
{
	if ( request == NULL || response == NULL )
		return -1;

	response->value_case = TYPES__RESPONSE__VALUE_INIT_CHAIN;
	response->init_chain = response_malloc_initchain();
	if ( response->init_chain == NULL )
	{
		return -1;
	}

	return 0;
}

int ToResponseBeginBlock(const Types__Request *request, Types__Response *response)
{
	if ( request == NULL || response == NULL )
		return -1;

	response->value_case = TYPES__RESPONSE__VALUE_BEGIN_BLOCK;
	response->begin_block = response_malloc_beginblock();
	if ( response->begin_block == NULL )
	{
		return -1;
	}

	return 0;
}

int ToResponseEndBlock(const Types__Request *request, Types__Response *response)
{
	if ( request == NULL || response == NULL )
		return -1;

	response->value_case = TYPES__RESPONSE__VALUE_END_BLOCK;
	response->end_block = response_malloc_endblock();
	if ( response->end_block == NULL )
	{
		return -1;
	}

	return 0;
}

int ToResponseException(const Types__Request *request, Types__Response *response)
{
	if ( request == NULL || response == NULL )
		return -1;

	response->value_case = TYPES__RESPONSE__VALUE_EXCEPTION;
	response->exception = response_malloc_exception();
	if ( response->exception == NULL )
	{
		return -1;
	}

	return 0;
}
