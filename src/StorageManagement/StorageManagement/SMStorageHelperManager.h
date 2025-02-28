#if !defined(STORAGEMANAGEMENT_SMSTORAGEHELPERMANAGER_H)
#define STORAGEMANAGEMENT_SMSTORAGEHELPERMANAGER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMStorageHelperManager
// 
/**\class SMStorageHelperManager SMStorageHelperManager.h StorageManagement/SMStorageHelperManager.h

 Description: Singleton to manager the StorageHelpers and ProxyFactories

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri May 14 10:23:01 EDT 1999
// $Id: SMStorageHelperManager.h,v 1.2 1999/10/18 18:26:06 cdj Exp $
//
// Revision history
//
// $Log: SMStorageHelperManager.h,v $
// Revision 1.2  1999/10/18 18:26:06  cdj
// seperated StorageHelpers from ProxyFactories
//
// Revision 1.1.1.1  1999/09/13 21:21:39  cdj
// imported package
//

// system include files
#include <set>

// user include files
#include "StorageManagement/SMCompareHelpers.h"
#include "StorageManagement/SMCompareFactories.h"

// forward declarations
#include "STLUtility/fwd_set.h"

class SMStorageHelperBase;
class SMProxyFactoryBase;
class DummyFriend;

class SMStorageHelperManager
{
      // ---------- friend classes and functions ---------------
      friend class DummyFriend; //stop compiler from complaining about
                                // no accessible constructors

   public:
      // ---------- constants, enums and typedefs --------------
      typedef STL_SET_COMP(SMStorageHelperBase*, SMCompareHelpers ) Set;
      typedef Set::iterator iterator;

      typedef STL_SET_COMP(SMProxyFactoryBase*, SMCompareFactories ) FactorySet;
      typedef FactorySet::iterator factory_iterator;
      // ---------- Constructors and destructor ----------------
      virtual ~SMStorageHelperManager();

      // ---------- member functions ---------------------------
      ///takes ownership of the SMStorageHelperBase's memory
      void registerHelper( SMStorageHelperBase* );
      void unregisterHelper( SMStorageHelperBase* );

      iterator begin() { return m_helpers.begin(); }
      iterator end() { return m_helpers.end(); }
      iterator find( const TypeTag& iType );


      ///does not take ownership of SMProxyFactoryBase's memory
      void registerFactory( SMProxyFactoryBase* );
      void unregisterFactory( SMProxyFactoryBase* );

      factory_iterator factory_begin() { return m_factories.begin(); }
      factory_iterator factory_end() { return m_factories.end(); }
      factory_iterator factory_find( const TypeTag& iType );
      // ---------- const member functions ---------------------
      

      // ---------- static member functions --------------------
      static SMStorageHelperManager& instance();

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SMStorageHelperManager();
      SMStorageHelperManager( const SMStorageHelperManager& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMStorageHelperManager& operator=( const SMStorageHelperManager& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      Set m_helpers;
      FactorySet m_factories;

      // ---------- static data members ------------------------
      static SMStorageHelperManager*& staticPointer();

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMStorageHelperManager.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMSTORAGEHELPERMANAGER_H */
