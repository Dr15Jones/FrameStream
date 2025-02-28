#if !defined(CLEODB_DBRUNHEADER_H)
#define CLEODB_DBRUNHEADER_H
// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBRunHeader
// 
// Description: Container for run header information
//
// Usage:
//    <usage>
//
// Author:      Your name here
// Created:     Mon Jan  1 00:00:00 EDT 1970
// $Id: DBRunHeader.h,v 1.3 1999/11/04 14:43:15 mkl Exp $
//
// Revision history
//
// $Log: DBRunHeader.h,v $
// Revision 1.3  1999/11/04 14:43:15  mkl
// added storage helpers for DBRunHeader and DBEventHeader
//
// Revision 1.2  1998/11/06 19:56:54  marsh
// Removed unneeded 'const's.
//
// Revision 1.1  1997/09/10 13:57:25  sjp
// File to handle DBRunHeader
//

// system include files

// user include files
#include "DataHandler/Stream.h" // for Stream::Type

// forward declarations

class DBRunHeader
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      static const Stream::Type& kStream ;

      // Constructors and destructor
      DBRunHeader( const Count aValue ) ;
      virtual ~DBRunHeader();

      // member functions

      // const member functions
      Count number() const ;

      // static member functions

   private:
      // Constructors and destructor
      DBRunHeader(); // stop default ;
      //needed for Storage: DBRunHeader( const DBRunHeader& ) ; // stop default

      // assignment operator(s)
      const DBRunHeader& operator=( const DBRunHeader& ) ; // stop default

      // data members
      Count m_value ;
};

// inline function definitions

#endif /* CLEODB_DBRUNHEADER_H */
