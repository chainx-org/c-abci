
#ifndef __UTIL_H__
#define __UTIL_H__

#include "dlist.h"
#include "littleEndian.h"
#include "message.h"
#include <string.h>

#define HASHLEN 8

void init_dummy();

void destroy_dummy();

int get_height();

uint8_t *get_last_app_hash();

Types__CodeType set_state(uint8_t *key, uint8_t *value, uint8_t *tx, size_t keylen, size_t valuelen, size_t txlen);

Types__CodeType check_transation(uint8_t *tx);

int *getcols(uint8_t *value, uint8_t split, uint8_t word[][64]);

#endif
