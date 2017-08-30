
#ifndef __UTIL_H__
#define __UTIL_H__

#include "dlist.h"
#include "message.h"

#define HASHLEN 10

void init_dummy();

void destory_dummy();

int get_height();

uint8_t *get_last_app_hash();

Types__CodeType set_state(uint8_t *key, uint8_t *value, uint8_t *tx);

Types__CodeType check_transation(uint8_t *tx);

int getcols(uint8_t *value, uint8_t split, uint8_t word[][64]);

#endif
