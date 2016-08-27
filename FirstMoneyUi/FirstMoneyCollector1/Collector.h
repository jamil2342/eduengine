#pragma once
#include <atlcomcli.h> 
#import "../firstMoneyClient/bin/Debug/firstMoneyClient.tlb"  
void NativeWrapMethod();
class Collector
{
public:
	Collector();
	~Collector();
	void Connect(void);

private:
	CComPtr<firstMoneyClient::IInterface> yourClass;
};

