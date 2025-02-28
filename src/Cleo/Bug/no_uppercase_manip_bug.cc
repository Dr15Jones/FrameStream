// -*- C++ -*-
// Eddy Barnes    7/11/00

// system include files
#include "Experiment/Experiment.h"
#include <string>
#include <strstream.h>

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

int main()
{
   const STD_PREFIX string aString = "hello, hello";
   ostrstream uppercaseStream;
   #if !defined(NO_UPPERCASE_MANIP_BUG)
   uppercaseStream << uppercase() << aString;
   #endif // NO_UPPERCASE_MANIP_BUG
}

