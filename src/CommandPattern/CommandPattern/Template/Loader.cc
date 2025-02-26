#if !defined(COMMANDPATTERN_LOADER_CC)
#define COMMANDPATTERN_LOADER_CC
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      Loader
// 
// Description: 
//
// Implementation: 
//
// Author:      Martin  Lohner
// Created:     Mon Oct 26 15:53:40 EST 1998
// $Id: Loader.cc,v 1.18 2000/12/01 20:23:26 cdj Exp $
//
// Revision history (at end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h> // for exit
#include <assert.h>
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "CommandPattern/Loader.h"
#include "CommandPattern/LoaderMultiFactoryChooser.h"
#include "CommandPattern/StringUtilities.h"
#include "DynamicLoader/DLSharedObjectHandler.h"
#include "DynamicLoader/DLFactoryBase.h"
#include "Utility/StringTokenizer.h"

// STL classes
#include <vector>
#include <map>

//
// constants, enums and typedefs
//
FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kLoaderFacilityString
 = "CommandPattern.Loader";

//
// static data member definitions
//

//
// constructors and destructor
//
template< class T >
Loader< T >::Loader( const string& environment ) 
   :  m_factoryManagerPtr( environment ),
     m_loadedMap( *new _loader_loaded_map_ ),
     m_loaded( *new _loader_loaded_ )
{
}

// Loader::Loader( const Loader& )
// {
// }

template< class T >
Loader< T >::~Loader()
{
   unloadAll();
   delete &m_loadedMap;
   delete &m_loaded;
}

//
// assignment operators
//
// const Loader& Loader::operator=( const Loader& )
// {
// }

//
// member functions
//

template< class T >
DABoolean
Loader< T >::add( const string& iName, 
		  DLFactoryBase* iFactory )
{
   return m_factoryManagerPtr->add( iName, iFactory );
}

template< class T >
void
Loader< T >::unloadAll()
{
   // clear out vector (and with it map)
   while( !m_loaded.empty() )
   {
      string object = m_loaded.back();
      report( DEBUG, kLoaderFacilityString )
	 << "unloading " << object << endl;
      unload( object );
   }

}

template< class T >
DABoolean
Loader< T >::load( const string& iName )
{
   DABoolean returnValue;
   T* object = 0;

   report( SYSTEM, "Loader" )
      << "trying to load \"" << iName << "\"..." << endl;

   // check that iName doesn't already exist!
   _loader_loaded_map_::iterator findName = m_loadedMap.find( iName );
   if( m_loadedMap.end() != findName ) {
      report( INFO, kLoaderFacilityString )
	 << iName << " has already been loaded" << endl;
      return returnValue = true;
   }


   // keep track of objects with "loadedAsName"
   string loadedAsName = iName;

   LoaderMultiFactoryChooser chooser;
   DLFactoryBase* factory = m_factoryManagerPtr->fetch( iName, 
							chooser,
							loadedAsName );
   if( 0 != factory ) {
      

      // first make the Object
      object = (T*)factory->make();
      if( 0 == object )
      {
	 report( ERROR, kLoaderFacilityString )
	    << makeErrorMesg( iName )
	    << endl;
      }
   }

   if( 0 != object ) // managed to make Object
   {
      // put in Object list
      m_loadedMap.insert( 
	 _loader_loaded_map_::value_type( loadedAsName, object ) 
	 );
      
      // and also active _loader_loaded_
      m_loaded.push_back( loadedAsName );

      // give derived class a change to do something with the object
      initialize( loadedAsName, *object ); 
   }

   return ( ( 0 != object ) ? true : false );
}

template< class T >
DABoolean
Loader< T >::unload( const string& iName )
{
   DABoolean returnValue = true;

   // now find in active Object list
   _loader_loaded_::iterator which = m_loaded.begin();
   _loader_loaded_::iterator end = m_loaded.end();
   while( which != end && !( *which == iName ) ) ++which;

   // and erase
   if( which != m_loaded.end() )
   { 
      // erase from _loader_loaded_map_
      _loader_loaded_map_::iterator iter = m_loadedMap.find( iName );
      if( iter != m_loadedMap.end() )
      {
	 T* object = (*iter).second;

	 assert( 0 != object );

	 // give derived class a change to do something with the object
	 finalize( iName, *object );

	 // call destructor explicitly
	 delete object;
	 
	 m_loadedMap.erase( iter );
      }
      
      // erase from vector of selected Objects
      m_loaded.erase( which );
      

      returnValue = true;
   }
   else
   {
      returnValue = false;
   }
   
   return returnValue;
}

template< class T >
T*
Loader< T >::fetch( const string& iName )
{
   T* object = 0;

   _loader_loaded_map_::iterator iter = m_loadedMap.find( iName );
   if( iter != m_loadedMap.end() )
   {
      object = (*iter).second;
   } 
//   else 
//   {
//      report( WARNING, kLoaderFacilityString )
//         << "couldn't find \"" << iName << "\"" << endl;
//   }

   return object;
}

template< class T >
DABoolean 
Loader< T >::reorder( const string& iListString )
{
   DABoolean returnValue = true;

   // --- first check that each entry really exists; else exit with error
   // make a copy of our current entries
   _loader_loaded_ copyOfLoaded( m_loaded );

   StringTokenizer items( iListString );
   while( true == items.hasMoreElements() )
   {
      string nextItem( items.nextElement() );

      // find in our copied list
      _loader_loaded_::iterator which = copyOfLoaded.begin();
      _loader_loaded_::iterator end = copyOfLoaded.end();
      while( which != end && !( *which == nextItem ) ) ++which;
      // and either give error message if not found or erase
      if( which == copyOfLoaded.end() )
      { 
	 report( ERROR, kLoaderFacilityString )
	    << nextItem 
	    << " is not a valid entry"
	    << endl;
	 return returnValue = false;
      }
      else
      {
	 copyOfLoaded.erase( which );
      }
   }

   // now check that there aren't any left over items!
   if( false == copyOfLoaded.empty() )
   {
      string errorMessage( "Left-overs:\n" );
      _loader_loaded_::iterator which = copyOfLoaded.begin();
      _loader_loaded_::iterator end = copyOfLoaded.end();
      for( ; which != end; ++which )
      {
	 errorMessage += *which + string( " " );
      }
      report( ERROR, kLoaderFacilityString )
	 << errorMessage
	 << endl;
      return returnValue = false;
   }
   
   // --- everything went fine: now really enter reordered items
   // erase current list first
   m_loaded.erase( m_loaded.begin(), m_loaded.end() );
   StringTokenizer validItems( iListString );
   while( true == validItems.hasMoreElements() )
   {
      m_loaded.push_back( validItems.nextElement() );
   }

   return returnValue;
}

//
// const member functions
//
template< class T >
const T*
Loader< T >::fetch( const string& iName ) const
{
   const T* object = 0;

   _loader_loaded_map_::iterator iter = m_loadedMap.find( iName );
   if( iter != m_loadedMap.end() )
   {
      object = (*iter).second;
   } 
//   else 
//   {
//      report( WARNING, kLoaderFacilityString )
//         << "couldn't find \"" << iName << "\"" << endl;
//   }

   return object;
}

template< class T >
string
Loader< T >::listAvailable() const
{
   return m_factoryManagerPtr->listAvailable( listAvailablePatternString() );
}

template< class T >
string
Loader< T >::listLoaded() const
{
   string returnValue;

   _loader_loaded_::const_iterator end( m_loaded.end() );
   for( _loader_loaded_::const_iterator iter = m_loaded.begin();
        iter != end;
        ++iter )
   {
      // assemble return string
      returnValue += string( " " ) + *iter + string( " :   " )
	 + m_factoryManagerPtr->fullName( *iter ) + string( "\n" );
   }

   return returnValue;
}

template< class T >
string
Loader< T >::factorySymbol() const
{
   return T::factorySymbol();
}

template< class T >
string
Loader< T >::makeErrorMesg( const string& iName ) const
{
   string returnValue = string( "Can't make " ) + iName;
   return returnValue;
}

//
// static member functions
//


// ------------------------------------------------------------------
// Revision history
//
// $Log: Loader.cc,v $
// Revision 1.18  2000/12/01 20:23:26  cdj
// now uses DynamicLoader package
//
// Revision 1.17  2000/09/05 17:53:27  mkl
// added verbose messages: loading modules and adding commands
//
// Revision 1.16  1999/10/08 21:45:21  mkl
// put in hooks for pattern searching in loading (if we ever decide to use it)
//
// Revision 1.15  1999/09/14 22:33:17  mkl
// fix 'proc reorder' command to not unload processors first
//
// Revision 1.14  1999/09/14 18:39:04  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
// Revision 1.13  1999/06/07 19:07:31  mkl
// unload static modules AFTER dynamic modules
//
// Revision 1.12  1999/05/19 20:45:49  mkl
// only give info message when trying to load already-loaded item.
//
// Revision 1.11  1999/04/30 18:16:57  mkl
// prettyfying Loader output; setting resultString for interpreter
//
// Revision 1.10  1999/04/14 21:15:42  mkl
// ordered container used in Suez
//
// Revision 1.9  1999/03/11 22:04:33  mkl
// turn off superfluous warning for 'param' command
//
// Revision 1.8  1999/02/22 23:40:54  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.7  1998/11/21 05:07:03  mkl
// it appears as if string MyString( someOtherString ) does not make a copy on Solaris
//
// Revision 1.6  1998/11/17 21:58:37  mkl
// rearranged deletes in dtor; again, shouldn't matter, but seems to help (it almost appears as if Solaris rearranges deletions in dtors at free will
//
// Revision 1.5  1998/11/12 02:23:56  mkl
// minor cleanup
//
// Revision 1.4  1998/11/10 23:22:14  mkl
// static linking of proc/ducers/source-/sink-formats/modules whatever; and cleanup
//
// Revision 1.3  1998/11/10 03:53:59  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.2  1998/11/09 21:24:52  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.1  1998/11/09 19:31:54  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
//

#endif /* COMMANDPATTERN_LOADER_CC */
