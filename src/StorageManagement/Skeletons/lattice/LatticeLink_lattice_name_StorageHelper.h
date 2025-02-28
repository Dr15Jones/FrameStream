#if !defined(_ucpackage_LATTICELINK_lattice_name_STORAGEHELPER_H)
#define _ucpackage_LATTICELINK_lattice_name_STORAGEHELPER_H
// -*- C++ -*-
//
// Package:     _package_
// Module:      LatticeLink_lattice_name_StorageHelper
// 
// Description: Storage helper to store a _class_ which is a Lattice link
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Wed Oct  6 10:46:26 EDT 1999
// $Id: LatticeLink_lattice_name_StorageHelper.h,v 1.1 1999/10/18 21:30:19 cdj Exp $
//
// Revision history
//
// $Log: LatticeLink_lattice_name_StorageHelper.h,v $
// Revision 1.1  1999/10/18 21:30:19  cdj
// renamed files
//
// Revision 1.1  1999/10/11 22:00:37  cdj
// added Lattice storage code
//

// system include files

// user include files
#include "StorageManagement/SMStorageHelper.h"
#include "_include_file_"
#include "_lattice_file_"
#include "StorageManagement/SMLatticeLinkInfoBase.h"

// forward declarations

class LatticeLink_lattice_name_StorageHelper :
   public SMStorageHelper< 
           SMLatticeLinkInfoBase< _lattice_name_ > >
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef SMLatticeLinkInfoBase< _lattice_name_ > StoreType;

      // ---------- Constructors and destructor ----------------
      LatticeLink_lattice_name_StorageHelper();
      virtual ~LatticeLink_lattice_name_StorageHelper();

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
      LatticeLink_lattice_name_StorageHelper( const LatticeLink_lattice_name_StorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const LatticeLink_lattice_name_StorageHelper& operator=( const LatticeLink_lattice_name_StorageHelper& ); // stop default

      // ---------- private member functions -------------------
   void registerVersion( StoreType* (LatticeLink_lattice_name_StorageHelper::*iMethod)( SMSourceStream&) );
      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/LatticeLink_lattice_name_StorageHelper.cc"
//#endif

#endif /* _ucpackage_LATTICELINK_lattice_name_STORAGEHELPER_H */
