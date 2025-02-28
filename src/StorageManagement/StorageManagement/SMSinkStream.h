#if !defined(STORAGEMANAGEMENT_SMSINKSTREAM_H)
#define STORAGEMANAGEMENT_SMSINKSTREAM_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMSinkStream
// 
// Description: Base class for classes used to write out objects to storage
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:18:19 EDT 1999
// $Id: SMSinkStream.h,v 1.2 1999/11/03 17:53:47 cdj Exp $
//
// Revision history
//
// $Log: SMSinkStream.h,v $
// Revision 1.2  1999/11/03 17:53:47  cdj
// added compression hints code
//
// Revision 1.1.1.1  1999/09/13 21:21:40  cdj
// imported package
//

// system include files
#include <string>

// user include files
#include "DataHandler/DataKeyTags.h"
#include "StorageManagement/SMFieldBase.h"

// forward declarations
class SMContentsBase;
class SMPackInfo;

class SMSinkStream
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMSinkStream() : m_packInfo( s_defaultPackInfo ){}
      virtual ~SMSinkStream() {}

      // ---------- member functions ---------------------------
      SMSinkStream& operator<<( const SMFieldBase& iField ) {
	 iField.store( *this );
	 return *this; }

      virtual void put( const char * iFieldName, char ) = 0;
      virtual void put( const char * iFieldName, short ) = 0;
      virtual void put( const char * iFieldName, int ) = 0;
      virtual void put( const char * iFieldName, long ) = 0;

      virtual void put( const char * iFieldName, unsigned char ) = 0;
      virtual void put( const char * iFieldName, unsigned short ) = 0;
      virtual void put( const char * iFieldName, unsigned int ) = 0;
      virtual void put( const char * iFieldName, unsigned long ) = 0;

      virtual void put( const char * iFieldName, float ) = 0;
      virtual void put( const char * iFieldName, double ) = 0;
      virtual void put( const char * iFieldName, const string& ) = 0;

      //used to tell sink that we are outputting a container
      virtual void put( const char * iFieldName, const SMContentsBase& ) = 0;

      virtual void beginObject( const TypeTag& ) = 0;
      virtual void endObject() = 0;

      //functions used for setting up compression
      void setPackInfo( const SMPackInfo& iPackInfo ) {
	 m_packInfo = &iPackInfo;
      }

      void unsetPackInfo() {
	 m_packInfo = s_defaultPackInfo;
      }

      // ---------- const member functions ---------------------
      const SMPackInfo& packInfo() const { return *m_packInfo; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SMSinkStream( const SMSinkStream& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMSinkStream& operator=( const SMSinkStream& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const SMPackInfo* m_packInfo;

      // ---------- static data members ------------------------
      static SMPackInfo* s_defaultPackInfo;

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMSinkStream.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMSINKSTREAM_H */
