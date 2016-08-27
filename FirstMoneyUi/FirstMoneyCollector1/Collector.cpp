#include "stdafx.h"
#include "Collector.h"
#using <mscorlib.dll>

#import "../firstMoneyClient/bin/Debug/firstMoneyClient.tlb"  


void NativeWrapMethod()
{
	//CoInitialize(NULL);

	//firstMoneyClient::IInterfacePtr yourClass(__uuidof(firstMoneyClient::ClassYouWantToUse));

	//yourClass->Connect();

	//CoUninitialize();
}

Collector::Collector()
{
	CoInitialize(NULL);

	yourClass.CoCreateInstance(__uuidof(firstMoneyClient::IInterface));
}
void Collector::Connect()
{
	yourClass->Connect();
}

Collector::~Collector()
{
	CoUninitialize();
}
