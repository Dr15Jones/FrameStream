#if !defined(_ucpackage___uchelper__H)
#define _ucpackage___uchelper__H
// -*- C++ -*-
//
// Package:     _package_
// Module:      _helper_
// 
// Description: StorageHelper to store a _class_
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: _helper_.h,v 1.2 1999/10/18 18:14:37 cdj Exp $
//
// Revision history
//
// $Log: _helper_.h,v $
// Revision 1.2  1999/10/18 18:14:37  cdj
// now inherits from SMStorageProxyHelper
//
// Revision 1.1.1.1  1999/09/13 21:21:45  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMStorageProxyHelper.h"
#include "_include_file_"

// forward declarations

class _helper_ : public SMStorageProxyHelper<_class_>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      _helper_() ;
      //virtual ~_helper_();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const _class_& iData );

      //functions to deliver specific storage versions of _class_
      _class_* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const _class_& getDefault() const;
      virtual DABoolean compare( const _class_* iNewData, 
				 const _class_& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      _helper_( const _helper_& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const _helper_& operator=( const _helper_& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( _class_* (_helper_::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* _ucpackage___uchelper__H */
