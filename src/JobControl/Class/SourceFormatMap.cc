// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      SourceFormatMap
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Mon May 25 17:42:51 EDT 1998
// $Id: SourceFormatMap.cc,v 1.24 2003/03/12 21:48:44 vk Exp $
//
// Revision history (at end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#include <stdlib.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#include <map>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "JobControl/SourceFormatMap.h"
#include "JobControl/FormatCommand.h"
#include "DataDelivery/SourceFormat.h"
#include "CommandPattern/StringUtilities.h"
#include "DataHandler/StreamSet.h"
#include "JobControl/GloballyVisibleSymbols.h"

// STL classes
#include <string>
#include <vector>
#include <map>
#include <set>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.SourceFormatMap" ;

//
// static data member definitions
//

//
// constructors and destructor
//
SourceFormatMap::SourceFormatMap( const string& environment )
   : FormatMap< SourceFormat >( "SourceFormatMap", environment ),
     m_command( *new FormatCommand< SourceFormatMap >( "source_format", this ) ),
     m_extensionVsName ( *new _extensionname_map_ )
{
   if( 0 == &m_extensionVsName
       || 0 == &m_command
      )
   {
      report( EMERGENCY, kFacilityString )
	 << "out of memory" << endl;
      assert( false );
      ::exit( 1 );
   }
}

// SourceFormatMap::SourceFormatMap( const SourceFormatMap& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SourceFormatMap::~SourceFormatMap()
{
   // need to unload here because of virtual finalize()
   FormatMap< SourceFormat >::unloadAll();

   delete &m_extensionVsName;
   delete &m_command;
}

//
// assignment operators
//
// const SourceFormatMap& SourceFormatMap::operator=( const SourceFormatMap& rhs )
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
BinderBase* 
SourceFormatMap::createBinder( const string& iName,
			       const Stream::Set& iBindStreams )
{
   BinderBase* returnValue = 0;

   // figure out extension
   string extension;
   extension = findExtension( iName, extension );

   _extensionname_map_::iterator it = m_extensionVsName.find( extension );
   if( m_extensionVsName.end() != it )
   {
      returnValue 
	 = loadedMap()[ ((*it).second)() ]->createBinder( iName, iBindStreams );
   }
   else {
      report( ERROR, kFacilityString )
	 << "no proper format found for " << iName << endl;
   }

   return returnValue;
}

Stream::Set
SourceFormatMap::defaultStreams( const string& iName )
{
   Stream::Set returnValue;
   
   // figure out extension
   string extension;
   extension = findExtension( iName, extension );
   
   _extensionname_map_::iterator it = m_extensionVsName.find( extension );
   if( m_extensionVsName.end() != it )
   {
      returnValue 
	 = loadedMap()[ ((*it).second)() ]->defaultStreams(iName);
   }
   else {
      report( ERROR, kFacilityString )
	 << "no default streams found for " << iName << endl;
   }
   
   return returnValue;
}

// ------------- overridden Loader< Producer > method
void
SourceFormatMap::initialize( const string& iName, SourceFormat& iFormat )
{
   // bind all format extensions
   const SourceFormat::Extensions& extensions = iFormat.extensions();
   bind( iName, extensions );
   
   // call globally visible symbol to make debugging easier
   formatsel();
}

// ------------- overridden Loader< Producer > method
void
SourceFormatMap::finalize( const string& iName, SourceFormat& iFormat )
{
   // unbind all extensions used by this format
   typedef vector< string > ToBeUnbound;
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
SourceFormatMap::bind( const string& iFormatName,
		       const string& iExtension )
{
   DABoolean returnValue = true;

   if( !( loadedMap().find(iFormatName) != loadedMap().end() ) ) {
      report( ERROR, kFacilityString )
	 << "no such formatname " << iFormatName << endl;
      return false;
   }

   string formatName = iFormatName;

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
	 << "extension already in use!" << endl;
      return false;
   }

   return returnValue;
}

DABoolean 
SourceFormatMap::unbind( const string& iExtension )
{
   DABoolean returnValue = true;

   _extensionname_map_::iterator findExtension 
      = m_extensionVsName.find( iExtension );
   if( m_extensionVsName.end() != findExtension ) {
      m_extensionVsName.erase( findExtension );
   }
   else {
      report( ERROR, kFacilityString )
	 << "no such extension " << iExtension << endl;
      returnValue = false;
   }

   return returnValue;
}

DABoolean 
SourceFormatMap::unbindAll()
{
   DABoolean returnValue = true;

   m_extensionVsName.erase( m_extensionVsName.begin(), 
			    m_extensionVsName.end() );

   return returnValue;
}

DABoolean 
SourceFormatMap::clearAll()
{
   DABoolean returnValue = true;

   unbindAll();
   unloadAll();

   return returnValue;
}

DABoolean 
SourceFormatMap::bind( const string& iFormatName,
		       const SourceFormat::Extensions& iExtensions )
{
   DABoolean returnValue = true;

   if( true == iExtensions.empty() ) {
      report( ERROR, kFacilityString )
	 << "format " << iFormatName << " supports NO extensions" << endl;
      return returnValue = false;
   }

   SourceFormat::Extensions::const_iterator itEnd = iExtensions.end();
   for( SourceFormat::Extensions::const_iterator it = iExtensions.begin();
	it != itEnd; 
	++it )
   {
      //report( INFO, kFacilityString )
      // << "binding " << iFormatName << " to " << *it << endl;
      DABoolean success = bind( iFormatName, *it );
      if( false == success ) returnValue = false;
   }

   return returnValue;
}

// ------------- overridden Loader< Producer > method
void
SourceFormatMap::errorMesg( const string& iName ) const
{
   report( ERROR, kFacilityString ) 
      << "cannot make format; "
      << "are you sure \"" << iName << "\" is a SourceFormat?" << endl;
}

// ------------- overridden Loader< Producer > method
string
SourceFormatMap::listLoaded() const
{
   string resultString;

   _extensionname_map_::const_iterator endExtension( m_extensionVsName.end() );
   for( _extensionname_map_::const_iterator itExtension 
	   = m_extensionVsName.begin();
	itExtension != endExtension;
	++itExtension )
   {
      resultString += string( " " ) + (*itExtension).first 
	 + string( " " ) + ((*itExtension).second)() + string( "\n" );
   }

   return resultString;
}

//
// static member functions
//


// ----------------------------------------------------------------
// Revision history
//
// $Log: SourceFormatMap.cc,v $
// Revision 1.24  2003/03/12 21:48:44  vk
// Adjust to Loader/LoaderBase modifications
//
// Revision 1.23  2003/02/20 18:44:57  cdj
// fixed improper casting of Source(Sink)Format to Source(Sink)FormatModule
//
// Revision 1.22  2002/06/11 17:55:01  cdj
// added ability to set the default streams based on the contents of the source file
//
// Revision 1.21  2000/12/04 04:43:26  cdj
// removed unused includes of SharedObjectHandler.h
//
// Revision 1.20  1999/06/12 00:03:59  mkl
// allow to specify default streams per source format
//
// Revision 1.19  1999/02/22 23:41:40  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.18  1998/12/02 05:55:05  mkl
// towards interacting with Source- and SinkFormats
//
// Revision 1.17  1998/11/17 05:18:57  mkl
// bug fix introduced by recent Loader changes
//
// Revision 1.16  1998/11/10 23:20:23  mkl
// static linking of proc/ducers/source-/sink-formats/modules whatever; and cleanup
//
// Revision 1.15  1998/11/10 03:52:23  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.14  1998/11/09 21:25:05  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.13  1998/11/09 19:33:12  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.12  1998/07/29 19:05:56  mkl
// give error when formats dont support any extensions
//
// Revision 1.11  1998/07/29 02:15:58  mkl
// disallow explicit extension setting for source/sink formats; formats know their extensions
//
// Revision 1.10  1998/07/27 17:42:24  mkl
// shorten names to allow compiling under g++
//
// Revision 1.9  1998/07/25 16:10:26  mkl
// add static linking of sources/sinks
//
// Revision 1.8  1998/07/21 16:21:58  mkl
// added histogram closing; new ActionResult::kStopProcessLoop
//
// Revision 1.7  1998/07/06 21:04:29  mkl
// unload unbinds all extensions bound to format
//
// Revision 1.6  1998/07/06 19:57:54  mkl
// simplify factory method; make it safer
//
// Revision 1.5  1998/06/23 23:00:47  mkl
// cleanup of LoadableInterface
//
// Revision 1.4  1998/06/23 20:15:40  mkl
// minor bug fixes
//
// Revision 1.3  1998/06/23 16:27:05  mkl
// fix finding of file.extension
//
// Revision 1.2  1998/06/17 21:57:45  mkl
// cleanup
//
// Revision 1.1  1998/06/17 18:19:26  mkl
// allow dynamic loading of source and sink formats
