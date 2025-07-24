#include <iostream>

#include "Experiment/Experiment.h"
#include "../JobControl/AsyncInterrupt.h"

int main()
{
   while( true )
   {
      bool stop = AsyncInterrupt::checkForUserInput();
      if( true == stop ) break;
   }

   return 0;
}
