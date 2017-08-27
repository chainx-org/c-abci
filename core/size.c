
#include "common.h"

size_t readsize(struct socket_tcp *tsocket, int timeout)
{
	size_t bytes = 0;
	uint8_t size = 0;
	uint8_t buff[8] =  {};
	uint64_t length = 0;
	bool negate = false;

	if ( tsocket == NULL )
	{
		tsocket->error = EINVAL;
		return -1;
	}

	bytes = socket_read(tsocket, &size, 1, timeout);
	if ( bytes != 1 )
	{
		return -1;
	}

	if ( size >> 4  == 0xF )
	{
        negate = true;
        size = size & 0x0F;
    }
    if ( size > 8 )
   	{
        return -1;
    }

    if ( size == 0 )
   	{
        return -1;
    }

	bytes = socket_read(tsocket, &buff[8-size], size, timeout);
	if ( bytes != size )
	{
		return -1;
	}


	if ( bigEndianUint64(buff, &length) == false )
		return -1;

    if ( negate )
   	{
        return -length;
    }
   	else
   	{
        return length; 
    }
}

size_t sendsize(struct socket_tcp *tsocket, size_t length, int timeout)
{
	int bits = 0;
	uint8_t size = 0;
	uint8_t buff[8] = {};
	bool    negate = false;

	if ( length < 0)
	{
		negate = true;
		length = -length; 
	}

	bits = getbits((uint64_t)length); /* 闀垮一共有几个字节  */

	if ( negate )
		size = (uint8_t)(bits + 0xF0);
	else
		size = (uint8_t)bits;

	if ( size <= 0 || size > 8)
		return -1;

	if ( socket_send(tsocket, &size, 1, timeout) != 1 )
		return -1;

	bigEndianPutUint64(buff, (uint64_t)length);

	if ( socket_send(tsocket, &buff[8-size], size, timeout) != size )
		return -1;

	return 0;
}
