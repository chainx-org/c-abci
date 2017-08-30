
#include "dummy.h"

#define VERSION "1.0.0"

static Types__ResponseInfo *Info()
{
	Types__ResponseInfo *info = NULL;
	info = response_malloc_info();
	if ( info == NULL )
	{
		return NULL;
	}
	info->version = malloc(strlen(VERSION));
	if ( info->version == NULL)
	{
		response_free_info(info);
		return NULL;
	}
	info->block_height = get_height();
	if ( info->block_height > 0 )
	{
		uint8_t *hash = NULL;
		info->has_last_block_height = 1;
		info->has_last_block_app_hash = 1;
		hash = get_hash();
		info->last_block_app_hash.data = malloc(strlen(hash));
		if ( info->last_block_app_hash.data == NULL )
		{
			response_free_info(info);
			return NULL;
		}
		memcpy(info->last_block_app_hash.data, hash, strlen(hash));
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
	int cols = 0;
	char *log = NULL;
	uint8_t hash[10] = {};
	uint8_t words[2][64] = {};

	Types__CodeType code = 0;
	Types__ResponseDeliverTx *deliver_tx = NULL;

	if ( req->has_tx )
	{
		cols = getcols(req->tx.data, (uint8_t)'=', words);
		if ( cols == 2 )
			code = set_state(words[0], words[1], req->tx.data);
		else
			code = set_state(words[0], words[0], req->tx.data);
	}

	deliver_tx = response_malloc_delivertx();
	if ( deliver_tx == NULL )
	{
		return NULL:
	}
	deliver_tx->has_code = 1;
	deliver_tx->code = code;

	if ( code != TYPES__CODE_TYPE__OK )
		log = "InternalError";
	else
		log = "OK";

	deliver_tx->log = malloc(strlen(log));
	if ( deliver_tx->log == NULL )
	{
		response_free_delivertx(delivertx);
		return NULL;
	}
	memcpy(deliver_tx->log, log, strlen(log));

	hash = get_hash();
	deliver_tx->data.data = malloc(strlen(hash));
	if ( deliver_tx->data.data == NULL )
	{
		response_free_delivertx(delivertx);
		return NULL;
	}
	memcpy(deliver_tx->data.data, hash, strlen(hash));

	return deliver_tx;
}

static Types__ResponseCheckTx *CheckTx(Types__RequestCheckTx *req)
{
	uint8_t *log = NULL;
	uint8_t hash[10] = {};
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

	checktx->log = malloc(strlen(log));
	if ( checktx->log == NULL )
	{
		response_free_checktx(checktx);
		return NULL;
	}
	memcpy(checktx->log, log, strlen(log));

	checktx->has_data = 1;
	hash = get_hash();
	checktx->data.data = malloc(strlen(hash));
	if ( checktx->data.data == NULL )
	{
		response_free_checktx(checktx);
		return NULL;
	}
	memcpy(checktx->data.data, hash, strlen(hash));

	return checktx;
}

static Types__ResponseCommit *Commit()
{
	uint8_t *log = "OK";
	uint8_t hash[10] = {};
	Types__CodeType code = 0;
	Types__ResponseCommit *commit = NULL;

	commit = response_malloc_commit();
	if ( commit == NULL )
	{
		return NULL;
	}
	commit->has_code = 1;
	commit->code = TYPES__CODE_TYPE__OK ;

	commit->log = malloc(strlen(log));
	if ( commit->log == NULL )
	{
		response_free_commit(commit);
		return NULL;
	}
	memcpy(commit->log, log, strlen(log));

	if ( get_height() > 0 )
	{
		commit->has_data = 1;
		hash = get_hash();
		commit->data.data = malloc(strlen(hash));
		if ( commit->data.data == NULL )
		{
			response_free_commit(commit);
			return NULL;
		}
		memcpy(commit->data.data, hash, strlen(hash));
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
