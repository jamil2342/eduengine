#pragma once


#define SHAREPOINT
#include "stdafx.h"
#include <list>
#include <vcclr.h>
//#include <winnt.h>
#include <OAIdl.h>
//#include "SharePointCollector.h"
#include "SharePointCollect.h"




using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics;
using namespace FASTMONEY;

void MarshalString(String ^ s, std::string& os);
void MarshalString(String ^ s, std::wstring& os);

namespace FastMoneyCollector
{
	public ref class FastMoneyCollector
	{


#ifdef SHAREPOINT



#endif
      /* Private Constructor to achieve signle ton*/
		FastMoneyCollector(void)
		{

			Obj = gcnew FastMoneyClient();
         
		}
	public:

		FastMoneyClient ^ Obj;
      /* Static reference to single ton instace.
         In order to use applications built in C.*/
		static FastMoneyCollector ^ Instance = gcnew FastMoneyCollector();

	};

	int m_iDataCounter;
	CSharePointCollect *m_pOwner;
}
