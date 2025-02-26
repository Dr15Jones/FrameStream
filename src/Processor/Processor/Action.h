#if !defined(PACKAGE_ACTION_H)
#define PACKAGE_ACTION_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      Action
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Thu Apr 17 17:15:56 EDT 1997
// $Id: Action.h,v 1.3 1997/07/11 05:59:24 mkl Exp $
//
// Revision history
//
// $Log: Action.h,v $
// Revision 1.3  1997/07/11 05:59:24  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.2  1997/06/14 03:52:53  mkl
// replaced static function calls with pointers to member functions
//
// Revision 1.1.1.1  1997/05/23 20:18:00  mkl
// imported processor sources
//

// system include files

// user include files
#include "Processor/ActionBase.h"

// forward declarations

template <class T>
class Action : public ActionBase
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      Action( ActionResult (T::*iMethod)( Frame& ), T* iProcessor )
	 : m_processor( iProcessor ),
	   m_method( iMethod ) {}
      virtual ~Action() {}
      
      // member functions
      virtual ActionResult operator()( Frame& iFrame ) 
      {
	 return (m_processor->*m_method)( iFrame );
      }

      // const member functions

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      //Action( const Action& );

      // assignment operator(s)
      //const Action& operator=( const Action& );

      // private member functions

      // private const member functions

      // data members
      T* m_processor;
      ActionResult (T::*m_method)( Frame& );

      // static data members

};

// inline function definitions

#endif /* PACKAGE_ACTION_H */



