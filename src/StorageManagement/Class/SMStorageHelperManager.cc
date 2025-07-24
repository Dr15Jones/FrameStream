// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMStorageHelperManager
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sun May 16 21:27:30 EDT 1999
// $Id: SMStorageHelperManager.cc,v 1.5 2000/04/24 20:20:47 mkl Exp $
//
// Revision history
//
// $Log: SMStorageHelperManager.cc,v $
// Revision 1.5  2000/04/24 20:20:47  mkl
// SMStorageHelperBase::versionToStore() now virtual.
//
// Revision 1.4  1999/12/15 00:49:33  cdj
// removed debug printouts in unregister functions because report may already be deleted
//
// Revision 1.3  1999/12/10 14:44:13  cdj
// modified debug output
//
// Revision 1.2  1999/10/18 18:22:13  cdj
// better error handling and seperates StorageHelpers from ProxyFactories
//
// Revision 1.1.1.1  1999/09/13 21:21:43  cdj
// imported package
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "StorageManagement/SMStorageHelperManager.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "StorageManagement.SMStorageHelperManager" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SMStorageHelperManager.cc,v 1.5 2000/04/24 20:20:47 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
SMStorageHelperManager::SMStorageHelperManager()
{
}

// SMStorageHelperManager::SMStorageHelperManager( const SMStorageHelperManager& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SMStorageHelperManager::~SMStorageHelperManager()
{
   staticPointer() = 0;
}

//
// assignment operators
//
// const SMStorageHelperManager& SMStorageHelperManager::operator=( const SMStorageHelperManager& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
void
SMStorageHelperManager::registerHelper( SMStorageHelperBase* iHelper )
{
   //assert( m_helpers.end() == m_helpers.find( iHelper ) );
   if( m_helpers.end() != m_helpers.find( iHelper ) ) {
      report(DEBUG, kFacilityString ) 
	 << " attempted to register 2nd Helper for "
	 << iHelper->typeTag().name() << std::endl;
   } else {
      report(DEBUG, kFacilityString) <<"registering " 
				     <<iHelper->typeTag().name()
				     << std::endl;
      m_helpers.insert( iHelper );
   }
}

void
SMStorageHelperManager::unregisterHelper( SMStorageHelperBase* iHelper )
{
   assert( 0 != iHelper );
   Set::iterator itHelper = m_helpers.find( iHelper );

   //assert fails if storage manager is destroyed before helpers
   //assert( itHelper != m_helpers.end() );
   if( itHelper != m_helpers.end() ) {
      m_helpers.erase( itHelper );
   }
}


SMStorageHelperManager::iterator
SMStorageHelperManager::find( const TypeTag& iType )
{
   //need a dummy class to allow the find to work
   class DummyStorageHelper : public SMStorageHelperBase {
      public:
	 DummyStorageHelper( const TypeTag& iType ) :
	    SMStorageHelperBase( iType ) {}
	 
	 DABoolean checkConsistance( SMSinkStream&, SMSourceStream& ){
	    return false; }

	 void useDefault( SMSinkStream & ) {};
	 virtual unsigned int versionToStore() const { 
	    return SMStorageHelperBase::kFirstVersionNumber;
	 }
   };
   DummyStorageHelper temp( iType );
   return m_helpers.find( &temp );
}


void
SMStorageHelperManager::registerFactory( SMProxyFactoryBase* iFactory )
{
   // assert can fail because some linkers will initialize a
   //  global object twice!
   //assert( m_factories.end() == m_factories.find( iFactory ) );
   if( m_factories.end() != m_factories.find( iFactory ) ) {
      report(DEBUG, kFacilityString ) 
	 << " attempted to register 2nd Factory for "
	 << iFactory->proxyTypeTag().name() << std::endl;
   } else {
      report(DEBUG, kFacilityString) <<"registering Factory " 
				     <<iFactory->proxyTypeTag().name()
				     << std::endl;
      m_factories.insert( iFactory );
   }
}

void
SMStorageHelperManager::unregisterFactory( SMProxyFactoryBase* iFactory )
{
   assert( 0 != iFactory );
   FactorySet::iterator itFactory = m_factories.find( iFactory );
   //assert fails if storage manager is destroyed before helpers
   //assert( itFactory != m_factories.end() );
   if( itFactory != m_factories.end() ) {
      m_factories.erase( itFactory );
   }
}


SMStorageHelperManager::factory_iterator
SMStorageHelperManager::factory_find( const TypeTag& iType )
{
   //need a dummy class to allow the find to work
   class DummyStorageFactory : public SMProxyFactoryBase {
      public:
	 DummyStorageFactory( const TypeTag& iType ) :
	    m_type( iType ) {}
	 
	 const TypeTag& proxyTypeTag() const { return m_type; }

	 SMProxyBase* makeProxy() const {
	    return 0; }
	 SMProxyWriterBase* makeProxyWriter() const {
	    return 0; }
      private:
	 TypeTag m_type;
   };
   DummyStorageFactory temp( iType );
   return m_factories.find( &temp );
}

//
// const member functions
//
SMStorageHelperManager&
SMStorageHelperManager::instance() {
   if( 0 == staticPointer() ) {
      staticPointer() = new SMStorageHelperManager;
      assert( 0 != staticPointer() );
   }
   return *( staticPointer() );
}

SMStorageHelperManager*&
SMStorageHelperManager::staticPointer()
{
   static SMStorageHelperManager* s_instance = 0;
   return s_instance;
}

//
// static member functions
//
