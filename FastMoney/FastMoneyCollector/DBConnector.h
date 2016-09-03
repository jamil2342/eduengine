#pragma once
//#import <C:\\Program Files\\Common Files\\System\\ado\\msado15.dll>
//class FastMoneyCollector;
using namespace FASTMONEY;
public  class CDBConnector
{
public:
	CDBConnector(void);
	~CDBConnector(void);


	ado::_ConnectionPtr	m_pPolyCon;
	ado::_ConnectionPtr	m_pSQLCon;

	void InitConnect();
	bool AddGroupToDB(const String^ szValue);
	bool AddFastMoneyDataToDB(Item ^ fm);


};

