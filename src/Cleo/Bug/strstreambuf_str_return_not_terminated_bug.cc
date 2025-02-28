// -*- C++ -*-
// Eddy Barnes    7/11/00

// system include files
#include "Experiment/Experiment.h"
#include <iostream.h>
#include <strstream.h>

int main()
{
   #if !defined(STRSTREAMBUF_STR_RETURN_NOT_TERMINATED_BUG)
   strstreambuf value;
   cin.get(value, 'x');
   cout << value.str();
   #endif
}

