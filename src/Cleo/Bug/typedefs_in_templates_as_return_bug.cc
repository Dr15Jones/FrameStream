// -*- C++ -*-
//
// Bug Name:    TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG
// 
// Description: 
//     In a template class, when a definition is provided outside
// the class declaration it does not understand the signature if the
// return class is a typedef inside the class declaration!
//
//     The solution is to define the necessary functions in the
// class declaration.
//
// Existence:
//   g++: v2.7.2
//
// Author:      Simon Patton
// Created:     Tue Aug  26 22:25:09 EDT 1997
// $Id: typedefs_in_templates_as_return_bug.cc,v 1.2 2001/01/16 22:25:23 cdj Exp $
//
// Revision history
//
// $Log: typedefs_in_templates_as_return_bug.cc,v $
// Revision 1.2  2001/01/16 22:25:23  cdj
// now closer to C++ standard
//
// Revision 1.1  1998/03/16 23:00:00  mkl
// Simon's bug code snipplets for bug/feature flags
//
//
#include "Experiment/Experiment.h"

template < class T >
class Box
{
   public:
      typedef int Id ;

#if defined(TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG)
      Id open() {
      }
#else
      Id open() ;
#endif /* TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG */
} ;

#if !defined(TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG)
template < class T >
Box< T >::Id Box< T >::open()
{
}
#endif /* TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG */

