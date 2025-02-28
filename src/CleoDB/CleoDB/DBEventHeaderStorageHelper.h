#if !defined(CLEODB_DBEVENTHEADERSTORAGEHELPER_H)
#define CLEODB_DBEVENTHEADERSTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBEventHeaderStorageHelper
// 
// Description: StorageHelper to store a DBEventHeader
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: DBEventHeaderStorageHelper.h,v 1.2 2001/05/23 16:47:48 bkh Exp $
//
// Revision history
//
// $Log: DBEventHeaderStorageHelper.h,v $
// Revision 1.2  2001/05/23 16:47:48  bkh
// Add time word
//
// Revision 1.1  1999/11/04 14:43:14  mkl
// added storage helpers for DBRunHeader and DBEventHeader
//
// Revision 1.1.1.1  1999/09/13 21:21:45  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMStorageProxyHelper.h"
#include "CleoDB/DBEventHeader.h"

// forward declarations

class DBEventHeaderStorageHelper : public SMStorageProxyHelper<DBEventHeader>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DBEventHeaderStorageHelper() ;
      //virtual ~DBEventHeaderStorageHelper();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const DBEventHeader& iData );

      //functions to deliver specific storage versions of DBEventHeader
      DBEventHeader* deliverV1( SMSourceStream& iSource );
      DBEventHeader* deliverV2( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const DBEventHeader& getDefault() const;
      virtual DABoolean compare( const DBEventHeader* iNewData, 
				 const DBEventHeader& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      DBEventHeaderStorageHelper( const DBEventHeaderStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DBEventHeaderStorageHelper& operator=( const DBEventHeaderStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( DBEventHeader* (DBEventHeaderStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* CLEODB_DBEVENTHEADERSTORAGEHELPER_H */
