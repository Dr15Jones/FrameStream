#if !defined(STORAGEMANAGEMENT_SMPROXY_H)
#define STORAGEMANAGEMENT_SMPROXY_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMProxy
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Wed Jun  2 14:14:19 EDT 1999
// $Id: SMProxy.h,v 1.3 2000/01/24 17:37:12 cdj Exp $
//
// Revision history
//
// $Log: SMProxy.h,v $
// Revision 1.3  2000/01/24 17:37:12  cdj
// can now access Record via SMSourceStream
//
// Revision 1.2  1999/12/10 14:45:00  cdj
// now inherits from DASourceProxy
//
// Revision 1.1.1.1  1999/09/13 21:21:41  cdj
// imported package
//

// system include files
#include <assert.h>

// user include files
#include "DataDelivery/DataSourceProxy.h"
#include "StorageManagement/SMProxyBase.h"
#include "StorageManagement/SMStorageHelper.h"
#include "StorageManagement/SMSourceStream.h"

// forward declarations

template< class T>
class SMProxy : public DataSourceProxy< T >, public SMProxyBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      // does not own the memory
      SMProxy( SMStorageHelper<T>* iHelper ) :
	 m_helper(iHelper), m_data(0) {}
      virtual ~SMProxy() {
	 delete m_data; }

      // ---------- member functions ---------------------------
      virtual ProxyBase* proxyBase() { return this; }

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void invalidateCache() {
	 delete m_data;
	 m_data = 0; }
      virtual const T* faultHandler( const Record& iRecord , 
                                     const DataKey& iKey ) {
	 assert( 0 != sourceStream() );
	 if( ! sourceStream()->valid() ) {
	    return static_cast< const T* >(0);
	 }
	 assert( 0 == m_data );
	 assert( 0 != m_helper );
	 sourceStream()->setRecord( iRecord );
	 m_data = m_helper->deliver( *( sourceStream() ) );
	 sourceStream()->clearRecord();
	 return m_data;
      }

      T*& data() { return m_data; }

      // ---------- protected const member functions ----------
      SMStorageHelper<T>* helper() const { return m_helper; }      

   private:
      // ---------- Constructors and destructor ----------------
      SMProxy(); // stop default
      SMProxy( const SMProxy& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMProxy& operator=( const SMProxy& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      SMStorageHelper<T>* m_helper;
      T* m_data;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMProxy.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMPROXY_H */
