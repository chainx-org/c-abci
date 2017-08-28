/*********************************************************************************************/
/*                    bits.c Created by xuli on 2017/08/15                                   */
/*                      本文件用于获取一个整型数据的位数                                     */
/*********************************************************************************************/
#include "bits.h"

int  getbits(uint64_t number)
{
	if ( number == 0 )
   	{
		return 0;
	}
	if ( number < ( 1 << 8 ))
	{
		return 1;
	}
	if ( number < ( 1 << 16 ))
   	{
		return 2;
	}
	if ( number < ( 1 << 24))
   	{
		return 3;
	}
	if ( number < ( (uint64_t)1 << 32 ))
   	{
		return 4;
	}
	if ( number < ( (uint64_t)1 << 40 ))
   	{
		return 5;
	}
	if ( number < ( (uint64_t)1 << 48 ))
   	{
		return 6;
	}
	if ( number < ( (uint64_t)1 << 56 ))
   	{
		return 7;
	}
	return 8;
}
