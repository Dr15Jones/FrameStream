// -*- C++ -*-
//
// Package:     Bug
// Module:      no_templated_member_functions_bug
// 
// Description: Test to see if the compiler supports templated member functions
//
// Usage:
//      If a compiler fails to compile this file, you should set the 
//      NO_TEMPLATED_MEMBER_FUNCTIONS_BUG flag
//
// Author:      Chris D Jones
// Created:     Sat Oct 23 13:45:54 EDT 1999
// $Id: no_templated_member_functions_bug.cc,v 1.2 2001/01/16 22:25:21 cdj Exp $
//
// Revision history
//
// $Log: no_templated_member_functions_bug.cc,v $
// Revision 1.2  2001/01/16 22:25:21  cdj
// now closer to C++ standard
//
// Revision 1.1  1999/10/23 20:57:05  cdj
// first submission
//
#include "Experiment/Experiment.h"
#include <iostream.h>

#if !defined(NO_TEMPLATED_MEMBER_FUNCTIONS_BUG)
class MyPrinter {
   public:
      template<class Iterator> void print( const Iterator& itStart, 
					   const Iterator& itEnd ) {
	 for( Iterator itObj = itStart; itObj != itEnd; ++itObj ) {
	    cout << *itObj << endl;
	 }
      }
};

int main(void)
{
   int values[] = {1, 3, 5, 8};

   MyPrinter printer;
   printer.print( &( values[0] ), 
		  ( &(values[0]) ) + sizeof(values)/sizeof(int) ) ;
}
#endif // NO_TEMPLATED_MEMBER_FUNCTIONS_BUG

