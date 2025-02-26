// -*- C++ -*-
// Eddy Barnes    7/11/00

// system include files
#include "Experiment/Experiment.h"
#include <iostream.h>
#include <string>

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

int main()
{
#if defined(NO_GETLINE_ISTREAM_STRING_BUG)
   const int size = 10;
   char aString[size];
   cin.getline(aString,size);
#else
   STD_PREFIX string aString;
   getline(cin, aString);
#endif
}

