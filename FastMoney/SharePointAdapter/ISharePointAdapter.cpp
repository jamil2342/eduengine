#include "StdAfx.h"
#include "ISharePointAdapter.h"
#include "SharePointAdapter.h"

ISharePointAdapter *ISharePointAdapter::CreateInstance(void)
{
	return ((ISharePointAdapter *)new CSharePointAdapter());
}

void ISharePointAdapter::Destroy(ISharePointAdapter *instance)
{
	instance->Disconnect();
	delete instance;
}
