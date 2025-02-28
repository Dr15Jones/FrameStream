//
// Martin Lohner, July 17, 1998
// The solaris compiler (CC 4.2) doesn't not allow 
// static const integral type definitions in class headers

#include "Experiment/Experiment.h"
#if !defined(NO_STATIC_CONST_INTEGRAL_DEFS_IN_CLASS_BUG)
class MyClass
{
   public:
      static const int myStaticInt = 3;
};
#endif // NO_STATIC_CONST_INTEGRAL_DEFS_IN_CLASS_BUG
