#if !defined(STORAGEMANAGEMENT_SMSTORAGEPROXYHELPER_H)
#define STORAGEMANAGEMENT_SMSTORAGEPROXYHELPER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMStorageProxyHelper
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 10:43:09 EDT 1999
// $Id: SMStorageProxyHelper.h,v 1.1 1999/10/18 18:29:20 cdj Exp $
//
// Revision history
//
// $Log: SMStorageProxyHelper.h,v $
// Revision 1.1  1999/10/18 18:29:20  cdj
// first submission
//
// Revision 1.1.1.1  1999/09/13 21:21:40  cdj
// imported package
//

// system include files
#include <vector>
#include <assert.h>

// user include files
#include "StorageManagement/SMStorageHelper.h"
#include "StorageManagement/SMStorageHelperManager.h"
#include "StorageManagement/SMProxyFactoryBase.h"

// forward declarations

template< class T >
class SMStorageProxyHelper : public SMStorageHelper< T >, 
			     public SMProxyFactoryBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMStorageProxyHelper() {
	 SMStorageHelperManager::instance().registerFactory( this ); }
      //virtual ~SMStorageProxyHelper();

      // ---------- member functions ---------------------------

      //inherited from SMProxyFactoryBase
      SMProxyBase* makeProxy() const;
      SMProxyWriterBase* makeProxyWriter() const;
      
      const TypeTag& proxyTypeTag() const { return typeTag(); }

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------
 
   private:
      // ---------- Constructors and destructor ----------------
      SMStorageProxyHelper( const SMStorageProxyHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMStorageProxyHelper& operator=( const SMStorageProxyHelper& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};


// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "StorageManagement/Template/SMStorageProxyHelper.cc"
#endif

#endif /* STORAGEMANAGEMENT_SMSTORAGEPROXYHELPER_H */

