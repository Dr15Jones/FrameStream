#if !defined(STORAGEMANAGEMENT_SMFAPTRTABLEPROXY_H)
#define STORAGEMANAGEMENT_SMFAPTRTABLEPROXY_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMFAPtrTableProxy
// 
// Description: A SMProxy designed specifically for FAPtrTables.
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Tue Jun 22 15:46:32 EDT 1999
// $Id: SMFAPtrTableProxy.h,v 1.2 2000/01/24 17:37:11 cdj Exp $
//
// Revision history
//
// $Log: SMFAPtrTableProxy.h,v $
// Revision 1.2  2000/01/24 17:37:11  cdj
// can now access Record via SMSourceStream
//
// Revision 1.1.1.1  1999/09/13 21:21:40  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMProxy.h"
#include "FrameAccess/FAPtrTable.h"

// forward declarations

template< class T >
class SMFAPtrTableProxy : public SMProxy< FAPtrTable< T > >
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMFAPtrTableProxy( SMFAPtrTableStorageHelper< T >* iHelper ):
	 SMProxy< FAPtrTable< T > >( iHelper ),
         m_helper( iHelper ) {}
      //virtual ~SMFAPtrTableProxy();

      // ---------- member functions ---------------------------
      virtual void invalidateCache() {
	 if( 0 != data() ) {
	    data()->eraseAll();
	 }
      }

      const FAPtrTable<T>* faultHandler( const Record& iRecord,
					 const DataKey& iKey ) {
	 assert( 0 != m_helper );
	 assert( 0 != sourceStream() );
	 if( !sourceStream()->valid() ) {
	    return static_cast< const FAPtrTable<T>* >(0);
	 }
	 if( 0 == data() ) {
	    data() = new FAPtrTable< T >;
	    assert( 0 != data() );
	 }
	 m_helper->setTable( data() );
	 sourceStream()->setRecord( iRecord );
	 data() = m_helper->deliver( *( sourceStream() ) );
	 sourceStream()->clearRecord();
	 return data();
      }
      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SMFAPtrTableProxy( const SMFAPtrTableProxy& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMFAPtrTableProxy& operator=( const SMFAPtrTableProxy& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      SMFAPtrTableStorageHelper< T >* m_helper;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMFAPtrTableProxy.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMFAPTRTABLEPROXY_H */
