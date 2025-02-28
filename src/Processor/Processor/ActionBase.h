#if !defined(PROCESSOR_ACTIONBASE_H)
#define PROCESSOR_ACTIONBASE_H
// -*- C++ -*-
//
// Package:     <Processor>
// Module:      ActionBase
// 
// Description: Abstract base class for Actions
//
// Usage:
//    Actions are functional objects which are executed when
//    a new Record appears in an Active Stream.
//
// Author:      Chris D. Jones
// Created:     Thu Apr 17 17:12:54 EDT 1997
// $Id: ActionBase.h,v 1.7 2003/09/19 19:30:31 cdj Exp $
//
// Revision history
//
// $Log: ActionBase.h,v $
// Revision 1.7  2003/09/19 19:30:31  cdj
// added kNoFiltering
//
// Revision 1.6  1999/03/14 22:23:43  mkl
// fixed bug in execution loop (anything but kPassed stopped event loop); get rid of void in function declaration/definion
//
// Revision 1.5  1998/07/21 16:23:25  mkl
// register producer proxies AFTER source proxies; new ActionResult::kStopProcessLoop
//
// Revision 1.4  1998/02/10 18:07:03  mkl
// return from fortran 'actions' handled
//
// Revision 1.3  1998/02/03 21:29:58  mkl
// switch over to STLUtility library
//
// Revision 1.2  1997/07/11 05:59:25  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.1.1.1  1997/05/23 20:18:00  mkl
// imported processor sources
//

// system include files

// user include files
#include "Processor/ActionResult.inc"

// forward declarations
class Frame;

class ActionBase
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      enum ActionResult { kPassed          = kActionPassed, 
			  kFailed          = kActionFailed,
			  kError           = kActionError,
			  kNoAction        = kActionNoAction,
			  kNoFiltering     = kActionNoAction,
  			  kStopProcessLoop = kActionStopProcessLoop
      };

      // Constructors and destructor
      ActionBase();
      virtual ~ActionBase();

      // member functions
      virtual ActionResult operator()( Frame& iFrame) = 0;

      // const member functions

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      //ActionBase( const ActionBase& );

      // assignment operator(s)
      //const ActionBase& operator=( const ActionBase& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* PROCESSOR_ACTIONBASE_H */
