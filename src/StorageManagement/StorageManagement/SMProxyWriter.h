#if !defined(STORAGEMANAGEMENT_SMPROXYWRITER_H)
#define STORAGEMANAGEMENT_SMPROXYWRITER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMProxyWriter
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Mon May 24 17:17:26 EDT 1999
// $Id: SMProxyWriter.h,v 1.1.1.1 1999/09/13 21:21:41 cdj Exp $
//
// Revision history
//
// $Log: SMProxyWriter.h,v $
// Revision 1.1.1.1  1999/09/13 21:21:41  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMProxyWriterBase.h"

// forward declarations
template< class T> class SMStorageHelper;

template <class T >
class SMProxyWriter : public SMProxyWriterBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef T value_type;

      // ---------- Constructors and destructor ----------------
      SMProxyWriter( SMStorageHelper<T>* iHelper ) :
	 m_helper( iHelper ), m_data(0) {}

      //virtual ~SMProxyWriter();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual DABoolean extractData( const DataKey& iKey,
				     const Record&  iRecord,
				     SMSinkStream&  iOStream ) ;

      // ---------- protected const member functions -----------
      virtual void writeData( SMSinkStream& iOStream ) const ;

   private:
      // ---------- Constructors and destructor ----------------
      SMProxyWriter(); // stop default
      SMProxyWriter( const SMProxyWriter& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMProxyWriter& operator=( const SMProxyWriter& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      SMStorageHelper<T>* m_helper;

      const T* m_data;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "StorageManagement/Template/SMProxyWriter.cc"
#endif

#endif /* STORAGEMANAGEMENT_SMPROXYWRITER_H */
