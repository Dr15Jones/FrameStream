#if !defined(PACKAGE_MYPROCESSOR_H)
#define PACKAGE_MYPROCESSOR_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      MyProcessor
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Thu Apr 17 18:04:24 EDT 1997
// $Id: MyProcessor.h,v 1.1.1.1 1997/05/23 20:18:01 mkl Exp $
//
// Revision history
//
// $Log: MyProcessor.h,v $
// Revision 1.1.1.1  1997/05/23 20:18:01  mkl
// imported processor sources
//


// system include files

// user include files
#if !defined(FILENAME_ONLY) /* relative path includes */
#include "Processor/Include/EventBeginRunProcessor.h"
#else /* filename-only includes */
#include "EventBeginRunProcessor.h"
#endif /* filename-only includes */

// forward declarations

class MyProcessor : public EventBeginRunProcessor
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      MyProcessor( void );
      virtual ~MyProcessor();

      // member functions
      virtual void event( Frame& iFrame);
      virtual void beginRun( Frame& iFrame );

      // const member functions

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      MyProcessor( const MyProcessor& );

      // assignment operator(s)
      const MyProcessor& operator=( const MyProcessor& );

      // private member functions

      // private const member functions

      // data members
      int m_data;

      // static data members

};

// inline function definitions

#endif /* PACKAGE_MYPROCESSOR_H */
