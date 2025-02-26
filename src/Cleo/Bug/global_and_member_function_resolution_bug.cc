// -*- C++ -*-
//
// Bug Name:    GLOBAL_AND_MEMBER_FUNCTION_RESOLUTION_BUG
// Module:      
// 
// Description: 
//     This is a pernicous bug that is not always easy to spot.  The
// code will compile, but the compiler will use a global function where
// there is a perfectly acceptable memeber function!
//
//     It the exmplae given here the only indication that a global
// function is being used is a complaint that there is no `operator=='
// function for the global `operator!=' function in the algorithm header
// file.
//
// Existance:
//   g++: v2.7.2
//
// Author:      Simon Patton
// Created:     Tue Aug  26 21:20:59 EDT 1997
// $Id: global_and_member_function_resolution_bug.cc,v 1.2 2001/01/16 22:25:16 cdj Exp $
//
// Revision history
//
// $Log: global_and_member_function_resolution_bug.cc,v $
// Revision 1.2  2001/01/16 22:25:16  cdj
// now closer to C++ standard
//
// Revision 1.1  1998/03/16 22:59:52  mkl
// Simon's bug code snipplets for bug/feature flags
//
//
#include "Experiment/Experiment.h"

#include <algorithm>

class Junk
{
   public:
      char operator!=( const Junk& ) const { return ( 0 ) ; }
} ;

int main()
{
   Junk a , b ;
#if defined(GLOBAL_AND_MEMBER_FUNCTION_RESOLUTION_BUG)
   a.operator!=( b ) ;
#else
   a != b ;
#endif
   return( 0 ) ;
}
