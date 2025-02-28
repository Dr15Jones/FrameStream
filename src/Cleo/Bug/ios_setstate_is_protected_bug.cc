// -*- C++ -*-
// Eddy Barnes    7/11/00

// system include files
#include "Experiment/Experiment.h"
#include <iostream.h>

int main()
{
   #if !defined(IOS_SETSTATE_IS_PROTECTED_BUG)
   cin.setstate(ios::failbit);
   #endif // IOS_SETSTATE_IS_PROTECTED_BUG
}



