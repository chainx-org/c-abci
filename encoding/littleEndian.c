/*********************************************************************************************/
/*                   littleEndian.c Created by xuli on 2017/08/10                            */
/*              本文件用于以小端模式存储的二进制与整型数据之间互相转换                       */
/*********************************************************************************************/

#include "littleEndian.h"

bool littleEndianUint16(const uint8_t *buff, uint16_t *value)
{

	if ( buff == NULL || value == NULL )
		return false;

	*value = ((uint16_t)buff[0]) | (uint16_t)(buff[1] << 8); 

	return true;

}

bool littleEndianPutUint16(uint8_t *buff, uint16_t value)
{
	if ( buff == NULL )
		return false;

	buff[0] = (uint8_t)value;
	buff[1] = (uint8_t)(value >> 8);

	return true;
}

bool littleEndianUint32(const uint8_t *buff, uint32_t *value)
{
	if ( buff == NULL || value == NULL )
		return false;


	*value = ((uint32_t)buff[0]) | ((uint32_t)buff[1]) << 8 | ((uint32_t)buff[2]) << 16 | ((uint32_t)buff[3]) << 24;

	return true;
}

bool littleEndianPutUint32(uint8_t *buff, uint32_t value)
{
	if ( buff == NULL )
		return false;

	buff[0] = (uint8_t)value;
	buff[1] = (uint8_t)(value >> 8);
	buff[2] = (uint8_t)(value >> 16);
	buff[3] = (uint8_t)(value >> 24);

	return true;
}

bool littleEndianUint64(const uint8_t *buff, uint64_t *value)
{
	if ( buff == NULL || value == NULL )
		return false;

	*value = ((uint64_t)buff[0]) | (((uint64_t)buff[1]) << 8) | (((uint64_t)buff[2]) << 16) | (((uint64_t)buff[3]) << 24) | \
		(((uint64_t)buff[4]) << 32) | (((uint64_t)buff[5]) << 40) | (((uint64_t)buff[6]) << 48) | (((uint64_t)buff[7]) << 56);

	return true;
}


bool littleEndianPutUint64(uint8_t *buff, uint64_t value)
{

	if ( buff == NULL )
		return false;

	buff[0] = (uint8_t)value;
	buff[1] = (uint8_t)(value >> 8);
	buff[2] = (uint8_t)(value >> 16);
	buff[3] = (uint8_t)(value >> 24);
	buff[4] = (uint8_t)(value >> 32);
	buff[5] = (uint8_t)(value >> 40);
	buff[6] = (uint8_t)(value >> 48);
	buff[7] = (uint8_t)(value >> 56);

	return true;
}

/* 原理：C语言中联合体union的存放顺序是所有成员都从低地址开始存放，而且所有成员共享存储空间 */
bool isLittleEndian()
{
    union data
    {
        short int a;
        char b;
    }data;
    data.a = 0x1234;

	/* 低字节存的是数据的高字节数据 */
    if( data.b == 0x12 )
    {
        /* 是大端模式 */
		return false; 
    }
    else 
    {
        /* 是小端模式*/
		return  true;
    }
}
