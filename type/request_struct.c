
#include "request_struct.h"

Types__RequestEcho *request_malloc_echo()
{
	Types__RequestEcho *echo = NULL;

	echo = (Types__RequestEcho*)malloc(sizeof(*echo));
	if ( echo == NULL )
	{
		return NULL;
	}

	types__request_echo__init(echo);

	return echo;
}

Types__RequestFlush *request_malloc_flush()
{
	Types__RequestFlush *flush = NULL;
	flush = (Types__RequestFlush*)malloc(sizeof(*flush));
	if ( flush == NULL )
	{
		return NULL;
	}

	types__request_flush__init(flush);

	return flush;
}

Types__RequestInfo *request_malloc_info()
{
	Types__RequestInfo *info = NULL;
	info = (Types__RequestInfo*)malloc(sizeof(*info));
	if ( info == NULL )
	{
		return NULL;
	}

	types__request_info__init(info);

	return info;
}

Types__RequestSetOption *request_malloc_setoption()
{
	Types__RequestSetOption *setoption = NULL;
	setoption = (Types__RequestSetOption*)malloc(sizeof(*setoption));
	if ( setoption == NULL )
	{
		return NULL;
	}

	types__request_set_option__init(setoption);

	return setoption;
}

Types__RequestDeliverTx *request_malloc_delivertx()
{
	Types__RequestDeliverTx *delivertx = NULL;
	delivertx = (Types__RequestDeliverTx*)malloc(sizeof(*delivertx));
	if ( delivertx == NULL )
	{
		return NULL;
	}
	types__request_deliver_tx__init(delivertx);

	return delivertx;
}

Types__RequestCheckTx *request_malloc_checktx()
{
	Types__RequestCheckTx *checktx = NULL;
	checktx = (Types__RequestCheckTx*)malloc(sizeof(*checktx));
	if ( checktx == NULL )
	{
		return NULL;
	}
	types__request_check_tx__init(checktx);

	return checktx;
}

Types__RequestCommit *request_malloc_commit()
{
	Types__RequestCommit *commit = NULL;
	commit = (Types__RequestCommit*)malloc(sizeof(*commit));
	if ( commit == NULL )
	{
		return NULL;
	}
	types__request_commit__init(commit);

	return commit;
}

Types__RequestQuery *request_malloc_query()
{
	Types__RequestQuery *query = NULL;
	query = (Types__RequestQuery*)malloc(sizeof(*query));
	if ( query == NULL )
	{
		return NULL;
	}

	types__request_query__init(query);

	return query;
}

Types__RequestInitChain *request_malloc_initchain()
{
	Types__RequestInitChain *initchain = NULL;
	initchain = (Types__RequestInitChain*)malloc(sizeof(*initchain));
	if ( initchain == NULL )
	{
		return NULL;
	}

	types__request_init_chain__init(initchain);

	return initchain;
}

Types__RequestBeginBlock *request_malloc_beginblock()
{
	Types__RequestBeginBlock *beginblock = NULL;
	beginblock = (Types__RequestBeginBlock*)malloc(sizeof(*beginblock));
	if ( beginblock == NULL )
	{
		return NULL;
	}

	types__request_begin_block__init(beginblock);

	return beginblock;
}

Types__RequestEndBlock *request_malloc_endblock()
{
	Types__RequestEndBlock *endblock = NULL;
	endblock = (Types__RequestEndBlock*)malloc(sizeof(*endblock));
	if ( endblock == NULL )
	{
		return NULL;
	}
	types__request_end_block__init(endblock);

	return endblock;
}

void request_free_echo(Types__RequestEcho *echo)
{
	if ( echo != NULL )
	{
		if ( echo->message != NULL )
			free(echo->message);

		free(echo);
	}
	return ;
}

void request_free_flush(Types__RequestFlush *flush)
{
	if ( flush )
	{
		free(flush);
	}
	return ;
}

void request_free_info(Types__RequestInfo *info)
{
	if ( info )
	{
		free(info);
	}
	return ;
}

void request_free_setoption(Types__RequestSetOption *setoption)
{
	if ( setoption )
	{
		if ( setoption->key )
			free(setoption->key);

		if ( setoption->value )
			free(setoption->value);

		free(setoption);
	}
	return ;
}

void request_free_delivertx(Types__RequestDeliverTx *delivertx)
{
	if ( delivertx )
	{
		if ( delivertx->tx.data )
			free(delivertx->tx.data);
		
		free(delivertx);
	}
	return ;
}

void request_free_checktx(Types__RequestCheckTx *checktx)
{
	if ( checktx )
	{
		if ( checktx->tx.data )
			free(checktx->tx.data);

		free(checktx);
	}

	return ;
}

void request_free_commit(Types__RequestCommit *commit)
{
	if ( commit )
	{
		free(commit);
	}
	return ;
}

void request_free_query(Types__RequestQuery *query)
{
	if ( query )
	{
		if ( query->data.data )
			free(query->data.data);

		if ( query->path )
			free(query->path);

		if ( query->prove.data )
			free(query->prove.data);

		free(query);
	}
	return ;
}

void request_free_initchain(Types__RequestInitChain *initchain)
{
	if ( initchain )
	{
		if ( initchain->validators )
		{
			/* TODO */
		}
		free(initchain);
	}
	return ;
}

void request_free_beginblock(Types__RequestBeginBlock *beginblock)
{
	if ( beginblock )
	{
		if ( beginblock->hash.data )
			free(beginblock->hash.data);

		if ( beginblock->header )
		{
			/* TODO */
		}
		free(beginblock);
	}
	return ;
}

void request_free_endblock(Types__RequestEndBlock *endblock)
{
	if ( endblock )
	{
		free(endblock);
	}
	return ;
}
