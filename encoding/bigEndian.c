/*********************************************************************************************/
/*                     bigEndian.c Created by xuli on 2017/08/10                             */
/*              ���ļ������Դ��ģʽ�洢�Ķ���������������֮�以��ת��                       */
/*********************************************************************************************/

#include "bigEndian.h"


bool bigEndianUint16(const uint8_t *buff, uint16_t *value)
{
	if ( buff == NULL || value == NULL )
		return false;

	*value = ((uint16_t)buff[1]) | ((uint16_t)(buff[0] << 8));

	return true;
}

bool bigEndianPutUint16(uint8_t *buff, uint16_t value)
{
	if ( buff == NULL )
		return false;

	buff[0] = (uint8_t)(value >> 8);
	buff[1] = (uint8_t)value;

	return true;
}

bool bigEndianUint32(const uint8_t *buff, uint32_t *value)
{
	if ( buff == NULL || value == NULL )
		return false;

	*value = ((uint32_t)buff[3]) | ((uint32_t)(buff[2]<<8)) | ((uint32_t)(buff[1] << 16)) | ((uint32_t)(buff[0] << 24));

	return true;
}

bool bigEndianPutUint32(uint8_t *buff, uint32_t value)
{
	if ( buff == NULL )
		return false;

	buff[0] = (uint8_t)(value >> 24);
	buff[1] = (uint8_t)(value >> 16);
	buff[2] = (uint8_t)(value >> 8);
	buff[3] = (uint8_t)value;
	
	return true;
}

bool bigEndianUint64(const uint8_t *buff, uint64_t *value)
{
	if ( buff == NULL || value == NULL )
		return false;

	*value = ((uint64_t)buff[7]) | (((uint64_t)buff[6]) << 8) | (((uint64_t)buff[5]) << 16) | (((uint64_t)buff[4]) << 24) | \
		(((uint64_t)buff[3]) << 32 ) | (((uint64_t)buff[2]) << 40) | (((uint64_t)buff[1]) << 48 ) | (((uint64_t)buff[0]) << 56);

	return true;
}

bool bigEndianPutUint64(uint8_t *buff, uint64_t value)
{

	if ( buff == NULL )
		return false;

	buff[0] = (uint8_t)(value >> 56);
	buff[1] = (uint8_t)(value >> 48);
	buff[2] = (uint8_t)(value >> 40);
	buff[3] = (uint8_t)(value >> 32);
	buff[4] = (uint8_t)(value >> 24);
	buff[5] = (uint8_t)(value >> 16);
	buff[6] = (uint8_t)(value >> 8);
	buff[7] = (uint8_t)value;
	return true;
}

/* ԭ��C������������union�Ĵ��˳�������г�Ա���ӵ͵�ַ��ʼ��ţ��������г�Ա����洢�ռ� */
bool isBigEndian()
{
    union data
    {
        short int a;
        char b;
    }data;
    data.a = 0x1234;

	/* ���ֽڴ�������ݵĸ��ֽ����� */
    if( data.b == 0x12 )
    {
        /* �Ǵ��ģʽ */
		return true;
    }
    else 
    {
        /* ��С��ģʽ*/
		return false;
    }
}
