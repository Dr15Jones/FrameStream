// -*- C++ -*-
//
// Bug Name:    NO_DEFAULT_COMPARE_IN_STL_BUG
// 
// Description: 
//     The STL container classes that provide an order, e.g. set, map,
// etc., expect a default Compare class (namely less< T >) to be
// provided.  In some implementations, for instance when the compiler
// can not handle default parameters for template, no default is
// provided.
//
//     This bug must be found in conjuction with either of the following
// two flags to make any sense.
//
//	NO_DEFAULT_ALLOCATOR_IN_STL_BUG
//	NO_ALLOCATOR_IN_STL_DECLARATION_BUG
//
// Existence:
//   g++: v2.7.2
//   cxx: "fixed" in V5.5-004
//
// Author:      Simon Patton
// Created:     Tue Aug  26 21:13:76 EDT 1997
// $Id: no_default_compare_in_stl_bug.cc,v 1.2 2001/01/16 22:25:19 cdj Exp $
//
// Revision history
//
// $Log: no_default_compare_in_stl_bug.cc,v $
// Revision 1.2  2001/01/16 22:25:19  cdj
// now closer to C++ standard
//
// Revision 1.1  1998/03/16 22:59:57  mkl
// Simon's bug code snipplets for bug/feature flags
//
//
#include "Experiment/Experiment.h"

#include <set>

#if !defined(NO_STD_NAMESPACE_BUG)
using namespace std;
#endif

#if defined(NO_DEFAULT_COMPARE_IN_STL_BUG)
set< int , less< int > > s ;
#else
set< int > s ;
#endif

