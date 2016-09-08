// Listener.h: interface for the CListener class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTENER_H__711B2E34_767E_11D3_80EE_00105AA9POO__INCLUDED_)
#define AFX_LISTENER_H__711B2E34_767E_11D3_80EE_00105AA9POO__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "publisher2000server.h"

#include <afxtempl.h>
#include "publishercommon.h"
#include "objectdefs.h"

class CSharePointInbound;
//class CPropSheet;

class CListenEvent 
{
public:
	CListenEvent::CListenEvent(	int type, REFNUM ref,LPCTSTR text = NULL) :
	  m_type(type),m_ref(ref), errMsg(text), bProcessed(false) {};

	int m_type;
	REFNUM m_ref;
	CString errMsg;
	BOOL  bProcessed;

};

class CSvrListener : public CComObjectRoot,public ICommonListener 
{
public:
	CSvrListener();
	~CSvrListener();

	BEGIN_COM_MAP(CSvrListener)
		COM_INTERFACE_ENTRY(ICommonListener)
	END_COM_MAP()

	STDMETHODIMP OnEvent(short type, REFNUM refnum, VARIANT info);
	_ThreadModel::AutoCriticalSection m_cs;

	void AddEvent(int type, REFNUM ref, LPCTSTR text = NULL);

	CTypedPtrList<CPtrList, CListenEvent*> m_EventList;

	CSharePointInbound *m_pCtrl;
	//CPropSheet *m_pSheet;

};

#endif // !defined(AFX_LISTENER_H__711B2E34_767E_11D3_80EE_00105AA9POO__INCLUDED_)
