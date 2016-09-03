

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Aug 09 07:50:20 2016
 */
/* Compiler settings for ..\..\..\..\Publisher2000Server\Publisher2000Server.idl:
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

#ifndef __Publisher2000Server_h__
#define __Publisher2000Server_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPubSvr_FWD_DEFINED__
#define __IPubSvr_FWD_DEFINED__
typedef interface IPubSvr IPubSvr;

#endif 	/* __IPubSvr_FWD_DEFINED__ */


#ifndef __IInboundSvr_FWD_DEFINED__
#define __IInboundSvr_FWD_DEFINED__
typedef interface IInboundSvr IInboundSvr;

#endif 	/* __IInboundSvr_FWD_DEFINED__ */


#ifndef __ICommonListener_FWD_DEFINED__
#define __ICommonListener_FWD_DEFINED__
typedef interface ICommonListener ICommonListener;

#endif 	/* __ICommonListener_FWD_DEFINED__ */


#ifndef __IPSDBListener_FWD_DEFINED__
#define __IPSDBListener_FWD_DEFINED__
typedef interface IPSDBListener IPSDBListener;

#endif 	/* __IPSDBListener_FWD_DEFINED__ */


#ifndef __IPSDBHelper_FWD_DEFINED__
#define __IPSDBHelper_FWD_DEFINED__
typedef interface IPSDBHelper IPSDBHelper;

#endif 	/* __IPSDBHelper_FWD_DEFINED__ */


#ifndef __IDataSecurity_FWD_DEFINED__
#define __IDataSecurity_FWD_DEFINED__
typedef interface IDataSecurity IDataSecurity;

#endif 	/* __IDataSecurity_FWD_DEFINED__ */


#ifndef __IFileStreamer_FWD_DEFINED__
#define __IFileStreamer_FWD_DEFINED__
typedef interface IFileStreamer IFileStreamer;

#endif 	/* __IFileStreamer_FWD_DEFINED__ */


#ifndef __PubSvr_FWD_DEFINED__
#define __PubSvr_FWD_DEFINED__

#ifdef __cplusplus
typedef class PubSvr PubSvr;
#else
typedef struct PubSvr PubSvr;
#endif /* __cplusplus */

#endif 	/* __PubSvr_FWD_DEFINED__ */


#ifndef __InboundSvr_FWD_DEFINED__
#define __InboundSvr_FWD_DEFINED__

#ifdef __cplusplus
typedef class InboundSvr InboundSvr;
#else
typedef struct InboundSvr InboundSvr;
#endif /* __cplusplus */

#endif 	/* __InboundSvr_FWD_DEFINED__ */


#ifndef __PSDBHelper_FWD_DEFINED__
#define __PSDBHelper_FWD_DEFINED__

#ifdef __cplusplus
typedef class PSDBHelper PSDBHelper;
#else
typedef struct PSDBHelper PSDBHelper;
#endif /* __cplusplus */

#endif 	/* __PSDBHelper_FWD_DEFINED__ */


#ifndef __DataSecurity_FWD_DEFINED__
#define __DataSecurity_FWD_DEFINED__

#ifdef __cplusplus
typedef class DataSecurity DataSecurity;
#else
typedef struct DataSecurity DataSecurity;
#endif /* __cplusplus */

#endif 	/* __DataSecurity_FWD_DEFINED__ */


#ifndef __FileStreamer_FWD_DEFINED__
#define __FileStreamer_FWD_DEFINED__

#ifdef __cplusplus
typedef class FileStreamer FileStreamer;
#else
typedef struct FileStreamer FileStreamer;
#endif /* __cplusplus */

#endif 	/* __FileStreamer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "adohelper.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_Publisher2000Server_0000_0000 */
/* [local] */ 



typedef unsigned long REFNUM;



extern RPC_IF_HANDLE __MIDL_itf_Publisher2000Server_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Publisher2000Server_0000_0000_v0_0_s_ifspec;

#ifndef __IPubSvr_INTERFACE_DEFINED__
#define __IPubSvr_INTERFACE_DEFINED__

/* interface IPubSvr */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPubSvr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D03D7B7C-71D0-11D3-80EA-00105AA9BDD3")
    IPubSvr : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenConnection( 
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM refnum,
            /* [in] */ BOOL open) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumInbounds( 
            /* [in] */ VARIANT session,
            /* [in] */ BOOL getImplemented,
            /* [out][in] */ VARIANT *inbounds,
            /* [out][in] */ VARIANT *implemented) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddListener( 
            /* [in] */ ICommonListener *ppv,
            /* [in] */ short type,
            /* [out][in] */ WORD *cookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveListener( 
            /* [in] */ short type,
            /* [in] */ WORD cookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExposePubVar( 
            /* [in] */ short exposeHow,
            /* [out][in] */ VARIANT *pubvars) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddPubVariable( 
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *pubfld) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ModifyPubVariable( 
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *pubfld,
            /* [in] */ BOOL bInclCalc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemovePubVariable( 
            /* [in] */ VARIANT session,
            /* [in] */ VARIANT pubfld) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPubVariable( 
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *updateVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveDatabase( 
            /* [in] */ VARIANT session,
            /* [in] */ VARIANT backup) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SynchClock( 
            /* [in] */ VARIANT session) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TVXact( 
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *pCentral,
            /* [out][in] */ VARIANT *pIBs,
            /* [in] */ int type) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCollectorSchema( 
            /* [in] */ VARIANT session,
            /* [in] */ int collectorType,
            /* [out][in] */ VARIANT *data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetImplementedforIB( 
            /* [in] */ VARIANT session,
            /* [in] */ ULONG refnum,
            /* [in] */ int typeID,
            /* [out][in] */ VARIANT *keys,
            /* [out][in] */ VARIANT *flds) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLegacyRefs( 
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *legacyRefs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddLegacyRef( 
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *legacyref) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadCalcs( 
            /* [in] */ VARIANT session,
            /* [in] */ VARIANT calcdata,
            /* [in] */ int flex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetServerIP( 
            /* [out][in] */ VARIANT *ipAddress) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateDataTblBlob( 
            /* [in] */ VARIANT blob) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadSymonVarAssoc( 
            /* [in] */ VARIANT symonPubAssoc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddBusEvent( 
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *event) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateBusEvent( 
            /* [in] */ VARIANT session,
            /* [in] */ VARIANT event) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteBusEvent( 
            /* [in] */ VARIANT session,
            /* [in] */ ULONG refnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetInboundDbSrcs( 
            /* [out][in] */ VARIANT *var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyLicense( 
            /* [in] */ VARIANT client,
            /* [out][in] */ VARIANT *data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCollectorNames( 
            /* [out][in] */ VARIANT *data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateHistorianTable( 
            /* [in] */ VARIANT data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveHistorianTable( 
            /* [in] */ VARIANT data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReloadKeysInHistoricalDB( 
            /* [in] */ ULONG refnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumPubVariables( 
            /* [out][in] */ VARIANT *pubvars) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAdherence4Me( 
            /* [in] */ VARIANT AdhTblStuff,
            /* [in] */ VARIANT adh_states) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAdherenceStates( 
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateAdherenceStates( 
            /* [in] */ VARIANT addStates,
            /* [in] */ VARIANT modStates) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDBHeader( 
            /* [out][in] */ VARIANT *data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDBHeader( 
            /* [out][in] */ VARIANT *data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetXMLData( 
            /* [out][in] */ VARIANT *inbounds,
            /* [out][in] */ VARIANT *ctypes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFeatureKey( 
            /* [out][in] */ VARIANT *mask) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE isCTypeAvail( 
            /* [out][in] */ VARIANT *var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAggEngineConfig( 
            /* [out][in] */ VARIANT *var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAggEngineConfig( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenConnectionSE( 
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM refnum,
            /* [in] */ BOOL open,
            /* [in] */ BSTR LoginSession) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPubSvrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPubSvr * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPubSvr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPubSvr * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPubSvr * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPubSvr * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPubSvr * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPubSvr * This,
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
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenConnection )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM refnum,
            /* [in] */ BOOL open);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumInbounds )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ BOOL getImplemented,
            /* [out][in] */ VARIANT *inbounds,
            /* [out][in] */ VARIANT *implemented);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddListener )( 
            IPubSvr * This,
            /* [in] */ ICommonListener *ppv,
            /* [in] */ short type,
            /* [out][in] */ WORD *cookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveListener )( 
            IPubSvr * This,
            /* [in] */ short type,
            /* [in] */ WORD cookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExposePubVar )( 
            IPubSvr * This,
            /* [in] */ short exposeHow,
            /* [out][in] */ VARIANT *pubvars);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddPubVariable )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *pubfld);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ModifyPubVariable )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *pubfld,
            /* [in] */ BOOL bInclCalc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemovePubVariable )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ VARIANT pubfld);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPubVariable )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *updateVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveDatabase )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ VARIANT backup);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SynchClock )( 
            IPubSvr * This,
            /* [in] */ VARIANT session);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TVXact )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *pCentral,
            /* [out][in] */ VARIANT *pIBs,
            /* [in] */ int type);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCollectorSchema )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ int collectorType,
            /* [out][in] */ VARIANT *data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetImplementedforIB )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ ULONG refnum,
            /* [in] */ int typeID,
            /* [out][in] */ VARIANT *keys,
            /* [out][in] */ VARIANT *flds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLegacyRefs )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *legacyRefs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddLegacyRef )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *legacyref);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadCalcs )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ VARIANT calcdata,
            /* [in] */ int flex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetServerIP )( 
            IPubSvr * This,
            /* [out][in] */ VARIANT *ipAddress);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateDataTblBlob )( 
            IPubSvr * This,
            /* [in] */ VARIANT blob);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadSymonVarAssoc )( 
            IPubSvr * This,
            /* [in] */ VARIANT symonPubAssoc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddBusEvent )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *event);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateBusEvent )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ VARIANT event);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteBusEvent )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ ULONG refnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetInboundDbSrcs )( 
            IPubSvr * This,
            /* [out][in] */ VARIANT *var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyLicense )( 
            IPubSvr * This,
            /* [in] */ VARIANT client,
            /* [out][in] */ VARIANT *data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCollectorNames )( 
            IPubSvr * This,
            /* [out][in] */ VARIANT *data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateHistorianTable )( 
            IPubSvr * This,
            /* [in] */ VARIANT data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveHistorianTable )( 
            IPubSvr * This,
            /* [in] */ VARIANT data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReloadKeysInHistoricalDB )( 
            IPubSvr * This,
            /* [in] */ ULONG refnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumPubVariables )( 
            IPubSvr * This,
            /* [out][in] */ VARIANT *pubvars);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAdherence4Me )( 
            IPubSvr * This,
            /* [in] */ VARIANT AdhTblStuff,
            /* [in] */ VARIANT adh_states);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAdherenceStates )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [out][in] */ VARIANT *data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateAdherenceStates )( 
            IPubSvr * This,
            /* [in] */ VARIANT addStates,
            /* [in] */ VARIANT modStates);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDBHeader )( 
            IPubSvr * This,
            /* [out][in] */ VARIANT *data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDBHeader )( 
            IPubSvr * This,
            /* [out][in] */ VARIANT *data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetXMLData )( 
            IPubSvr * This,
            /* [out][in] */ VARIANT *inbounds,
            /* [out][in] */ VARIANT *ctypes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFeatureKey )( 
            IPubSvr * This,
            /* [out][in] */ VARIANT *mask);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *isCTypeAvail )( 
            IPubSvr * This,
            /* [out][in] */ VARIANT *var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAggEngineConfig )( 
            IPubSvr * This,
            /* [out][in] */ VARIANT *var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAggEngineConfig )( 
            IPubSvr * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenConnectionSE )( 
            IPubSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM refnum,
            /* [in] */ BOOL open,
            /* [in] */ BSTR LoginSession);
        
        END_INTERFACE
    } IPubSvrVtbl;

    interface IPubSvr
    {
        CONST_VTBL struct IPubSvrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPubSvr_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPubSvr_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPubSvr_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPubSvr_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPubSvr_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPubSvr_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPubSvr_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPubSvr_OpenConnection(This,session,refnum,open)	\
    ( (This)->lpVtbl -> OpenConnection(This,session,refnum,open) ) 

#define IPubSvr_EnumInbounds(This,session,getImplemented,inbounds,implemented)	\
    ( (This)->lpVtbl -> EnumInbounds(This,session,getImplemented,inbounds,implemented) ) 

#define IPubSvr_AddListener(This,ppv,type,cookie)	\
    ( (This)->lpVtbl -> AddListener(This,ppv,type,cookie) ) 

#define IPubSvr_RemoveListener(This,type,cookie)	\
    ( (This)->lpVtbl -> RemoveListener(This,type,cookie) ) 

#define IPubSvr_ExposePubVar(This,exposeHow,pubvars)	\
    ( (This)->lpVtbl -> ExposePubVar(This,exposeHow,pubvars) ) 

#define IPubSvr_AddPubVariable(This,session,pubfld)	\
    ( (This)->lpVtbl -> AddPubVariable(This,session,pubfld) ) 

#define IPubSvr_ModifyPubVariable(This,session,pubfld,bInclCalc)	\
    ( (This)->lpVtbl -> ModifyPubVariable(This,session,pubfld,bInclCalc) ) 

#define IPubSvr_RemovePubVariable(This,session,pubfld)	\
    ( (This)->lpVtbl -> RemovePubVariable(This,session,pubfld) ) 

#define IPubSvr_GetPubVariable(This,session,updateVal)	\
    ( (This)->lpVtbl -> GetPubVariable(This,session,updateVal) ) 

#define IPubSvr_SaveDatabase(This,session,backup)	\
    ( (This)->lpVtbl -> SaveDatabase(This,session,backup) ) 

#define IPubSvr_SynchClock(This,session)	\
    ( (This)->lpVtbl -> SynchClock(This,session) ) 

#define IPubSvr_TVXact(This,session,pCentral,pIBs,type)	\
    ( (This)->lpVtbl -> TVXact(This,session,pCentral,pIBs,type) ) 

#define IPubSvr_GetCollectorSchema(This,session,collectorType,data)	\
    ( (This)->lpVtbl -> GetCollectorSchema(This,session,collectorType,data) ) 

#define IPubSvr_GetImplementedforIB(This,session,refnum,typeID,keys,flds)	\
    ( (This)->lpVtbl -> GetImplementedforIB(This,session,refnum,typeID,keys,flds) ) 

#define IPubSvr_GetLegacyRefs(This,session,legacyRefs)	\
    ( (This)->lpVtbl -> GetLegacyRefs(This,session,legacyRefs) ) 

#define IPubSvr_AddLegacyRef(This,session,legacyref)	\
    ( (This)->lpVtbl -> AddLegacyRef(This,session,legacyref) ) 

#define IPubSvr_LoadCalcs(This,session,calcdata,flex)	\
    ( (This)->lpVtbl -> LoadCalcs(This,session,calcdata,flex) ) 

#define IPubSvr_GetServerIP(This,ipAddress)	\
    ( (This)->lpVtbl -> GetServerIP(This,ipAddress) ) 

#define IPubSvr_UpdateDataTblBlob(This,blob)	\
    ( (This)->lpVtbl -> UpdateDataTblBlob(This,blob) ) 

#define IPubSvr_LoadSymonVarAssoc(This,symonPubAssoc)	\
    ( (This)->lpVtbl -> LoadSymonVarAssoc(This,symonPubAssoc) ) 

#define IPubSvr_AddBusEvent(This,session,event)	\
    ( (This)->lpVtbl -> AddBusEvent(This,session,event) ) 

#define IPubSvr_UpdateBusEvent(This,session,event)	\
    ( (This)->lpVtbl -> UpdateBusEvent(This,session,event) ) 

#define IPubSvr_DeleteBusEvent(This,session,refnum)	\
    ( (This)->lpVtbl -> DeleteBusEvent(This,session,refnum) ) 

#define IPubSvr_GetInboundDbSrcs(This,var)	\
    ( (This)->lpVtbl -> GetInboundDbSrcs(This,var) ) 

#define IPubSvr_VerifyLicense(This,client,data)	\
    ( (This)->lpVtbl -> VerifyLicense(This,client,data) ) 

#define IPubSvr_GetCollectorNames(This,data)	\
    ( (This)->lpVtbl -> GetCollectorNames(This,data) ) 

#define IPubSvr_UpdateHistorianTable(This,data)	\
    ( (This)->lpVtbl -> UpdateHistorianTable(This,data) ) 

#define IPubSvr_RemoveHistorianTable(This,data)	\
    ( (This)->lpVtbl -> RemoveHistorianTable(This,data) ) 

#define IPubSvr_ReloadKeysInHistoricalDB(This,refnum)	\
    ( (This)->lpVtbl -> ReloadKeysInHistoricalDB(This,refnum) ) 

#define IPubSvr_EnumPubVariables(This,pubvars)	\
    ( (This)->lpVtbl -> EnumPubVariables(This,pubvars) ) 

#define IPubSvr_SetAdherence4Me(This,AdhTblStuff,adh_states)	\
    ( (This)->lpVtbl -> SetAdherence4Me(This,AdhTblStuff,adh_states) ) 

#define IPubSvr_GetAdherenceStates(This,session,data)	\
    ( (This)->lpVtbl -> GetAdherenceStates(This,session,data) ) 

#define IPubSvr_UpdateAdherenceStates(This,addStates,modStates)	\
    ( (This)->lpVtbl -> UpdateAdherenceStates(This,addStates,modStates) ) 

#define IPubSvr_GetDBHeader(This,data)	\
    ( (This)->lpVtbl -> GetDBHeader(This,data) ) 

#define IPubSvr_SetDBHeader(This,data)	\
    ( (This)->lpVtbl -> SetDBHeader(This,data) ) 

#define IPubSvr_GetXMLData(This,inbounds,ctypes)	\
    ( (This)->lpVtbl -> GetXMLData(This,inbounds,ctypes) ) 

#define IPubSvr_GetFeatureKey(This,mask)	\
    ( (This)->lpVtbl -> GetFeatureKey(This,mask) ) 

#define IPubSvr_isCTypeAvail(This,var)	\
    ( (This)->lpVtbl -> isCTypeAvail(This,var) ) 

#define IPubSvr_GetAggEngineConfig(This,var)	\
    ( (This)->lpVtbl -> GetAggEngineConfig(This,var) ) 

#define IPubSvr_SetAggEngineConfig(This,var)	\
    ( (This)->lpVtbl -> SetAggEngineConfig(This,var) ) 

#define IPubSvr_OpenConnectionSE(This,session,refnum,open,LoginSession)	\
    ( (This)->lpVtbl -> OpenConnectionSE(This,session,refnum,open,LoginSession) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPubSvr_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_Publisher2000Server_0000_0001 */
/* [local] */ 

typedef 
enum _DETAIL_LEVEL
    {
        DETAIL_implemented	= 0,
        DETAIL_tables	= ( DETAIL_implemented + 1 ) ,
        DETAIL_tables_with_desc	= ( DETAIL_tables + 1 ) ,
        DETAIL_both	= ( DETAIL_tables_with_desc + 1 ) ,
        DETAIL_both_with_desc	= ( DETAIL_both + 1 ) 
    } 	DETAIL_LEVEL;

typedef 
enum specialImpTypeSvr
    {
        SSIT_UnimpTbl	= 0x1,
        SSIT_PSDBHelperAvail	= ( SSIT_UnimpTbl + 1 ) ,
        SSIT_ImplAdherence	= ( SSIT_PSDBHelperAvail + 1 ) ,
        SSIT_UnImplAdherence	= ( SSIT_ImplAdherence + 1 ) ,
        SSIT_AdherenceLicensed	= ( SSIT_UnImplAdherence + 1 ) 
    } 	specialImpTypeSvr;

typedef 
enum systemCustomIFTypes
    {
        SCIF_GetAdhIBInfo	= 3000,
        SCIF_GetAdh_TableCnt	= ( SCIF_GetAdhIBInfo + 1 ) ,
        SCIF_GetAdh_States	= ( SCIF_GetAdh_TableCnt + 1 ) 
    } 	systemCustomIFTypes;



extern RPC_IF_HANDLE __MIDL_itf_Publisher2000Server_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Publisher2000Server_0000_0001_v0_0_s_ifspec;

#ifndef __IInboundSvr_INTERFACE_DEFINED__
#define __IInboundSvr_INTERFACE_DEFINED__

/* interface IInboundSvr */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInboundSvr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A7BB4BC5-75C5-11D3-80ED-00105AA9BDD3")
    IInboundSvr : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetInboundConfig( 
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM objid,
            /* [out][in] */ VARIANT *config) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetInboundConfig( 
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM objid,
            /* [in] */ VARIANT config,
            /* [in] */ BOOL Ok2Disconnect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteInbound( 
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM objid,
            /* [in] */ BOOL bDeleteHistorian) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CustomInboundFunc( 
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM objid,
            /* [in] */ int funcID,
            /* [out][in] */ VARIANT *internal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddInbound( 
            /* [in] */ VARIANT session,
            /* [in] */ VARIANT info,
            /* [out][in] */ REFNUM *refnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenSession( 
            /* [out][in] */ VARIANT *session) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseSession( 
            /* [in] */ VARIANT session) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetConnection( 
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM refnum,
            /* [in] */ BOOL open) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetComPorts( 
            /* [out][in] */ VARIANT *session,
            /* [out][in] */ VARIANT *comports) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddListener( 
            /* [in] */ ICommonListener *ppv,
            /* [in] */ short type,
            /* [out][in] */ WORD *cookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveListener( 
            /* [in] */ short type,
            /* [in] */ WORD cookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsUniqueInboundName( 
            /* [in] */ VARIANT session,
            /* [in] */ VARIANT inboundinfo,
            /* [out][in] */ BOOL *isUnique) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAllKeys( 
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM ibRef,
            /* [out] */ VARIANT *keys) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetImplemented( 
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM ibRef,
            /* [in] */ VARIANT keys,
            /* [in] */ VARIANT flds) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SpecialImplement( 
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM ibRef,
            /* [in] */ specialImpTypeSvr type,
            /* [in] */ VARIANT info) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteInboundSE( 
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM objid,
            /* [in] */ BOOL bDeleteHistorian,
            /* [in] */ BSTR LoginSession) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IInboundSvrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInboundSvr * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInboundSvr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInboundSvr * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInboundSvr * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInboundSvr * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInboundSvr * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInboundSvr * This,
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
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetInboundConfig )( 
            IInboundSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM objid,
            /* [out][in] */ VARIANT *config);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetInboundConfig )( 
            IInboundSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM objid,
            /* [in] */ VARIANT config,
            /* [in] */ BOOL Ok2Disconnect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteInbound )( 
            IInboundSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM objid,
            /* [in] */ BOOL bDeleteHistorian);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CustomInboundFunc )( 
            IInboundSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM objid,
            /* [in] */ int funcID,
            /* [out][in] */ VARIANT *internal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddInbound )( 
            IInboundSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ VARIANT info,
            /* [out][in] */ REFNUM *refnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenSession )( 
            IInboundSvr * This,
            /* [out][in] */ VARIANT *session);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseSession )( 
            IInboundSvr * This,
            /* [in] */ VARIANT session);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetConnection )( 
            IInboundSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM refnum,
            /* [in] */ BOOL open);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetComPorts )( 
            IInboundSvr * This,
            /* [out][in] */ VARIANT *session,
            /* [out][in] */ VARIANT *comports);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddListener )( 
            IInboundSvr * This,
            /* [in] */ ICommonListener *ppv,
            /* [in] */ short type,
            /* [out][in] */ WORD *cookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveListener )( 
            IInboundSvr * This,
            /* [in] */ short type,
            /* [in] */ WORD cookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsUniqueInboundName )( 
            IInboundSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ VARIANT inboundinfo,
            /* [out][in] */ BOOL *isUnique);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAllKeys )( 
            IInboundSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM ibRef,
            /* [out] */ VARIANT *keys);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetImplemented )( 
            IInboundSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM ibRef,
            /* [in] */ VARIANT keys,
            /* [in] */ VARIANT flds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SpecialImplement )( 
            IInboundSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM ibRef,
            /* [in] */ specialImpTypeSvr type,
            /* [in] */ VARIANT info);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteInboundSE )( 
            IInboundSvr * This,
            /* [in] */ VARIANT session,
            /* [in] */ REFNUM objid,
            /* [in] */ BOOL bDeleteHistorian,
            /* [in] */ BSTR LoginSession);
        
        END_INTERFACE
    } IInboundSvrVtbl;

    interface IInboundSvr
    {
        CONST_VTBL struct IInboundSvrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInboundSvr_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInboundSvr_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInboundSvr_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInboundSvr_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IInboundSvr_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IInboundSvr_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IInboundSvr_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IInboundSvr_GetInboundConfig(This,session,objid,config)	\
    ( (This)->lpVtbl -> GetInboundConfig(This,session,objid,config) ) 

#define IInboundSvr_SetInboundConfig(This,session,objid,config,Ok2Disconnect)	\
    ( (This)->lpVtbl -> SetInboundConfig(This,session,objid,config,Ok2Disconnect) ) 

#define IInboundSvr_DeleteInbound(This,session,objid,bDeleteHistorian)	\
    ( (This)->lpVtbl -> DeleteInbound(This,session,objid,bDeleteHistorian) ) 

#define IInboundSvr_CustomInboundFunc(This,session,objid,funcID,internal)	\
    ( (This)->lpVtbl -> CustomInboundFunc(This,session,objid,funcID,internal) ) 

#define IInboundSvr_AddInbound(This,session,info,refnum)	\
    ( (This)->lpVtbl -> AddInbound(This,session,info,refnum) ) 

#define IInboundSvr_OpenSession(This,session)	\
    ( (This)->lpVtbl -> OpenSession(This,session) ) 

#define IInboundSvr_CloseSession(This,session)	\
    ( (This)->lpVtbl -> CloseSession(This,session) ) 

#define IInboundSvr_SetConnection(This,session,refnum,open)	\
    ( (This)->lpVtbl -> SetConnection(This,session,refnum,open) ) 

#define IInboundSvr_GetComPorts(This,session,comports)	\
    ( (This)->lpVtbl -> GetComPorts(This,session,comports) ) 

#define IInboundSvr_AddListener(This,ppv,type,cookie)	\
    ( (This)->lpVtbl -> AddListener(This,ppv,type,cookie) ) 

#define IInboundSvr_RemoveListener(This,type,cookie)	\
    ( (This)->lpVtbl -> RemoveListener(This,type,cookie) ) 

#define IInboundSvr_IsUniqueInboundName(This,session,inboundinfo,isUnique)	\
    ( (This)->lpVtbl -> IsUniqueInboundName(This,session,inboundinfo,isUnique) ) 

#define IInboundSvr_GetAllKeys(This,session,ibRef,keys)	\
    ( (This)->lpVtbl -> GetAllKeys(This,session,ibRef,keys) ) 

#define IInboundSvr_SetImplemented(This,session,ibRef,keys,flds)	\
    ( (This)->lpVtbl -> SetImplemented(This,session,ibRef,keys,flds) ) 

#define IInboundSvr_SpecialImplement(This,session,ibRef,type,info)	\
    ( (This)->lpVtbl -> SpecialImplement(This,session,ibRef,type,info) ) 

#define IInboundSvr_DeleteInboundSE(This,session,objid,bDeleteHistorian,LoginSession)	\
    ( (This)->lpVtbl -> DeleteInboundSE(This,session,objid,bDeleteHistorian,LoginSession) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInboundSvr_INTERFACE_DEFINED__ */


#ifndef __ICommonListener_INTERFACE_DEFINED__
#define __ICommonListener_INTERFACE_DEFINED__

/* interface ICommonListener */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICommonListener;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7A05FED4-767D-11D3-80EE-00105AA9BDD3")
    ICommonListener : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnEvent( 
            /* [in] */ short type,
            /* [in] */ REFNUM refnum,
            /* [in] */ VARIANT info) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICommonListenerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICommonListener * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICommonListener * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICommonListener * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnEvent )( 
            ICommonListener * This,
            /* [in] */ short type,
            /* [in] */ REFNUM refnum,
            /* [in] */ VARIANT info);
        
        END_INTERFACE
    } ICommonListenerVtbl;

    interface ICommonListener
    {
        CONST_VTBL struct ICommonListenerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommonListener_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICommonListener_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICommonListener_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICommonListener_OnEvent(This,type,refnum,info)	\
    ( (This)->lpVtbl -> OnEvent(This,type,refnum,info) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICommonListener_INTERFACE_DEFINED__ */


#ifndef __IPSDBListener_INTERFACE_DEFINED__
#define __IPSDBListener_INTERFACE_DEFINED__

/* interface IPSDBListener */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPSDBListener;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A4FA5FBD-8A79-11D5-8340-00105AA9BDD3")
    IPSDBListener : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SystemShutdown( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE XactionComplete( 
            /* [in] */ int reqID,
            /* [in] */ int XactionType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE XactionFailed( 
            /* [in] */ int reqID,
            /* [in] */ int XactionType,
            /* [in] */ int errCode,
            /* [in] */ BSTR msgText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE XactionCompleteWithDetails( 
            /* [in] */ int reqID,
            /* [in] */ int XactionType,
            /* [in] */ int errCode,
            /* [in] */ VARIANT response,
            /* [in] */ BSTR msgText) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPSDBListenerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPSDBListener * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPSDBListener * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPSDBListener * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SystemShutdown )( 
            IPSDBListener * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *XactionComplete )( 
            IPSDBListener * This,
            /* [in] */ int reqID,
            /* [in] */ int XactionType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *XactionFailed )( 
            IPSDBListener * This,
            /* [in] */ int reqID,
            /* [in] */ int XactionType,
            /* [in] */ int errCode,
            /* [in] */ BSTR msgText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *XactionCompleteWithDetails )( 
            IPSDBListener * This,
            /* [in] */ int reqID,
            /* [in] */ int XactionType,
            /* [in] */ int errCode,
            /* [in] */ VARIANT response,
            /* [in] */ BSTR msgText);
        
        END_INTERFACE
    } IPSDBListenerVtbl;

    interface IPSDBListener
    {
        CONST_VTBL struct IPSDBListenerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPSDBListener_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPSDBListener_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPSDBListener_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPSDBListener_SystemShutdown(This)	\
    ( (This)->lpVtbl -> SystemShutdown(This) ) 

#define IPSDBListener_XactionComplete(This,reqID,XactionType)	\
    ( (This)->lpVtbl -> XactionComplete(This,reqID,XactionType) ) 

#define IPSDBListener_XactionFailed(This,reqID,XactionType,errCode,msgText)	\
    ( (This)->lpVtbl -> XactionFailed(This,reqID,XactionType,errCode,msgText) ) 

#define IPSDBListener_XactionCompleteWithDetails(This,reqID,XactionType,errCode,response,msgText)	\
    ( (This)->lpVtbl -> XactionCompleteWithDetails(This,reqID,XactionType,errCode,response,msgText) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPSDBListener_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_Publisher2000Server_0000_0004 */
/* [local] */ 

typedef 
enum implementType
    {
        implement_none	= 0,
        implement_yes	= ( implement_none + 1 ) ,
        implement_all	= ( implement_yes + 1 ) ,
        implement_selected_flds	= ( implement_all + 1 ) ,
        unimplement_all	= ( implement_selected_flds + 1 ) 
    } 	implementType;

typedef 
enum implementXactType
    {
        ITXT_UpdateImplementedTablesI	= 0,
        ITXT_UpdateImplementedTablesD	= ( ITXT_UpdateImplementedTablesI + 1 ) ,
        ITXT_UpdateImplementedTablesU	= ( ITXT_UpdateImplementedTablesD + 1 ) ,
        ITXT_UpdateImplTablesI_ADO	= ( ITXT_UpdateImplementedTablesU + 1 ) ,
        ITXT_UpdateImplTablesU_ADO	= ( ITXT_UpdateImplTablesI_ADO + 1 ) ,
        ITXT_ImplAdhTable_ADO	= ( ITXT_UpdateImplTablesU_ADO + 1 ) ,
        ITXT_UNImplAdhTable_ADO	= ( ITXT_ImplAdhTable_ADO + 1 ) 
    } 	implementXactType;

typedef 
enum tblXactType
    {
        CTXT_TablesOnly	= 0,
        CTXT_TablesCollector	= ( CTXT_TablesOnly + 1 ) ,
        CTXT_TablesCollectorIB	= ( CTXT_TablesCollector + 1 ) ,
        CTXT_XMLTablesOnly	= ( CTXT_TablesCollectorIB + 1 ) ,
        CTXT_XMLTablesCollector	= ( CTXT_XMLTablesOnly + 1 ) ,
        CTXT_HistTablesOnly	= ( CTXT_XMLTablesCollector + 1 ) ,
        CTXT_HistTablesCollector	= ( CTXT_HistTablesOnly + 1 ) ,
        CTXT_HistTablesCollectorIB	= ( CTXT_HistTablesCollector + 1 ) 
    } 	tblXactType;

typedef 
enum chgViewType
    {
        CVT_AddPolyView	= 0,
        CVT_DeletePolyView	= ( CVT_AddPolyView + 1 ) ,
        CVT_AddHistView	= ( CVT_DeletePolyView + 1 ) 
    } 	chgViewType;



extern RPC_IF_HANDLE __MIDL_itf_Publisher2000Server_0000_0004_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Publisher2000Server_0000_0004_v0_0_s_ifspec;

#ifndef __IPSDBHelper_INTERFACE_DEFINED__
#define __IPSDBHelper_INTERFACE_DEFINED__

/* interface IPSDBHelper */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPSDBHelper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A4FA5FBB-8A79-11D5-8340-00105AA9BDD3")
    IPSDBHelper : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddListener( 
            /* [in] */ IPSDBListener *ppv,
            /* [out] */ int *cookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveListener( 
            /* [in] */ int cookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddInbound2DB( 
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT instInfo,
            /* [in] */ implementType implement,
            /* [in] */ VARIANT *moreInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InsertDataTblRecs( 
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT psdbDatum,
            /* [in] */ VARIANT recdata) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateDataTblRecs( 
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT psdbDatum,
            /* [in] */ VARIANT recdata) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteDataTblRecs( 
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT psdbDatum,
            /* [in] */ VARIANT recdata) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteInboundType( 
            /* [out][in] */ int *reqID,
            /* [in] */ int typeID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteInbound( 
            /* [out][in] */ int *reqID,
            /* [in] */ ULONG inboundRef) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNewRefnum( 
            /* [out][in] */ ULONG *refnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ModifyImplemented( 
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT implementInfo,
            /* [in] */ implementXactType type) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetInbound( 
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT ibID,
            /* [in] */ int bDetailed,
            /* [in] */ int inclTblFlds) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetInboundType( 
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT typeID,
            /* [in] */ int bDetailed,
            /* [in] */ int inclTblFlds) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteCollectorTable( 
            /* [out][in] */ int *reqID,
            /* [in] */ int typeID,
            /* [in] */ VARIANT tables,
            /* [in] */ BOOL bSingleThread) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddCollectorTables( 
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT schema,
            /* [in] */ tblXactType TblXactType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetImplementedForIB( 
            /* [in] */ ULONG refnum,
            /* [in] */ int typeID,
            /* [out][in] */ VARIANT *keys,
            /* [out][in] */ VARIANT *flds) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddLegacyRefnums( 
            /* [in] */ VARIANT data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveIBData( 
            /* [in] */ ULONG refnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ModifyInbound( 
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT info) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateDataTblBlob( 
            /* [in] */ VARIANT blob) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteAllRecords( 
            /* [in] */ ULONG ibRef,
            /* [in] */ ULONG cType,
            /* [in] */ BSTR dbTableName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeCollectorViews( 
            /* [in] */ VARIANT vwName,
            /* [in] */ VARIANT vwVar,
            /* [in] */ chgViewType vwChgType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitAdherence4Me( 
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT ibAdhStuff,
            /* [in] */ VARIANT adh_states) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWorldRefnum( 
            /* [out][in] */ ULONG *refnum) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPSDBHelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPSDBHelper * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPSDBHelper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPSDBHelper * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPSDBHelper * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPSDBHelper * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPSDBHelper * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPSDBHelper * This,
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
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddListener )( 
            IPSDBHelper * This,
            /* [in] */ IPSDBListener *ppv,
            /* [out] */ int *cookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveListener )( 
            IPSDBHelper * This,
            /* [in] */ int cookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddInbound2DB )( 
            IPSDBHelper * This,
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT instInfo,
            /* [in] */ implementType implement,
            /* [in] */ VARIANT *moreInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InsertDataTblRecs )( 
            IPSDBHelper * This,
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT psdbDatum,
            /* [in] */ VARIANT recdata);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateDataTblRecs )( 
            IPSDBHelper * This,
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT psdbDatum,
            /* [in] */ VARIANT recdata);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteDataTblRecs )( 
            IPSDBHelper * This,
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT psdbDatum,
            /* [in] */ VARIANT recdata);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteInboundType )( 
            IPSDBHelper * This,
            /* [out][in] */ int *reqID,
            /* [in] */ int typeID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteInbound )( 
            IPSDBHelper * This,
            /* [out][in] */ int *reqID,
            /* [in] */ ULONG inboundRef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNewRefnum )( 
            IPSDBHelper * This,
            /* [out][in] */ ULONG *refnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ModifyImplemented )( 
            IPSDBHelper * This,
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT implementInfo,
            /* [in] */ implementXactType type);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetInbound )( 
            IPSDBHelper * This,
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT ibID,
            /* [in] */ int bDetailed,
            /* [in] */ int inclTblFlds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetInboundType )( 
            IPSDBHelper * This,
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT typeID,
            /* [in] */ int bDetailed,
            /* [in] */ int inclTblFlds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteCollectorTable )( 
            IPSDBHelper * This,
            /* [out][in] */ int *reqID,
            /* [in] */ int typeID,
            /* [in] */ VARIANT tables,
            /* [in] */ BOOL bSingleThread);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddCollectorTables )( 
            IPSDBHelper * This,
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT schema,
            /* [in] */ tblXactType TblXactType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetImplementedForIB )( 
            IPSDBHelper * This,
            /* [in] */ ULONG refnum,
            /* [in] */ int typeID,
            /* [out][in] */ VARIANT *keys,
            /* [out][in] */ VARIANT *flds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddLegacyRefnums )( 
            IPSDBHelper * This,
            /* [in] */ VARIANT data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveIBData )( 
            IPSDBHelper * This,
            /* [in] */ ULONG refnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ModifyInbound )( 
            IPSDBHelper * This,
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT info);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateDataTblBlob )( 
            IPSDBHelper * This,
            /* [in] */ VARIANT blob);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteAllRecords )( 
            IPSDBHelper * This,
            /* [in] */ ULONG ibRef,
            /* [in] */ ULONG cType,
            /* [in] */ BSTR dbTableName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChangeCollectorViews )( 
            IPSDBHelper * This,
            /* [in] */ VARIANT vwName,
            /* [in] */ VARIANT vwVar,
            /* [in] */ chgViewType vwChgType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitAdherence4Me )( 
            IPSDBHelper * This,
            /* [out][in] */ int *reqID,
            /* [in] */ VARIANT ibAdhStuff,
            /* [in] */ VARIANT adh_states);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWorldRefnum )( 
            IPSDBHelper * This,
            /* [out][in] */ ULONG *refnum);
        
        END_INTERFACE
    } IPSDBHelperVtbl;

    interface IPSDBHelper
    {
        CONST_VTBL struct IPSDBHelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPSDBHelper_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPSDBHelper_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPSDBHelper_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPSDBHelper_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPSDBHelper_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPSDBHelper_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPSDBHelper_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPSDBHelper_AddListener(This,ppv,cookie)	\
    ( (This)->lpVtbl -> AddListener(This,ppv,cookie) ) 

#define IPSDBHelper_RemoveListener(This,cookie)	\
    ( (This)->lpVtbl -> RemoveListener(This,cookie) ) 

#define IPSDBHelper_AddInbound2DB(This,reqID,instInfo,implement,moreInfo)	\
    ( (This)->lpVtbl -> AddInbound2DB(This,reqID,instInfo,implement,moreInfo) ) 

#define IPSDBHelper_InsertDataTblRecs(This,reqID,psdbDatum,recdata)	\
    ( (This)->lpVtbl -> InsertDataTblRecs(This,reqID,psdbDatum,recdata) ) 

#define IPSDBHelper_UpdateDataTblRecs(This,reqID,psdbDatum,recdata)	\
    ( (This)->lpVtbl -> UpdateDataTblRecs(This,reqID,psdbDatum,recdata) ) 

#define IPSDBHelper_DeleteDataTblRecs(This,reqID,psdbDatum,recdata)	\
    ( (This)->lpVtbl -> DeleteDataTblRecs(This,reqID,psdbDatum,recdata) ) 

#define IPSDBHelper_DeleteInboundType(This,reqID,typeID)	\
    ( (This)->lpVtbl -> DeleteInboundType(This,reqID,typeID) ) 

#define IPSDBHelper_DeleteInbound(This,reqID,inboundRef)	\
    ( (This)->lpVtbl -> DeleteInbound(This,reqID,inboundRef) ) 

#define IPSDBHelper_GetNewRefnum(This,refnum)	\
    ( (This)->lpVtbl -> GetNewRefnum(This,refnum) ) 

#define IPSDBHelper_ModifyImplemented(This,reqID,implementInfo,type)	\
    ( (This)->lpVtbl -> ModifyImplemented(This,reqID,implementInfo,type) ) 

#define IPSDBHelper_GetInbound(This,reqID,ibID,bDetailed,inclTblFlds)	\
    ( (This)->lpVtbl -> GetInbound(This,reqID,ibID,bDetailed,inclTblFlds) ) 

#define IPSDBHelper_GetInboundType(This,reqID,typeID,bDetailed,inclTblFlds)	\
    ( (This)->lpVtbl -> GetInboundType(This,reqID,typeID,bDetailed,inclTblFlds) ) 

#define IPSDBHelper_DeleteCollectorTable(This,reqID,typeID,tables,bSingleThread)	\
    ( (This)->lpVtbl -> DeleteCollectorTable(This,reqID,typeID,tables,bSingleThread) ) 

#define IPSDBHelper_AddCollectorTables(This,reqID,schema,TblXactType)	\
    ( (This)->lpVtbl -> AddCollectorTables(This,reqID,schema,TblXactType) ) 

#define IPSDBHelper_GetImplementedForIB(This,refnum,typeID,keys,flds)	\
    ( (This)->lpVtbl -> GetImplementedForIB(This,refnum,typeID,keys,flds) ) 

#define IPSDBHelper_AddLegacyRefnums(This,data)	\
    ( (This)->lpVtbl -> AddLegacyRefnums(This,data) ) 

#define IPSDBHelper_SaveIBData(This,refnum)	\
    ( (This)->lpVtbl -> SaveIBData(This,refnum) ) 

#define IPSDBHelper_ModifyInbound(This,reqID,info)	\
    ( (This)->lpVtbl -> ModifyInbound(This,reqID,info) ) 

#define IPSDBHelper_UpdateDataTblBlob(This,blob)	\
    ( (This)->lpVtbl -> UpdateDataTblBlob(This,blob) ) 

#define IPSDBHelper_DeleteAllRecords(This,ibRef,cType,dbTableName)	\
    ( (This)->lpVtbl -> DeleteAllRecords(This,ibRef,cType,dbTableName) ) 

#define IPSDBHelper_ChangeCollectorViews(This,vwName,vwVar,vwChgType)	\
    ( (This)->lpVtbl -> ChangeCollectorViews(This,vwName,vwVar,vwChgType) ) 

#define IPSDBHelper_InitAdherence4Me(This,reqID,ibAdhStuff,adh_states)	\
    ( (This)->lpVtbl -> InitAdherence4Me(This,reqID,ibAdhStuff,adh_states) ) 

#define IPSDBHelper_GetWorldRefnum(This,refnum)	\
    ( (This)->lpVtbl -> GetWorldRefnum(This,refnum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPSDBHelper_INTERFACE_DEFINED__ */


#ifndef __IDataSecurity_INTERFACE_DEFINED__
#define __IDataSecurity_INTERFACE_DEFINED__

/* interface IDataSecurity */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDataSecurity;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B804CC44-1738-497E-A2AA-E08CEE077FC2")
    IDataSecurity : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Execute( 
            /* [in] */ BSTR commandString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRecordset( 
            /* [in] */ BSTR commandString,
            /* [out] */ _Recordset **Results) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDataSecurityVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDataSecurity * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDataSecurity * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDataSecurity * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDataSecurity * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDataSecurity * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDataSecurity * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDataSecurity * This,
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
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Execute )( 
            IDataSecurity * This,
            /* [in] */ BSTR commandString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRecordset )( 
            IDataSecurity * This,
            /* [in] */ BSTR commandString,
            /* [out] */ _Recordset **Results);
        
        END_INTERFACE
    } IDataSecurityVtbl;

    interface IDataSecurity
    {
        CONST_VTBL struct IDataSecurityVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDataSecurity_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDataSecurity_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDataSecurity_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDataSecurity_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDataSecurity_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDataSecurity_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDataSecurity_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IDataSecurity_Execute(This,commandString)	\
    ( (This)->lpVtbl -> Execute(This,commandString) ) 

#define IDataSecurity_GetRecordset(This,commandString,Results)	\
    ( (This)->lpVtbl -> GetRecordset(This,commandString,Results) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDataSecurity_INTERFACE_DEFINED__ */


#ifndef __IFileStreamer_INTERFACE_DEFINED__
#define __IFileStreamer_INTERFACE_DEFINED__

/* interface IFileStreamer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IFileStreamer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29B88468-0867-40EE-BEE3-D46D159D8D64")
    IFileStreamer : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IFileStreamerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileStreamer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileStreamer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileStreamer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFileStreamer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFileStreamer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFileStreamer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFileStreamer * This,
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
        
        END_INTERFACE
    } IFileStreamerVtbl;

    interface IFileStreamer
    {
        CONST_VTBL struct IFileStreamerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileStreamer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileStreamer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileStreamer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileStreamer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFileStreamer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFileStreamer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFileStreamer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFileStreamer_INTERFACE_DEFINED__ */



#ifndef __PUBLISHER2000SERVERLib_LIBRARY_DEFINED__
#define __PUBLISHER2000SERVERLib_LIBRARY_DEFINED__

/* library PUBLISHER2000SERVERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PUBLISHER2000SERVERLib;

EXTERN_C const CLSID CLSID_PubSvr;

#ifdef __cplusplus

class DECLSPEC_UUID("D03D7B7D-71D0-11D3-80EA-00105AA9BDD3")
PubSvr;
#endif

EXTERN_C const CLSID CLSID_InboundSvr;

#ifdef __cplusplus

class DECLSPEC_UUID("A7BB4BC6-75C5-11D3-80ED-00105AA9BDD3")
InboundSvr;
#endif

EXTERN_C const CLSID CLSID_PSDBHelper;

#ifdef __cplusplus

class DECLSPEC_UUID("A4FA5FBC-8A79-11D5-8340-00105AA9BDD3")
PSDBHelper;
#endif

EXTERN_C const CLSID CLSID_DataSecurity;

#ifdef __cplusplus

class DECLSPEC_UUID("FD092D3E-1716-45F9-90EB-9C52D0748155")
DataSecurity;
#endif

EXTERN_C const CLSID CLSID_FileStreamer;

#ifdef __cplusplus

class DECLSPEC_UUID("10885155-2AA7-4D2B-8C23-9A24B502BE5E")
FileStreamer;
#endif
#endif /* __PUBLISHER2000SERVERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


