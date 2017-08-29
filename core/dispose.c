
#include "common.h"

static int handle_response(struct socket_tcp *tsocket, Types__Response *response);

static int handle_request(Application app, Types__Request *request, Types__Response *response, size_t size);


int dispose_connect(struct socket_tcp *tsocket, Application app)
{
	size_t size = 0;
	size_t bytes = 0;
	size_t length = 0;
	struct pollfd pollfd =  {};

	pollfd.fd = tsocket->fd;
	pollfd.events = POLLIN;

	while( 1 )
	{
		if ( poll(&pollfd, 1, POLLTIMEOUT) <= 0 )
            continue ;

        if ( !(pollfd.revents & POLLIN) )
            continue ;

		uint8_t *data = NULL;
		Types__Request *request = NULL;
		Types__Response response = {};

		length = readsize(tsocket, READTIMEOUT);
		if ( length < 1 )
		{
			printf("socket closed or receive data error. fd:%d\n", tsocket->fd);
			return -1;
		}

	    data = (uint8_t*)malloc(length);
		if ( data == NULL )
		{
			printf("no more memory, malloc error.");
			return -1;
		}
		memset(data, 0, sizeof(length));

		bytes = socket_read(tsocket, data, length, READTIMEOUT);
		if ( bytes != length )
		{
			return -1;
		}

		types__response__init(&response);
		request = types__request__unpack(NULL, length, data);
		free(data);
		size = types__request__get_packed_size(request);
		printf("request:length:%lu size:%lu", length, size);

		handle_request(app, request, &response, length);

		handle_response(tsocket, &response);

		types__request__free_unpacked(request, NULL);
	}
	return 0;
}

static int handle_request(Application app, Types__Request *request, Types__Response *response, size_t size)
{
	switch( request->value_case )
	{
		case TYPES__REQUEST__VALUE_ECHO:
			printf("TYPES__REQUEST__VALUE_ECHO\n");
			ToResponseEcho(request, response);
			break ;
		case TYPES__REQUEST__VALUE_FLUSH:
			printf("TYPES__REQUEST__VALUE_FLUSH:\n");
			ToResponseFlush(request, response);
			break ;
		case TYPES__REQUEST__VALUE_INFO:
			printf("TYPES__REQUEST__VALUE_INFO\n");
			ToResponseInfo(request, response);
			app(request, response);
			break ;
		case TYPES__REQUEST__VALUE_SET_OPTION:
			printf("TYPES__REQUEST__VALUE_OPTION\n");
			ToResponseSetOption(request, response);
			app(request, response);
			
			break ;
		case TYPES__REQUEST__VALUE_DELIVER_TX:
			printf("TYPES__REQUEST__VALUE_DELIVER_TX\n");
			ToResponseDeliverTx(request, response);
			app(request, response);
			break ;
		case TYPES__REQUEST__VALUE_CHECK_TX:
			printf("TYPES__REQUEST__VALUE_CHECK_TX\n");
			ToResponseCheckTx(request, response);
			app(request, response);
			break ;
		case TYPES__REQUEST__VALUE_COMMIT:
			printf("TYPES__REQUEST__VALUE_COMMIT\n");
			ToResponseCommit(request, response);
			app(request, response);
			break ;
		case TYPES__REQUEST__VALUE_QUERY:
			printf("TYPES__REQUEST__VALUE_QUERY\n");
			ToResponseQuery(request, response);
			app(request, response);
			break ;
		case TYPES__REQUEST__VALUE_INIT_CHAIN:
			printf("TYPES__REQUEST__VALUE_INIT_CHAIN\n");
			ToResponseInitChain(request, response);
			app(request, response);
			break ;
		case TYPES__REQUEST__VALUE_BEGIN_BLOCK:
			printf("TYPES__REQUEST__VALUE_BEGIN_BLOCK\n");
			ToResponseBeginBlock(request, response);
			app(request, response);
			break ;
		case TYPES__REQUEST__VALUE_END_BLOCK:
			printf("TYPES__REQUEST__VALUE_END_BLOCK\n");
			ToResponseEndBlock(request, response);
			app(request, response);
			break ;
		default:
			printf("TYPES__REQUEST__VALUE__NOT_SET\n");
			ToResponseException(request, response);
			return -1;
	}
	return 0;
}

static int handle_response(struct socket_tcp *tsocket, Types__Response *response)
{
	size_t size = 0;
	size_t bytes = 0;
	uint8_t data[1024] = {};

	size = types__response__pack(response, data);

//	size = types__response__get_packed_size(response);
	printf("fd:%d send value_case:%d send size:%lu\n", tsocket->fd, response->value_case, size);

	if ( sendsize(tsocket, size, SENDTIMEOUT) == -1 )
		return -1;

	bytes = socket_send(tsocket, data, size, SENDTIMEOUT);
	if ( bytes != size )
	{
		printf("send data failed.\n");
	}

	switch( response->value_case )
	{
		case TYPES__RESPONSE__VALUE_ECHO:
			response_free_echo(response->echo);
			break ;
		case TYPES__RESPONSE__VALUE_FLUSH:
			response_free_flush(response->flush);
		//	flush();
			break ;
		case TYPES__RESPONSE__VALUE_INFO:
			response_free_info(response->info);
			break ;
		case TYPES__RESPONSE__VALUE_SET_OPTION:
			response_free_setoption(response->set_option);
			break ;
		case TYPES__RESPONSE__VALUE_DELIVER_TX:
			response_free_delivertx(response->deliver_tx);
			break ;
		case TYPES__RESPONSE__VALUE_CHECK_TX:
			response_free_checktx(response->check_tx);
			break ;
		case TYPES__RESPONSE__VALUE_COMMIT:
			response_free_commit(response->commit);
			break ;
		case TYPES__RESPONSE__VALUE_QUERY:
			response_free_query(response->query);
			break ;
		case TYPES__RESPONSE__VALUE_INIT_CHAIN:
			response_free_initchain(response->init_chain);
			break ;
		case TYPES__RESPONSE__VALUE_BEGIN_BLOCK:
			response_free_beginblock(response->begin_block);
			break ;
		case TYPES__RESPONSE__VALUE_END_BLOCK:
			response_free_endblock(response->end_block);
			break ;
		case TYPES__RESPONSE__VALUE_EXCEPTION:
			response_free_exception(response->exception);
		default:
			return -1;
	}

	return 0;
}
