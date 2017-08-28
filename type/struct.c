
#include "struct.h"

Types__ResponseEcho *malloc_echo()
{
	Types__ResponseEcho *echo = NULL;

	echo = (Types__ResponseEcho*)malloc(sizeof(*echo));
	if ( echo == NULL )
	{
		return NULL;
	}

	types__response_echo__init(echo);

	return echo;
}

Types__ResponseFlush *malloc_flush()
{
	Types__ResponseFlush *flush = NULL;
	flush = (Types__ResponseFlush*)malloc(sizeof(*flush));
	if ( flush == NULL )
	{
		return NULL;
	}

	types__response_flush__init(flush);

	return flush;
}

Types__ResponseInfo *malloc_info()
{
	Types__ResponseInfo *info = NULL;
	info = (Types__ResponseInfo*)malloc(sizeof(*info));
	if ( info == NULL )
	{
		return NULL;
	}

	types__response_info__init(info);

	return info;
}

Types__ResponseSetOption *malloc_setoption()
{
	Types__ResponseSetOption *setoption = NULL;
	setoption = (Types__ResponseSetOption*)malloc(sizeof(*setoption));
	if ( setoption == NULL )
	{
		return NULL;
	}

	types__response_set_option__init(setoption);

	return setoption;
}

Types__ResponseDeliverTx *malloc_delivertx()
{
	Types__ResponseDeliverTx *delivertx = NULL;
	delivertx = (Types__ResponseDeliverTx*)malloc(sizeof(*delivertx));
	if ( delivertx == NULL )
	{
		return NULL;
	}
	types__response_deliver_tx__init(delivertx);

	return delivertx;
}

Types__ResponseCheckTx *malloc_checktx()
{
	Types__ResponseCheckTx *checktx = NULL;
	checktx = (Types__ResponseCheckTx*)malloc(sizeof(*checktx));
	if ( checktx == NULL )
	{
		return NULL;
	}
	types__response_check_tx__init(checktx);

	return checktx;
}

Types__ResponseCommit *malloc_commit()
{
	Types__ResponseCommit *commit = NULL;
	commit = (Types__ResponseCommit*)malloc(sizeof(*commit));
	if ( commit == NULL )
	{
		return NULL;
	}
	types__response_commit__init(commit);

	return commit;
}

Types__ResponseQuery *malloc_query()
{
	Types__ResponseQuery *query = NULL;
	query = (Types__ResponseQuery*)malloc(sizeof(*query));
	if ( query == NULL )
	{
		return NULL;
	}

	types__response_query__init(query);

	return query;
}

Types__ResponseInitChain *malloc_initchain()
{
	Types__ResponseInitChain *initchain = NULL;
	initchain = (Types__ResponseInitChain*)malloc(sizeof(*initchain));
	if ( initchain == NULL )
	{
		return NULL;
	}

	types__response_init_chain__init(initchain);

	return initchain;
}

Types__ResponseBeginBlock *malloc_beginblock()
{
	Types__ResponseBeginBlock *beginblock = NULL;
	beginblock = (Types__ResponseBeginBlock*)malloc(sizeof(*beginblock));
	if ( beginblock == NULL )
	{
		return NULL;
	}

	types__response_begin_block__init(beginblock);

	return beginblock;
}

Types__ResponseEndBlock *malloc_endblock()
{
	Types__ResponseEndBlock *endblock = NULL;
	endblock = (Types__ResponseEndBlock*)malloc(sizeof(*endblock));
	if ( endblock == NULL )
	{
		return NULL;
	}
	types__response_end_block__init(endblock);

	return endblock;
}

Types__ResponseException *malloc_exception()
{
	Types__ResponseException *exception = NULL;
	exception = (Types__ResponseException*)malloc(sizeof(*exception));
	if ( exception == NULL )
	{
		return NULL;
	}
	types__response_exception__init(exception);

	return exception;
}

void free_echo(Types__ResponseEcho *echo)
{
	if ( echo != NULL )
	{
		if ( echo->message != NULL )
			free(echo->message);

		free(echo);
	}
	return ;
}

void free_flush(Types__ResponseFlush *flush)
{
	if ( flush )
	{
		free(flush);
	}
	return ;
}

void free_info(Types__ResponseInfo *info)
{
	if ( info )
	{
		if ( info->data )
			free(info->data);

		if ( info->version )
			free(info->version);

		if ( info->last_block_app_hash.data )
			free(info->last_block_app_hash.data);

		free(info);
	}
	return ;
}

void free_setoption(Types__ResponseSetOption *setoption)
{
	if ( setoption )
	{
		if ( setoption->log )
			free(setoption->log);

		free(setoption);
	}
	return ;
}

void free_delivertx(Types__ResponseDeliverTx *delivertx)
{
	if ( delivertx )
	{
		if ( delivertx->log )
			free(delivertx->log);

		if ( delivertx->data.data )
			free(delivertx->data.data);
		
		free(delivertx);
	}
	return ;
}

void free_checktx(Types__ResponseCheckTx *checktx)
{
	if ( checktx )
	{
		if ( checktx->log )
			free(checktx->log);

		if ( checktx->data.data )
			free(checktx->data.data);

		free(checktx);
	}

	return ;
}

void free_commit(Types__ResponseCommit *commit)
{
	if ( commit )
	{
		if ( commit->log )
			free(commit->log);

		if ( commit->data.data )
			free(commit->data.data);

		free(commit);
	}
	return ;
}

void free_query(Types__ResponseQuery *query)
{
	if ( query )
	{
		if ( query->log )
			free(query->log);

		if ( query->key.data )
			free(query->key.data);

		if ( query->value.data )
			free(query->value.data );

		if ( query->proof.data )
			free(query->proof.data );

		free(query);
	}
	return ;
}

void free_initchain(Types__ResponseInitChain *initchain)
{
	if ( initchain )
	{
		free(initchain);
	}
	return ;
}

void free_beginblock(Types__ResponseBeginBlock *beginblock)
{
	if ( beginblock )
	{
		free(beginblock);
	}
	return ;
}

void free_validator(Types__Validator *validator)
{
}

void free_endblock(Types__ResponseEndBlock *endblock)
{
	if ( endblock )
	{
		if ( endblock->diffs )
		{
			if ( *(endblock->diffs) )
				free_validator(*(endblock->diffs));
		}

		free(endblock);
	}
	return ;
}

void free_exception(Types__ResponseException *exception)
{
	if ( exception )
	{
		if ( exception->error )
		{
			free(exception->error);
		}
		free(exception);
	}

	return ;
}
