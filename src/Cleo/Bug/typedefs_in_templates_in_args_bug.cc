// -*- C++ -*-
//
// Bug Name:    TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG
// 
// Description: 
//     In a template class, when a definition is provided outside
// the class declaration it does not recognize variables that are
// typedefed inside the class declaration!
//
//     One solution is to define the necessary functions in the
// class declaration.
//
// Existence:
//   g++: v2.7.2
//
// Author:      Simon Patton
// Created:     Tue Aug  26 22:25:09 EDT 1997
// $Id: typedefs_in_templates_in_args_bug.cc,v 1.3 2001/01/16 22:25:24 cdj Exp $
//
// Revision history
//
// $Log: typedefs_in_templates_in_args_bug.cc,v $
// Revision 1.3  2001/01/16 22:25:24  cdj
// now closer to C++ standard
//
// Revision 1.2  1998/04/09 23:15:24  cleo3
// port to egcs
//
// Revision 1.1  1998/03/16 23:00:01  mkl
// Simon's bug code snipplets for bug/feature flags
//
//

#include "Experiment/Experiment.h"

template < class T >
class Box
{
   public:
      typedef int Id ;

#if defined(TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG)
      Box( const Id& aId ) {
      }
#else
      Box( const Id& aId ) ;
#endif /* TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG */
} ;

#if !defined(TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG)
template < class T >
Box< T >::Box( const Box::Id& aId )
{
}
#endif /* TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG */

