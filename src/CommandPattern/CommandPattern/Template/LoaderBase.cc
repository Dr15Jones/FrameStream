#if !defined(COMMANDPATTERN_LOADERBASE_CC)
#define COMMANDPATTERN_LOADERBASE_CC
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      LoaderBase
// 
// Description: Base loader class which implement full functionality of loader
//              Can load objects, keep track of loaded objects, communicate with
//              Dynamic Loader factory (DLFactoryBase).
//
// Implementation: 
//
// Author:      Martin  Lohner
// Created:     Mon Oct 26 15:53:40 EST 1998
// $Id: LoaderBase.cc,v 1.7 2003/09/19 20:37:49 cdj Exp $
//
// Revision history (at end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h> // for exit
#include <assert.h>
#include <iostream>

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif

#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "CommandPattern/LoaderBase.h"
#include "CommandPattern/LoaderMultiFactoryChooser.h"
#include "CommandPattern/StringUtilities.h"
#include "DynamicLoader/DLSharedObjectHandler.h"
#include "DynamicLoader/DLFactoryBase.h"
#include "Utility/StringTokenizer.h"

// STL classes
#include <vector>
#include <map>

#include "C++Std/iostream.h"
//
// constants, enums and typedefs
//
//FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kLoaderBaseFacilityString
static const char* const kLoaderBaseFacilityString
 = "CommandPattern.LoaderBase";

//
// static data member definitions
//

//
// constructors and destructor
//
template< class T >
LoaderBase< T >::LoaderBase( const string& environment ) 
   :  m_factoryManagerPtr( environment )
{
}

// LoaderBase::LoaderBase( const LoaderBase& )
// {
// }

template< class T >
LoaderBase< T >::~LoaderBase()
{
   unloadAll();
}

//
// assignment operators
//
// const LoaderBase& LoaderBase::operator=( const LoaderBase& )
// {
// }

//
// member functions
//

template< class T >
DABoolean
LoaderBase< T >::add( const string& iName, 
		  DLFactoryBase* iFactory )
{
   string sName = shortName(iName);
   return m_factoryManagerPtr->add( sName, iFactory );
}


template< class T >
DABoolean
LoaderBase< T >::alreadyLoaded( const string& iName )
{
  // check if iName already exist
  typename _loader_loaded_map_::iterator findName = m_loadedMap.find( iName );
  if( m_loadedMap.end() != findName ) {
     return true;
  }
  return false;
}

template< class T >
DABoolean
LoaderBase< T >::alreadyLoadedFactory( const string& iName )
{
   return m_factoryManagerPtr->isLoaded(iName);
}

template< class T >
DABoolean
LoaderBase< T >::load( const string& iName )
{
   DABoolean returnValue;
   T* object = 0;

   // disassemble input name for Dynamic Loader
   string pName = localPath(iName);
   string sName = shortName(iName);
   pair<string,string> pairName = disassembleName(sName);
   string shortName             = pairName.first;
   string tag                   = pairName.second;
   string loadedAsName          = shortName+tag;

   report( DEBUG, kLoaderBaseFacilityString )
      <<" iName "<< iName 
      <<" pathName " << pName 
      <<" shortName " << shortName 
      <<" loadedAsName " << loadedAsName << endl;

   // check that iName doesn't already exist!
   if( alreadyLoaded(loadedAsName) ) {
      report( INFO, kLoaderBaseFacilityString )
      << loadedAsName << " has already been loaded " << endl;
      return true;
   }

   LoaderMultiFactoryChooser chooser;
   DLFactoryBase* factory = m_factoryManagerPtr->fetch( pName+shortName, 
							chooser,
							loadedAsName );

   // keep track of objects with "loadedAsName",
   // DLManager assign shortName to loadedAsName and we want to keep original name
   loadedAsName = shortName+tag;

   if( 0 != factory ) {
      // first make the Object
      object = (T*)factory->make();
      if( 0 == object )
      {
	 report( ERROR, kLoaderBaseFacilityString )
	    << makeErrorMesg( loadedAsName )
	    << endl;
      }
   }

   if( 0 != object ) // managed to make Object
   {
      // put in Object list
      m_loadedMap.insert( 
	 _loader_loaded_map_::value_type( loadedAsName, object ) 
	 );
      
      // give derived class a change to do something with the object
      initialize( loadedAsName, *object ); 
   }

   return ( ( 0 != object ) ? true : false );
}

template< class T >
void
LoaderBase< T >::unloadAll()
{
   typename _loader_loaded_map_::const_iterator end( m_loadedMap.end() );
   typename _loader_loaded_map_::const_iterator iter;
   T* object = 0; string objectName="";
   for( iter = m_loadedMap.begin(); iter != end; ++iter )
   {
     // unload( objectName );
     objectName = (*iter).first;
     T* object  = (*iter).second;
     report( DEBUG, kLoaderBaseFacilityString )
       << "unloading " << objectName << endl;

     assert( 0 != object );

     // give derived class a change to do something with the object
     finalize( objectName, *object );

     // call destructor explicitly
     delete object;
   }
   m_loadedMap.clear();
}

template< class T >
DABoolean
LoaderBase< T >::unload( const string& iName )
{
   DABoolean returnValue = true;
   
   // erase from _loader_loaded_map_
   string sName = shortName(iName);
   typename _loader_loaded_map_::iterator iter = m_loadedMap.find( sName );
   if( iter != m_loadedMap.end() )  {
      
      T* object = (*iter).second;
      
      assert( 0 != object );
      
      if(canUnload(sName,*object) ) {
         
         // give derived class a change to do something with the object
         finalize( sName, *object );
         
         // call destructor explicitly
         delete object;
         
         m_loadedMap.erase( iter );
      } else {
         return false;
      }
         
   } else {
      return false;
   }
return true;
}

template< class T >
T*
LoaderBase< T >::fetch( const string& iName )
{
   T* object = 0;

   string sName = shortName(iName);
   typename _loader_loaded_map_::iterator iter = m_loadedMap.find( sName );
   if( iter != m_loadedMap.end() )
   {
     object = (*iter).second;
   }
   return object;
}

//
// const member functions
//
template< class T >
const T*
LoaderBase< T >::fetch( const string& iName ) const
{
   const T* object = 0;

   string sName = shortName(iName);
   typename _loader_loaded_map_::const_iterator iter = m_loadedMap.find( sName );
   if( iter != m_loadedMap.end() )
   {
     object = (*iter).second;
   } else  {
     report( DEBUG, kLoaderBaseFacilityString )
       << "couldn't find \"" << iName << "\"" << endl;
   }

   return object;
}

template< class T >
string
LoaderBase< T >::listAvailable() const
{
   return m_factoryManagerPtr->listAvailable( listAvailablePatternString() );
}

template< class T >
string
LoaderBase< T >::listLoaded() const
{
   string returnValue;

   typename _loader_loaded_map_::const_iterator end( m_loadedMap.end() );
   typename _loader_loaded_map_::const_iterator iter;
   for( iter = m_loadedMap.begin(); iter != end; ++iter )
   {
      // disassemble name
      pair<string,string> pairName = disassembleName((*iter).first);
      string name = pairName.first;
      string tag  = pairName.second;
      
      // assemble return string
      T* object = (*iter).second;

/*
      // Copy address of object into stream for later printout
      char str[80];
      ostrstream objAddress(str,sizeof(str));
      objAddress << object;
      string strAddress = objAddress.str();
*/      
      report( DEBUG, kLoaderBaseFacilityString )
        << "object "<<name<<" fullName "<<name+tag<<" object address "<<object<<endl;

      returnValue += string( " " ) + (*iter).first + string( " :   " )
	 + m_factoryManagerPtr->fullName( name ) + string( "\n" );

   }

   return returnValue;
}

template< class T >
string
LoaderBase< T >::factorySymbol() const
{
   return T::factorySymbol();
}

template< class T >
string 
LoaderBase< T >::shortName(const string& iName) const
{
   string name = iName;
   string tag="";

   // disassemble .<extension> (by deafult we assume only .o or .so)
   int iSearch = iName.find(".so");
   int jSearch = iName.find(".o");
   if( iSearch!= string::npos ) {

     tag.assign(iName,iSearch,iName.size());
     name.replace(iSearch,iName.size()-iSearch,"");

   } else if( jSearch != string::npos ) {

     tag.assign(iName,jSearch,iName.size());
     name.replace(jSearch,iName.size()-jSearch,"");

   }


   // disassemble <full_path_to_object>/ part and return remaining string
   string sName=name;
   int kSearch = name.rfind("/");
   if( kSearch!= string::npos ) {
     sName.assign(name,kSearch+1,name.size());
   }

   return sName;
}

template< class T >
string 
LoaderBase< T >::localPath(const string& iName) const
{
   string name = iName;

   // disassemble <path_to_object>/ part
   string pathName=iName;
   int kSearch = name.rfind("/");

   if( kSearch!= string::npos ) {
     pathName.erase(kSearch+1,name.size()-kSearch);
   } else {
     pathName = "";
   }

   return pathName;
}



template< class T >
string
LoaderBase< T >::makeErrorMesg( const string& iName ) const
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
// $Log: LoaderBase.cc,v $
// Revision 1.7  2003/09/19 20:37:49  cdj
// added alreadyLoadedFactory and canUnload methods
//
// Revision 1.6  2003/03/19 19:50:59  vk
// Fix local path problem
//
// Revision 1.5  2003/03/18 17:05:28  vk
// Fix error message in Suez when load second time the same object
//
// Revision 1.4  2003/03/18 15:39:46  cdj
// My last change removed a necessary side-effect from a report message. I put back the message but moved the side-effect out of the message format.
//
// Revision 1.3  2003/03/17 21:46:00  cdj
// changed reporting level for some messages from LoaderBase to avoid confusing users
//
// Revision 1.2  2003/03/14 17:43:03  vk
// Fix sstream for OSF using USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG & strstream.h
//
// Revision 1.1  2003/03/12 21:34:08  vk
// Redesign loader class into LoaderBase, Loader (single loader) and MultiLoader
//
// Revision 1.19  2002/12/09 15:25:12  cleo3
// added typename
//
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

#endif /* COMMANDPATTERN_LOADERBASE_CC */
