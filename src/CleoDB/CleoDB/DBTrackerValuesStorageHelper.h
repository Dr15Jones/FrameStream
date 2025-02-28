#if !defined(CLEODB_DBTRACKERVALUESSTORAGEHELPER_H)
#define CLEODB_DBTRACKERVALUESSTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBTrackerValuesStorageHelper
// 
// Description: StorageHelper to store a DBTrackerValues
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: DBTrackerValuesStorageHelper.h,v 1.1 2000/03/01 00:40:21 cdj Exp $
//
// Revision history
//
// $Log: DBTrackerValuesStorageHelper.h,v $
// Revision 1.1  2000/03/01 00:40:21  cdj
// first submission
//
// Revision 1.2  1999/10/18 18:14:37  cdj
// now inherits from SMStorageProxyHelper
//
// Revision 1.1.1.1  1999/09/13 21:21:45  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMStorageProxyHelper.h"
#include "CleoDB/DBTrackerValues.h"

// forward declarations

class DBTrackerValuesStorageHelper : public SMStorageProxyHelper<DBTrackerValues>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DBTrackerValuesStorageHelper() ;
      //virtual ~DBTrackerValuesStorageHelper();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const DBTrackerValues& iData );

      //functions to deliver specific storage versions of DBTrackerValues
      DBTrackerValues* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const DBTrackerValues& getDefault() const;
      virtual DABoolean compare( const DBTrackerValues* iNewData, 
				 const DBTrackerValues& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      DBTrackerValuesStorageHelper( const DBTrackerValuesStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DBTrackerValuesStorageHelper& operator=( const DBTrackerValuesStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( DBTrackerValues* (DBTrackerValuesStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* CLEODB_DBTRACKERVALUESSTORAGEHELPER_H */
