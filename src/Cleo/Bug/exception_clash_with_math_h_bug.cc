// -*- C++ -*-
//
// Package:     Bug
// Module:      exception_clash_with_math_h_bug
// 
// Description: On some version of DEC's cxx compiler, the compiler would
//    report an error if you tried to include math.h because math.h defined
//    'exception' which conflicted with cxx's internal exception.
//
// Usage:
//     If this file fails to compile, recompile with 
//      EXCEPTION_CLASH_WITH_MATH_H_BUG set
//
// Author:      Chris D Jones
// Created:     Sat Oct 23 15:53:45 EDT 1999
// $Id: exception_clash_with_math_h_bug.cc,v 1.2 2001/01/16 22:25:16 cdj Exp $
//
// Revision history
//
// $Log: exception_clash_with_math_h_bug.cc,v $
// Revision 1.2  2001/01/16 22:25:16  cdj
// now closer to C++ standard
//
// Revision 1.1  1999/10/23 20:57:04  cdj
// first submission
//
#include "Experiment/Experiment.h"

#if defined(EXCEPTION_CLASH_WITH_MATH_H_BUG)
#define exception _math_bug_
#include <math.h>  // required for trigonometry and fabs
#undef exception
#else
#include <math.h>  // required for trigonometry and fabs
#endif

#include <exception>
#if !defined(NO_NAMESPACE_BUG)
using namespace std;
#endif
int
main() {
   double sin( 0 );
   return 0;
}
