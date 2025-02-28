#if !defined(CLEODB_DBRUNHEADERSTORAGEHELPER_H)
#define CLEODB_DBRUNHEADERSTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBRunHeaderStorageHelper
// 
// Description: StorageHelper to store a DBRunHeader
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Nov 4 16:55:38 EDT 1999
// $Id: DBRunHeaderStorageHelper.h,v 1.1 1999/11/04 14:43:15 mkl Exp $
//
// Revision history
//
// $Log: DBRunHeaderStorageHelper.h,v $
// Revision 1.1  1999/11/04 14:43:15  mkl
// added storage helpers for DBRunHeader and DBEventHeader
//
//

// system include files

// user include files
#include "StorageManagement/SMStorageProxyHelper.h"
#include "CleoDB/DBRunHeader.h"

// forward declarations

class DBRunHeaderStorageHelper : public SMStorageProxyHelper<DBRunHeader>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DBRunHeaderStorageHelper() ;
      //virtual ~DBRunHeaderStorageHelper();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const DBRunHeader& iData );

      //functions to deliver specific storage versions of DBRunHeader
      DBRunHeader* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const DBRunHeader& getDefault() const;
      virtual DABoolean compare( const DBRunHeader* iNewData, 
				 const DBRunHeader& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      DBRunHeaderStorageHelper( const DBRunHeaderStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DBRunHeaderStorageHelper& operator=( const DBRunHeaderStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( DBRunHeader* (DBRunHeaderStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* CLEODB_DBRUNHEADERSTORAGEHELPER_H */
