#include <windows.h>
#include <tchar.h>
#include "classfactory.h"           // For the class factory
#include "HelloWorldComService_i.c"      // For component GUIDs
#include "reg.h"
#include "dbug_msvc.hpp"

HINSTANCE   g_hInst     = NULL;
long        g_cDllRef   = 0;

static CHAR * db_unit = __FILE__;

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    DBUG_PUSH("d:t:O,dllmain.dbg");

    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Hold the instance of this DLL module, we will use it to get the 
        // path of the DLL to register the component.
        g_hInst = hInstance;
        DisableThreadLibraryCalls(hInstance);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}


//
//   FUNCTION: DllGetClassObject(REFCLSID, REFIID, void **)
//
//   PURPOSE: Create the class factory and query to the specific interface.
//
//   PARAMETERS:
//   * rclsid - The CLSID that will associate the correct data and code.
//   * riid - A reference to the identifier of the interface that the caller 
//     is to use to communicate with the class object.
//   * ppv - The address of a pointer variable that receives the interface 
//     pointer requested in riid. Upon successful return, *ppv contains the 
//     requested interface pointer. If an error occurs, the interface pointer 
//     is NULL. 
//
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    HRESULT hr = CLASS_E_CLASSNOTAVAILABLE;

	DBUG_ENTER("DllGetClassObject()");

    if (IsEqualCLSID(CLSID_SimpleObject, rclsid))
    {
        hr = E_OUTOFMEMORY;

        ClassFactory *pClassFactory = new ClassFactory();
        if (pClassFactory)
        {
            hr = pClassFactory->QueryInterface(riid, ppv);
            pClassFactory->Release();
        }
		else {
			DBUG_PRINT("", ("Failed to create class object"))
		}
    }

	DBUG_PRINT("", ("hr is %d",hr))

    DBUG_RETURN(hr);
}

//
//   FUNCTION: DllCanUnloadNow(void)
//
//   PURPOSE: Check if we can unload the component from the memory.
//
//   NOTE: The component can be unloaded from the memory when its reference 
//   count is zero (i.e. nobody is still using the component).
// 
STDAPI DllCanUnloadNow(void)
{
    return g_cDllRef > 0 ? S_FALSE : S_OK;
}


//
//   FUNCTION: DllRegisterServer(void)
//
//   PURPOSE: Register the COM server.
// 
STDAPI DllRegisterServer(void)
{
    HRESULT hr;
    TCHAR szModule[MAX_PATH];

    DBUG_ENTER("DllRegisterServer");

    if (GetModuleFileName(g_hInst, szModule, ARRAYSIZE(szModule)) == 0)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        DBUG_PRINT(db_unit, ("GetModuleFileName failed with %d", hr));
        DBUG_RETURN(hr);
    }

    // Register the component.
    hr = RegisterInprocServer(szModule, 
        CLSID_SimpleObject, 
        _T("HelloWorldComService.SimpleObject Class"), 
        _T("Apartment"), 
        LIBID_HelloWorldComService, 
        _T("HelloWorldComService.SimpleObject.1"), 
        _T("HelloWorldComService.SimpleObject"));
    if (SUCCEEDED(hr))
    {
        // Register the type library.
        hr = RegisterTypeLib(szModule);
        DBUG_PRINT(db_unit, ("RegisterTypeLib returned %d", hr));
    }
    else {
        DBUG_PRINT(db_unit, ("RegisterInprocServer failed with %d", hr));
    }

    DBUG_RETURN(hr);
}


//
//   FUNCTION: DllUnregisterServer(void)
//
//   PURPOSE: Unregister the COM server.
// 
STDAPI DllUnregisterServer(void)
{
    HRESULT hr = S_OK;
    TCHAR szModule[MAX_PATH];

    DBUG_ENTER("DllUnregisterServer");

    if (GetModuleFileName(g_hInst, szModule, ARRAYSIZE(szModule)) == 0)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        DBUG_RETURN(hr);
    }

    // Unregister the component.
    hr = UnregisterInprocServer(CLSID_SimpleObject, 
        _T("HelloWorldComService.SimpleObject.1"), 
        _T("HelloWorldComService.SimpleObject"));
    if (SUCCEEDED(hr))
    {
        // Unregister the type library.
        hr = UnregisterTypeLib(szModule);
    }
    DBUG_RETURN(hr);
}
