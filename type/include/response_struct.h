
#ifndef __STRUCT_H__
#define __STRUCT_H__

#include "types.pb-c.h"
#include <stdlib.h>

Types__ResponseEcho *response_malloc_echo();

Types__ResponseFlush *response_malloc_flush();

Types__ResponseInfo *response_malloc_info();

Types__ResponseSetOption *response_malloc_setoption();

Types__ResponseDeliverTx *response_malloc_delivertx();

Types__ResponseCheckTx *response_malloc_checktx();

Types__ResponseCommit *response_malloc_commit();

Types__ResponseQuery *response_malloc_query();

Types__ResponseInitChain *response_malloc_initchain();

Types__ResponseBeginBlock *response_malloc_beginblock();

Types__ResponseEndBlock *response_malloc_endblock();

Types__ResponseException *response_malloc_exception();

void response_free_echo(Types__ResponseEcho *echo);

void response_free_flush(Types__ResponseFlush *flush);

void response_free_info(Types__ResponseInfo *info);

void response_free_setoption(Types__ResponseSetOption *setoption);;

void response_free_delivertx(Types__ResponseDeliverTx *delivertx);

void response_free_checktx(Types__ResponseCheckTx *checktx);

void response_free_commit(Types__ResponseCommit *commit);

void response_free_query(Types__ResponseQuery *query);

void response_free_initchain(Types__ResponseInitChain *initchain);

void response_free_beginblock(Types__ResponseBeginBlock *beginblock);

void response_free_endblock(Types__ResponseEndBlock *endblock);

void response_free_exception(Types__ResponseException *exception);

#endif
