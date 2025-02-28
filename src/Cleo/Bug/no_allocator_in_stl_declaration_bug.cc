// -*- C++ -*-
//
// Bug Name:    NO_ALLOCATOR_IN_STL_DECLARATION_BUG
// 
// Description: 
//     Many of the earlier version of compilers did not include
// the `Allocator' parameter in the STL declarations.  This is only
// important if you wish to forward declare the containers rather
// than using the include file (which can bring in many problems).
//
// Existance:
//   g++: v2.7.2
//   cxx: "fixed" in V5.5-004
//
// Author:      Simon Patton
// Created:     Tue Aug  26 20:42:34 EDT 1997
// $Id: no_allocator_in_stl_declaration_bug.cc,v 1.2 2001/01/16 22:25:19 cdj Exp $
//
// Revision history
//
// $Log: no_allocator_in_stl_declaration_bug.cc,v $
// Revision 1.2  2001/01/16 22:25:19  cdj
// now closer to C++ standard
//
// Revision 1.1  1998/03/16 22:59:56  mkl
// Simon's bug code snipplets for bug/feature flags
//
//
#include "Experiment/Experiment.h"

#include <vector>

#if defined(NO_ALLOCATOR_IN_STL_DECLARATION_BUG)
template < class T > class vector ;
#else
template < class T , class Allocator > class vector ;
#endif
