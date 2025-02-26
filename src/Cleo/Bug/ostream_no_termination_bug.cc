#include "Experiment/Experiment.h"

#if defined(OSTRSTREAM_NO_TERMINATION_BUG)
#include <stdio.h>
#else
#include <string>
// #include <sstream> // not yet available
#include <strstream.h>
#endif

#include <iostream.h>

int main()
{
   int sum = 99;

// buggy ostrstream implementation and no stringstream in sight 
#if defined(OSTRSTREAM_NO_TERMINATION_BUG)
   const unsigned int kSize=100;
   char number[kSize];
   snprintf( number, kSize, "%d", sum );
#else
   //ostringstream summaryNumber; // not yet available: <sstream>
   ostrstream number;
   number << sum;
#endif
   cout << "Number=" << number << endl;
   
   return 0;
}

