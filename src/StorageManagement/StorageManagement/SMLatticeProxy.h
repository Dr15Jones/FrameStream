#if !defined(STORAGEMANAGEMENT_SMLATTICEPROXY_H)
#define STORAGEMANAGEMENT_SMLATTICEPROXY_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      SMLatticeProxy
// 
/**\class SMLatticeProxy SMLatticeProxy.h package/SMLatticeProxy.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Mar 22 09:45:10 EST 2002
// $Id: SMLatticeProxy.h,v 1.1 2002/03/25 19:14:15 cdj Exp $
//
// Revision history
//
// $Log: SMLatticeProxy.h,v $
// Revision 1.1  2002/03/25 19:14:15  cdj
// now reuse Lattice during readback
//

// system include files

// user include files
#include "StorageManagement/SMProxy.h"
#include "StorageManagement/SMLatticeStorageHelper.h"

// forward declarations

template <class T>
class SMLatticeProxy : public SMProxy< T >
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMLatticeProxy( SMLatticeStorageHelper<T>* iHelper):
         SMProxy<T>(iHelper),
         m_helper( iHelper ) {}
         
      //virtual ~SMLatticeProxy();

      // ---------- member functions ---------------------------
      virtual void invalidateCache() {
         if( 0 != data() ) {
            data()->removeAll();
         }
      }
      
      const T* faultHandler( const Record& iRecord,
			     const DataKey& iKey ) {
	 assert( 0 != m_helper );
	 assert( 0 != sourceStream() );
	 if( !sourceStream()->valid() ) {
	    return static_cast< const T* >(0);
	 }
	 m_helper->setLattice( data() );
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
      SMLatticeProxy( const SMLatticeProxy& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMLatticeProxy& operator=( const SMLatticeProxy& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      SMLatticeStorageHelper<T>* m_helper;
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/SMLatticeProxy.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMLATTICEPROXY_H */
