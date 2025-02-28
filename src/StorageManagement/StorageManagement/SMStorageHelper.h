#if !defined(STORAGEMANAGEMENT_SMSTORAGEHELPER_H)
#define STORAGEMANAGEMENT_SMSTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMStorageHelper
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 10:43:09 EDT 1999
// $Id: SMStorageHelper.h,v 1.6 2003/02/05 21:08:56 cleo3 Exp $
//
// Revision history
//
// $Log: SMStorageHelper.h,v $
// Revision 1.6  2003/02/05 21:08:56  cleo3
// added includes needed for cxx 6.5
//
// Revision 1.5  2000/04/27 21:07:28  mkl
// moved 'begin/endObject' logic to SMStorageHelper::deliver( SourceStream, iVersion ) function
//
// Revision 1.4  2000/04/24 20:21:10  mkl
// SMStorageHelperBase::versionToStore() now virtual.
//
// Revision 1.3  2000/02/18 22:30:28  cdj
// wsun modified SM_REGISTER_VERSION_DEF so templated helper_ works properly
//
// Revision 1.2  1999/10/18 18:24:18  cdj
// no longer creates proxies
//
// Revision 1.1.1.1  1999/09/13 21:21:40  cdj
// imported package
//

// system include files
#include <vector>
#include <assert.h>

// user include files
#include "StorageManagement/SMStorageHelperRegisterBase.h"
#include "StorageManagement/sm_macros.h"
#include "STLUtility/fwd_vector.h"
#include "StorageManagement/SMSourceStream.h"
// forward declarations

template< class T >
class SMStorageHelper : public SMStorageHelperRegisterBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMStorageHelper();
      virtual ~SMStorageHelper();

      // ---------- member functions ---------------------------
      void store( SMSinkStream& iSink, const T& iData );

      T* deliver( SMSourceStream& iSource );
      T* deliver( SMSourceStream& iSource, unsigned int iVersion ) {

	 iSource.beginObject( typeTag() );

	 assert( (iVersion-kFirstVersionNumber) < m_deliverers.size() );
	 void* temp = m_deliverers[ iVersion - kFirstVersionNumber ];
	 T* returnValue = static_cast<DelivererBase*>(temp)->deliver( iSource ); 

	 iSource.endObject();

	 return returnValue;
      }

      virtual DABoolean checkConsistance(SMSinkStream&iSink, 
					 SMSourceStream& iSource );

      virtual void useDefault( SMSinkStream& iSink );

      // ---------- const member functions ---------------------
      virtual unsigned int versionToStore() const {
	 return m_deliverers.size() - 1 + kFirstVersionNumber;
      }

      // ---------- static member functions --------------------

      class DelivererBase {
	 public:
	    virtual ~DelivererBase() {}
	    virtual T* deliver( SMSourceStream& iSource ) = 0;
      };

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const T& iData ) = 0;

      // ---------- protected const member functions -----------
      T* make( const T& iTempData ) const;

      virtual const T& getDefault() const = 0;
      virtual DABoolean compare( const T* iNewData, const T& iOldData ) const = 0;

      void registerDeliverVersion( DelivererBase* iDeliverer ) {
	 m_deliverers.push_back( iDeliverer ); }
 
   private:
      // ---------- Constructors and destructor ----------------
      SMStorageHelper( const SMStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMStorageHelper& operator=( const SMStorageHelper& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      // Using a vector< void*> instead of a vector< DelivererBase*>
      //  to avoid having to instantiate a specialized vector for
      //  EACH instatiation of SMStorageHelper
      // This should be safe since only add to this vector from
      //  registerDeliverVersion()
      STL_VECTOR( void* ) m_deliverers;

      // ---------- static data members ------------------------

};

//macro to write registerVersion method
#define SM_REGISTER_VERSION_DEF( helper_ , class_ ) \
void helper_ ::registerVersion( class_* (helper_ ::*iMethod)(SMSourceStream&))\
{ registerDeliverVersion( new SMDeliverer< class_, helper_ >( iMethod, this ) ); }

//macro to specify method to call to store data of an object
//#define SM_VAR( object_, method_ ) object_.method_()

//macro to register a storage helper
#define SM_REGISTER_STORAGE( helper_ ) static helper_ s_ ## helper_;

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "StorageManagement/Template/SMStorageHelper.cc"
#endif

#endif /* STORAGEMANAGEMENT_SMSTORAGEHELPER_H */
