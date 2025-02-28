#if !defined(STORAGEMANAGEMENT_SMCOMPAREFACTORIES_H)
#define STORAGEMANAGEMENT_SMCOMPAREFACTORIES_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMCompareFactories
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Sun May 16 17:04:29 EDT 1999
// $Id: SMCompareFactories.h,v 1.1 1999/10/18 18:29:17 cdj Exp $
//
// Revision history
//
// $Log: SMCompareFactories.h,v $
// Revision 1.1  1999/10/18 18:29:17  cdj
// first submission
//
// Revision 1.1.1.1  1999/09/13 21:21:40  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMProxyFactoryBase.h"

// forward declarations

class SMCompareFactories
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
    typedef const SMProxyFactoryBase* second_argument_type;
    typedef const SMProxyFactoryBase* first_argument_type;
    typedef DABoolean result_type;
    bool operator() (const SMProxyFactoryBase* x, 
		     const SMProxyFactoryBase* y) const { 
       return x->proxyTypeTag().value() < y->proxyTypeTag().value(); }

      // ---------- Constructors and destructor ----------------
      SMCompareFactories() {}
      //virtual ~SMCompareFactories(); //use default

      // ---------- member functions ---------------------------
      

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMCompareFactories( const SMCompareFactories& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMCompareFactories& operator=( const SMCompareFactories& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMCompareFactories.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMCOMPAREFACTORIES_H */
