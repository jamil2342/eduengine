#pragma once
#include <atlcomcli.h>
#include "stdafx.h"

#include "YahooAPIWrapper.h"
#include <iostream>
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
		const char* stock = "GOOG";
		YahooAPIWrapper yahoo;

		double bid = yahoo.GetBid(stock);
		double ask = yahoo.GetAsk(stock);
		const char* capi = yahoo.GetCapitalization(stock);

		const char** bidAskCapi = yahoo.GetValues(stock, "b3b2j1");

		std::cout << "Bid: " << bid << std::endl;
		std::cout << "Ask: " << ask << std::endl;
		std::cout << "Capi: " << capi << std::endl;

		std::cout << "BidAskCapi[0]: " << bidAskCapi[0] << std::endl;
		std::cout << "BidAskCapi[1]: " << bidAskCapi[1] << std::endl;
		std::cout << "BidAskCapi[2]: " << bidAskCapi[2] << std::endl;
		//connect();
		//firstMoneyClient::ClassYouWantToUse::Connect();s
	
		//firstMoneyClient::ClassYouWantToUse  * obj;// ^ obj = gcnew  ClassYouWantToUse;
		//obj = new  firstMoneyClient::ClassYouWantToUse();
		//obj->Disconnect();
		//// Initialize COM.
		//HRESULT hr = CoInitialize(NULL);

		////// Create the interface pointer.
		//_ClassYouWantToUsePtr pICalc(__uuidof(_ClassYouWantToUsePtr));

		//long lResult = 0;

		// Call the Add method.
		
		//pICalc->Add(5, 10, &lResult);

		//wprintf(L"The result is %d", lResult);

		// Uninitialize COM.
		//CoUninitialize();
		return;
		//CComPtr<firstMoneyClient::IInterface> yourClass;
		//firstMoneyClient::IInterfacePtr yourClass(__uuidof(NamespaceOfYourProject::ClassYouWantToUse));

		//yourClass->Connect();


		//CComPtr<firstMoneyClient::IInterface> yourClass;
		//firstMoneyClient::IInterfacePtr yourClass(__uuidof(NamespaceOfYourProject::ClassYouWantToUse));
		//firstMoneyClient::ClassYouWantToUse  yourclass = new ClassYouWantToUse();
		//firstMoneyClient::ClassYouWantToUse ^ obj = gcnew firstMoneyClient::ClassYouWantToUse;// ClassYouWantToUse;
		//YahooAPI ^ yahoo;/// = gcnew YahooAPI;
		//yahoo->GetBid("10");

		//firstMoneyClient::ClassYouWantToUse ^ obj =  gcnew  ClassYouWantToUse;
		//obj->Disconnect();
		//yourClass.Connect();
		int i = 10;
		int b = i;
		b += i;
	}
};

