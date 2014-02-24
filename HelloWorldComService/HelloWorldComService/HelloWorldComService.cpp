// HelloWorldComService.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "HelloWorldComService.h"


// This is an example of an exported variable
HELLOWORLDCOMSERVICE_API int nHelloWorldComService=0;

// This is an example of an exported function.
HELLOWORLDCOMSERVICE_API int fnHelloWorldComService(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see HelloWorldComService.h for the class definition
CHelloWorldComService::CHelloWorldComService()
{
	return;
}
