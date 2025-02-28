#if !defined(JOBCONTROL_ASYNCINTERRUPT_H)
#define JOBCONTROL_ASYNCINTERRUPT_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      AsyncInterrupt
// 
// Description: handling of asynchronous interrupts
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Sep  4 17:21:32 EDT 1997
// $Id: AsyncInterrupt.h,v 1.2 1997/09/18 21:26:59 cdj Exp $
//
// Revision history
//
// $Log: AsyncInterrupt.h,v $
// Revision 1.2  1997/09/18 21:26:59  cdj
// changed Boolean to DABoolean
//
// Revision 1.1  1997/09/05 02:37:21  mkl
// wrap asynchronous interrupt handling in wrapper class
//

// system include files

// user include files

// forward declarations

class AsyncInterrupt
{
      // friend classes and functions
      friend class Dummy; // to get rid of g++ warnings

   public:
      // constants, enums and typedefs

      // Constructors and destructor

      // member functions

      // const member functions

      // static member functions
      static DABoolean checkForUserInput( void );

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      AsyncInterrupt();
      virtual ~AsyncInterrupt();
      AsyncInterrupt( const AsyncInterrupt& );

      // assignment operator(s)
      const AsyncInterrupt& operator=( const AsyncInterrupt& );

      // private member functions

      // private const member functions

      // data members

      // static data members
      static DABoolean readTerminal( char& input );
      static int checkAsynchronousInput( int& numberOfBytes );
};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "JobControl/Template/AsyncInterrupt.cc"
//#endif

#endif /* JOBCONTROL_ASYNCINTERRUPT_H */
