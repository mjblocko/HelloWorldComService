
#ifndef REG_H_
#define REG_H_

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
//   * libid - Type library ID.
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
//              } DEFINE_GUID(<< name >> ,
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
                             LPCTSTR pszVerIndProgID);


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
//   HKCR\<ProgID> key in the registry.
//
HRESULT UnregisterInprocServer(const CLSID& clsid, 
                               LPCTSTR pszProgID, 
                               LPCTSTR pszVerIndProgID);


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
//              }
//          }
//      }
//   }
//
HRESULT RegisterTypeLib(LPCTSTR pszTypeLib);


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
HRESULT UnregisterTypeLib(LPCTSTR pszTypeLib);

#endif  // REG_H_
