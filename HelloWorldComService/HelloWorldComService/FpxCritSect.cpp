
#include <windows.h>
#include "fpxcritsect.h"

//===[ Public members ]==================================================

//---> Class constructor #1 <--------------------------------------------
FpxCritSect::FpxCritSect(void)
{
  // Create our own FpxCritSecLock object
  pOurLockObj = new FpxCritSecLock;
  pLockObj = pOurLockObj;
}


//---> Class constructor #2 <--------------------------------------------
FpxCritSect::FpxCritSect(FpxCritSecLock    *_pLockObj, bool fEnter)
{
  // Use supplied lock object
  pOurLockObj = NULL;
  pLockObj = _pLockObj;

  // Enter the critical section now?
  if (fEnter) {
    // Yes, do it
    pLockObj->_Enter();
  }
}


//---> Class destructor <------------------------------------------------
FpxCritSect::~FpxCritSect()
{
  // Leave anything we might be in and clean up
  pLockObj->_Leave();
  delete pOurLockObj;
}
