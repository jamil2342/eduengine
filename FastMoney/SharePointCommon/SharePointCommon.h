#ifndef _SHAREPOINT_COMMON_H_
#define _SHAREPOINT_COMMON_H_


#include "Publishercommon.h"
#include <s2locks.h>
#include <StreamHelper.h>
#include "objectdefs.h"
#include "PSDBDefines.h"

#define SHAREPOINT_VERSION 2
#define MAX_URL_SIZE 512
#define MAX_AGENT_SIZE 512
#define MAX_QUERY_SIZE 1024
#define MAX_BYPASS_SIZE 4096

const char MY_DESC[] = "ShareView Collector";
const char MY_NAME[] = "ShareViewCollector";

//const VARTYPE intfld = VT_I4;
//const VARTYPE dlbfld = VT_R8;
//const VARTYPE strfld = VT_ARRAY;
//
////  Bit Setting For Changed Types
//const BYTE INT_TYPE = 0x1;
//const BYTE DBL_TYPE = 0x2;
//const BYTE STR_TYPE = 0x4;

enum Custom_Functions
{
	GetDebugMsgs,
	CaptureDebug,
	CONFIGURE_SHAREPOINT,
	GET_LIST_TITLES,
	GET_LIST_FIELDS,
	PUBLISH_FIELDS,
	GET_LIST_VIEWS,
	GET_LAST_ERROR,
};

class PSDBDatum;
class CUpdateBlob;
class CField;

typedef std::map<string, int> TYPE_MAP;

typedef std::map<long, CField*> FIELD_MAP;
typedef FIELD_MAP::iterator FIELD_MAP_ITER;

class CField
{
public:
	CField(LPCSTR szField, LPCSTR szType)
	{
		m_fieldName = szField;
		m_fieldType = szType;
	}
	std::string m_fieldName;
	std::string m_fieldType;
};

//// **************************************************************************
//class CTables
//{
//public:
//	CTables(LPCTSTR szTable, long lTableID)
//	{
//		CString lower(szTable);
//		m_tableName = lower.MakeLower();
//		m_tableId = lTableID;
//		m_pDatum = NULL;
//	}
//	
//	std::string m_tableName;
//	long m_tableId;
//
//	CUpdateBlob *m_pDatum;
//	string m_polyTableName;
//	FIELD_MAP m_fields;
//
//};


//typedef std::map<long, CTables*> TABLE_MAP;
//typedef TABLE_MAP::iterator TABLE_MAP_ITER;

class CSharePointCommon_v1 :public InboundInfo
{
public:
	char    m_szServiceUrl[MAX_URL_SIZE];
	char	m_szProxy[MAX_URL_SIZE];
	char	m_szCertPath[_MAX_PATH];
	char	m_szContentFolder[_MAX_PATH];
	char	m_szUser[STANDARD_STRING];
	char	m_szPassword[STANDARD_STRING];
	char	m_szDomain[STANDARD_STRING];
	char	m_szFuagAuth[STANDARD_STRING];
	char	m_szAuthType[MAX_AGENT_SIZE];
	char	m_szListTitle[STANDARD_STRING];
	char	m_szPrevListTitle[STANDARD_STRING];
	char	m_szViewTitle[STANDARD_STRING];
	char    m_szCamlQuery[MAX_QUERY_SIZE];
	int		m_authmode;
	bool	m_ntlm;
	
	long	m_tableCount;
	long    m_fieldCount;
	long    m_keyCount;

	long	m_prevTableCount;
	long    m_prevFieldCount;
	long    m_prevKeyCount;

	bool	m_debugcollector;
	bool	m_debugclient;

	short   m_update_interval;	//sec

	CSharePointCommon_v1()
	{
		memset( m_szServiceUrl, 0, MAX_URL_SIZE );
		memset( m_szProxy, 0, MAX_URL_SIZE );
		memset( m_szCertPath, 0, _MAX_PATH );
		memset( m_szContentFolder, 0, _MAX_PATH);
		memset( m_szUser, 0, STANDARD_STRING );
		memset( m_szPassword, 0, STANDARD_STRING );
		memset( m_szDomain, 0, STANDARD_STRING );
		memset( m_szListTitle, 0, STANDARD_STRING );
		memset( m_szViewTitle, 0, STANDARD_STRING );
		memset( m_szPrevListTitle, 0, STANDARD_STRING );
		memset( m_szFuagAuth, 0, STANDARD_STRING );
		memset( m_szAuthType, 0, MAX_AGENT_SIZE );
		memset( m_szCamlQuery, 0 , MAX_QUERY_SIZE);

		m_authmode = 0;
		m_tableCount = 0;
		m_fieldCount = 0;
		m_keyCount = 0;
		m_prevTableCount = 0;
		m_prevFieldCount = 0;
		m_prevKeyCount = 0;
		m_update_interval = 0;
		m_authmode = 0;
		m_ntlm = false;
		m_debugcollector = false;
		m_debugclient = false;
	}
};

#define SIZEOF_SHAREPOINT_COMMON_V1 sizeof(CSharePointCommon_v1)

class CSharePointCommon :public InboundInfo
{
public:
	char    m_szServiceUrl[MAX_URL_SIZE];
	char	m_szProxy[MAX_URL_SIZE];
	char	m_szCertPath[_MAX_PATH];
	char	m_szContentFolder[_MAX_PATH];
	char	m_szUser[STANDARD_STRING];
	char	m_szPassword[STANDARD_STRING];
	char	m_szDomain[STANDARD_STRING];
	char	m_szFuagAuth[STANDARD_STRING];
	char	m_szAuthType[MAX_AGENT_SIZE];
	char	m_szListTitle[STANDARD_STRING];
	char	m_szPrevListTitle[STANDARD_STRING];
	char	m_szViewTitle[STANDARD_STRING];
	char    m_szCamlQuery[MAX_QUERY_SIZE];
	char    m_szProxyUser[STANDARD_STRING];
	char    m_szProxyPassword[STANDARD_STRING];
	char    m_szProxyDomain[STANDARD_STRING];
	char    m_szProxyAuthType[STANDARD_STRING];
	char    m_szProxyBypassList[MAX_BYPASS_SIZE];
	int		m_authmode;
	bool	m_ntlm;

	long	m_tableCount;
	long    m_fieldCount;
	long    m_keyCount;

	long	m_prevTableCount;
	long    m_prevFieldCount;
	long    m_prevKeyCount;

	bool	m_debugcollector;
	bool	m_debugclient;
	bool	m_bUseProxy;
	bool	m_bBypassProxy;

	long   m_update_interval;	//sec
	long   m_update_timeout;	//sec

	CSharePointCommon()
	{
		memset(m_szServiceUrl, 0, MAX_URL_SIZE);
		memset(m_szProxy, 0, MAX_URL_SIZE);
		memset(m_szCertPath, 0, _MAX_PATH);
		memset(m_szContentFolder, 0, _MAX_PATH);
		memset(m_szUser, 0, STANDARD_STRING);
		memset(m_szPassword, 0, STANDARD_STRING);
		memset(m_szDomain, 0, STANDARD_STRING);
		memset(m_szListTitle, 0, STANDARD_STRING);
		memset(m_szViewTitle, 0, STANDARD_STRING);
		memset(m_szPrevListTitle, 0, STANDARD_STRING);
		memset(m_szFuagAuth, 0, STANDARD_STRING);
		memset(m_szAuthType, 0, MAX_AGENT_SIZE);
		memset(m_szCamlQuery, 0, MAX_QUERY_SIZE);
		memset(m_szProxyUser, 0, STANDARD_STRING);
		memset(m_szProxyPassword, 0, STANDARD_STRING);
		memset(m_szProxyDomain, 0, STANDARD_STRING);
		memset(m_szProxyAuthType, 0, STANDARD_STRING);
		memset(m_szProxyBypassList, 0, MAX_BYPASS_SIZE);
		m_authmode = 0;
		m_tableCount = 0;
		m_fieldCount = 0;
		m_keyCount = 0;
		m_prevTableCount = 0;
		m_prevFieldCount = 0;
		m_prevKeyCount = 0;
		m_update_interval = 0;
		m_bUseProxy = false;
		m_bBypassProxy = false;
		m_update_timeout = 0;
	}
};

#define SIZEOF_SHAREPOINT_COMMON sizeof(CSharePointCommon)

#endif
