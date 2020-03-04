/*
 * ʵ���Լ����㷨����У��͵�
 */
#include "stdafx.h"

/* �ۼ�У��� */
BYTE u8Sum_Calc8(const BYTE *pu8Data, short i16Len)
{
	BYTE sum=0;
	for(short i=0; i<i16Len; ++i)
		sum += pu8Data[i];
	return sum;
}

/* CRCУ��� */
WORD u16CRC_Calc16(const BYTE *pu8Data, short i16Len)
{
	BYTE i;
	WORD u16CRC = 0;
    while(--i16Len >= 0)
    {
    	i = 8;
    	u16CRC = u16CRC ^ (((WORD)*pu8Data++) << 8);

    	do
        {
    		if (u16CRC & 0x8000)
    		{
    			u16CRC = u16CRC << 1 ^ 0x1021;
    		}
    		else
    		{
    			u16CRC = u16CRC << 1;
    		}
        }
    	while(--i);
    }
    return u16CRC;
}

/* CString�ַ���תChar���� */
int My_CStringToChar(char* pDest, CString& pSource)
{
	 wchar_t* pawstr = NULL;
	 pawstr = pSource.GetBuffer(pSource.GetLength()+1);
	 //ABC �� һ���� ���ȶ�Ϊ3
	 wcstombs(pDest,pawstr,pSource.GetLength()+1);
	 //memcpy(pDest, (char*)pawstr, pSource.GetLength()*sizeof(wchar_t));
	 return  pSource.GetLength(); 
}

unsigned int CaculateCRC(const CByteArray& m_Array, int Count)
{
	unsigned int CRC = 0;
	int i;
	unsigned char j;
	unsigned char temp;
	for(i = 0;i < Count;i++) 
	{
		temp = m_Array.GetAt(i+3) ; //�ӵ�������ʼȡ
		for(j = 0x80;j != 0;j /= 2)  //ÿһλ���в���
		{			
			if((CRC & 0x8000) != 0)
			{
				CRC <<= 1; 
				CRC ^= 0x1021;
			}
			else 
				CRC <<= 1;
			if((temp & j) != 0) 
				CRC ^= 0x1021;
		}
	}	
	return CRC;
}