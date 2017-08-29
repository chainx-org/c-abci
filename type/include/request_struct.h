
#ifndef __STRUCT_H__
#define __STRUCT_H__

#include "types.pb-c.h"
#include <stdlib.h>

Types__RequestEcho *request_malloc_echo();

Types__RequestFlush *request_malloc_flush();

Types__RequestInfo *request_malloc_info();

Types__RequestSetOption *request_malloc_setoption();

Types__RequestDeliverTx *request_malloc_delivertx();

Types__RequestCheckTx *request_malloc_checktx();

Types__RequestCommit *request_malloc_commit();

Types__RequestQuery *request_malloc_query();

Types__RequestInitChain *request_malloc_initchain();

Types__RequestBeginBlock *request_malloc_beginblock();

Types__RequestEndBlock *request_malloc_endblock();

void request_free_echo(Types__RequestEcho *echo);

void request_free_flush(Types__RequestFlush *flush);

void request_free_info(Types__RequestInfo *info);

void request_free_setoption(Types__RequestSetOption *setoption);;

void request_free_delivertx(Types__RequestDeliverTx *delivertx);

void request_free_checktx(Types__RequestCheckTx *checktx);

void request_free_commit(Types__RequestCommit *commit);

void request_free_query(Types__RequestQuery *query);

void request_free_initchain(Types__RequestInitChain *initchain);

void request_free_beginblock(Types__RequestBeginBlock *beginblock);

void request_free_endblock(Types__RequestEndBlock *endblock);

#endif
