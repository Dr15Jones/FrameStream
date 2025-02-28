#if !defined(STORAGEMANAGEMENT_SMLATTICELINKSTORAGEHELPER_H)
#define STORAGEMANAGEMENT_SMLATTICELINKSTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMLatticeLinkStorageHelper
// 
// Description: Storage Helper for saving Lattice link information
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Mon Oct  4 14:16:52 EDT 1999
// $Id: SMLatticeLinkStorageHelper.h,v 1.1 1999/10/11 22:00:43 cdj Exp $
//
// Revision history
//
// $Log: SMLatticeLinkStorageHelper.h,v $
// Revision 1.1  1999/10/11 22:00:43  cdj
// added Lattice storage code
//

// system include files

// user include files
#include "StorageManagement/SMStorageHelper.h"
#include "StorageManagement/SMLatticeLinkInfoBase.h"

// forward declarations

template < class Lattice >
class SMLatticeLinkStorageHelper :
   public SMStorageHelper< SMLatticeLinkInfoBase<Lattice> >

{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef SMLatticeLinkInfoBase<Lattice> StoreType;

      // ---------- Constructors and destructor ----------------
      SMLatticeLinkStorageHelper();
      virtual ~SMLatticeLinkStorageHelper();

      // ---------- member functions ---------------------------
      virtual StoreType* deliverV1( SMSourceStream& iSource );

      // ---------- const member functions ---------------------

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
      SMLatticeLinkStorageHelper( const SMLatticeLinkStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMLatticeLinkStorageHelper& operator=( const SMLatticeLinkStorageHelper& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMLatticeLinkStorageHelper.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMLATTICELINKSTORAGEHELPER_H */
