
#ifndef UTILS_H_
#define UTILS_H_

#include <wtypes.h>

class Utils
{
public:
  Utils();
  virtual        ~Utils();

  static CHAR  * WideToAscii(CHAR* a_pszDest, WCHAR *a_pwszSrc);
  static WCHAR * AsciiToWide(WCHAR* a_pwszDest, CHAR* a_pszSrc);
 /* static void    Guid2Str(const GUID guid, CHAR * sz);
  static void    Str2Guid(CHAR * sz, GUID *pguid);*/

};

#endif

