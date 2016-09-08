// EventMgr.cpp: implementation of the CEventMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SharePointCollector.h"
#include "SharePointCollect.h"
#include "EventMgr.h"

#include <process.h>

#include "pubutility.h"
#include "objectdefs.h"
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
CEventMgr::CEventMgr()
{
	m_StopPending = false;

	m_pEventThread = NULL;
}

CEventMgr::~CEventMgr()
{
	if(m_pEventThread)
		delete m_pEventThread;

	m_pEventThread = NULL;
}

void CEventMgr::Init(CSharePointCollect *pOwner)
{
	_ASSERTE(pOwner);
	m_pOwner = pOwner;
	m_pEventThread = new CEventThread(this);

	if(	m_pEventThread->CreateThread(0,0,NULL, INFINITE))
	{
		ATLTRACE("CEventMgr - thread created successfully\n");
	}
}


HRESULT  CEventMgr::AddEvent(int type)
{
	Acquire lock(this);	

	m_synchPulse.WriteLock();
	m_inactive_cnt = 0;
	m_synchPulse.WriteUnLock();

	CDBEvent *pretEvent = new CDBEvent(type);

	m_EventList.push_back(pretEvent);   //pop_front
	m_pEventThread->ProcessTransaction();

	return S_OK;		
}

bool CEventMgr::GetNextEvent(CDBEvent& dbevent)
{
	Acquire lock(this);	
	if(m_EventList.empty())
		return false;

	deque<CDBEvent*>::iterator m_EventListiter;

	CDBEvent *pretEvent; 
	m_EventListiter = m_EventList.begin();
	pretEvent = *m_EventListiter;
	m_EventList.pop_front();

	dbevent = *pretEvent;

	delete pretEvent;

	return true;
}

//////////////////////////////////////////////////////////////

CEventThread::CEventThread(CEventMgr * parent)
{
	pmgr = parent;
}


CEventThread::~CEventThread()
{
	m_sharepoint.m_pThreadMgr = NULL;
}


void CEventThread::ProcessTransaction()
{
	m_pWorkEvent->SetEvent();
}

void CEventThread::DoWork()
{
	// This is so _Crt calls are output to Debug
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT );

	while (pmgr->GetNextEvent(m_currentEvent))
	{
		switch(m_currentEvent.type)
		{
			case T_StartData:
				this->m_nCycleTime = pmgr->m_pOwner->m_base.m_update_interval < 5 ? pmgr->m_pOwner->m_base.m_update_interval * 1000 : 5000;
				StartData();
				break;
			case T_StopData	:
				StopData();
				this->m_nCycleTime = -1;
				break;
			case T_PublishFields:
				PublishFields();
				break;
			case T_GetImplementedForIB:
				GetImplementedForIB();
				break;
			default:
				break;
		}
	}
	if (m_sharepoint.m_ConnectionOpen == ACTIVE)
	{
		if (WaitForSingleObject(pmgr->m_pOwner->m_hStartupDone,0) == WAIT_OBJECT_0)
			m_sharepoint.DoQuery();
		else
			OutputDebugString("DoWork() - not ready.");

	}
	if (m_sharepoint.m_ConnectionOpen == ERR_RECOVERY)
	{
		int cycletime = this->m_nCycleTime / 1000;
		cycletime = cycletime < 1 ? 1 : cycletime;
		char szBuf[256];
		sprintf_s(szBuf, _countof(szBuf), "DoWork() countdown to retry = %d\n", SHAREPOINT_ERROR_RECOVERY_TIMEOUT - m_sharepoint.m_nErrorRecovery*cycletime);
		OutputDebugString(szBuf);
		pmgr->m_pOwner->DoEvent(CT_InboundStateChange, ERR_RECOVERY);
		if (m_sharepoint.m_nErrorRecovery++ >= SHAREPOINT_ERROR_RECOVERY_TIMEOUT / cycletime)
		{
			sprintf_s(szBuf, _countof(szBuf), "DoWork() Attempting to restart\n");
			OutputDebugString(szBuf);
			StartData();
		}
	}
}

//////////////////////////////////////////////////////////////

void CEventThread::GetImplementedForIB()
{
	VARIANT keys;	VariantInit(&keys);
	VARIANT flds;	VariantInit(&flds);

	keys.vt = VT_I4;
	keys.lVal = 1;

	flds.vt = VT_I4;
	flds.lVal = RCT_BY_INTERNAL;
	IPSDBHelper *helper = pmgr->m_pOwner->GetPSDBHelper();
	try
	{
		helper->GetImplementedForIB(pmgr->m_pOwner->m_base.m_refnum, pmgr->m_pOwner->m_base.m_collectorType, &keys, &flds);		
	}
	catch(...)
	{
	}

	pmgr->m_pOwner->m_impFlds.ReleaseQ();	// in case it was a refresh

	int size;
	int count;
	HRESULT	res = GetSizeAndCount(flds, &size, &count);

	if (res == S_OK  && size >1 && count == 1)
	{
		BYTE *pPtr;
		memfile mf;

		SafeArrayAccessData(flds.parray, (void**)&pPtr);
		mf.write(pPtr, size);
		SafeArrayUnaccessData(flds.parray);

		mf.seek(0);
		pmgr->m_pOwner->m_impFlds.StreamFldsIn(mf);
		pmgr->m_pOwner->m_impFlds.BuildMap();
	}

	pmgr->m_pOwner->m_keys.ReleaseAll();
	pmgr->m_pOwner->m_keys.m_ibRef = pmgr->m_pOwner->m_base.m_refnum;
	pmgr->m_pOwner->m_keys.VariantIn(&keys);

	//allow startup 
	SetEvent(pmgr->m_pOwner->m_hStartupDone);
	OutputDebugString("CEventMgr::GetImplementedForIB() - done. m_hStartupDone signaled.");
	return;
}
 
void CEventThread::StartData()
{
	m_sharepoint.InitData(this);
	if(m_sharepoint.Connect() == S_OK)	
	{
		pmgr->m_pOwner->DoEvent(CT_InboundStateChange,ACTIVE);
		m_sharepoint.m_ConnectionOpen = ACTIVE;
	}
	else
	{
		pmgr->m_pOwner->DoEvent(CT_InboundStateChange,INACTIVE);
		m_sharepoint.m_ConnectionOpen = INACTIVE;
	}
}

void CEventThread::StopData()
{
	ATLTRACE("StopData() - attempting disconnect\n");
	m_sharepoint.doDisconnect();
	ATLTRACE("StopData() - disconnected\n");
	if(pmgr && pmgr->m_pOwner)
		pmgr->m_pOwner->DoEvent(CT_InboundStateChange,INACTIVE);
	m_sharepoint.m_nErrorRecovery = 0;
}

void CEventThread::PublishFields()
{
	if (pmgr->m_pOwner->m_base.m_state != ACTIVE)
		m_sharepoint.InitData(this);

	m_sharepoint.PublishFields();
}
