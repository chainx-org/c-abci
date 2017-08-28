
#ifndef __STRUCT_H__
#define __STRUCT_H__

#include "types.pb-c.h"
#include <stdlib.h>

Types__ResponseEcho *malloc_echo();

Types__ResponseFlush *malloc_flush();

Types__ResponseInfo *malloc_info();

Types__ResponseSetOption *malloc_setoption();

Types__ResponseDeliverTx *malloc_delivertx();

Types__ResponseCheckTx *malloc_checktx();

Types__ResponseCommit *malloc_commit();

Types__ResponseQuery *malloc_query();

Types__ResponseInitChain *malloc_initchain();

Types__ResponseBeginBlock *malloc_beginblock();

Types__ResponseEndBlock *malloc_endblock();

Types__ResponseException *malloc_exception();

void free_echo(Types__ResponseEcho *echo);

void free_flush(Types__ResponseFlush *flush);

void free_info(Types__ResponseInfo *info);

void free_setoption(Types__ResponseSetOption *setoption);;

void free_delivertx(Types__ResponseDeliverTx *delivertx);

void free_checktx(Types__ResponseCheckTx *checktx);

void free_commit(Types__ResponseCommit *commit);

void free_query(Types__ResponseQuery *query);

void free_initchain(Types__ResponseInitChain *initchain);

void free_beginblock(Types__ResponseBeginBlock *beginblock);

void free_endblock(Types__ResponseEndBlock *endblock);

void free_exception(Types__ResponseException *exception);

#endif
