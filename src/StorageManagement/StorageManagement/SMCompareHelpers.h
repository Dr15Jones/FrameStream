#if !defined(STORAGEMANAGEMENT_SMCOMPAREHELPERS_H)
#define STORAGEMANAGEMENT_SMCOMPAREHELPERS_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMCompareHelpers
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Sun May 16 17:04:29 EDT 1999
// $Id: SMCompareHelpers.h,v 1.1.1.1 1999/09/13 21:21:40 cdj Exp $
//
// Revision history
//
// $Log: SMCompareHelpers.h,v $
// Revision 1.1.1.1  1999/09/13 21:21:40  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMStorageHelperBase.h"

// forward declarations

class SMCompareHelpers
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
    typedef const SMStorageHelperBase* second_argument_type;
    typedef const SMStorageHelperBase* first_argument_type;
    typedef DABoolean result_type;
    bool operator() (const SMStorageHelperBase* x, 
		     const SMStorageHelperBase* y) const { 
       return x->typeTag().value() < y->typeTag().value(); }

      // ---------- Constructors and destructor ----------------
      SMCompareHelpers() {}
      //virtual ~SMCompareHelpers(); //use default

      // ---------- member functions ---------------------------
      

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMCompareHelpers( const SMCompareHelpers& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMCompareHelpers& operator=( const SMCompareHelpers& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMCompareHelpers.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMCOMPAREHELPERS_H */
