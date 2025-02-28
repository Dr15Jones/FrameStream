#if !defined(CLEODB_DBEVENTHEADER_H)
#define CLEODB_DBEVENTHEADER_H
// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBEventHeader
// 
// Description: Event header information
//
// Usage:
//   
//
// Author:      Simon Patton
// Created:     Mon Apr  7 16:52:05 EDT 1997
// $Id: DBEventHeader.h,v 1.6 2001/05/23 16:47:47 bkh Exp $
//
// Revision history
//
// $Log: DBEventHeader.h,v $
// Revision 1.6  2001/05/23 16:47:47  bkh
// Add time word
//
// Revision 1.5  1999/11/04 14:43:13  mkl
// added storage helpers for DBRunHeader and DBEventHeader
//
// Revision 1.4  1997/08/06 18:08:26  sjp
// Removed dependence on DataField
//
// Revision 1.3  1997/07/09 18:01:40  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.2  1997/04/14 19:52:57  sjp
// First working version
//
// Revision 1.1  1997/04/10 02:10:32  sjp
// Add filename only includes.
// Prepared for templated DataField system
//


// system include files

// user include files
#include "DataHandler/Stream.h" // for Stream::Type


// forward declarations

class DBEventHeader
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      // following must be a reference to avoid confusion when static
      //   objects are being created.
      static const Stream::Type& kStream ;

      enum { k_MCTime = 10101 } ; // magic time value in MC time

      // Constructors and destructor
      DBEventHeader( Count  run       ,
		     Count  number    ,
		     UInt32 timeMost  ,
		     UInt32 timeLeast    ) ;

      DBEventHeader( Count  run       ,
		     Count  number    ,
		     UInt64 time    = 0     ) ;

      virtual ~DBEventHeader() ;

      // member functions

      // const member functions
      Count     run()        const ;
      Count     number()     const ;
      UInt64    time()       const ;

      DABoolean monteCarlo() const ; // flag indicating is MC event

      UInt32 timeMost()  const ; // accessor for storage helper
      UInt32 timeLeast() const ; // accessor for storage helper

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      DBEventHeader();
      // needed for StorageManagement: DBEventHeader( const DBEventHeader& );

      // assignment operator(s)
      const DBEventHeader& operator=( const DBEventHeader& );

      // private member functions

      // private const member functions

      // data members
      Count  m_run   ;
      Count  m_event ;
      UInt64 m_time  ;

      // static data members

};

// inline function definitions

#endif /* CLEODB_DBEVENTHEADER_H */
