#include <windows.h>

#include "fpxcritseclock.h"

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//---------------|  FpxCritSecLock class implementation  |--------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------

//---> Class constructor #1 <--------------------------------------------
FpxCritSecLock::FpxCritSecLock()
{
  // Initialize the thing
  _Init();
}


//---> Class destructor <------------------------------------------------
FpxCritSecLock::~FpxCritSecLock()
{
  // Destroy the thing
  _Destroy();
}

//===[ Private/protected members ]=======================================

//---> _Init() - Initialize platform-specific code <---------------------
void FpxCritSecLock::_Init()
{
  // allocate the crit sec space
  InitializeCriticalSection(&critSec);
}


//---> _Destroy() - Destroy the critical section data <------------------
void FpxCritSecLock::_Destroy()
{
  // Clean up
  DeleteCriticalSection(&critSec);
}


//===[ Public members ]==================================================

//---> _Enter() - Enter the critical section <---------------------------
void FpxCritSecLock::_Enter()
{
  // Enter the critical section
  EnterCriticalSection(&critSec);
}


//---> _Leave() - Leave the critical section <---------------------------
void FpxCritSecLock::_Leave()
{
  // Do it
  LeaveCriticalSection(&critSec);
}
