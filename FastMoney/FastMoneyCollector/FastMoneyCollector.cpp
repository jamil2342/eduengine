
#include "FastMoneyCollector.h"
#include "MemFile.h"
#include "DBConnector.h"
using namespace System;



namespace FastMoneyCollector
{
#ifdef __cplusplus
	extern "C"
	{
#endif

		__declspec(dllexport) int GetFastMoney(wchar_t* Url)
		{

			FastMoneyClient ^ Service = FastMoneyCollector::Instance->Obj;
			array< Item^ >^ local = Service->GetFastMoney(gcnew String(Url));

			try
			{
				CDBConnector dbCon;
				dbCon.InitConnect();

				for (size_t i = 0; i < local->Length; i++)
				{
					dbCon.AddFastMoneyDataToDB(local[i]);
				}


				return 1;
			}
			catch (_com_error ex)
			{
				return 0;
			}

		}

#ifdef __cplusplus
	}
#endif
}