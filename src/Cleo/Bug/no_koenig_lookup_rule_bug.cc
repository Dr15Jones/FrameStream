// -*- C++ -*-
// Eddy Barnes    7/3/00

// system include files
#include "Experiment/Experiment.h"
#include <iostream.h>

#if !defined(NO_NAMESPACE_BUG)
namespace N {
   enum Arg {zero, one};
   int f(Arg a, int i) {
      return 1;
   }
}

using namespace N;

void f(Arg a, long i) {}

int main() {
   Arg w = one;
   #if !defined(NO_KOENIG_LOOKUP_RULE_BUG)
   if(f(w,0)) cout << "koenig lookup rule is enacted" << endl;
   #endif // NO_KOENIG_LOOKUP_RULE_BUG
   return 0;
}
#endif // NO_NAMESPACE_BUG
