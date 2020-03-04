#ifndef __MY_ALGORIGHM_H
#define __MY_ALGORIGHM_H

BYTE u8Sum_Calc8(const BYTE *pu8Data, short i16Len);
WORD u16CRC_Calc16(const BYTE *pu8Data, short i16Len);
int My_CStringToChar(char* pDest, CString & pSource);
unsigned int CaculateCRC(const CByteArray& m_Array, int Count);

#endif // __MY_ALGORIGHM_H