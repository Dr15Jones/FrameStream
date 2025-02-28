#if !defined(STORAGEMANAGEMENT_SMFAPTRTABLESTORAGEHELPER_H)
#define STORAGEMANAGEMENT_SMFAPTRTABLESTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMFAPtrTableStorageHelper
// 
// Description: StorageHelper template for storing FAPtrTables
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri Jun 11 14:34:10 EDT 1999
// $Id: SMFAPtrTableStorageHelper.h,v 1.3 1999/12/15 22:05:59 cdj Exp $
//
// Revision history
//
// $Log: SMFAPtrTableStorageHelper.h,v $
// Revision 1.3  1999/12/15 22:05:59  cdj
// removed the destructor to avoid crash at Suez exit on OSF1
//
// Revision 1.2  1999/10/18 18:23:39  cdj
// now inherits from SMStorageProxyHelper
//
// Revision 1.1.1.1  1999/09/13 21:21:40  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMStorageProxyHelper.h"
#include "FrameAccess/FAPtrTable.h"

// forward declarations

template < class T >
class SMFAPtrTableStorageHelper :
   public SMStorageProxyHelper< FAPtrTable< T > >
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef FAPtrTable< T > StoreType;

      // ---------- Constructors and destructor ----------------
      SMFAPtrTableStorageHelper();
      //virtual ~SMFAPtrTableStorageHelper();

      // ---------- member functions ---------------------------
      virtual StoreType* deliverV1( SMSourceStream& iSource );

      void setTable( StoreType* iTable ) {
	 m_table = iTable; }

      // ---------- const member functions ---------------------
      SMProxyBase* makeProxy() const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const StoreType& iData );

      // ---------- protected const member functions -----------
      virtual const StoreType& getDefault() const;
      virtual DABoolean compare( const StoreType* iNewData, 
				 const StoreType& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      SMFAPtrTableStorageHelper( const SMFAPtrTableStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMFAPtrTableStorageHelper& operator=( const SMFAPtrTableStorageHelper& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      StoreType* m_table;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "StorageManagement/Template/SMFAPtrTableStorageHelper.cc"
#endif

#endif /* STORAGEMANAGEMENT_SMFAPTRTABLESTORAGEHELPER_H */
