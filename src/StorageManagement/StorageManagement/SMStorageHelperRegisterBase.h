#if !defined(STORAGEMANAGEMENT_SMSTORAGEHELPERREGISTERBASE_H)
#define STORAGEMANAGEMENT_SMSTORAGEHELPERREGISTERBASE_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMStorageHelperRegisterBase
// 
// Description: Type of SMStorageHelperBase that automatically registers
//                the Helper with SMStorageHelperManager
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 28 16:35:08 EDT 1999
// $Id: SMStorageHelperRegisterBase.h,v 1.1.1.1 1999/09/13 21:21:42 cdj Exp $
//
// Revision history
//
// $Log: SMStorageHelperRegisterBase.h,v $
// Revision 1.1.1.1  1999/09/13 21:21:42  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMStorageHelperBase.h"

// forward declarations

class SMStorageHelperRegisterBase : public SMStorageHelperBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMStorageHelperRegisterBase( const TypeTag& iTypeTag );
      virtual ~SMStorageHelperRegisterBase();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SMStorageHelperRegisterBase(); // stop default
      SMStorageHelperRegisterBase( const SMStorageHelperRegisterBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMStorageHelperRegisterBase& operator=( const SMStorageHelperRegisterBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMStorageHelperRegisterBase.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMSTORAGEHELPERREGISTERBASE_H */
