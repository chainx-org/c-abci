
#include "util.h"

static struct dlist dummy;

struct data {
	uint8_t *tx;
	uint8_t *apphash;
	uint8_t *key;
	uint8_t *value;
};

static uint64_t HashDefaultCB(const uint8_t *key, size_t dataLen)
{
    uint64_t d = 0;

    if (dataLen < 2) {
        d = ((uint8_t *)key)[0];
    } else if (dataLen < 4) {
        d = ((uint16_t *)key)[0];
    } else if (dataLen < 8) {
        d = ((uint32_t *)key)[0];
    } else {
        d = ((uint64_t *)key)[0];
    }

    return d >> 3;
}

static void free_data(void *temp)
{
	struct data *data = (struct data*)temp;
	if ( data )
	{
		if ( data->tx )
			free(data->tx);

		if ( data->apphash )
			free(data->apphash);

		if ( data->key )
			free(data->key);

		if ( data->value )
			free(data->value);
	}
	return ;
}

void init_dummy()
{
	create_dlist(&dummy);
	return ;
}

void destroy_dummy()
{
	destroy_dlist(&dummy, free_data);
	return ;
}

int get_height()
{
	return dummy.size;
}

uint8_t *get_last_app_hash()
{
	if ( dummy.size )
	{
		return ((struct data*)dummy.tail->data)->apphash;
	}
	return NULL;
}


Types__CodeType set_state(uint8_t *key, uint8_t *value, uint8_t *tx, size_t keylen, size_t valuelen, size_t txlen)
{
	uint64_t ihash;
	uint8_t chash[HASHLEN] = {};
	struct data data = {};

	data.tx = (uint8_t*)malloc(txlen);
	if ( data.tx == NULL )
	{
		free_data(&data);
		return TYPES__CODE_TYPE__InternalError;
	}
	printf("txlen:%lu\n", txlen);
	memcpy(data.tx, tx, txlen);

	data.key = (uint8_t*)malloc(keylen);
	if ( data.key == NULL )
	{
		free_data(&data);
		return TYPES__CODE_TYPE__InternalError;
	}
	printf("keylen:%lu\n", keylen);
	memcpy(data.key, key, keylen);

	data.value = (uint8_t*)malloc(valuelen);
	if ( data.value == NULL )
	{
		free_data(&data);
		return TYPES__CODE_TYPE__InternalError;
	}
	printf("valuelen:%lu\n", valuelen);
	memcpy(data.value, value, valuelen);

	ihash = HashDefaultCB(value, valuelen);

	littleEndianPutUint64(chash, ihash);

	data.apphash = (uint8_t*)malloc(HASHLEN);
	if ( data.apphash == NULL )
	{
		free_data(&data);
		return TYPES__CODE_TYPE__InternalError;
	}
	int i = 0;
	for (i = 0; i < HASHLEN; i++)
	{
		printf("chash[%d]:0x%x\n", i, chash[i]);
	}

	printf("HASHLEN:%d\n", HASHLEN);
	memcpy(data.apphash, chash, HASHLEN);
	printf("memmcpy done\n");

	insert_tail(&dummy, &data, sizeof(struct data));

	return TYPES__CODE_TYPE__OK;
}

Types__CodeType check_transation(uint8_t *tx)
{
	return TYPES__CODE_TYPE__OK; 
}

int *getcols(uint8_t *value, uint8_t split, uint8_t words[][64])
{
	int i = 0, j = 0;
	int cols = 0;
	int *bytes = (int*)malloc(10*sizeof(int));

	if ( bytes == NULL )
	{
		return NULL;
	}
	memset(bytes, 0, 10*sizeof(int));

	for (i = 0; value[i] != (uint8_t)'\0'; i++)
	{
		printf("value[%d]:0x%x\n", i, value[i]);
		if ( value[i] != split )
		{
			words[cols][j] = value[i];
			j++;
		}
		else
		{
			cols += 1;
			bytes[cols] = j; 
			j = 0;
		}
	}
	cols += 1;
	bytes[cols] = j;

	printf("cols:%d\n", cols);
	bytes[0] = cols;
	for (i = 0; i < cols; i++)
	{
		printf("bytes[%d]:%d\n", i, bytes[i]);
	}
	return bytes;
}
