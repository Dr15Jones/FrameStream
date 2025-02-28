#if !defined(STORAGEMANAGEMENT_SMPROXYWRITERBASE_H)
#define STORAGEMANAGEMENT_SMPROXYWRITERBASE_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMProxyWriterBase
// 
// Description: Base class for Objects that write the data out to a 
//               SMSinkStream
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Mon May 24 17:02:26 EDT 1999
// $Id: SMProxyWriterBase.h,v 1.2 2000/07/19 18:52:08 mkl Exp $
//
// Revision history
//
// $Log: SMProxyWriterBase.h,v $
// Revision 1.2  2000/07/19 18:52:08  mkl
// add a success return from SMProxyWriter::store
//
// Revision 1.1.1.1  1999/09/13 21:21:41  cdj
// imported package
//

// system include files

// user include files

// forward declarations
class DataKey;
class Record;
class SMSinkStream;

class SMProxyWriterBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMProxyWriterBase();
      virtual ~SMProxyWriterBase();

      // ---------- member functions ---------------------------
      DABoolean store( const DataKey& iKey     ,
		       const Record&  iRecord  ,
		       SMSinkStream&  iOStream  ) ;

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual DABoolean extractData( const DataKey& iKey,
				     const Record&  iRecord,
				     SMSinkStream&  iOStream ) = 0 ;

      // ---------- protected const member functions -----------
      virtual void writeData( SMSinkStream& iOStream ) const =0 ;

   private:
      // ---------- Constructors and destructor ----------------
      SMProxyWriterBase( const SMProxyWriterBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMProxyWriterBase& operator=( const SMProxyWriterBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMProxyWriterBase.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMPROXYWRITERBASE_H */
