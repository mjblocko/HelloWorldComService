

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Feb 23 20:26:16 2014
 */
/* Compiler settings for HelloWorldComService.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __HelloWorldComService_h_h__
#define __HelloWorldComService_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISimpleObject_FWD_DEFINED__
#define __ISimpleObject_FWD_DEFINED__
typedef interface ISimpleObject ISimpleObject;

#endif 	/* __ISimpleObject_FWD_DEFINED__ */


#ifndef __SimpleObject_FWD_DEFINED__
#define __SimpleObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class SimpleObject SimpleObject;
#else
typedef struct SimpleObject SimpleObject;
#endif /* __cplusplus */

#endif 	/* __SimpleObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __HelloWorldComService_LIBRARY_DEFINED__
#define __HelloWorldComService_LIBRARY_DEFINED__

/* library HelloWorldComService */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_HelloWorldComService;

#ifndef __ISimpleObject_INTERFACE_DEFINED__
#define __ISimpleObject_INTERFACE_DEFINED__

/* interface ISimpleObject */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISimpleObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("40E88A85-1CAF-4B5F-9496-686CDA31A774")
    ISimpleObject : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE HelloWorld( 
            /* [retval][out] */ BSTR *pRet) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProcessThreadID( 
            /* [out] */ long *pdwProcessId,
            /* [out] */ long *pdwThreadId) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISimpleObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISimpleObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISimpleObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISimpleObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISimpleObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISimpleObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISimpleObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISimpleObject * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *HelloWorld )( 
            ISimpleObject * This,
            /* [retval][out] */ BSTR *pRet);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessThreadID )( 
            ISimpleObject * This,
            /* [out] */ long *pdwProcessId,
            /* [out] */ long *pdwThreadId);
        
        END_INTERFACE
    } ISimpleObjectVtbl;

    interface ISimpleObject
    {
        CONST_VTBL struct ISimpleObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISimpleObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISimpleObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISimpleObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISimpleObject_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISimpleObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISimpleObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISimpleObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISimpleObject_HelloWorld(This,pRet)	\
    ( (This)->lpVtbl -> HelloWorld(This,pRet) ) 

#define ISimpleObject_GetProcessThreadID(This,pdwProcessId,pdwThreadId)	\
    ( (This)->lpVtbl -> GetProcessThreadID(This,pdwProcessId,pdwThreadId) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISimpleObject_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SimpleObject;

#ifdef __cplusplus

class DECLSPEC_UUID("1D054628-D8A9-4216-B7B6-C698BAAF1EE1")
SimpleObject;
#endif
#endif /* __HelloWorldComService_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


