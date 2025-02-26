// -*- C++ -*-
// Eddy Barnes    7/27/00

// system include files
#include "Experiment/Experiment.h"

#include <iostream.h>
#include <strstream.h>

//using namespace std;
class Ruby 
#if !defined(NO_STD_NAMESPACE_BUG) 
: public std::strstreambuf
#endif
{
   public:
      void Special();
};


void Ruby::Special()
{
#if defined(SEEKOFF_PROTOTYPE_WITHOUT_DEFAULT_3RDARG_BUG) 
#if !defined(NO_STD_NAMESPACE_BUG) 
    seekoff(0, ios::beg, ios::in | ios::out );
#endif
#else
    seekoff(0, ios::beg );
#endif
}

int main()
{
   Ruby Tuesday;
   Tuesday.Special();
}

