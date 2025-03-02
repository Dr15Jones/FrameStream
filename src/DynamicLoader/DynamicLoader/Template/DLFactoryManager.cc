// -*- C++ -*-
//
// Package:     <DynamicLoader>
// Module:      DLFactoryManager
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Nov 24 13:37:47 EST 2000
// $Id: DLFactoryManager.cc,v 1.3 2003/08/14 16:29:59 cdj Exp $
//
// Revision history
//
// $Log: DLFactoryManager.cc,v $
// Revision 1.3  2003/08/14 16:29:59  cdj
// added isLoaded method to DLFactoryManager
//
// Revision 1.2  2002/12/09 15:42:47  cleo3
// use C style cast since C++ forbids conversion of void* to pointer to function
//
// Revision 1.1.1.1  2000/11/30 20:51:31  cdj
// imported DynamicLoader source
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

// user include files
#include "Experiment/report.h"
#include "DynamicLoader/DLFactoryManager.h"
#include "DynamicLoader/DLDynamicallyLoadedFactory.h"

#include "Utility/StringTokenizer.h"

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
FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kDLFactoryManagerFacilityString = "DynamicLoader.DLFactoryManager" ;

/*

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DLFactoryManager.cc,v 1.3 2003/08/14 16:29:59 cdj Exp $";
static const char* const kTagString = "$Name:  $";
*/
//
// static data member definitions
//

//
// constructors and destructor
//
//DLFactoryManager::DLFactoryManager()
//{
//}

// DLFactoryManager::DLFactoryManager( const DLFactoryManager& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//DLFactoryManager::~DLFactoryManager()
//{
//}

//
// assignment operators
//
// const DLFactoryManager& DLFactoryManager::operator=( const DLFactoryManager& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }
typedef STL_MAP(string, DLFactoryBase*) FactoryMap;

//
// member functions
//
template <class T>
DABoolean
DLFactoryManager<T>::add( const string& iName, DLFactoryBase* iFactory )
{
   m_factoryMap.insert( make_pair( iName, iFactory ) );
   return true;
}

template <class T>
DABoolean
DLFactoryManager<T>::remove( const string& iName )
{
   DABoolean returnValue = false;
   FactoryMap::iterator itFound = 
      m_factoryMap.find( iName );

   if( itFound != m_factoryMap.end() ) {

      delete (*itFound).second;

      //see if this was dynamically loaded
      if( 0 != m_soh.fetch( iName ) ) {
	 m_soh.unload( iName );
      }
      returnValue = true;
   }
   return returnValue;
}


template <class T>
void
DLFactoryManager<T>::removeAll()
{
   FactoryMap::iterator itEnd = m_factoryMap.end();
   for( FactoryMap::iterator itFactory = 
	   m_factoryMap.begin();
	itFactory != itEnd;
	++itFactory ) {
      delete (*itFactory).second;
   }
   m_factoryMap.erase( m_factoryMap.begin(), itEnd );

   m_soh.unloadAll();
}

template <class T>
DLFactoryBase*
DLFactoryManager<T>::fetch( const string& iName,
			    DLMultiFactoryChooserBase& iChooser,
			    string& oShortName )
{
   DLFactoryBase* returnValue = 0;

   oShortName = m_soh.shortName( iName );

   //see if we have already loaded it
   FactoryMap::iterator itFound = m_factoryMap.find( oShortName );

   if( m_factoryMap.end() != itFound ) {
      return (*itFound).second;
   }

   //Try to dynamically load a factory
    if( true == m_soh.load( iName, string(""), iChooser, oShortName ) ) {
      //search for the proper symbol

      // string consists of factorySymbols separated by ":"
      StringTokenizer symbols( T::factorySymbol(), ':' );
      DABoolean loadingWithSecondaryFactory = false;
      while( symbols.hasMoreElements() ) 
      {
	 // give warning if we use secondary factory symbols
	 if( true == loadingWithSecondaryFactory )
	 {
	    report( WARNING, kDLFactoryManagerFacilityString )
	       << loadingAsSuperClassMesg( iName )
	       << endl;
	 }
	 string factorySymbolString( symbols.nextElement() );
	 void* symbol = 0;
	 DABoolean status = m_soh.getSymbol( oShortName, 
					     factorySymbolString,
					     false,        // no verbose error reports
					     symbol );

	 if( true == status )
	 {
	    //use C style cast since C++ forbids conversion of void*
	    // to pointer to function
	    returnValue = new DLDynamicallyLoadedFactory( 
	       (DLDynamicallyLoadedFactory::FactoryFcn)(symbol) );
	    m_factoryMap.insert( make_pair(oShortName, returnValue ) );

	    // break out of loop over symbols
	    break;
	 }
	 else 
	 {
	    loadingWithSecondaryFactory = true;
	 }
      }
      
      // if no symbol "make<Object>" found
      if( nullptr == returnValue )
      {
	 report( ERROR, kDLFactoryManagerFacilityString )
	    << symbolErrorMesg( iName )
	    << endl;
	 
	 // might as well unload object
	 m_soh.unload( oShortName );
      }

   }

   return returnValue;
}




//
// const member functions
//
template <class T>
string
DLFactoryManager<T>::listAvailable(const string& iPattern ) const
{
   const string kMemory( "memory/");
   string returnValue = kMemory;

   FactoryMap::const_iterator itEnd = m_factoryMap.end();
   for( FactoryMap::const_iterator itFactory = m_factoryMap.begin();
	itFactory != itEnd;
	++itFactory) {
 
      if( 0 == m_soh.fetch( (*itFactory).first ) ) {
	 returnValue += string( " " ) + (*itFactory).first + string( "\n" );
      }
   }
   if( returnValue.size() == kMemory.size() ) {
      returnValue += string("\n");
   }

   returnValue += m_soh.listAvailable( iPattern );

   return returnValue;
}

template <class T>
string
DLFactoryManager<T>::listLoaded() const
{
   string returnValue;
   
   FactoryMap::const_iterator itEnd = m_factoryMap.end();
   for( FactoryMap::const_iterator itFactory = m_factoryMap.begin();
	itFactory != itEnd;
	++itFactory) {
 
      returnValue += string( " " ) + (*itFactory).first + string( " :  " )
	 + fullName( (*itFactory).first ) + string( "\n" );
   }
   return returnValue;
}

template< class T>
DABoolean
DLFactoryManager<T>::isLoaded(const string& iName ) const
{
   return (m_factoryMap.end() != m_factoryMap.find(iName) );
}

template< class T >
string 
DLFactoryManager<T>::fullName( const string& iName ) const
{
   string returnValue = m_soh.fullName( iName );
   if( returnValue == string( "" ) ) {
      returnValue = string( "memory" );
   }
   
   return returnValue;
}

template< class T >
string
DLFactoryManager< T >::loadingAsSuperClassMesg( const string& iName ) const
{
   string returnValue = string( "Loading " ) 
      + iName + string( " as a superclass" );
   return returnValue;
}

template< class T >
string
DLFactoryManager< T >::symbolErrorMesg( const string& iName ) const
{
   string returnValue = string( "Can't find symbol for " ) + iName;
   return returnValue;
}

//
// static member functions
//
