// -*- C++ -*-
//
// Bug Name:    NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG
// Module:      
// 
// Description: 
//     The template implementation does not support default parameters
//
// Existance:
//   
//
// Author:      Simon Patton
// Created:     Tue Aug  26 20:42:34 EDT 1997
// $Id: no_default_parameters_for_templates_bug.cc,v 1.2 2001/01/16 22:25:20 cdj Exp $
//
// Revision history
//
// $Log: no_default_parameters_for_templates_bug.cc,v $
// Revision 1.2  2001/01/16 22:25:20  cdj
// now closer to C++ standard
//
// Revision 1.1  1998/03/16 22:59:58  mkl
// Simon's bug code snipplets for bug/feature flags
//
//
#include "Experiment/Experiment.h"

#include <iostream.h>

#if defined(NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG)
template < class T , class U > class Junk
#else
template < class T , class U = int > class Junk
#endif // NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG 
{
   public:
      Junk( T a ,
	    U b ) :
	 m_a( a ) ,
	 m_b( b ) {}
      void print() { cout << m_a << " " << m_b << endl ; }
   private:
      T m_a ;
      T m_b ;
} ;

int main()
{
#if defined(NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG)
   Junk< float , int > a( 1 , 2 ) ;
#else
   Junk< float > a( 1 , 2 ) ;
#endif // NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG 
   a.print() ;
   return( 0 ) ;
}
