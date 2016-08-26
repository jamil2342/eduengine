#pragma once
#include <atlcomcli.h>
#import "../firstMoneyClient/bin/Debug/firstMoneyClient.tlb"  


using namespace firstMoneyClient;
class firstMoneycollectorForUse
{
public:

	firstMoneycollectorForUse()
	{
	}

	~firstMoneycollectorForUse()
	{
	}
	void callWebService()
	{


		// Initialize COM.
		//HRESULT hr = CoInitialize(NULL);

		//// Create the interface pointer.
		//ICalculatorPtr pICalc(__uuidof(ManagedClass));

		//long lResult = 0;

		//// Call the Add method.
		//pICalc->Add(5, 10, &lResult);

		//wprintf(L"The result is %d", lResult);

		//// Uninitialize COM.
		//CoUninitialize();
		//return;
		//CComPtr<firstMoneyClient::IInterface> yourClass;
		//firstMoneyClient::IInterfacePtr yourClass(__uuidof(NamespaceOfYourProject::ClassYouWantToUse));

		//yourClass->Connect();


		//CComPtr<firstMoneyClient::IInterface> yourClass;
		//firstMoneyClient::IInterfacePtr yourClass(__uuidof(NamespaceOfYourProject::ClassYouWantToUse));
		firstMoneyClient::ClassYouWantToUse  yourclass= new ;

		yourClass.Connect();
		int i = 10;
		int b = i;
		b += i;
	}
};

