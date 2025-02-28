#if !defined(STORAGEMANAGEMENT_SMPROXYFACTORYBASE_H)
#define STORAGEMANAGEMENT_SMPROXYFACTORYBASE_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMProxyFactoryBase
// 
/**\class SMProxyFactoryBase SMProxyFactoryBase.h StorageManagement/SMProxyFactoryBase.h

 Description: Abstract Base class for Storage Management classes that create a 
              SMStorageProxyBase and SMProxyWriterBase

 Usage:
    This class is mearly an interface.  This interface is used to add the
    ability to create a Proxy or ProxyWriter to a class that is already
    inheriting from SMStorageHelperBase.  

*/
//
// Author:      Chris D Jones
// Created:     Tue Oct 12 15:34:45 EDT 1999
// $Id: SMProxyFactoryBase.h,v 1.1 1999/10/18 18:29:19 cdj Exp $
//
// Revision history
//
// $Log: SMProxyFactoryBase.h,v $
// Revision 1.1  1999/10/18 18:29:19  cdj
// first submission
//

// system include files

// user include files
#include "DataHandler/DataKeyTags.h"

// forward declarations
class SMProxyBase;
class SMProxyWriterBase;

class SMProxyFactoryBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMProxyFactoryBase() {}
      //virtual ~SMProxyFactoryBase() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual SMProxyBase* makeProxy() const = 0;
      virtual SMProxyWriterBase* makeProxyWriter() const = 0;

      virtual const TypeTag& proxyTypeTag() const = 0;
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMProxyFactoryBase( const SMProxyFactoryBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMProxyFactoryBase& operator=( const SMProxyFactoryBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMProxyFactoryBase.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMPROXYFACTORYBASE_H */
