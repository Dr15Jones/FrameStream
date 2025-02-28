// -*- C++ -*-
//
// Package:     JobControl
// Module:      SourceManager
// 
// Description: manages sources internally and hands them off 
//              as DataBinders to FrameDeliverer
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue Jul 22 10:53:20 EDT 1997
// $Id: SourceManager.cc,v 1.64 2004/03/29 12:17:59 cdj Exp $
//
// Revision history
// (at end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#if defined(OSTRSTREAM_NO_TERMINATION_BUG)
#include <stdio.h>
#endif

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>                                         
#include <vector>
#include <map>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif

// user include files
#include "Experiment/report.h"
#include "JobControl/SourceManager.h"
#include "JobControl/SinkManager.h"
#include "Utility/FileNameUtils.h"
#include "JobControl/Binder.h"
#include "DataDelivery/DataSourceBinder.h"
#include "ChainDelivery/ChainSourceBinder.h"
#include "DataDelivery/FrameDeliverer.h"
#include "DataHandler/StreamSet.h"
#include "Processor/MasterProcessor.h"
#include "DefaultModule/DefaultModule.h"
// temporarily needed; will use JobContext in future
#include "JobControl/JobControl.h"
#include "JobControl/CompareDataSourceDescriptors.h"

// STL classes
#include <vector>
#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#  include <map>
#  include <multimap.h>
#else
#  include <map>
#endif                   
#include "STLUtility/fwd_set.h"
#include <set>

// static (local) functions
static
SourceManager::Token
addCountToToken( SourceManager::Token& iStumpToken, Count iCount )
{
   SourceManager::Token newToken;

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
// buggy ostrstream implementation and no stringstream in sight 
#if defined(OSTRSTREAM_NO_TERMINATION_BUG)
   const unsigned int kSize=100;
   char number[kSize];
   snprintf( number, kSize, "%d", iCount );
   newToken = iStumpToken + string( "_" ) + string( number );
#else
   //ostringstream number; // not yet available: <sstream>
   ostrstream number;
   number << iCount;
   newToken = iStumpToken + string( "_" ) + string( number.str() );
#endif
#else
   ostringstream number; // not yet available: <sstream>
   number << iCount;
   newToken = iStumpToken + string( "_" ) + number.str();
#endif

   return newToken;
}

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.SourceManager";

typedef SOURCEMANAGER_SOURCEMAP SourceMap;

//
// static data member definitions
//
//
// constructors and destructor
//
SourceManager::SourceManager( FrameDeliverer& iDeliverer )
   : Module( "SourceManager", "SourceManager" ),
     m_sourceCommand( "source", this ),
     m_streamCommand( "stream", this ),
     m_sourceMap( *new SourceMap ),
     m_sourceInUseMap( *new SourceMap ),
     m_streamsToBeActivated( *new StreamSet ),
     m_frameDeliverer( iDeliverer )
{
   if(    0 == &m_sourceMap
       || 0 == &m_sourceInUseMap
       || 0 == &m_streamsToBeActivated
      )
   {
      report( EMERGENCY ,
              kFacilityString )
                 << "Unable to allocate memory"
                 << endl ;
      assert(false);
      ::exit( 1 );
   }
}

// SourceManager::SourceManager( const SourceManager& )
// {
// }

SourceManager::~SourceManager()
{
   removeAllSources();
   delete &m_sourceMap;
   delete &m_sourceInUseMap;
   delete &m_streamsToBeActivated;
}

//
// assignment operators
//
// const SourceManager& SourceManager::operator=( const SourceManager& )
// {
// }

//
// member functions
//
DABoolean
SourceManager::addSource( BinderBase* iBinder, Token& ioToken )
//---------------------------------------------------------------
// adds sources to be used.
//
// There are several ways to start a chain:
// 1.) src create <token>
//     *input add <token> <sourcename>
//     ...
// 2.) *input source <sourcename>
//     (system reports back a <token>)
//     *input add <token> <anothersource>
//     ...
// 3.) One could also imagine letting the user use:
//     *input add <newToken> <sourcename>
//     *input add <newToken> <anothersource>
//     ...
//
//---------------------------------------------------------------
{
   DABoolean status = true;

   // if token is in use, don't allow adding
   SourceMap::iterator tokenInUseIter = m_sourceInUseMap.find( ioToken );
   if( m_sourceInUseMap.end() != tokenInUseIter )
   {
      report( ERROR, kFacilityString ) 
	 << "Source in use; need to use edit command first!" << endl;
      return( status = false );
   }
   //See if a source with the same sourceID and parameter already exist
   for(SourceMap::iterator itSource = m_sourceInUseMap.begin();
       itSource != m_sourceInUseMap.end();
      ++itSource ) {
      if( (0 != &(itSource->second->dsBinder())) &&
	  (0 != iBinder->dsBinderP()) && 
	  itSource->second->dsBinder().dataSourceID() == (*iBinder)->dataSourceID() &&
	  itSource->second->dsBinder().parameters() == 
	  (*iBinder)->parameters() ) {
	 report( ERROR, kFacilityString)
	    <<"Source in use with exact same id ("<<(*iBinder)->dataSourceID()
	    <<") and parameters ("
	    <<(*iBinder)->parameters()<<")\n  Use edit command to change the original source "<<(*itSource).first <<endl;
	 return (status = false );
      }
   }

   for(SourceMap::iterator itSource = m_sourceMap.begin();
      itSource != m_sourceMap.end();
      ++itSource ) {
      //dsBinder can be 0 when a 'source create' command is used
      if( 0 != &(itSource->second->dsBinder()) && 
	  (0 != iBinder->dsBinderP()) &&
	  itSource->second->dsBinder().dataSourceID() == (*iBinder)->dataSourceID() &&
	  itSource->second->dsBinder().parameters() == 
	  (*iBinder)->parameters() ) {
	 report( ERROR, kFacilityString)
	    <<"Source with exact same id ("<<(*iBinder)->dataSourceID()
	    <<") and parameters ("
	    <<(*iBinder)->parameters()<<")\n  Use 'source' command to change or remove the original source "<<(*itSource).first <<endl;
	 return (status = false );
      }
   }

   // token not in use

   // find entry in map
   SourceMap::iterator tokenIter = m_sourceMap.find( ioToken );

   // if no such token exists yet, create new one
   if( m_sourceMap.end() == tokenIter
      || string( "" ) == ioToken
      || iBinder->isDummy() )
   {
      // if token is not given, base token on sourceName!
      if( string( "" ) == ioToken ) {
	 ioToken = iBinder->dataSourceID();
      }

      // use sourcename without extension or path
      ioToken = FileNameUtils::basename( ioToken );
      ioToken = createToken( ioToken );

      // check if streams defined; if not add default streams
      if( true != iBinder->isDummy() )
      {
	 StreamSet streams = iBinder->boundStreams();
	 if( streams.empty() )
	 {
	    streams.add( Stream::kEvent );
	    streams.add( Stream::kBeginRun );
	    streams.add( Stream::kStartRun );
	    
	    iBinder->bindStreams( streams );

	    string message( "using default streams:" );
	    Stream::Set::const_iterator itEnd = streams.end();
	    for( Stream::Set::const_iterator it = streams.begin();
		 it != itEnd;
		 ++it )
	    {
	       message += string(" ")+(*it).value();
	    }
	    report( INFO, kFacilityString ) << message << endl;
	 }
      }	 

      // tell Binder about what its token is
      iBinder->setToken( ioToken );

      // now add source info to map
      m_sourceMap.insert( SourceMap::value_type( ioToken, iBinder ) ); 
      
   }
   else // token exists
   {
      BinderBase* binderInMap = (*tokenIter).second;

      // place holder from "source create token"
      if( true == binderInMap->isDummy() ) 
      {
	 // erase original dummy Binder entry
	 m_sourceMap.erase( tokenIter );
	 
	 // check if streams defined; if not add default streams
	 StreamSet streams = iBinder->boundStreams();
	 // the binder should always have bound streams, else something is wrong!
	 assert( false == streams.empty() );
	 
	 // now add source info to map
	 m_sourceMap.insert( SourceMap::value_type( ioToken, iBinder ) ); 
	 iBinder->setToken(ioToken);
      }
      else {
	 status = binderInMap->addBinder( iBinder );

	 // tell Binder about what its token is
	 binderInMap->setToken( ioToken );
      }
   }
   
   return status;
}

DABoolean
SourceManager::useSources( DABoolean& oNewSources )
// -------------------------------------------------------------
// hand over all sources in our sourcesMap to FD
// -------------------------------------------------------------
{
   DABoolean success = true;

   // need to report back if there were new sources
   oNewSources = ! m_sourceMap.empty();

   // now register all new sources with FrameDeliverer
   SourceMap::iterator itEnd = m_sourceMap.end();
   for( SourceMap::iterator source = m_sourceMap.begin();
	source != itEnd;
	++source )
   {
      // avoid Dummy Binder type
      if( (*source).second->isDummy() ) continue;

      // add it to FD
      FrameDeliverer::AddSourceStatus status;

      DataSourceBinder& DSB = (*(*source).second).dsBinder();

      if( FrameDeliverer::kAddSourceNoError !=
	  ( status = m_frameDeliverer.addSource( DSB ) ) )
      {
	 string sourceName( DSB.dataSourceID() );
	 switch( status )
	 {
	    case FrameDeliverer::kAddSourceBinderFailedToMakeController:
	    {
	       report( EMERGENCY, kFacilityString )
		  << "Source \"" << sourceName << "\": " 
		  << "failed to make Controller" << endl;
	       break;
	    }
	    case FrameDeliverer::kAddSourceInvalidStopsForSource:
	    {
	       report( EMERGENCY, kFacilityString )
		  << "Source \"" << sourceName << "\": " 
		  << "can't goto those stops" << endl;
	       break;
	    }
	    case FrameDeliverer::kAddSourceSourceInaccessible:
	    {
	       report( EMERGENCY, kFacilityString )
		  << "Source \"" << sourceName << "\": " 
		  << "inaccessible " << endl;
	       break;
	    }
	    case FrameDeliverer::kAddSourceBadParameters:
	    {
	       report( EMERGENCY, kFacilityString )
		  << "Source \"" << sourceName << "\": " 
		  << "Bad Source parameters" << endl;
	       break;
	    }
	    case FrameDeliverer::kAddSourceUnknownError:
	    default:
	    {
	       report( EMERGENCY, kFacilityString )
		  << "Source \"" << sourceName << "\": " 
		  << "Unknown AddSource error from FrameDeliverer" << endl;
	       break;
	    }
	 }
	 success = false;
      }
      else
      {
	 report( INFO, kFacilityString )
	    << "Opened data source \"" << (*source).first << "\"." << endl;

	 // move source over to sourceInUseMap
	 m_sourceInUseMap.insert( *source );

	 // don't erase here, erase below in separate loop!
	 //m_sourceMap.erase( source );
      }

   } // loop over sources

   // now erase all the successfully opened sources from the SourceMap
   SourceMap::const_iterator itInUseEnd = m_sourceInUseMap.end();
   for( SourceMap::const_iterator sourceInUse = m_sourceInUseMap.begin();
	sourceInUse != itInUseEnd;
	++sourceInUse )
   {
      m_sourceMap.erase( (*sourceInUse).first );
   }

   return success;
}

DABoolean
SourceManager::editSource( const Token& iToken )
{
   DABoolean success = true;

   // find source with token
   SourceMap::iterator tokenIter = m_sourceInUseMap.find( iToken );
   if( m_sourceInUseMap.end() == tokenIter  ) 
   {
      report( ERROR, kFacilityString ) 
	 << "No such source \"" << iToken << "\" in use!" << endl;

      success = false;
   }
   else
   {
      report( WARNING, kFacilityString ) 
	 << "Editing a source will recycle it!" << endl;

      DABoolean status = removeSourceInUse( iToken );

      if( true == status )
      {
	 m_sourceMap.insert( *tokenIter );

	 // list it to be nice to user for editing
	 report( INFO, kFacilityString )
	    << listSource( iToken )
	    << endl;
	 success = true;
      }

   }

   return success;
}

DABoolean
SourceManager::removeSource( const Token& iToken )
{
   DABoolean success = false;
   DABoolean sourceInUseMap=true, sourceInMap=true;
   // find source with token

   // 1.) in SourceMap
   SourceMap::iterator tokenIter = m_sourceMap.find( iToken );
   if( m_sourceMap.end() == tokenIter  ) 
   {
      sourceInMap = false;
   }
   else
   {
      delete (*tokenIter).second;
      m_sourceMap.erase( tokenIter );
      report( INFO, kFacilityString ) 
	 << "Removed source \"" << iToken << "\"." << endl;
      success = true;
   }

   // 2.) in SourceInUseMap
   SourceMap::iterator tokenInUseIter = m_sourceInUseMap.find( iToken );
   if( m_sourceInUseMap.end() == tokenInUseIter  ) 
   {
      sourceInUseMap = false;
   }
   else
   {
      sourceInUseMap = removeSourceInUse( iToken );
   }

   // check if source was in either map
   if(    false == sourceInMap
       && false == sourceInUseMap )
   {
      report( WARNING, kFacilityString ) 
	 << "Can't remove unknown source \"" << iToken << "\"." << endl;
      success = false;
   }

   return success;
}

DABoolean
SourceManager::removeAllSources()
{
   DABoolean status = true;

   // remove all source from FrameDeliverer
   m_frameDeliverer.removeAllSources();

   // clear all source from our internal maps
   //   make sure to delete the sources!
   SourceMap::iterator endIt = m_sourceMap.end();
   for( SourceMap::iterator it = m_sourceMap.begin();
        it != endIt;
        ++it )
   {
      delete (*it).second;
   }
   m_sourceMap.erase( m_sourceMap.begin(), m_sourceMap.end() );

   SourceMap::iterator inUseEndIt = m_sourceInUseMap.end();
   for( SourceMap::iterator inUseIt = m_sourceInUseMap.begin();
        inUseIt != inUseEndIt;
        ++inUseIt )
   {
      delete (*inUseIt).second;
   }
   m_sourceInUseMap.erase( m_sourceInUseMap.begin(), m_sourceInUseMap.end() );

   return status;
}

DABoolean
SourceManager::removeSourceInUse( const Token& iToken )
{
   DABoolean success = true;

   // find source with token
   SourceMap::iterator sourceInUse = m_sourceInUseMap.find( iToken );
   if( m_sourceInUseMap.end() == sourceInUse  ) 
   {
      report( WARNING, kFacilityString ) 
	 << "Can't remove source-in-use \"" << iToken << "\"." << endl;

      success = false;
   }
   else
   {
      //report( INFO, kFacilityString )
      //  << "Will remove source-in-use \""<< iToken << "\"." << endl;

      // remove DataSourceBinder from FrameDeliverer
      DataSourceBinder& DSB = (*(*sourceInUse).second).dsBinder();

      FrameDeliverer::RemoveSourceStatus status;
      if( FrameDeliverer::kRemoveSourceNoError !=
	  ( status = m_frameDeliverer.removeSource( DSB ) ) )
      {
	 switch(status){
	    case FrameDeliverer::kRemoveSourceNoMatchingSource:
	    {
	       report( EMERGENCY, kFacilityString ) 
		  << "No matching source." << endl;
	       break;
	    }
	    default:
	    {
	       report( EMERGENCY, kFacilityString ) 
		  << "Unknown error." << endl;
	       break;
	    }
	 }
	 success = false;
      }
      else
      {
	 report( INFO, kFacilityString )
	    << "Removed source-in-use \"" << iToken << "\"" << endl;
	 delete (*sourceInUse).second;
	 m_sourceInUseMap.erase( sourceInUse );

	 success = true;
      }
   }

   return success;
}

DABoolean
SourceManager::removeSourceFromChain( const Token& iToken,
				      const SourceName& sourceName )
{
   DABoolean success = false;

   if( true == isSourceInUseMap( iToken ) )
   {
      report( ERROR, kFacilityString ) 
	 << "Can't remove source \"" << sourceName 
	 << "\"\n because \"" << iToken 
	 << "\" is in use;\n use edit command first!" << endl;

      return( success = false );
   }

   // find right chain with token
   SourceMap::iterator tokenIter = m_sourceMap.find( iToken );
   if( m_sourceMap.end() == tokenIter  ) 
   {
      report( ERROR, kFacilityString ) 
	 << "Can't remove source \"" << sourceName 
	 << "\" from unknown \"" << iToken << "\"." << endl;

      return( success = false );
   }

   // get ahold of Chain
   if( false == (*tokenIter).second->isChain() )
   {
      report( ERROR, kFacilityString ) 
	 << "Can't remove source \"" << sourceName 
	 << "\" from Non-Chain \"" << iToken << "\"." << endl;
      return( success = false );
   }
   // have a chain in front of us

   ChainSourceBinderBase& CSB 
      = (ChainSourceBinderBase&)(*(*tokenIter).second).dsBinder();

   DABoolean status = CSB.removeSource( DataSourceDescriptor( sourceName ) );
   if( false == status )
   {
      report( ERROR, kFacilityString ) 
	 << "Can't remove source \"" << sourceName 
	 << "\" from chain \"" << iToken << "\"." << endl;
      return( success = false );
   }
	   
   return success;
}

DABoolean
SourceManager::bindStreamsToSource( const Token& iToken, 
				    const StreamSet& iStreams ) 
{
   DABoolean status = true;

   // if token is in use, don't allow adding
   SourceMap::iterator tokenInUseIter = m_sourceInUseMap.find( iToken );
   if( m_sourceInUseMap.end() != tokenInUseIter )
   {
      report( ERROR, kFacilityString ) 
	 << "Source in use; need to use edit command first!" << endl;
      return( status = false );
   }
   // token not in use

   // find entry in map and rebind new streams to binder
   SourceMap::iterator tokenIter = m_sourceMap.find( iToken );
   if( m_sourceMap.end() != tokenIter )
   {
      BinderBase* binder = (*tokenIter).second;
      binder->bindStreams( iStreams );
   }      

   return status;
}

DABoolean
SourceManager::setToBeActiveStreamsInSource( 
   const Token& iToken, 
   const StreamSet& iToBeActiveStreams ) 
{
   DABoolean status = true;

   // if token is in use, don't allow adding
   SourceMap::iterator tokenInUseIter = m_sourceInUseMap.find( iToken );
   if( m_sourceInUseMap.end() != tokenInUseIter )
   {
      report( ERROR, kFacilityString ) 
	 << "Source in use; need to use edit command first!" << endl;
      return( status = false );
   }
   // token not in use

   // find entry in map and rebind new streams to binder
   SourceMap::iterator tokenIter = m_sourceMap.find( iToken );
   if( m_sourceMap.end() != tokenIter )
   {
      BinderBase* binder = (*tokenIter).second;
      binder->setToBeActiveStreams( iToBeActiveStreams );
   }      
   else 
   {
      report( ERROR, kFacilityString ) 
	 << "Unknown Source " << iToken << endl;
      return( status = false );
   }

   return status;
}

DABoolean
SourceManager::clearToBeActiveStreamsInSource( const Token& iToken )
{
   DABoolean status = true;

   // if token is in use, don't allow adding
   SourceMap::iterator tokenInUseIter = m_sourceInUseMap.find( iToken );
   if( m_sourceInUseMap.end() != tokenInUseIter )
   {
      report( ERROR, kFacilityString ) 
	 << "Source in use; need to use edit command first!" << endl;
      return( status = false );
   }
   // token not in use

   // find entry in map and rebind new streams to binder
   SourceMap::iterator tokenIter = m_sourceMap.find( iToken );
   if( m_sourceMap.end() != tokenIter )
   {
      BinderBase* binder = (*tokenIter).second;
      binder->clearToBeActiveStreams();
   }      
   else 
   {
      report( ERROR, kFacilityString ) 
	 << "Unknown Source " << iToken << endl;
      return( status = false );
   }

   return status;
}

DABoolean
SourceManager::clearToBeActiveStreamsInAllSources()
{
   DABoolean status = true;

   // find entry in map and rebind new streams to binder
   SourceMap::iterator endTokenIter = m_sourceMap.end();
   for( SourceMap::iterator tokenIter = m_sourceMap.begin();
	tokenIter != endTokenIter;
	++tokenIter )
   {
      BinderBase* binder = (*tokenIter).second;
      binder->clearToBeActiveStreams();
   }      

   return status;
}

void
SourceManager::setStreamsToBeActivated( 
   const StreamSet& iStreamsToBeActivated )
{
   m_streamsToBeActivated = iStreamsToBeActivated;
}

StreamSet&
SourceManager::streamsToBeActivated( const MasterProcessor& iMasterProcessor, 
				     const SinkManager& iSinkManager )
{
   // ------------------------------------------------------------
   // 1.) User activates by hand
   // --> these streams are stored in m_streamsToBeActivated

   // ------------------------------------------------------------
   // 2.) Actions bound to streams
   // Check all processors for streams to be made active and add
   // those to m_streamsToBeActivated

   // ------------------------------------------------------------
   // 3.) Streams to be written out

   // We only have to worry about the streams that weren't covered 
   // explicitly by the user!
   
   const StreamSet& procStreams = iMasterProcessor.streamsToBeActivated();

   StreamSet::const_iterator endProcStream = procStreams.end();
   for( StreamSet::const_iterator procStream = procStreams.begin();
	procStream != endProcStream;
	++procStream )
   { 
      StreamSet::iterator foundStream 
	 = m_streamsToBeActivated.find( *procStream );
      if( m_streamsToBeActivated.end() == foundStream )
      {
	 //report( INFO, kFacilityString ) 
	 //   << "stream \"" << (*procStream).value() 
	 //   << "\" bound to action" << endl;
	 m_streamsToBeActivated.insert( *procStream );
      }
   }


   const StreamSet& sinkStreams = iSinkManager.streamsToBeActivated();

   StreamSet::const_iterator endSinkStream = sinkStreams.end();
   for( StreamSet::const_iterator sinkStream = sinkStreams.begin();
	sinkStream != endSinkStream;
	++sinkStream )
   { 
      StreamSet::iterator foundStream 
	 = m_streamsToBeActivated.find( *sinkStream );
      if( m_streamsToBeActivated.end() == foundStream )
      {
	 //report( INFO, kFacilityString ) 
	 //   << "stream \"" << (*sinkStream).value() 
	 //   << "\" to be written to a sink" << endl;
	 m_streamsToBeActivated.insert( *sinkStream );
      }
   }

   return m_streamsToBeActivated;
}

DABoolean
SourceManager::activateStreams( const MasterProcessor& iMasterProcessor,
				const SinkManager& iSinkManager )
// ---------------------------------------------------------------
// There are two causes for a stream to be activated:
// 1.) User activates by hand
// 2.) User has written code in form of a processor 
//       action --> bound to stream
// 3.) User wants to write stream out to Sink
// ---------------------------------------------------------------
{
   DABoolean success = true;

   StreamSet streams = streamsToBeActivated( iMasterProcessor,
					     iSinkManager );

   // if we don't have streams-to-be-activated, return false
   if( true == streams.empty() ) 
   {
      report( ERROR, kFacilityString ) 
	 << "No Active Streams specified!\n" 
	 << "(Make sure you have a processor selected\n"
	 << "with at least one action bound to a stream!)"
	 << endl;
      return( success = false );
   }

   // ---------- now have a complete set of streams to be activated --------

   // make a mmap<stream,sources>: 
   //     for a given stream which sources can provide it
   typedef multimap< StreamType, const BinderBase*, less<StreamType> > 
      StreamSourceMM;
   StreamSourceMM streamSourceMM;
   
   SourceMap::const_iterator endSrcIt = m_sourceInUseMap.end();
   for( SourceMap::const_iterator srcIt = m_sourceInUseMap.begin();
	srcIt != endSrcIt;
	++srcIt )
   {
      const BinderBase* binder = (*srcIt).second;

      const StreamSet& streams = binder->boundStreams();
      //const DataSourceDescriptor* sourceDescriptor = binder->dsBinderP();;

      StreamSet::const_iterator endStrIt = streams.end();
      for( StreamSet::const_iterator strIt = streams.begin();
	   strIt != endStrIt;
	   ++strIt )
      {
	 //streamSourceMM.insert( StreamSourceMM::value_type( *strIt,
	 //						    sourceDescriptor ) );
	 streamSourceMM.insert( StreamSourceMM::value_type( *strIt,
							    binder ) );
      }
   }


   // make a set< DataSourceDescriptor >:
   //     to be able to find DataSourceDescriptors by name easily
   typedef STL_SET_COMP( DataSourceDescriptor, CompareDataSourceDescriptors )
      SourceDescriptorSet;
   SourceDescriptorSet sourceDescriptorSet;


   StreamSet streamsThatUserMustChooseSource;

   // loop over streams-to-be-made-active
   StreamSet::const_iterator endStream = streams.end();
   for( StreamSet::const_iterator stream = streams.begin();
	stream != endStream;
	++stream )
   { 
      const DataSourceDescriptor* sourceDescriptor = 0;

      StreamSourceMM::iterator streamSource = streamSourceMM.find( *stream );

      Count howManySuppliers = streamSourceMM.count( *stream );
      switch( howManySuppliers )
      {
	 case 0: // if there is no supplier, alert user!
	 {
	    report( ERROR, kFacilityString ) 
	       << "There is no Source that can supply "
	       << "Active Stream \"" << (*stream).value() << "\"!" << endl;
	    sourceDescriptor = 0;
	    success = false;
	    break;
	 }

	 case 1: // just one supplier --> ideal
	 {
	    sourceDescriptor = (*streamSource).second->dsBinderP();
	    break;
	 }
	 
	 default: // more than on supplier
	 {
	    // if any source claims it to be a "toBeActive" stream, 
	    // use that source; if more than one, use the last one:
	    DABoolean anyToBeActiveStreamsFound = false;
	    StreamSourceMM::iterator lastSource
	       = streamSourceMM.upper_bound( *stream ); 
	    for( StreamSourceMM::iterator source 
		    = streamSourceMM.lower_bound( *stream ); 
		 source != lastSource;
		 ++source )
	    {
	       // find Binder
	       SourceMap::iterator tokenInUseIter 
		  = m_sourceInUseMap.find( (*source).second->token() );
	       if( m_sourceInUseMap.end() != tokenInUseIter ) 
	       {
		  BinderBase* binder = (*tokenInUseIter).second;
		  if( true == binder->isToBeActiveStream( *stream ) )
		  {
		     sourceDescriptor = (*source).second->dsBinderP();
		     anyToBeActiveStreamsFound = true;
		  }
	       }
	       else 
	       {
		  report( ERROR, kFacilityString ) 
		     << "couldn't find " 
		     << (*source).second->dataSourceID() << endl;
	       }
	    }
	    // if found one, don't need to go further
	    if( true == anyToBeActiveStreamsFound ) break;


	    //prompt user for choice later
	    streamsThatUserMustChooseSource.add( *stream );

	    break;
	 }
      } // end of switch on number of suppliers

      // if there is no valid Source, continue
      if( 0 == sourceDescriptor ) continue;

      // insert if not present in map yet
      SourceDescriptorSet::iterator whichSourceDescriptor
	 = sourceDescriptorSet.find( *sourceDescriptor );
      if( sourceDescriptorSet.end() == whichSourceDescriptor )
      { 
	 // create blank copy and insert
	 DataSourceDescriptor newDSD( *sourceDescriptor );
	 newDSD.clearStreams();
	 sourceDescriptorSet.insert( newDSD );
      } 

      whichSourceDescriptor = sourceDescriptorSet.find( *sourceDescriptor );
      // bind active stream
      StreamSet tempStreams = (*whichSourceDescriptor).boundStreams();
      tempStreams.add( *stream );
      DataSourceDescriptor& activeDSD 
	 = (DataSourceDescriptor&)(*whichSourceDescriptor);
      activeDSD.bindStreams( tempStreams );
      
   } // loop over streams to be activated
   

   //prompt user for which source should be used for these streams
   // The default one will be the one that has the most number of active 
   // streams or the first one if there is a tie.
   for( StreamSet::iterator itStream = streamsThatUserMustChooseSource.begin();
	itStream != streamsThatUserMustChooseSource.end();
	++itStream ) {

      //first choose which source is the default choice
      Count count = 1;
      Count whichOne = 1;
      unsigned int maxNumberOfActiveStreams = 0;
      StreamSourceMM::iterator endInSeries
	 = streamSourceMM.upper_bound( *itStream ); 
      StreamSourceMM::iterator beginInSeries
	 = streamSourceMM.lower_bound( *itStream ); 
      for( StreamSourceMM::iterator it = beginInSeries; 
	   it != endInSeries;
	   ++it, ++count )
      {

	 const DataSourceDescriptor* sourceDescriptor = 
	    (*it).second->dsBinderP();

	 //see if this is already an active stream
	 SourceDescriptorSet::iterator whichSourceDescriptor
	    = sourceDescriptorSet.find( *sourceDescriptor );
	 if( whichSourceDescriptor != sourceDescriptorSet.end() ) {
	    unsigned int numberOfActiveStreams = 
	       (*whichSourceDescriptor).boundStreams().size();
	    if( numberOfActiveStreams > maxNumberOfActiveStreams ) {
	       maxNumberOfActiveStreams = numberOfActiveStreams;
	       whichOne = count;
	    }
	 }
      }
  
      report( SYSTEM, kFacilityString )
	 << "Stream \"" << (*itStream).value() 
	 << "\" can be supplied by more than one source.\n"
	 << "Please advise on which one to use (by number):" << endl;

      count = 0;
      {
      for( StreamSourceMM::iterator it = beginInSeries; 
	   it != endInSeries;
	   ++it )
      {
	 if( ++count == whichOne ) {
	    cout <<"*";
	 } else {
	    cout <<" ";
	 }
	 cout 
	    << count << ") " 
	    << (*it).second->dataSourceID() << endl;
      }
      }
      if( Switch::kOn 
	  == JobControl::instance()->defaultModule().usePrompting() )
      {
	 DABoolean validChoice = false;
	 do
	 {
	    DABoolean badInput = false;
	    cin >> whichOne;
	    if( ios::failbit == cin.fail() ) {
	       badInput = true;
	       cin.clear(); // reset bad state
	       cin.ignore( 80, '\n' ); // throw away input (up to 80chars)
	    }
	    validChoice = 
	       ( true == badInput 
		 || whichOne < 1 || whichOne > count ) ? false : true;
	    if( false == validChoice )
	    {
	       report( SYSTEM, kFacilityString ) 
		  << "Bad choice. Try again!" << endl;
	    }
	 } 
	 while( false == validChoice );
      }
      
      // now get that SourceName
      StreamSourceMM::iterator streamSource = beginInSeries;
      const DataSourceDescriptor* sourceDescriptor = 0;
      for( Count i=1; i<whichOne; ++i, ++streamSource );
      sourceDescriptor = (*streamSource).second->dsBinderP();
      

      // insert if not present in map yet
      SourceDescriptorSet::iterator whichSourceDescriptor
	 = sourceDescriptorSet.find( *sourceDescriptor );
      if( sourceDescriptorSet.end() == whichSourceDescriptor )
      { 
	 // create blank copy and insert
	 DataSourceDescriptor newDSD( *sourceDescriptor );
	 newDSD.clearStreams();
	 sourceDescriptorSet.insert( newDSD );
      } 

      whichSourceDescriptor = sourceDescriptorSet.find( *sourceDescriptor );
      // bind active stream
      StreamSet tempStreams = (*whichSourceDescriptor).boundStreams();
      tempStreams.add( *itStream );
      DataSourceDescriptor& activeDSD 
	 = (DataSourceDescriptor&)(*whichSourceDescriptor);
      activeDSD.bindStreams( tempStreams );

   } //loop over streams to prompt user


   // now hand over activator DSD's to FrameDeliverer (first clear out old)
   m_frameDeliverer.removeAllActiveSources();
   SourceDescriptorSet::const_iterator endSD = sourceDescriptorSet.end();
   for( SourceDescriptorSet::const_iterator activeSD 
	   = sourceDescriptorSet.begin();
	activeSD != endSD;
	++activeSD )
   {
      DABoolean status 
	 = handActiveDSDToFrameDeliverer( *activeSD );

      if( false == status ) 
      {
	 success = false;
      }
      else 
      {
	 report( INFO, kFacilityString )
	    << "Using " << (*activeSD).dataSourceID()
	    << " for active streams: ";
	 const StreamSet& streams = (*activeSD).boundStreams();
	 StreamSet::const_iterator lastStreamIter = streams.end();
	 for( StreamSet::const_iterator streamIter = streams.begin();
	      streamIter != lastStreamIter;
	      ++streamIter )
	 {
	    report( INFO, kFacilityString )
	       << (*streamIter).value() << " ";
	 }
	 report( INFO, kFacilityString ) << endl;
      }
   }
   if( true == success )
   {
      report( INFO, kFacilityString )
         << "Defined active streams." <<endl;

      success = true;
   }


   // if there a no DSDs to hand to FD, we don't have active streams; 
   // report false
   if( true == sourceDescriptorSet.empty() )
   {
      report( ERROR, kFacilityString ) 
	 << "Couldn't find sources providing the specified Active Streams" 
	 << endl;
      success = false;
   }

   return success;
}

DABoolean
SourceManager::handActiveDSDToFrameDeliverer( 
   const DataSourceDescriptor& activeSource )
{
   DABoolean success = true;

   // activeSource returns 'true' if data source was openned sucessfully
   // To determine what caused a failure, look at activeStreamError.
   FrameDeliverer::AddActiveSourceStatus status;
   if( FrameDeliverer::kAddActiveSourceNoError != 
       ( status = m_frameDeliverer.addActiveSource( activeSource ) ) )
   {
      switch( status ) {
                                   
         case FrameDeliverer::kAddActiveSourceDataSourceNotPresent:
         {
            report( EMERGENCY, kFacilityString ) 
               // << "kAddActiveStreamDataSourceNotPresent" << endl;
               << "No datasource defined. Please first define source!" 
	       << endl;
            break; 
         }
         case FrameDeliverer::kAddActiveSourceInvalidStreamsForSource:
         {
            report( EMERGENCY, kFacilityString )
               // << "kAddActiveStreamInvalidStreamsForSource" << endl;
               << "Invalid streams for this source type; please try again!" 
	       << endl;
	    break;
         }
         default:
         {
            report( EMERGENCY, kFacilityString )
               << "Unknown error (?)" << endl;
            break;
         }
      }
      success = false;
   }

   return success;
}

DABoolean
SourceManager::renameToken( const Token& iOldToken, const Token& iNewToken )
{
   DABoolean success = true;

   // if source is in use, refuse
   if( true == isSourceInUseMap( iOldToken ) )
   {
      report( ERROR, kFacilityString ) 
	 << "Can't change Source Name for source in use" << endl;
      return success = false;
   }
      
   // make sure that iNewToken is not used yet
   DABoolean tokenExists = checkIfTokenExists( iNewToken );
   if( true == tokenExists )
   {
      report( ERROR, kFacilityString ) 
	 << "New Source Name \"" << iNewToken 
	 << "\" already exists; choose new one!" << endl;
      return success = false;
   }

   // find source with token
   if( false == isSourceInMap( iOldToken ) ) 
   {
      report( ERROR, kFacilityString ) 
	 << "Couldn't change unknown source \"" 
	 << iOldToken << "\"" << endl;
      success = false;
   }
   else
   {
      // get ahold of source and reinsert with new token 
      SourceMap::iterator tokenIter = m_sourceMap.find( iOldToken );
      BinderBase* binder = (*tokenIter).second;
      m_sourceMap.insert( SourceMap::value_type( iNewToken, binder ) );

      // now erase old source
      m_sourceMap.erase( tokenIter );

      success = true;
   }


   return success;
}

void
SourceManager::resetSourcesToBeginning()
{
   //move sources from m_sourceInUseMap to sourceMap
   SourceMap::const_iterator itInUseEnd = m_sourceInUseMap.end();
   for( SourceMap::const_iterator sourceInUse = m_sourceInUseMap.begin();
	sourceInUse != itInUseEnd;
	++sourceInUse )
   {
      m_sourceMap.insert( (*sourceInUse) );
   }
   //don't forget to empty out the in use list
   m_sourceInUseMap.erase(m_sourceInUseMap.begin(), m_sourceInUseMap.end());
}

//
// const member functions
//
const SourceManager::Token
SourceManager::createToken( Token iToken ) const
   // the approach taken is to ALWAYS return a token; 
   // the user can change it later, if she doesn't like it.
{
   Count count = 2;
   
   Token newToken;
   if( "" != iToken ) 
   { 
      newToken = iToken;
   }
   else
   {
      newToken = string( "source" );
   }
   Token stumpToken = newToken;
   //newToken = addCountToToken( stumpToken, 1 );

   while( true == checkIfTokenExists( newToken ) )
   { 
      //report( INFO, kFacilityString ) 
      // << "Source Name \"" << newToken 
      // << "\" already exists; trying another ..." << endl;
      
      newToken = addCountToToken( stumpToken, count );
      ++count;
   }

   report( INFO, kFacilityString )
      << "creating Source Name \"" << newToken << "\" " << endl;

   return newToken;
}

DABoolean
SourceManager::hasSource( const Token& iToken ) const
{
   return checkIfTokenExists( iToken );
}

DABoolean
SourceManager::checkIfTokenExists( const Token& iToken ) const
{
   DABoolean exists = false;

   // check sourceMap
   SourceMap::iterator tokenIter = m_sourceMap.find( iToken );
   if( m_sourceMap.end() != tokenIter ) 
   {
      exists = true;
   }

   // check sourceInUseMap
   SourceMap::iterator tokenInUseIter = m_sourceInUseMap.find( iToken );
   if( m_sourceInUseMap.end() != tokenInUseIter ) 
   {
      exists = true;
   }

   return exists;
}

string
SourceManager::statusOfAllSources() const
{
   string resultString;

   typedef FrameDeliverer::StatusOfSources StatusOfSources;
   StatusOfSources statusOfSources = m_frameDeliverer.statusOfSources();
   StatusOfSources::const_iterator itEnd = statusOfSources.end();
   for( StatusOfSources::const_iterator it = statusOfSources.begin();
	it != itEnd;
	++it )
   {
      FrameDeliverer::SourceStatus status( (*it).first );
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#if defined(OSTRSTREAM_NO_TERMINATION_BUG)
      const unsigned int kSize=100;
      char codeString[kSize];
      snprintf( codeString, kSize, "%d", status );
      string statusString = (status == FrameDeliverer::kSourceNoError ) 
	 ? string("ok") : string( "bad (code=" )+string( codeString )+string(")");
#else
      //ostringstream number; // not yet available: <sstream>
      ostrstream codeString;
      codeString << int( status );
      string statusString = (status == FrameDeliverer::kSourceNoError ) 
	 ? string("ok") : string( "bad (code=" )+codeString.str()+string(")");
#endif
#else
      ostringstream codeString;
      codeString << int( status );
      string statusString = (status == FrameDeliverer::kSourceNoError ) 
	 ? string("ok") : string( "bad (code=" )+codeString.str()+string(")");
#endif
      resultString += findTokenFor((*it).second)
	 +string( " : " )+statusString+ string( "\n" );
   }
   
   return resultString;
}


SourceManager::Token
SourceManager::findTokenFor( const DataSourceDescriptor& iDescriptor ) const
{
   SourceManager::Token returnValue;


   SourceMap::const_iterator lastToken( m_sourceMap.end() );
   for( SourceMap::const_iterator tokenIter = m_sourceMap.begin();
	tokenIter != lastToken;
	++tokenIter )
   {
      if(  ( &((*(*tokenIter).second).dsBinder()) != 0 ) && 
	     (*(*tokenIter).second).dsBinder() == iDescriptor ) {
	 return (*tokenIter).first;
      }
   }
      
   SourceMap::const_iterator lastTokenInUse( m_sourceInUseMap.end() );
   for( SourceMap::const_iterator tokenInUseIter 
	   = m_sourceInUseMap.begin();
	tokenInUseIter != lastTokenInUse;
	++tokenInUseIter )
   {
      if( ( 0 != &((*(*tokenInUseIter).second).dsBinder()) ) && 
	  (*(*tokenInUseIter).second).dsBinder() == iDescriptor ) {
	 return (*tokenInUseIter).first;
      }
   }
   return returnValue;
}

string
SourceManager::listTokens() const
{
   string resultString;
   //resultString += string( "\nListing of all Tokens:\n" );

   SourceMap::const_iterator lastToken = m_sourceMap.end();
   for( SourceMap::const_iterator iter = m_sourceMap.begin();
	iter != lastToken;
	++iter )
   {
      resultString += string( "   " ) + (*iter).first + string( "\n" );
   }

   SourceMap::const_iterator lastInUseToken = m_sourceInUseMap.end();
   for( SourceMap::const_iterator iterInUse = m_sourceInUseMap.begin();
	iterInUse != lastInUseToken;
	++iterInUse )
   {
      resultString += string( " * " ) + (*iterInUse).first + string( "\n" );
   }

   return resultString;
}

const vector<SourceManager::Token>
SourceManager::tokens() const
{
   vector<Token> tokens;

   SourceMap::const_iterator lastToken = m_sourceMap.end();
   for( SourceMap::const_iterator iter = m_sourceMap.begin();
	iter != lastToken;
	++iter )
   {
      tokens.push_back( (*iter).first );
   }

   return tokens;
}

string
SourceManager::list( const Token& iToken ) const
{
   string resultString;
   //resultString += string( "Listing source \"" );
   resultString += iToken + string( "\":\n" );

   resultString += listSource( iToken );
   resultString += listSourceInUse( iToken );

   return resultString;
}

string
SourceManager::listAllSources() const
{
   string resultString;

   if( true == m_sourceMap.empty() && true == m_sourceInUseMap.empty() )
   {
      resultString += string( "\n" );
   }
   else
   {
      //resultString += string( "\nListing all Sources:\n" );

      SourceMap::const_iterator lastToken( m_sourceMap.end() );
      for( SourceMap::const_iterator tokenIter = m_sourceMap.begin();
	   tokenIter != lastToken;
	   ++tokenIter )
      {
	 resultString += listSource( (*tokenIter).first );
      }
      
      SourceMap::const_iterator lastTokenInUse( m_sourceInUseMap.end() );
      for( SourceMap::const_iterator tokenInUseIter 
	      = m_sourceInUseMap.begin();
	   tokenInUseIter != lastTokenInUse;
	   ++tokenInUseIter )
      {
	 resultString += listSourceInUse( (*tokenInUseIter).first );
      }
   }      

   return resultString;
}

string
SourceManager::listSource( const Token& iToken ) const
{
   return listSourceImplementation( iToken, m_sourceMap );
}

string
SourceManager::listSourceInUse( const Token& iToken ) const 
{
   return listSourceImplementation( iToken, m_sourceInUseMap, "*" );
}

string
SourceManager::listSourceImplementation( const Token& iToken, 
					 const SourceMap& iMap,
					 string iSpecialPrint ) const
{
   string resultString;
   const string indentation( "     " );

   SourceMap::const_iterator source = iMap.find( iToken );
   if( iMap.end() == source )
   {
      resultString += string( "\n" );
   }
   else
   {
      const BinderBase* binder = (*source).second;
      
      if( true == binder->isDummy() )
      {
	 resultString += string( " " ) + iSpecialPrint 
	    + string( " Source \"" ) + iToken + string( "\": empty\n" );
      } else
      if( true == binder->isChain() )
      {
	 resultString += string( " " ) + iSpecialPrint 
	    + string( " Source \"" ) + iToken + string( "\":\n" );
	 resultString += listSourcesInChain( binder );
      }
      else
      {
	 const SourceName& sourceName = binder->dataSourceID();

	 // only print token name, if sourceName != token
	 if( sourceName == iToken )
	 {
	    resultString += string( " " ) + iSpecialPrint
	       + string( " Source " ) + sourceName;
	 }
	 else
	 {
	    resultString += string( " " ) + iSpecialPrint 
	       + string( " Source \"" ) + iToken + string( "\":\n" );
	    resultString += indentation + sourceName;
	 }
	 resultString += string( "\n" ) + indentation + string( "Streams: " );
	 const StreamSet& streams = binder->boundStreams();
	 StreamSet::const_iterator endStream = streams.end();
	 for( StreamSet::const_iterator stream = streams.begin();
	      stream != endStream;
	      ++stream )
	 {
	    if( true == binder->isToBeActiveStream( *stream ) )
	    {
	       resultString += string( " " ) + iSpecialPrint + (*stream).value();
	    }
	    else
	    {
	       resultString += string( " " )  + (*stream).value();
	    }
	 }
	 resultString += string( "\n" );

	 // and parameters
	 if( binder->parameters() != string( "" ) )
	 {
	    resultString += indentation + string( "Parameters: " ) 
	       + binder->parameters() + string( "\n" );
	 }
      }

   }

   return resultString;
}

string
SourceManager::listSourcesInChain( const BinderBase* iBinder ) const
{
   string resultString;
   const string indentation( "      " );

   assert( true == iBinder->isChain() );

   ChainSourceBinderBase& CSB = (ChainSourceBinderBase&)(*iBinder).dsBinder();

   typedef vector<DataSourceDescriptor> Sources;
   Sources sources = CSB.sources();
   
   // print out streams for chain
   resultString += indentation + string( "Streams: " );
   const StreamSet& streams = CSB.boundStreams();
   StreamSet::const_iterator endStream = streams.end();
   for( StreamSet::const_iterator stream = streams.begin();
	stream != endStream;
	++stream )
   {
      resultString += string( " " ) + (*stream).value();
   }
   resultString += string( "\n" );
   
   // and parameters
   if( iBinder->parameters() != string( "" ) )
   {
      resultString += indentation + string( "Parameters: " ) 
	 + iBinder->parameters() + string( "\n" );
   }

   // loop over all entries in chain
   Sources::const_iterator itEnd = sources.end();
   for( Sources::const_iterator i = sources.begin();
	i != itEnd;
	++i )
   {
      resultString += 
	 string( "      " ) + (*i).dataSourceID() + string( "\n" );
   }
  
   return resultString;
}

string
SourceManager::listStreams() const
{
   string resultString;

   // ------ reevaluate streams based on sources every time we're called!
   // make a mmap<stream,sources>: 
   //     for a given stream which sources can provide it
   typedef multimap< StreamType, BinderBase*, less<StreamType> > StreamSourceMM;
   StreamSourceMM streamSourceMM;
   
   SourceMap::const_iterator endSrcIt = m_sourceMap.end();
   for( SourceMap::const_iterator srcIt = m_sourceMap.begin();
	srcIt != endSrcIt;
	++srcIt )
   {
      BinderBase* binder = (*srcIt).second;

      if( binder->isDummy() ) continue;

      StreamSet streams = binder->boundStreams();

      StreamSet::const_iterator endStrIt = streams.end();
      for( StreamSet::const_iterator strIt = streams.begin();
	   strIt != endStrIt;
	   ++strIt )
      {
	 streamSourceMM.insert( StreamSourceMM::value_type( *strIt,
							    binder ) );
      }
   }

   SourceMap::const_iterator endSrcInUseIt = m_sourceInUseMap.end();
   for( SourceMap::const_iterator srcInUseIt = m_sourceInUseMap.begin();
	srcInUseIt != endSrcInUseIt;
	++srcInUseIt )
   {
      BinderBase* binder = (*srcInUseIt).second;

      const StreamSet& streams = binder->boundStreams();

      StreamSet::const_iterator endStrIt = streams.end();
      for( StreamSet::const_iterator strIt = streams.begin();
	   strIt != endStrIt;
	   ++strIt )
      {
	 streamSourceMM.insert( StreamSourceMM::value_type( *strIt,
							    binder ) );
      }
   }

   // print out streams for chain
   resultString += string( "Streams:\n" );

   StreamSourceMM::const_iterator endStream = streamSourceMM.end();
   for( StreamSourceMM::const_iterator stream = streamSourceMM.begin();
	stream != endStream;
	++stream )
   {
      resultString += string( " " ) + (*stream).first.value() + string( ":\n" );
      
      StreamSourceMM::iterator lastSource
	 = streamSourceMM.upper_bound( (*stream).first ); 
      for( StreamSourceMM::iterator source
	      = streamSourceMM.lower_bound( (*stream).first ); 
	   source != lastSource;
	   ++source )
      {
	 BinderBase* binder = (*source).second;
	 const char* sourceName = binder->dataSourceID().c_str();
	 if( (*source).second->isChain() ) {
	    sourceName = (*source).first.value().c_str();
	 }

	 resultString += string( "    " );

	 // print special if stream is toBeActive
	 if( true == binder->isToBeActiveStream( (*stream).first ) )
	 {
	    resultString += string( "*" );
	 }
	 resultString += sourceName + string( "\n" );
      }
   }
   
   return resultString;
}

string
SourceManager::listStreamsToBeActivated() const
{
   string resultString;

   // print out streams for chain
   resultString += string( "Active Streams: " );

   const StreamSet& streams = streamsToBeActivated();

   StreamSet::const_iterator endStream = streams.end();
   for( StreamSet::const_iterator stream = streams.begin();
	stream != endStream;
	++stream )
   {
      resultString += string( " " ) + (*stream).value();
   }
   resultString += string( "\n" );
   
   return resultString;
}

DABoolean
SourceManager::isSourceInMap( const Token& iToken ) const
{
   DABoolean success = true;

   SourceMap::iterator tokenIter = m_sourceMap.find( iToken );
   if( m_sourceMap.end() == tokenIter  ) 
   {
      success = false;
   }   

   return success;
}

DABoolean 
SourceManager::isSourceInUseMap( const Token& iToken ) const
{
   DABoolean success = true;

   SourceMap::iterator tokenIter = m_sourceInUseMap.find( iToken );
   if( m_sourceInUseMap.end() == tokenIter  ) 
   {
      success = false;
   }   

   return success;
}

const StreamSet&
SourceManager::streamsToBeActivated() const
{
   return m_streamsToBeActivated;
}

//
// static member functions
//


// -----------------------------------------
// Revision Log:
//
// $Log: SourceManager.cc,v $
// Revision 1.64  2004/03/29 12:17:59  cdj
// yet another bug fix for the previous change
//
// Revision 1.63  2004/03/28 20:35:32  cdj
// fixed bug in last change which caused a crash when 'source create' was used
//
// Revision 1.62  2004/03/26 15:27:21  cdj
// catch the case where users try to add the same source multiple times
//
// Revision 1.61  2004/01/15 19:04:37  cdj
// fixed problem when have a dummy source in the job when try to remove active source which has reached its end
//
// Revision 1.60  2002/12/06 16:36:46  cleo3
// deal with strstream/stringstream
//
// Revision 1.59  2002/10/10 18:10:07  cdj
// fixed minor bug that a chain with only one file could not be set as active using 'source act'
//
// Revision 1.58  2001/12/11 15:57:35  cdj
// source status command now uses token names
//
// Revision 1.57  2001/03/01 02:11:50  cdj
// add StartRun as a default Stream
//
// Revision 1.56  2000/12/02 19:26:56  cdj
// added findTokenFor so JobControl doesn't have to know how Tokens are built
//
// Revision 1.55  2000/11/18 21:40:29  cdj
// if multiple possible active sources, default is the souce that already has active streams
//
// Revision 1.54  2000/05/15 15:34:30  mkl
// switch non-EMERGENCY suez messages to SYSTEM severity level
//
// Revision 1.53  2000/04/21 21:45:56  mkl
// print out what source has problems when handing off to FrameDeliverer
//
// Revision 1.52  2000/04/10 18:39:25  mkl
// SourceManager: replace couts with report
//
// Revision 1.51  2000/04/10 18:27:41  mkl
// use source-name token-reduction consistently
//
// Revision 1.50  2000/03/22 23:35:16  mkl
// turned cin-related couts into report(EMERGENCY) so that can check for errors in logfiles AND avoid too-high report level
//
// Revision 1.49  2000/03/17 15:38:19  cdj
// added resetSourcesToBeginning() (needed for FrameIterate). Fixed some minor memory leaks
//
// Revision 1.48  2000/02/03 17:07:43  mkl
// fix prompting response when several options present
//
// Revision 1.47  2000/01/19 16:53:13  mkl
// force reload of proxies after new source is added
//
// Revision 1.46  1999/12/11 19:07:32  mkl
// added 'source status' command; use bug flag for linux string compare function problem
//
// Revision 1.45  1999/10/08 21:46:44  mkl
// put in hooks for pattern searching in loading (if we ever decide to use it); fix bug with file chaining
//
// Revision 1.44  1999/07/16 15:00:16  mkl
// turn off annoying 'trying another source name' message
//
// Revision 1.43  1999/06/14 15:55:44  mkl
// return token name as tcl resultString
//
// Revision 1.42  1999/06/12 15:42:19  mkl
// print out what streams are the default
//
// Revision 1.41  1999/06/12 00:03:59  mkl
// allow to specify default streams per source format
//
// Revision 1.40  1999/06/07 19:06:09  mkl
// dont use all streams of a source as active, if any is
//
// Revision 1.39  1999/05/28 20:25:00  mkl
// Solaris stringstream does not exist, and strstream does not terminate; use snprintf instead
//
// Revision 1.38  1999/04/30 18:15:21  mkl
// first version of source act command handling
//
// Revision 1.37  1999/04/24 16:22:42  mkl
// keep track of DataSourceDescriptors, not just names of files
//
// Revision 1.36  1999/04/14 21:16:25  mkl
// ordered container used in Suez
//
// Revision 1.35  1999/03/11 22:02:42  mkl
// source out stream will activate stream; turn off superfluous warning for 'param' command
//
// Revision 1.34  1999/02/22 23:41:41  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.33  1999/01/27 22:55:25  mkl
// rewrote StringUtil utility functions
//
// Revision 1.32  1999/01/21 00:02:00  mkl
// added minor convenience functions 'hasSource/Sink'
//
// Revision 1.31  1998/12/02 22:20:55  mkl
// bug fix handling of multiple active sources
//
// Revision 1.30  1998/11/09 19:33:13  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.29  1998/10/05 16:42:51  mkl
// give more meaningful error message if no active streams
//
// Revision 1.28  1998/09/08 19:37:48  mkl
// rename overloaded virtual function (renaming was in order anyways)
//
// Revision 1.27  1998/07/28 15:53:17  mkl
// ripple effect: needed to include set
//
// Revision 1.26  1998/06/23 23:00:47  mkl
// cleanup of LoadableInterface
//
// Revision 1.25  1998/06/23 20:15:40  mkl
// minor bug fixes
//
// Revision 1.24  1998/06/17 18:18:10  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.23  1997/10/15 02:19:14  mkl
// proper listing and ambiguitiy handling
//
// Revision 1.22  1997/10/07 19:25:24  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.21  1997/10/07 04:19:05  mkl
// report --> cout for INFO messages
//
// Revision 1.20  1997/10/05 15:13:57  mkl
// New StringUtil methods
//
// Revision 1.19  1997/09/18 21:26:57  cdj
// changed Boolean to DABoolean
//
// Revision 1.18  1997/09/10 07:19:49  mkl
// minor
//
// Revision 1.17  1997/09/10 01:52:37  mkl
// replaced \n by end
//
// Revision 1.16  1997/09/05 22:35:27  mkl
// undid singleton patteron for MasterProcessor
//
// Revision 1.15  1997/09/04 06:38:53  mkl
// moved StringUtilities, STL_AlgoString, and STL_SharedObject to better places
//
// Revision 1.14  1997/09/03 05:57:51  mkl
// moved from 'const string kFacilityString' to 'static const char* const'
//
// Revision 1.13  1997/09/03 02:38:52  mkl
// restructuring suez libraries
//
// Revision 1.12  1997/08/29 04:21:58  mkl
// simplify JobControl: remove FileInput/Output files, bug flag changes, handling of suffix .gz etc.
//
// Revision 1.11  1997/08/22 06:27:33  mkl
// beauty
//
// Revision 1.10  1997/08/22 04:21:53  mkl
// standardize error messages from commands
//
// Revision 1.9  1997/08/20 06:23:39  mkl
// symmetrized sinks with sources in terms of user interface
//
// Revision 1.8  1997/08/17 04:22:37  mkl
// minor changes to user printout
//
// Revision 1.7  1997/08/15 08:11:28  mkl
// changed Stream::Type to StreamType as constructor for the sake of cxx5.6
//
// Revision 1.6  1997/08/14 21:08:47  mkl
// don't erase iterator and then use it!
//
// Revision 1.5  1997/08/13 21:03:00  mkl
// changes to make it work with cxx
//
// Revision 1.4  1997/08/13 07:10:50  mkl
// Chains of Sources, new activation of streams, and ProxyDict
//
// Revision 1.3  1997/08/08 05:56:00  mkl
// quick fix four bogged source command
//
// Revision 1.2  1997/08/08 05:21:04  mkl
// first attempt at chains-of-files
//
// Revision 1.1  1997/07/24 04:59:50  mkl
// adding chains of sources
//

