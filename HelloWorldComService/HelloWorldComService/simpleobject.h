
#ifndef SIMPLEOBJECT_H_
#define SIMPLEOBJECT_H_

#include "HelloWorldComService_h.h"  // For ISimpleObject

class SimpleObject : public ISimpleObject
{
public:
  // IUnknown
  IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv);
  IFACEMETHODIMP_(ULONG) AddRef();
  IFACEMETHODIMP_(ULONG) Release();

  // IDispatch
  IFACEMETHODIMP GetTypeInfoCount(UINT *pctinfo);
  IFACEMETHODIMP GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo **pptinfo);
  IFACEMETHODIMP GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID* rgdispid);
  IFACEMETHODIMP Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pdispParams, VARIANT *pvarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);

    // ISimpleObject
  IFACEMETHODIMP get_FloatProperty(FLOAT *pVal);
	IFACEMETHODIMP put_FloatProperty(FLOAT newVal);
	IFACEMETHODIMP HelloWorld(BSTR *pRet);
	IFACEMETHODIMP GetProcessThreadID(LONG *pdwProcessId, LONG *pdwThreadId);

  SimpleObject();

protected:
  virtual ~SimpleObject();

private:
  // Reference count of component.
  long m_cRef;

  // The value of FloatProperty.
  float m_fField;

  // Pointer to type-library (for implementing IDispatch).
  LPTYPEINFO m_ptinfo;

  // Helper function to load the type info (for implementing IDispatch).
  HRESULT LoadTypeInfo(ITypeInfo **pptinfo, const CLSID& libid, const CLSID& iid, LCID lcid);
};

#endif  // SIMPLEOBJECT_H_
