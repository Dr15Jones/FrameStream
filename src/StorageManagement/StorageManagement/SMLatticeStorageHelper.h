#if !defined(STORAGEMANAGEMENT_SMLATTICESTORAGEHELPER_H)
#define STORAGEMANAGEMENT_SMLATTICESTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMLatticeStorageHelper
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Tue Jun  8 09:21:53 EDT 1999
// $Id: SMLatticeStorageHelper.h,v 1.3 2002/03/25 19:14:16 cdj Exp $
//
// Revision history
//
// $Log: SMLatticeStorageHelper.h,v $
// Revision 1.3  2002/03/25 19:14:16  cdj
// now reuse Lattice during readback
//
// Revision 1.2  1999/10/18 18:23:22  cdj
// now inherits from SMStorageProxyHelper
//
// Revision 1.1  1999/10/11 22:00:43  cdj
// added Lattice storage code
//

// system include files

// user include files
#include "StorageManagement/SMStorageProxyHelper.h"

// forward declarations

template < class T >
class SMLatticeStorageHelper : public SMStorageProxyHelper< T >
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef T StoreType;

      // ---------- Constructors and destructor ----------------
      SMLatticeStorageHelper();
      virtual ~SMLatticeStorageHelper();

      // ---------- member functions ---------------------------
      virtual StoreType* deliverV1( SMSourceStream& iSource );

      void setLattice( StoreType* iLattice ) {
            m_lattice = iLattice ; 
      }
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
      SMLatticeStorageHelper( const SMLatticeStorageHelper<T>& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMLatticeStorageHelper& operator=( const SMLatticeStorageHelper& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------
      StoreType* m_lattice;
};

// inline function definitions

#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "StorageManagement/Template/SMLatticeStorageHelper.cc"
#endif

#endif /* STORAGEMANAGEMENT_SMLATTICESTORAGEHELPER_H */
