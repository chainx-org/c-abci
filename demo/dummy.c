
#include "dummy.h"

static int Info(Types__ResponseInfo *info)
{
}

static int DeliverTx(Types__RequestDeliverTx *req, Types__ResponseDeliverTx *rsp)
{
}

static int CheckTx(Types__RequestCheckTx *req, Types__ResponseCheckTx *checktx)
{
}

static int Commit(Types__ResponseCommit *commit)
{
}

static int Query(Types__RequestQuery *req, Types__ResponseQuery *rsp)
{
}

/* 下面函数不实现 */
static int SetOption(Types__RequestSetOption *req, Types__ResponseSetOption *rsp)
{
}

static int InitChain(Types__RequestInitChain *req)
{
}

static int BeginBlock(Types__RequestBeginBlock *req, Types__ResponseBeginBlock *rsp)
{
}

int EndBlock(Types__RequestEndBlock *req, Types__ResponseEndBlock *rsp)
{
}


int ABCIApplication(Types__Request *request, Types__Response *response)
{
	int ret = 0;

	switch( request->value_case )
	{
		case TYPES__REQUEST__VALUE_INFO:
			ret = Info(response->info);
			break ;
		case TYPES__REQUEST__VALUE_SET_OPTION:
			ret = SetOption(request->set_option, response->set_option);
			break ;
		case TYPES__REQUEST__VALUE_DELIVER_TX:
			ret = DeliverTx(request->deliver_tx, response->deliver_tx);
			break ;
		case TYPES__REQUEST__VALUE_CHECK_TX:
			ret = CheckTx(request->check_tx, response->check_tx);
			break ;
		case TYPES__REQUEST__VALUE_COMMIT:
			ret = Commit(response->commit);
			break ;
		case TYPES__REQUEST__VALUE_QUERY:
			ret = Query(request->query, response->query);
			break ;
		case TYPES__REQUEST__VALUE_INIT_CHAIN:
			ret = InitChain(request->init_chain);
			break ;
		case TYPES__REQUEST__VALUE_BEGIN_BLOCK:
			ret = BeginBlock(request->begin_block, response->begin_block);
			break ;
		case TYPES__REQUEST__VALUE_END_BLOCK:
			ret = EndBlock(request->end_block, response->end_block);
			break ;
	}
	return ret;
}
