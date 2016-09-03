

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Aug 09 07:50:19 2016
 */
/* Compiler settings for ..\..\..\..\PublisherCommon\InboundCollector.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __InboundCollector_h__
#define __InboundCollector_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IIBCollector_FWD_DEFINED__
#define __IIBCollector_FWD_DEFINED__
typedef interface IIBCollector IIBCollector;

#endif 	/* __IIBCollector_FWD_DEFINED__ */


#ifndef __IInboundEvents_FWD_DEFINED__
#define __IInboundEvents_FWD_DEFINED__
typedef interface IInboundEvents IInboundEvents;

#endif 	/* __IInboundEvents_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_InboundCollector_0000_0000 */
/* [local] */ 


typedef 
enum specialImpType
    {
        SIT_UnimpTbl	= 0x1,
        SIT_PSDBHelperAvail	= ( SIT_UnimpTbl + 1 ) ,
        SIT_ImplAdherence	= ( SIT_PSDBHelperAvail + 1 ) ,
        SIT_UnImplAdherence	= ( SIT_ImplAdherence + 1 ) ,
        SIT_AdherenceLicensed	= ( SIT_UnImplAdherence + 1 ) ,
        SIT_NewDay	= ( SIT_AdherenceLicensed + 1 ) ,
        SIT_SymonView2Enabled	= ( SIT_NewDay + 1 ) 
    } 	specialImpType;

typedef 
enum systemCustomFuncType
    {
        SCFT_GetLicenseOver	= 10000
    } 	systemCustomFuncType;



extern RPC_IF_HANDLE __MIDL_itf_InboundCollector_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_InboundCollector_0000_0000_v0_0_s_ifspec;

#ifndef __IIBCollector_INTERFACE_DEFINED__
#define __IIBCollector_INTERFACE_DEFINED__

/* interface IIBCollector */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IIBCollector;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5FE79210-A806-11D3-811F-00105AA9BDD3")
    IIBCollector : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetInboundID( 
            /* [in] */ VARIANT info) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddListener( 
            /* [in] */ IInboundEvents *pListener,
            /* [out][in] */ short *cookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveListener( 
            /* [in] */ short cookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableConnection( 
            /* [in] */ BOOL open) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CustomIF( 
            /* [in] */ int type,
            /* [out][in] */ VARIANT *internalInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetConfig( 
            /* [out][in] */ VARIANT *config,
            /* [in] */ BOOL restart) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetConfig( 
            /* [out][in] */ VARIANT *config) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUpdatePulse( 
            /* [in] */ int secs,
            /* [in] */ BOOL onlyOnNoActivity) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAllKeys( 
            /* [out] */ VARIANT *keys) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetImplemented( 
            /* [in] */ VARIANT keys,
            /* [in] */ VARIANT flds) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SpecialImplement( 
            /* [in] */ specialImpType type,
            /* [in] */ VARIANT info) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIBCollectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIBCollector * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIBCollector * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIBCollector * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIBCollector * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIBCollector * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIBCollector * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIBCollector * This,
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
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetInboundID )( 
            IIBCollector * This,
            /* [in] */ VARIANT info);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddListener )( 
            IIBCollector * This,
            /* [in] */ IInboundEvents *pListener,
            /* [out][in] */ short *cookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveListener )( 
            IIBCollector * This,
            /* [in] */ short cookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnableConnection )( 
            IIBCollector * This,
            /* [in] */ BOOL open);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CustomIF )( 
            IIBCollector * This,
            /* [in] */ int type,
            /* [out][in] */ VARIANT *internalInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetConfig )( 
            IIBCollector * This,
            /* [out][in] */ VARIANT *config,
            /* [in] */ BOOL restart);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetConfig )( 
            IIBCollector * This,
            /* [out][in] */ VARIANT *config);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetUpdatePulse )( 
            IIBCollector * This,
            /* [in] */ int secs,
            /* [in] */ BOOL onlyOnNoActivity);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAllKeys )( 
            IIBCollector * This,
            /* [out] */ VARIANT *keys);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetImplemented )( 
            IIBCollector * This,
            /* [in] */ VARIANT keys,
            /* [in] */ VARIANT flds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SpecialImplement )( 
            IIBCollector * This,
            /* [in] */ specialImpType type,
            /* [in] */ VARIANT info);
        
        END_INTERFACE
    } IIBCollectorVtbl;

    interface IIBCollector
    {
        CONST_VTBL struct IIBCollectorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIBCollector_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIBCollector_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIBCollector_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIBCollector_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIBCollector_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIBCollector_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIBCollector_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IIBCollector_SetInboundID(This,info)	\
    ( (This)->lpVtbl -> SetInboundID(This,info) ) 

#define IIBCollector_AddListener(This,pListener,cookie)	\
    ( (This)->lpVtbl -> AddListener(This,pListener,cookie) ) 

#define IIBCollector_RemoveListener(This,cookie)	\
    ( (This)->lpVtbl -> RemoveListener(This,cookie) ) 

#define IIBCollector_EnableConnection(This,open)	\
    ( (This)->lpVtbl -> EnableConnection(This,open) ) 

#define IIBCollector_CustomIF(This,type,internalInfo)	\
    ( (This)->lpVtbl -> CustomIF(This,type,internalInfo) ) 

#define IIBCollector_SetConfig(This,config,restart)	\
    ( (This)->lpVtbl -> SetConfig(This,config,restart) ) 

#define IIBCollector_GetConfig(This,config)	\
    ( (This)->lpVtbl -> GetConfig(This,config) ) 

#define IIBCollector_SetUpdatePulse(This,secs,onlyOnNoActivity)	\
    ( (This)->lpVtbl -> SetUpdatePulse(This,secs,onlyOnNoActivity) ) 

#define IIBCollector_GetAllKeys(This,keys)	\
    ( (This)->lpVtbl -> GetAllKeys(This,keys) ) 

#define IIBCollector_SetImplemented(This,keys,flds)	\
    ( (This)->lpVtbl -> SetImplemented(This,keys,flds) ) 

#define IIBCollector_SpecialImplement(This,type,info)	\
    ( (This)->lpVtbl -> SpecialImplement(This,type,info) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIBCollector_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_InboundCollector_0000_0001 */
/* [local] */ 

typedef 
enum changeType
    {
        CT_InboundStateChange	= 0x1,
        CT_InboundAdd	= ( CT_InboundStateChange + 1 ) ,
        CT_InboundConfigChange	= ( CT_InboundAdd + 1 ) ,
        CT_InboundPulse	= ( CT_InboundConfigChange + 1 ) ,
        CT_InboundErrMsg	= ( CT_InboundPulse + 1 ) ,
        CT_InboundInfoMsg	= ( CT_InboundErrMsg + 1 ) ,
        CT_InboundCustom	= ( CT_InboundInfoMsg + 1 ) ,
        CT_InboundKeysChanged	= ( CT_InboundCustom + 1 ) ,
        CT_InboundStateActiveWithInfo	= ( CT_InboundKeysChanged + 1 ) ,
        CT_InboundProgress	= ( CT_InboundStateActiveWithInfo + 1 ) 
    } 	changeType;



extern RPC_IF_HANDLE __MIDL_itf_InboundCollector_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_InboundCollector_0000_0001_v0_0_s_ifspec;

#ifndef __IInboundEvents_INTERFACE_DEFINED__
#define __IInboundEvents_INTERFACE_DEFINED__

/* interface IInboundEvents */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInboundEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5FE79213-A806-11D3-811F-00105AA9BDD3")
    IInboundEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InboundChange( 
            /* [in] */ short type,
            /* [in] */ VARIANT info) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IInboundEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInboundEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInboundEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInboundEvents * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InboundChange )( 
            IInboundEvents * This,
            /* [in] */ short type,
            /* [in] */ VARIANT info);
        
        END_INTERFACE
    } IInboundEventsVtbl;

    interface IInboundEvents
    {
        CONST_VTBL struct IInboundEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInboundEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInboundEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInboundEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInboundEvents_InboundChange(This,type,info)	\
    ( (This)->lpVtbl -> InboundChange(This,type,info) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInboundEvents_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


