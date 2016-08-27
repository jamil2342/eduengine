#pragma once
#include <atlcomcli.h> 
#include <initguid.h>
#import "../firstMoneyClient/bin/Debug/firstMoneyClient.tlb"  
using namespace firstMoneyClient;
void NativeWrapMethod();
class Collector
{
public:
	Collector();
	~Collector();
	void Connect(void);

private:
	CComPtr<firstMoneyClient::IInterface> yourClass;
	//ClassYouWantToUse * client;
};

