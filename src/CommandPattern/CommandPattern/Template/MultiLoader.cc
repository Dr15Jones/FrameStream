#if !defined(COMMANDPATTERN_MULTILOADER_CC)
#define COMMANDPATTERN_MULTILOADER_CC
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      MultiLoader
// 
// Description: 
//
// Implementation: 
//
// Author:      Valentine Kouznetsov
// Created:     Fri Feb 28 09:41:27 EST 2003
// $Id: MultiLoader.cc,v 1.7 2003/09/19 20:41:01 cdj Exp $
//
// $Log: MultiLoader.cc,v $
// Revision 1.7  2003/09/19 20:41:01  cdj
// deal with new case that unload is not allowed
//
// Revision 1.6  2003/07/24 18:24:03  vk
// Fix bug with unloading tagged proc/prod when full path was specified
//
// Revision 1.5  2003/03/19 19:50:59  vk
// Fix local path problem
//
// Revision 1.4  2003/03/18 17:05:28  vk
// Fix error message in Suez when load second time the same object
//
// Revision 1.3  2003/03/17 02:11:12  vk
// Set default tag
//
// Revision 1.2  2003/03/14 17:43:03  vk
// Fix sstream for OSF using USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG & strstream.h
//
// Revision 1.1  2003/03/12 21:34:09  vk
// Redesign loader class into LoaderBase, Loader (single loader) and MultiLoader
//
//
// For more detail see LoaderBase class

// system include files
#include <stdlib.h> // for exit
#include <assert.h>
#include <iostream>
#include <utility>
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
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/Experiment.h"
#include "Experiment/report.h"

#include "CommandPattern/MultiLoader.h"
#include "CommandPattern/LoaderMultiFactoryChooser.h"
#include "CommandPattern/StringUtilities.h"

#include "DynamicLoader/DLSharedObjectHandler.h"
#include "DynamicLoader/DLFactoryBase.h"

#include "Utility/StringTokenizer.h"

// STL classes
#include <vector>

//
// constants, enums and typedefs
//
static const char* const kMultiLoaderFacilityString
 = "CommandPattern.MultiLoader";

//
// static data member definitions
//

//
// constructors and destructor
//
template< class T >
MultiLoader< T >::MultiLoader( const std::string& environment ) 
   :  LoaderBase<T>( environment ),
      m_loaded( *new _loader_loaded_ )
{
}

template< class T >
MultiLoader< T >::~MultiLoader()
{
   unloadAll();
   delete &m_loaded;
}

// MultiLoader::MultiLoader( const MultiLoader& )
// {
// }

//
// assignment operators
//
// const MultiLoader& MultiLoader::operator=( const MultiLoader& )
// {
// }

//
// member functions
//

template< class T >
DABoolean
MultiLoader< T >::load( const std::string& iName )
{
   DABoolean status = true;

   // get shortName first
   std::string sName = LoaderBase<T>::shortName(iName);
 
   if(!LoaderBase<T>::alreadyLoaded(sName)) {
     std::string pName = LoaderBase<T>::localPath(iName);
     status = LoaderBase<T>::load(pName+sName);
     if(status) {
       m_loaded.push_back( sName );
       T* object = LoaderBase<T>::fetch(sName);
       initializeTag("", *object);
       report( DEBUG, kMultiLoaderFacilityString )
         << "load iName "<<iName<<" shortName "<<sName<<" object address "<<object<<std::endl;
     }
   }
   return status;
}

template< class T >
DABoolean
MultiLoader< T >::load( const std::string& iName, const std::string& iTag )
{

   // get shortName first & local path
   std::string sName = LoaderBase<T>::shortName(iName);
   std::string pName = LoaderBase<T>::localPath(iName);

   // build fullName out of shortName and provided Tag
   std::string fullName = pName+sName+"@"+iTag;
   std::string tagName  = sName+"@"+iTag;

   DABoolean returnValue = false;

   // check that iName doesn't already exist!
   if( LoaderBase<T>::alreadyLoaded(fullName) ) {
       report( INFO, kMultiLoaderFacilityString )
         << " To load object multiple times specify unique production tag" << std::endl;
     return true;
   }

   // load stuff
   returnValue = LoaderBase<T>::load(fullName);

   // and also active _loader_loaded_
   // keep our tagName in the vector to be compatible with suez
   // e.g. MyTrackProc@com
   m_loaded.push_back( tagName );

   // give derived class a change to do something with the object
   T* object = LoaderBase<T>::fetch(fullName);
   initializeTag( iTag, *object ); 

   report( DEBUG, kMultiLoaderFacilityString )
     << "loaded iName "<<iName<<" fullName "<<fullName<<" object address "<<object<<std::endl;
   return returnValue;
}

template< class T >
DABoolean 
MultiLoader< T >::reorder( const std::string& iListString )
{
   DABoolean returnValue = true;

   // --- first check that each entry really exists; else exit with error
   // make a copy of our current entries
   _loader_loaded_ copyOfLoaded( m_loaded );

   StringTokenizer items( iListString );
   while( true == items.hasMoreElements() )
   {
      std::string nextItem( items.nextElement() );

      // find in our copied list
      _loader_loaded_::iterator which = copyOfLoaded.begin();
      _loader_loaded_::iterator end = copyOfLoaded.end();
      while( which != end && !( *which == nextItem ) ) ++which;
      // and either give error message if not found or erase
      if( which == copyOfLoaded.end() )
      { 
	 report( ERROR, kMultiLoaderFacilityString )
	    << nextItem 
	    << " is not a valid entry"
	    << std::endl;
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
      std::string errorMessage( "Left-overs:\n" );
      _loader_loaded_::iterator which = copyOfLoaded.begin();
      _loader_loaded_::iterator end = copyOfLoaded.end();
      for( ; which != end; ++which )
      {
	 errorMessage += *which + std::string( " " );
      }
      report( ERROR, kMultiLoaderFacilityString )
	 << errorMessage
	 << std::endl;
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

template< class T >
void
MultiLoader< T >::unloadAll()
{
   // clear out vector (and with it map)
   while( !m_loaded.empty() )
   {
      std::string object = m_loaded.back();
      report( DEBUG, kMultiLoaderFacilityString )
	 << "unloading " << object << std::endl;
      unload( object );
   }

}

template< class T >
DABoolean
MultiLoader< T >::unload( const std::string& iName )
{
   DABoolean returnValue = true;

   // now find in active Object list
   _loader_loaded_::iterator which = m_loaded.begin();
   _loader_loaded_::iterator end = m_loaded.end();
   while( which != end && !( *which == iName ) ) ++which;

   // and erase
   if( which != m_loaded.end() )
   { 

      // look for names with tags
      report( DEBUG, kMultiLoaderFacilityString )
	 << "unloading " << iName << std::endl;

      // erase Object from _loader_loaded_map_ using its short name
      if( LoaderBase<T>::unload(iName) ) {

         // erase from vector of selected Objects
         m_loaded.erase( which );
      } else {
         returnValue = false;
      }
   }
   else
   {
      returnValue = false;
   }
   
   return returnValue;
}


template< class T >
std::pair<std::string,std::string>
MultiLoader< T >::disassembleName(const std::string& iName) const
{
   // first disassemble <full_path_to_object>/ part
   std::string shortName=LoaderBase<T>::shortName(iName);

   // now do a job with extension
   int iSearch = shortName.find("@");
   std::string tag="";

   if(iSearch!=std::string::npos) {
     tag.assign(shortName,iSearch,shortName.size());
     shortName.replace(iSearch,shortName.size()-iSearch,"");
   }
   report( DEBUG, kMultiLoaderFacilityString )
     << "disassemple " <<iName << " into name "<< shortName << " tag " << tag << std::endl;

   return std::pair<std::string,std::string>(shortName,tag);
}

template< class T >
std::string
MultiLoader< T >::makeErrorMesg( const std::string& iName ) const
{
   std::string returnValue = std::string( "MultiLoader " ) + LoaderBase<T>::makeErrorMesg(iName);
   return returnValue;
}

#endif /* COMMANDPATTERN_MULTILOADER_CC */
