#include <stdio.h>
#include "utils.h"


Utils::Utils()
{
}


Utils::~Utils()
{
}

CHAR * Utils::WideToAscii(CHAR* a_pszDest, WCHAR *a_pwszSrc)
{
  int iX = WideCharToMultiByte(GetACP(), 0, a_pwszSrc, -1, a_pszDest, 0, NULL, NULL);
  WideCharToMultiByte(GetACP(), 0, a_pwszSrc, -1, a_pszDest, iX, NULL, NULL);
  return(a_pszDest);
}

WCHAR * Utils::AsciiToWide(WCHAR* a_pwszDest, CHAR* a_pszSrc)
{
  int iX = MultiByteToWideChar(GetACP(), 0, a_pszSrc, -1, a_pwszDest, 0);
  MultiByteToWideChar(GetACP(), 0, a_pszSrc, -1, a_pwszDest, iX);
  return a_pwszDest;
}


//void Utils::Guid2Str(const GUID guid, CHAR * sz)
//{
//  sprintf(sz, "%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x",
//    (unsigned long)guid.Data1,
//    (unsigned short)guid.Data2,
//    (unsigned short)guid.Data3,
//    (unsigned char)guid.Data4[0],
//    (unsigned char)guid.Data4[1],
//    (unsigned char)guid.Data4[2],
//    (unsigned char)guid.Data4[3],
//    (unsigned char)guid.Data4[4],
//    (unsigned char)guid.Data4[5],
//    (unsigned char)guid.Data4[6],
//    (unsigned char)guid.Data4[7]);
//}
//
//void Utils::Str2Guid(CHAR * sz, GUID *pguid)
//{
//  int Data1, Data2, Data3;
//  int Data4[8];
//  sscanf_s(sz, "%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x",
//    &Data1,
//    &Data2,
//    &Data3,
//    Data4 + 0,
//    Data4 + 1,
//    Data4 + 2,
//    Data4 + 3,
//    Data4 + 4,
//    Data4 + 5,
//    Data4 + 6,
//    Data4 + 7);
//
//  pguid->Data1 = Data1;
//  pguid->Data2 = Data2;
//  pguid->Data3 = Data3;
//  pguid->Data4[0] = Data4[0];
//  pguid->Data4[1] = Data4[1];
//  pguid->Data4[2] = Data4[2];
//  pguid->Data4[3] = Data4[3];
//  pguid->Data4[4] = Data4[4];
//  pguid->Data4[5] = Data4[5];
//  pguid->Data4[6] = Data4[6]; 
//  pguid->Data4[7] = Data4[7];
//}
