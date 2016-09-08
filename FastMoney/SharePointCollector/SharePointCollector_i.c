

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Sep 08 05:15:50 2016
 */
/* Compiler settings for SharePointCollector.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IIBCollector,0x5FE79210,0xA806,0x11D3,0x81,0x1F,0x00,0x10,0x5A,0xA9,0xBD,0xD3);


MIDL_DEFINE_GUID(IID, IID_IInboundEvents,0x5FE79213,0xA806,0x11D3,0x81,0x1F,0x00,0x10,0x5A,0xA9,0xBD,0xD3);


MIDL_DEFINE_GUID(IID, IID_ISharePointCollect,0x7A40C4C5,0x77F1,0x4350,0xA5,0x9D,0x85,0x4C,0xEA,0xA2,0x2F,0x32);


MIDL_DEFINE_GUID(IID, LIBID_SharePointCollectorLib,0x37F2B5D2,0xAD4B,0x41D9,0xB5,0xF5,0xE7,0x27,0x94,0xD7,0xDA,0x0F);


MIDL_DEFINE_GUID(CLSID, CLSID_SharePointCollect,0x16B172C2,0x8025,0x4E85,0xA6,0x36,0x90,0xEF,0x65,0x4A,0x11,0x5A);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



