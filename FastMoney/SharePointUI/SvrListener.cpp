// Listener.cpp: implementation of the CListener class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SharePointUI.h"
#include "SvrListener.h"

#include "Page1.h"
#include "publisherCommon.h"
//#include "propsheet.h"
#include "SharePointInbound.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSvrListener::CSvrListener()
{
	m_pCtrl = NULL;
//	m_pSheet = NULL;
}

CSvrListener::~CSvrListener()
{

	CListenEvent *data;

	POSITION pos = m_EventList.GetHeadPosition();
	while(pos)
	{
		data = m_EventList.GetNext(pos);
		if (data)
			delete data;
	}
	m_EventList.RemoveAll();
}



HRESULT CSvrListener::OnEvent(short type, REFNUM refnum, VARIANT info)
{
	TRACE2("SharePoint OnEvent(type %d, REFNUM %d\n",type,refnum);

	m_cs.Lock();

	CListenEvent *data;
	POSITION prevpos;
	POSITION pos = m_EventList.GetHeadPosition();

	while(pos)
	{
		prevpos = pos;
		data = m_EventList.GetNext(pos);
		if (data && data->bProcessed)
		{
			delete data;
			m_EventList.RemoveAt(prevpos);
		}
	}

	switch(type)
	{
		case SystemShutDown:
			AddEvent(type,refnum);
			break;

		case InboundErrMsg:
			if(refnum == m_pCtrl->m_base.m_refnum)
			{
				CString temp(info.bstrVal);
				AddEvent(type,refnum,(LPCTSTR)temp);
			}
			break;

		case InboundRemoved:
			if(refnum == m_pCtrl->m_base.m_refnum)
				AddEvent(type,refnum);
			break;

		case InboundConfigChg:
			if(refnum == m_pCtrl->m_base.m_refnum)
				AddEvent(type,refnum);
			break;

	}

	m_cs.Unlock();
	return S_OK;


}


void CSvrListener::AddEvent(int type, REFNUM ref, LPCTSTR text)
{
	TRACE2("SharePoint AddEvent(type %d, REFNUM %d\n",type,  ref);


	CListenEvent *pretEvent = new CListenEvent(type, ref, text);
	m_EventList.AddTail(pretEvent);   

//	if(m_pSheet && m_pSheet->m_hWnd)
//		m_pSheet->PostMessage(WM_DATACHANGE, type, (LPARAM)pretEvent);

}
