#if !defined(UTILITY_UTIDENTIFIERLESS_H)
#define UTILITY_UTIDENTIFIERLESS_H
// -*- C++ -*-
//
// Package:     Utility
// Module:      UTIdentifierLess
// 
// Description: Uses the UTIdentifier's index to do high speed comparisons
//
// Usage:
//    This functional object is most useful when used as the comparison 
//    operator in a map or set that contains a UTIdentifier
//
// Author:      Chris D. Jones
// Created:     Tue Apr 29 13:12:09 EDT 1997
// $Id: UTIdentifierLess.h,v 1.4 1997/09/18 21:35:47 cdj Exp $
//
// Revision history
//
// $Log: UTIdentifierLess.h,v $
// Revision 1.4  1997/09/18 21:35:47  cdj
// changed Boolean to DABoolean
//
// Revision 1.3  1997/09/01 16:23:11  sjp
// Moved TBIdentifier to UTIdentifier
//
// Revision 1.2  1997/07/07 16:15:50  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1  1997/04/30 13:43:24  sjp
// New file to speed up matching identifiers
//


// system include files

// user include files
#include "Utility/UTIdentifier.h"


// forward declarations

template< class ID, class T>
class UTIdentifierLess
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      //UTIdentifierLess();
      //virtual ~UTIdentifierLess();

      // member functions

      // const member functions
      DABoolean operator()( const UTIdentifier< ID, T>& iLHS,
			  const UTIdentifier< ID, T>& iRHS) const {
	 return ( iLHS.index() < iRHS.index() );
      };
	 

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      //UTIdentifierLess( const UTIdentifierLess& );

      // assignment operator(s)
      //const UTIdentifierLess& operator=( const UTIdentifierLess& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* UTILITY_UTIDENTIFIERLESS_H */
