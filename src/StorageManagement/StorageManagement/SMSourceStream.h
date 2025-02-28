#if !defined(STORAGEMANAGEMENT_SMSOURCESTREAM_H)
#define STORAGEMANAGEMENT_SMSOURCESTREAM_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMSourceStream
// 
// Description: Base class for classes used to read out object from storage
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:18:25 EDT 1999
// $Id: SMSourceStream.h,v 1.3 2000/04/24 20:21:09 mkl Exp $
//
// Revision history
//
// $Log: SMSourceStream.h,v $
// Revision 1.3  2000/04/24 20:21:09  mkl
// SMStorageHelperBase::versionToStore() now virtual.
//
// Revision 1.2  2000/01/24 17:37:12  cdj
// can now access Record via SMSourceStream
//
// Revision 1.1.1.1  1999/09/13 21:21:40  cdj
// imported package
//

// system include files
#include <string>

// user include files
#include "DataHandler/DataKeyTags.h"

// forward declarations
class SMMakeContentsBase;
class Record;

class SMSourceStream
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMSourceStream(): m_record(0) {}
      virtual ~SMSourceStream() {}

      // ---------- member functions ---------------------------
      virtual SMSourceStream& operator>>( char  &) = 0;
      virtual SMSourceStream& operator>>( short &) = 0;
      virtual SMSourceStream& operator>>( int   &) = 0;
      virtual SMSourceStream& operator>>( long  &) = 0;

      virtual SMSourceStream& operator>>( unsigned char  &) = 0;
      virtual SMSourceStream& operator>>( unsigned short &) = 0;
      virtual SMSourceStream& operator>>( unsigned int   &) = 0;
      virtual SMSourceStream& operator>>( unsigned long  &) = 0;

      virtual SMSourceStream& operator>>( float  &) = 0;
      virtual SMSourceStream& operator>>( double &) = 0;
      virtual SMSourceStream& operator>>( string& ) = 0;

      // need to know when enter/exit object
      // (since not all may require to know, implement default)
      virtual void beginObject( const TypeTag& ) {}
      virtual void endObject() {}

      ///used to tell sink that we are outputting a container
      virtual SMSourceStream& operator>>( const SMMakeContentsBase& ) = 0;

      ///SMProxy's faultHandler sets the record
      void setRecord( const Record& iRecord ) { m_record = &iRecord ; }
      void clearRecord() { m_record = 0; }

      // ---------- const member functions ---------------------
      ///find out which version was stored
      virtual unsigned int versionUsed( const TypeTag& iType ) const = 0;

      ///is there any valid data in this source
      virtual DABoolean valid() const = 0;

      ///provides SMStorageHelper access to the Record so extract is possible
      const Record& record() const { return *m_record; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SMSourceStream( const SMSourceStream& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMSourceStream& operator=( const SMSourceStream& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const Record* m_record;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMSourceStream.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMSOURCESTREAM_H */
