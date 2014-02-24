#ifndef FPXCRITSEC_H_
#define FPXCRITSEC_H_

#include "fpxcritseclock.h"

class FpxCritSect
{
protected:
  // Protected class data
    FpxCritSecLock     *pLockObj,              // Ptr to lock object we're using
                       *pOurLockObj;           // Ptr to lock object we created

public:
  FpxCritSect();
  FpxCritSect(FpxCritSecLock *, bool = true);
  virtual ~FpxCritSect();

  // Enter/leave logic
  void            Enter(void);                // Enter the critical section
  void            Leave(void);                // Leave the critical section
};

#endif
