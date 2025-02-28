// -*- C++ -*-
//
// Bug Name:    LOOSES_NESTED_CLASS_DECLARATION_BUG
// 
// Description: 
//     The declaration of a nested class appears to be lost if the
// enclosing class is forward declared after the full declaration.
//
// Existence:
//   cxx: all versions
//
// Author:      Simon Patton
// Created:     Thu May  17 13:06:83 EDT 1996
// $Id: looses_nested_class_declaration_bug.cc,v 1.2 2001/01/16 22:25:17 cdj Exp $
//
// Revision history
//
// $Log: looses_nested_class_declaration_bug.cc,v $
// Revision 1.2  2001/01/16 22:25:17  cdj
// now closer to C++ standard
//
// Revision 1.1  1998/03/16 22:59:53  mkl
// Simon's bug code snipplets for bug/feature flags
//
//
#include "Experiment/Experiment.h"

template < class T >
class Junk
{
   public:
      class nested_class
      {
      } ;
} ;

#if !defined(LOOSES_NESTED_CLASS_DECLARATION_BUG)
template < class T > class Junk ;
#endif

int main()
{
   Junk< int > a ;
   Junk< int >::nested_class b ;
   return( 0 ) ;
}
