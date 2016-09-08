// PSDBListener.h: interface for the CPSDBListener class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PSDBLISTENER_H__6F283C28_59C4_11D5_8322_00105AA9BDD3__INCLUDED_)
#define AFX_PSDBLISTENER_H__6F283C28_59C4_11D5_8322_00105AA9BDD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PSDBMsgs.h"
#include "Publisher2000Server.h"

class CR3Collect;

#include <map>
using namespace std;


typedef	map<int,int>::iterator REQUESTIter;

class CPSDBListener : public CComObjectRoot ,public IPSDBListener 
{
	friend class CSharePointCollect;
	CSharePointCollect *m_pMgr;

public:
	CPSDBListener();
	virtual ~CPSDBListener();
	int cookie;

	_ThreadModel::AutoCriticalSection m_cs;

	BSTR m_empty;
	VARIANT m_unused;

	void AddEvent(int reqID, int type, int errCode, BSTR msg, VARIANT response);


	map<int,int> m_myReqs;
	void AddReqID(int reqID);
	void SetMgr(CSharePointCollect *pMgr) {m_pMgr = pMgr;};

	BEGIN_COM_MAP(CPSDBListener)
		COM_INTERFACE_ENTRY(IPSDBListener)
	END_COM_MAP()


	// IPolyHelpListener
public:
	STDMETHOD(XactionFailed)(/*[in]*/int reqID, /*[in]*/int XactionType, /*[in]*/int errCode, /*[in]*/BSTR msgText);
	STDMETHOD(XactionComplete)(/*[in]*/int reqID, /*[in]*/int XactionType);
	STDMETHOD(XactionCompleteWithDetails)(/*[in]*/int reqID, /*[in]*/int XactionType,/*[in]*/int errCode, /*[in]*/VARIANT response, /*[in]*/BSTR msgText);
	STDMETHOD(SystemShutdown)();

};

#endif // !defined(AFX_PSDBLISTENER_H__6F283C28_59C4_11D5_8322_00105AA9BDD3__INCLUDED_)
