// PSDBListener.cpp: implementation of the CPSDBListener class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SharePointCollector.h"
#include "SharePointCollect.h"
#include "PSDBListener.h"
#include "PSDBMsgs.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPSDBListener::CPSDBListener() : m_empty(NULL)
{
	cookie = 0;
	m_pMgr = NULL;
	VariantInit(&m_unused);
}

CPSDBListener::~CPSDBListener()
{

}


void CPSDBListener::AddEvent(int reqID, int type, int errCode, BSTR msg, VARIANT response)
{

	REQUESTIter iter = m_myReqs.find(reqID);
	if(iter != m_myReqs.end())
	{
//		AtlTrace("My event %d type %d (errCode %d)\n",reqID,get_type_str(type),errCode);
		m_pMgr->AddEvent(reqID, type, errCode, msg, response);

		// this is already locked, due to xaction
		m_myReqs.erase(iter);
	}
	else
	{
	//	AtlTrace("\nAny event %d type %s (errCode %d)",reqID,get_type_str(type),errCode);
	}

}


HRESULT CPSDBListener::XactionFailed(int reqID, int XactionType, int errCode, BSTR msg)
{
	m_cs.Lock();
	AtlTrace("XactionFailed %d type %s (errCode %d)\n",reqID,get_type_str(XactionType),errCode);

	// most users want to use XactionType
	AddEvent(reqID,SHAREPOINT_POLYFAILED,errCode,msg,m_unused);

	SysFreeString(msg);

	m_cs.Unlock();
	return S_OK;
}
HRESULT CPSDBListener::XactionComplete(int reqID, int XactionType)
{
	m_cs.Lock();
	AtlTrace("XactionComplete Success %d type %s \n",reqID,get_type_str(XactionType));

	// most users want to use XactionType
	AddEvent(reqID,SHAREPOINT_POLYSUCCEEDED,0,m_empty,m_unused);
	m_cs.Unlock();
	return S_OK;
}

HRESULT CPSDBListener::XactionCompleteWithDetails(int reqID, int XactionType, int errCode,VARIANT response, BSTR msgText)
{
	m_cs.Lock();
	AtlTrace("XactionCompleteWithDetails %d type %s (errCode %d)\n",reqID,get_type_str(XactionType),errCode);

	// most users want to use XactionType

	AddEvent(reqID,SHAREPOINT_POLYSUCCEEDED,errCode,msgText,response);

	VariantClear(&response);
	SysFreeString(msgText);

	m_cs.Unlock();
	return S_OK;
}

HRESULT CPSDBListener::SystemShutdown()
{
	m_cs.Lock();

	AtlTrace("CPSDBListener::SystemShutdown\n");

	if(m_pMgr)
	{
		m_pMgr->AddEvent(0, SHAREPOINT_LOST_SVR_CONNECTION,0,m_empty, m_unused);
	}

	m_cs.Unlock();
	return S_OK;
}


void CPSDBListener::AddReqID(int reqID)
{
	m_cs.Lock();
	m_myReqs.insert(pair<int,int>(reqID,reqID));
	m_cs.Unlock();

}
