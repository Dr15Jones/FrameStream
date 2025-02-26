// -*- C++ -*-
// Eddy Barnes    7/11/00

// system include files
#include "Experiment/Experiment.h"
#include <fstream.h>

int main()
{
   #if !defined(NO_IS_OPEN_FUNCTION_IN_FSTREAM_BUG)
   ifstream aFileHandle;
   if(aFileHandle.is_open()) {}
   #endif
}




