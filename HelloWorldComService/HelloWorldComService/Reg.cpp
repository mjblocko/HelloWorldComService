
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "reg.h"
#include "utils.h"
#include "dbug_msvc.hpp"

static char * db_unit = __FILE__;


LONG DeleteRegistryTree(HKEY    hKeyParent,           // Parent of key to delete
                        LPCTSTR lpszKeyChild)  // Key to delete
{
	HKEY hKeyChild ;

	LONG lRes = RegOpenKeyEx(hKeyParent, lpszKeyChild, 0, KEY_ALL_ACCESS, &hKeyChild) ;
	if (lRes != ERROR_SUCCESS)
	{
		return lRes ;
	}

	FILETIME time ;
	TCHAR szBuffer[256] ;
	DWORD dwSize = 256 ;
	while (RegEnumKeyEx(hKeyChild, 0, szBuffer, &dwSize, NULL, NULL, NULL, &time) == S_OK)
	{
		lRes = DeleteRegistryTree(hKeyChild, szBuffer) ;
		if (lRes != ERROR_SUCCESS)
		{
			RegCloseKey(hKeyChild) ;
			return lRes;
		}
		dwSize = 256 ;
	}
	RegCloseKey(hKeyChild) ;
	return RegDeleteKey(hKeyParent, lpszKeyChild) ;
}

//
//   FUNCTION: SetHKCRRegistryKeyAndValue
//
//   PURPOSE: The function creates a HKCR registry key and sets the specified 
//   registry value.
//
//   PARAMETERS:
//   * pszSubKey - specifies the registry key under HKCR. If the key does not 
//     exist, the function will create the registry key.
//   * pszValueName - specifies the registry value to be set. If pszValueName 
//     is NULL, the function will set the default value.
//   * pszData - specifies the string data of the registry value.
// 
HRESULT SetHKCRRegistryKeyAndValue(LPCTSTR pszSubKey,
                                   LPCTSTR pszValueName, 
                                   LPCTSTR pszData)
{
    HRESULT hr;
    HKEY hKey = NULL;

	DBUG_ENTER("SetHKCRRegistryKeyAndValue()");



    // Creates the specified registry key. If the key already exists, the 
    // function opens it. 

	DBUG_PRINT("", ("Creating key [%s]", pszSubKey));
	if (pszValueName != NULL) {
		DBUG_PRINT("", ("       Value [%s]",pszValueName));
	}
	DBUG_PRINT("", ("        Data [%s]",pszData));
 
    hr = HRESULT_FROM_WIN32(RegCreateKeyEx(HKEY_CLASSES_ROOT, pszSubKey, 0, 
        NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL));

    if (SUCCEEDED(hr))
    {
        if (pszData != NULL)
        {
            // Set the specified value of the key.
            DWORD cbData = lstrlen(pszData) * sizeof(*pszData);
            hr = HRESULT_FROM_WIN32(RegSetValueEx(hKey, pszValueName, 0, 
                REG_SZ, reinterpret_cast<const BYTE *>(pszData), cbData));
        }
        RegCloseKey(hKey);
    }
	DBUG_PRINT("", ("hr is %d", hr));

    DBUG_RETURN(hr);
}


//
//   FUNCTION: RegisterInprocServer 
//
//   PURPOSE: Register the in-process component in the registry.
//
//   PARAMETERS:
//   * pszModule - Path of the module that contains the component
//   * clsid - Class ID of the component
//   * pszFriendlyName - Friendly name
//   * pszThreadModel - Threading model
//   * libid - Type library ID
//   * pszProgID - ProgID of the component
//   * pszVerIndProgID - Version independent ProgID
//
//   NOTE: The function creates the HKCR\CLSID\{<CLSID>} key and the 
//   HKCR\<ProgID> key in the registry.
// 
//   HKCR
//   {
//      <ProgID> = s '<Friendly Name>'
//      {
//          CLSID = s '{<CLSID>}'
//      }
//      <VersionIndependentProgID> = s '<Friendly Name>'
//      {
//          CLSID = s '{<CLSID>}'
//          CurVer = s '<ProgID>'
//      }
//      NoRemove CLSID
//      {
//          ForceRemove {<CLSID>} = s '<Friendly Name>'
//          {
//              ProgID = s '<ProgID>'
//              VersionIndependentProgID = s '<VersionIndependentProgID>'
//              InprocServer32 = s '%MODULE%'
//              {
//                  val ThreadingModel = s '<Thread Model>'
//              }
//              TypeLib = s '{<LIBID>}'
//          }
//      }
//   }
        
//
HRESULT RegisterInprocServer(LPCTSTR pszModule, 
                             const CLSID& clsid, 
                             LPCTSTR pszFriendlyName,
                             LPCTSTR pszThreadModel,
                             const IID& libid,
                             LPCTSTR pszProgID, 
                             LPCTSTR pszVerIndProgID)
{
    HRESULT hr = E_INVALIDARG;
    DBUG_ENTER("RegisterInprocServer()");

	DBUG_PRINT("", ("pszModule         : [%s]", pszModule));
	DBUG_PRINT("", ("pszFriendlyName   : [%s]", pszFriendlyName));
	DBUG_PRINT("", ("pszThreadModel    : [%s]", pszThreadModel ));
	DBUG_PRINT("", ("pszProgID         : [%s]", pszProgID      ));
	DBUG_PRINT("", ("pszVerIndProgID   : [%s]", pszVerIndProgID      ));

    if (pszModule == NULL || pszThreadModel == NULL)
    {
      DBUG_RETURN(hr);
    }

    CHAR szCLSID[MAX_PATH];
    CHAR szLIBID[MAX_PATH];

	wchar_t wszCLSID[MAX_PATH];
	StringFromGUID2(clsid, wszCLSID, ARRAYSIZE(wszCLSID));

	wchar_t wszLIBID[MAX_PATH];
	StringFromGUID2(libid, wszLIBID, ARRAYSIZE(wszLIBID));

	Utils::WideToAscii(szCLSID, wszCLSID);
	Utils::WideToAscii(szLIBID, wszLIBID);

    DBUG_PRINT(db_unit, ("szCLSID is %s", szCLSID));
    DBUG_PRINT(db_unit, ("szLIBID is %s", szLIBID));

    TCHAR szSubkey[MAX_PATH];
    // Create the HKCR\CLSID\{<CLSID>} key.
    hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), _T("CLSID\\%s"), szCLSID);

    DBUG_PRINT(db_unit, ("szSubKey is %s", szSubkey));

    if (SUCCEEDED(hr))
    {
        hr = SetHKCRRegistryKeyAndValue(szSubkey, NULL, pszFriendlyName);
      
        // Create the HKCR\CLSID\{<CLSID>}\ProgID key with the default value 
        // '<ProgID>'
        if (SUCCEEDED(hr) && pszProgID != NULL)
        {
            hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey),
                _T("CLSID\\%s\\ProgID"), szCLSID);
            if (SUCCEEDED(hr))
            {
                hr = SetHKCRRegistryKeyAndValue(szSubkey, NULL, pszProgID);
            }
        }

        // Create the HKCR\CLSID\{<CLSID>}\VersionIndependentProgID key with 
        // the default value '<VersionIndependentProgID>'.
        if (SUCCEEDED(hr) && pszVerIndProgID != NULL)
        {
            hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), 
                _T("CLSID\\%s\\VersionIndependentProgID"), szCLSID);
            if (SUCCEEDED(hr))
            {
                hr = SetHKCRRegistryKeyAndValue(szSubkey, NULL, pszVerIndProgID);
            }
        }

        // Create the HKCR\CLSID\{<CLSID>}\TypeLib key with the default value 
        // '{<LIBID>}'
        if (SUCCEEDED(hr))
        {
            hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), 
                _T("CLSID\\%s\\TypeLib"), szCLSID);
            if (SUCCEEDED(hr))
            {
                hr = SetHKCRRegistryKeyAndValue(szSubkey, NULL, szLIBID);
            }
        }

        // Create the HKCR\CLSID\{<CLSID>}\InprocServer32 key.
        if (SUCCEEDED(hr))
        {
            hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), 
                _T("CLSID\\%s\\InprocServer32"), szCLSID);
            if (SUCCEEDED(hr))
            {
                // Set the default value of the InprocServer32 key to the 
                // path of the COM module.
                hr = SetHKCRRegistryKeyAndValue(szSubkey, NULL, pszModule);
                if (SUCCEEDED(hr))
                {
                    // Set the threading model of the component.
                    hr = SetHKCRRegistryKeyAndValue(szSubkey, 
                        _T("ThreadingModel"), pszThreadModel);
                }
            }
        }
    }

    // Create the HKCR\<ProgId> key.
    if (SUCCEEDED(hr) && pszProgID != NULL)
    {
        hr = SetHKCRRegistryKeyAndValue(pszProgID, NULL, pszFriendlyName);

        // Create the HKCR\<ProgId>\CLSID key with the default value 
        // '{<CLSID>}'.
        if (SUCCEEDED(hr))
        {
            hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), _T("%s\\CLSID"), 
                pszProgID);
            if (SUCCEEDED(hr))
            {
                hr = SetHKCRRegistryKeyAndValue(szSubkey, NULL, szCLSID);
            }
        }
    }

    // Create the HKCR\<VersionIndependentProgID> key.
    if (SUCCEEDED(hr) && pszVerIndProgID != NULL)
    {
        hr = SetHKCRRegistryKeyAndValue(pszVerIndProgID, NULL, pszFriendlyName);

        // Create the HKCR\<VersionIndependentProgID>\CLSID key with the 
        // default value '{<CLSID>}'.
        if (SUCCEEDED(hr))
        {
            hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), _T("%s\\CLSID"), 
                pszVerIndProgID);
            if (SUCCEEDED(hr))
            {
                hr = SetHKCRRegistryKeyAndValue(szSubkey, NULL, szCLSID);
            }
        }

        // Create the HKCR\<VersionIndependentProgID>\CurVer key with the 
        // default value '<ProgID>'.
        if (SUCCEEDED(hr) && pszProgID != NULL)
        {
            hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), _T("%s\\CurVer"), 
                pszVerIndProgID);
            if (SUCCEEDED(hr))
            {
                hr = SetHKCRRegistryKeyAndValue(szSubkey, NULL, pszProgID);
            }
        }
    }
    DBUG_RETURN(hr);
}


//
//   FUNCTION: RegisterTypeLib
//
//   PURPOSE: Register the type library.
//
//   PARAMETERS:
//   * pszTypeLib - The type library file.
//
//   NOTE: The function creates the HKCR\TypeLib\{<LIBID>} key and the 
//   HKCR\Interface\{<IID>} key in the registry.
// 
//   HKCR
//   {
//      NoRemove TypeLib
//      {
//          ForceRemove {<LIBID>}
//          {
//              1.0
//              {
//                  0
//                  {
//                      win32 = s '%MODULE%'
//                  }
//                  FLAGS = 0
//                  HELPDIR = s '%MODULE DIR%'
//              }
//          }
//      }
//      NoRemove Interface
//      {
//          ForceRemove {<IID>} = s '<Interface Name>'
//          {
//              ProxyStubClsid = s '<ProgID>'
//              ProxyStubClsid32 = s '<VersionIndependentProgID>'
//              TypeLib = s '{<LIBID>}'
//              {
//                  val Version = s '<TypeLib Version>'
//              }to create class object
//          }
//      }
//   } to create class object
//
HRESULT RegisterTypeLib(LPCTSTR pszTypeLib)
{
    HRESULT hr;
    ITypeLib *pTLB = NULL;

    WCHAR wszTypeLib[MAX_PATH];
    DBUG_ENTER("RegisterTypeLib()");

	DBUG_PRINT("", ("pszTypeLib is %s", pszTypeLib));

    Utils::AsciiToWide(wszTypeLib, (char *)pszTypeLib);

    hr = LoadTypeLibEx(wszTypeLib, REGKIND_REGISTER, &pTLB);
    if (SUCCEEDED(hr))
    {
        pTLB->Release();
    }
	DBUG_PRINT("", ("hr is %d", hr));

    DBUG_RETURN(hr);
}


//
//   FUNCTION: UnregisterInprocServer(void)
//
//   PURPOSE: Unegister the in-process component in the registry.
//
//   PARAMETERS:
//   * clsid - Class ID of the component
//   * pszProgID - ProgID of the component
//   * pszVerIndProgID - Version independent ProgID
//
//   NOTE: The function deletes the HKCR\CLSID\{<CLSID>} key and the 
//   HKCR\<ProgID> key in the registry. to create class objectto create class object
//
HRESULT UnregisterInprocServer(const CLSID& clsid, 
                               LPCTSTR pszProgID, 
                               LPCTSTR pszVerIndProgID)
{
    HRESULT hr = S_OK;

    TCHAR szSubkey[MAX_PATH];
    TCHAR szCLSID[MAX_PATH];

	DBUG_ENTER("UnregisterInprocServer()");

	wchar_t wszCLSID[MAX_PATH];
	StringFromGUID2(clsid, wszCLSID, ARRAYSIZE(wszCLSID));

	Utils::WideToAscii(szCLSID, wszCLSID);

    // Delete the HKCR\CLSID\{<CLSID>} key.
    hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), _T("CLSID\\%s"), szCLSID);
    if (SUCCEEDED(hr))
    {
		DBUG_PRINT("", ("DeleteRegistryTree(%s)", szSubkey));
        hr = HRESULT_FROM_WIN32(DeleteRegistryTree(HKEY_CLASSES_ROOT, szSubkey));
    }

    // Delete the HKCR\<ProgID> key.
    if (SUCCEEDED(hr) && pszProgID != NULL)
    { 
		DBUG_PRINT("", ("DeleteRegistryTree(%s)", pszProgID));
        hr = HRESULT_FROM_WIN32(DeleteRegistryTree(HKEY_CLASSES_ROOT, pszProgID));
    }

    // Delete the HKCR\<VersionIndependentProgID> key.
    if (SUCCEEDED(hr) && pszVerIndProgID != NULL)
    {
		DBUG_PRINT("", ("DeleteRegistryTree(%s)", pszVerIndProgID));
        hr = HRESULT_FROM_WIN32(DeleteRegistryTree(HKEY_CLASSES_ROOT, (LPCTSTR)pszVerIndProgID));
    }

    DBUG_RETURN(hr);
}


//
//   FUNCTION: UnregisterTypeLib
//
//   PURPOSE: Unregister the type library.
//
//   PARAMETERS:
//   * pszTypeLib - The type library file.
//
//   NOTE: The function deletes the HKCR\TypeLib\{<LIBID>} key and the 
//   HKCR\Interface\{<IID>} key in the registry.
//
HRESULT UnregisterTypeLib(LPCTSTR pszTypeLib)
{
    HRESULT hr;

    ITypeLib *pTLB = NULL;
    WCHAR wszTypeLib[MAX_PATH];

    Utils::AsciiToWide(wszTypeLib, (char *)pszTypeLib);
    hr = LoadTypeLibEx(wszTypeLib, REGKIND_NONE, &pTLB);
    if (SUCCEEDED(hr))
    {
        TLIBATTR *pAttr = NULL;
		hr = pTLB->GetLibAttr(&pAttr);
        if (SUCCEEDED(hr))
        {
            hr = UnRegisterTypeLib(pAttr->guid, pAttr->wMajorVerNum, 
                pAttr->wMinorVerNum, pAttr->lcid, pAttr->syskind);

            pTLB->ReleaseTLibAttr(pAttr);
        }

        pTLB->Release();
    }

    return hr;
}
