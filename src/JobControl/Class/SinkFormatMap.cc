// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      SinkFormatMap
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Mon May 25 17:42:51 EDT 1998
// $Id: SinkFormatMap.cc,v 1.21 2003/03/12 21:48:44 vk Exp $
//
// Revision history (at end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#include <stdlib.h>

// user include files
#include "Experiment/report.h"
#include "JobControl/SinkFormatMap.h"
#include "JobControl/FormatCommand.h"
#include "DataStorage/SinkFormat.h"
#include "DataStorage/DataSinkBinder.h"

#include "CommandPattern/StringUtilities.h"

#include "JobControl/GloballyVisibleSymbols.h"
#include "DataStorage/DataStringTagsToStore.h"

// STL classes
#include <string>
#include <vector>
#include <map>
#include <set>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.SinkFormatMap" ;

//
// static data member definitions
//

//
// constructors and destructor
//
SinkFormatMap::SinkFormatMap( const std::string& environment )
   : FormatMap< SinkFormat >( "SinkFormatMap", environment ),
     m_command( *new FormatCommand< SinkFormatMap >( "sink_format", this ) ),
     m_extensionVsName ( *new _extensionname_map_ )
{
}

// SinkFormatMap::SinkFormatMap( const SinkFormatMap& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SinkFormatMap::~SinkFormatMap()
{
   // need to unload here because of virtual finalize()
   FormatMap< SinkFormat >::unloadAll();

   delete &m_extensionVsName;
   delete &m_command;
}

//
// assignment operators
//
// const SinkFormatMap& SinkFormatMap::operator=( const SinkFormatMap& rhs )
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
DataSinkBinder*
SinkFormatMap::createBinder( const std::string& iName,
			     const Stream::Set& iBindStreams )
{
   DataSinkBinder* returnValue = 0;

   // figure out extension
   std::string extension;
   extension = findExtension( iName, extension );

   _extensionname_map_::iterator it = m_extensionVsName.find( extension );
   if( m_extensionVsName.end() != it )
   {
      returnValue 
	 = loadedMap()[ ((*it).second)() ]->createBinder( iName, iBindStreams );
   }
   else {
      report( ERROR, kFacilityString )
	 << "no proper format found for " << iName << std::endl;
   }
   
   return returnValue;
}

DataSinkBinder*
SinkFormatMap::createBinder( const std::string& iName,
			     const Stream::Set& iBindStreams,
			     const StreamToDataStringTagsToStoreMap& iStreamTagsMap )
{
   DataSinkBinder* returnValue = 0;

   // figure out extension
   std::string extension;
   extension = findExtension( iName, extension );

   _extensionname_map_::iterator it = m_extensionVsName.find( extension );
   if( m_extensionVsName.end() != it )
   {
   	//does this support specifying output?
   	if( loadedMap()[ ((*it).second) () ]->canSpecifyDataToStore() ) {
   		returnValue 
	         = loadedMap()[ ((*it).second)() ]->createBinder( iName, 
	                                                          iBindStreams,
	                                                          iStreamTagsMap );
   	} else {
   		report(WARNING, kFacilityString ) 
   		   <<"sink type does not support specifying output"
   		   <<"\nwill ignore output specification"<<std::endl;
   		returnValue 
	         = loadedMap()[ ((*it).second)() ]->createBinder( iName, iBindStreams );
   	}
   }
   else {
      report( ERROR, kFacilityString )
	 << "no proper format found for " << iName << std::endl;
   }
   
   return returnValue;
}

// ------------- overridden Loader< Producer > method
void
SinkFormatMap::initialize( const std::string& iName, SinkFormat& iFormat )
{
   // bind all format extensions
   const SinkFormat::Extensions& extensions = iFormat.extensions();
   bind( iName, extensions );

   // call globally visible symbol to make debugging easier
   formatsel();
}

// ------------- overridden Loader< Producer > method
void
SinkFormatMap::finalize( const std::string& iName, SinkFormat& iFormat )
{
   // unbind all extensions used by this format
   typedef std::vector< std::string > ToBeUnbound;
   ToBeUnbound toBeUnbound;
   _extensionname_map_::const_iterator end = m_extensionVsName.end();
   for( _extensionname_map_::const_iterator it = m_extensionVsName.begin();
	it != end;
	++it ) {
      if( iName == ((*it).second)() ) {
	 toBeUnbound.push_back( (*it).first );
      }
   }
   for( ToBeUnbound::const_iterator boundIt = toBeUnbound.begin();
	boundIt != toBeUnbound.end();
	++boundIt )
   {
      unbind( *boundIt );
   }
}

//
// const member functions
//
DABoolean 
SinkFormatMap::bind( const std::string& iFormatName,
		     const std::string& iExtension )
{
   DABoolean returnValue = true;

   if( !( loadedMap().find(iFormatName) != loadedMap().end() ) ) {
     report( ERROR, kFacilityString )
        << "no such formatname " << iFormatName << std::endl;
     return false;
   }

   std::string formatName = iFormatName;

   // check that extension hasn't been bound yet
   _extensionname_map_::iterator findExtension 
      = m_extensionVsName.find( iExtension );
   if( m_extensionVsName.end() == findExtension ) {
      m_extensionVsName.insert(
	 _extensionname_map_::value_type( iExtension,
					  StringWrapper( formatName ) )
	 );
   }
   else {
      report( ERROR, kFacilityString )
	 << "extension already in use!" << std::endl;
      return false;
   }


   return returnValue;
}

DABoolean 
SinkFormatMap::unbind( const std::string& iExtension )
{
   DABoolean returnValue = true;

   _extensionname_map_::iterator findExtension 
      = m_extensionVsName.find( iExtension );
   if( m_extensionVsName.end() != findExtension ) {
      m_extensionVsName.erase( findExtension );
   }
   else {
      report( ERROR, kFacilityString )
	 << "no such extension " << iExtension << std::endl;
      returnValue = false;
   }

   return returnValue;
}

DABoolean 
SinkFormatMap::unbindAll()
{
   DABoolean returnValue = true;

   m_extensionVsName.erase( m_extensionVsName.begin(), 
			    m_extensionVsName.end() );

   return returnValue;
}

DABoolean 
SinkFormatMap::clearAll()
{
   DABoolean returnValue = true;

   unbindAll();
   unloadAll();

   return returnValue;
}

DABoolean 
SinkFormatMap::bind( const std::string& iFormatName,
		     const SinkFormat::Extensions& iExtensions )
{
   DABoolean returnValue = true;

   if( true == iExtensions.empty() ) {
      report( ERROR, kFacilityString )
	 << "format " << iFormatName << " supports NO extensions" << std::endl;
      return returnValue = false;
   }

   SinkFormat::Extensions::const_iterator itEnd = iExtensions.end();
   for( SinkFormat::Extensions::const_iterator it = iExtensions.begin();
	it != itEnd; 
	++it )
   {
      DABoolean success = bind( iFormatName, *it );
      if( false == success ) returnValue = false;
   }

   return returnValue;
}

// ------------- overridden Loader< Producer > method
void
SinkFormatMap::errorMesg( const std::string& iName ) const
{
   report( ERROR, kFacilityString ) 
      << "cannot make format; "
      << "are you sure \"" << iName << "\" is a SinkFormat?" << std::endl;
}

// ------------- overridden Loader< Producer > method
std::string
SinkFormatMap::listLoaded() const
{
   std::string resultString;

   _extensionname_map_::const_iterator endExtension( m_extensionVsName.end() );
   for( _extensionname_map_::const_iterator itExtension 
	   = m_extensionVsName.begin();
	itExtension != endExtension;
	++itExtension )
   {
      resultString += std::string( " " ) + (*itExtension).first 
	 + std::string( " " ) + ((*itExtension).second)() + std::string( "\n" );
   }

   return resultString;
}

//
// static member functions
//


// -------------------------------------------------------------------
// Revision history
//
// $Log: SinkFormatMap.cc,v $
// Revision 1.21  2003/03/12 21:48:44  vk
// Adjust to Loader/LoaderBase modifications
//
// Revision 1.20  2003/02/20 18:44:56  cdj
// fixed improper casting of Source(Sink)Format to Source(Sink)FormatModule
//
// Revision 1.19  2001/06/15 21:06:22  cdj
// can now specify data (not) to store in a sink
//
// Revision 1.18  2000/12/04 04:43:26  cdj
// removed unused includes of SharedObjectHandler.h
//
// Revision 1.17  1999/02/22 23:41:39  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.16  1998/12/02 05:55:00  mkl
// towards interacting with Source- and SinkFormats
//
// Revision 1.15  1998/11/17 05:18:55  mkl
// bug fix introduced by recent Loader changes
//
// Revision 1.14  1998/11/10 23:20:21  mkl
// static linking of proc/ducers/source-/sink-formats/modules whatever; and cleanup
//
// Revision 1.13  1998/11/10 03:52:23  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.12  1998/11/09 21:25:05  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.11  1998/11/09 19:33:11  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.10  1998/07/29 19:05:55  mkl
// give error when formats dont support any extensions
//
// Revision 1.9  1998/07/29 02:15:58  mkl
// disallow explicit extension setting for source/sink formats; formats know their extensions
//
// Revision 1.8  1998/07/27 17:42:24  mkl
// shorten names to allow compiling under g++
//
// Revision 1.7  1998/07/25 16:10:25  mkl
// add static linking of sources/sinks
//
// Revision 1.6  1998/07/06 21:04:28  mkl
// unload unbinds all extensions bound to format
//
// Revision 1.5  1998/07/06 19:57:54  mkl
// simplify factory method; make it safer
//
// Revision 1.4  1998/06/23 23:00:47  mkl
// cleanup of LoadableInterface
//
// Revision 1.3  1998/06/23 20:15:39  mkl
// minor bug fixes
//
// Revision 1.2  1998/06/17 21:57:44  mkl
// cleanup
//
// Revision 1.1  1998/06/17 18:19:26  mkl
// allow dynamic loading of source and sink formats
//
