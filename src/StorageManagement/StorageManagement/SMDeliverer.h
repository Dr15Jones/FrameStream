#if !defined(STORAGEMANAGEMENT_SMDELIVERER_H)
#define STORAGEMANAGEMENT_SMDELIVERER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMDeliverer
// 
// Description: A type of SMStorageHelper::DeliverBase that calls a function
//    of a StorageHelper to do the work
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri Jun 18 10:03:52 EDT 1999
// $Id: SMDeliverer.h,v 1.1.1.1 1999/09/13 21:21:42 cdj Exp $
//
// Revision history
//
// $Log: SMDeliverer.h,v $
// Revision 1.1.1.1  1999/09/13 21:21:42  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMStorageHelper.h"

// forward declarations

template< class Return, class Helper >
class SMDeliverer : public SMStorageHelper< Return >::DelivererBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMDeliverer( Return* (Helper::*iMethod)( SMSourceStream&),
		   Helper* iHelper ) :
	 m_helper( iHelper),
	 m_method( iMethod ) {}

      //virtual ~SMDeliverer();

      // ---------- member functions ---------------------------
      Return* deliver( SMSourceStream& iSource ) {
	 return (m_helper->*m_method)( iSource );
      }

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SMDeliverer( const SMDeliverer& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMDeliverer& operator=( const SMDeliverer& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      Helper* m_helper;
      Return* (Helper::*m_method)( SMSourceStream& );
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMDeliverer.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMDELIVERER_H */
