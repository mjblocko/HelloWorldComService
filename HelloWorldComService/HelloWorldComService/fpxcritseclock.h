#ifndef FPXCRITSECLOCK_H_
#define FPXCRITSECLOCK_H_

//--> Forward declarations <-----------------------------------
class FpxCritSect;

class FpxCritSecLock
{
protected:
  // Protected class data for Win32
#if defined(_WIN32)
  CRITICAL_SECTION  critSec;                // Critical section data
#endif

  // Protected class members
  void            _Init(void);                // Platform specific
  void            _Destroy(void);             // Platform specific
  void            _Enter(void);               // Enter the critical section
  void            _Leave(void);               // Leave the critical section

  // Friend classes
  friend class    FpxCritSect;

public:
  // Intialization & Termination
  FpxCritSecLock();
  virtual ~FpxCritSecLock();
};

#endif
