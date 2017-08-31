
#include "dummy.h"
#include "util.h"

#define VERSION "1.0.0"
#define HASHLEN 8

static Types__ResponseInfo *Info()
{
	Types__ResponseInfo *info = NULL;
	info = response_malloc_info();
	if ( info == NULL )
	{
		return NULL;
	}
	info->version = (char*)malloc(strlen(VERSION));
	if ( info->version == NULL)
	{
		response_free_info(info);
		return NULL;
	}
	info->has_last_block_height = 1;
	info->last_block_height = get_height();
	if ( info->last_block_height > 0 )
	{
		uint8_t *hash = NULL;
		info->has_last_block_app_hash = 1;
		hash = get_last_app_hash();
		info->last_block_app_hash.data = (uint8_t*)malloc(HASHLEN);
		if ( info->last_block_app_hash.data == NULL )
		{
			response_free_info(info);
			return NULL;
		}
		info->last_block_app_hash.len = HASHLEN;
		memcpy(info->last_block_app_hash.data, hash, HASHLEN);
	}
	else
	{
		info->has_last_block_height = 0;
		info->has_last_block_app_hash = 0;
	}

	return info;
}

static Types__ResponseDeliverTx *DeliverTx(Types__RequestDeliverTx *req)
{
	int *cols = 0;
	char *log = NULL;
	uint8_t *hash = NULL;
	uint8_t words[2][64] = {};

	Types__CodeType code = 0;
	Types__ResponseDeliverTx *deliver_tx = NULL;

	if ( req->has_tx )
	{
		cols = getcols(req->tx.data, (uint8_t)'=', words);
		if ( cols[0] == 2 )
		{
			printf("set two\n");
			code = set_state(words[0], words[1], req->tx.data, cols[1], cols[2], req->tx.len);
		}
		else
		{
			printf("set one\n");
			code = set_state(words[0], words[0], req->tx.data, cols[1], cols[1], req->tx.len);
		}
	}

	deliver_tx = response_malloc_delivertx();
	if ( deliver_tx == NULL )
	{
		return NULL;
	}
	deliver_tx->has_code = 1;
	deliver_tx->code = code;

	if ( code != TYPES__CODE_TYPE__OK )
		log = "InternalError";
	else
		log = "OK";

	deliver_tx->log = (char*)malloc(strlen(log));
	if ( deliver_tx->log == NULL )
	{
		response_free_delivertx(deliver_tx);
		return NULL;
	}
	memcpy(deliver_tx->log, log, strlen(log));

	hash = get_last_app_hash();
	if ( hash != NULL )
	{
		deliver_tx->has_data = 1;
		deliver_tx->data.data = (uint8_t*)malloc(HASHLEN);
		if ( deliver_tx->data.data == NULL )
		{
			response_free_delivertx(deliver_tx);
			return NULL;
		}
		deliver_tx->data.len = HASHLEN;
		memcpy(deliver_tx->data.data, hash, HASHLEN);
	}

	return deliver_tx;
}

static Types__ResponseCheckTx *CheckTx(Types__RequestCheckTx *req)
{
	uint8_t *log = NULL;
	uint8_t *hash = NULL;
	Types__CodeType code = 0;
	Types__ResponseCheckTx *checktx = NULL;

	if ( req->has_tx )
	{
		code = check_transation(req->tx.data);
	}

	checktx = response_malloc_checktx();
	if ( checktx == NULL )
	{
		return NULL;
	}
	checktx->has_code = 1;
	checktx->code = code;

	if ( code != TYPES__CODE_TYPE__OK )
		log = "InternalError";
	else
		log = "OK";

	checktx->log =(char*)malloc(strlen(log));
	if ( checktx->log == NULL )
	{
		response_free_checktx(checktx);
		return NULL;
	}
	memcpy(checktx->log, log, strlen(log));

	checktx->has_data = 1;
	hash = get_last_app_hash();
	if ( hash != NULL )
	{
		checktx->data.data =(uint8_t*)malloc(HASHLEN);
		if ( checktx->data.data == NULL )
		{
			response_free_checktx(checktx);
			return NULL;
		}
		memcpy(checktx->data.data, hash, HASHLEN);
		checktx->data.len = HASHLEN;
	}

	return checktx;
}

static Types__ResponseCommit *Commit()
{
	uint8_t *log = "OK";
	uint8_t *hash = NULL;
	//Types__CodeType code = 0;
	Types__ResponseCommit *commit = NULL;

	commit = response_malloc_commit();
	if ( commit == NULL )
	{
		return NULL;
	}
	commit->has_code = 1;
	commit->code = TYPES__CODE_TYPE__OK ;

	commit->log = (char*)malloc(strlen(log));
	if ( commit->log == NULL )
	{
		response_free_commit(commit);
		return NULL;
	}
	memcpy(commit->log, log, strlen(log));

	if ( get_height() > 0 )
	{
		commit->has_data = 1;
		hash = get_last_app_hash();
		commit->data.data = (uint8_t*)malloc(HASHLEN);
		if ( commit->data.data == NULL )
		{
			response_free_commit(commit);
			return NULL;
		}
		memcpy(commit->data.data, hash, HASHLEN);
		commit->data.len = HASHLEN;
	}

	return commit;
}

/* 下面函数不实现 */
static Types__ResponseQuery *Query(Types__RequestQuery *req)
{
	return NULL;
}

static Types__ResponseSetOption *SetOption(Types__RequestSetOption *req )
{
	return NULL;
}

static Types__ResponseInitChain *InitChain(Types__RequestInitChain *req)
{
	return NULL;
}

static Types__ResponseBeginBlock *BeginBlock(Types__RequestBeginBlock *req)
{
	return NULL;
}

static Types__ResponseEndBlock *EndBlock(Types__RequestEndBlock *req)
{
	return NULL;
}


void *ABCIApplication(Types__Request *request)
{
	switch( request->value_case )
	{
		case TYPES__REQUEST__VALUE_INFO:
			return Info();
		case TYPES__REQUEST__VALUE_SET_OPTION:
			return SetOption(request->set_option);
		case TYPES__REQUEST__VALUE_DELIVER_TX:
			return DeliverTx(request->deliver_tx);
		case TYPES__REQUEST__VALUE_CHECK_TX:
			return CheckTx(request->check_tx);
		case TYPES__REQUEST__VALUE_COMMIT:
			return  Commit();
		case TYPES__REQUEST__VALUE_QUERY:
			return Query(request->query);
		case TYPES__REQUEST__VALUE_INIT_CHAIN:
			return InitChain(request->init_chain);
		case TYPES__REQUEST__VALUE_BEGIN_BLOCK:
			return BeginBlock(request->begin_block);
		case TYPES__REQUEST__VALUE_END_BLOCK:
			return EndBlock(request->end_block);
	}
}
