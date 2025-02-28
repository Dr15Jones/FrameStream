// -*- C++ -*-
//
// Package:     JobControl
// Module:      SinkManager
// 
// Description: manages sinks internally and hands them off 
//              as DataSinkBinders to FrameStorer
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue Aug 19 14:53:20 EDT 1997
// $Id: SinkManager.cc,v 1.22 2003/09/19 21:20:33 cdj Exp $
//
// Revision history
//
// $Log: SinkManager.cc,v $
// Revision 1.22  2003/09/19 21:20:33  cdj
// changes needed for Path implementation
//
// Revision 1.21  1999/05/12 20:35:25  mkl
// clean out old dependencies
//
// Revision 1.20  1999/04/14 21:16:24  mkl
// ordered container used in Suez
//
// Revision 1.19  1999/03/11 22:02:40  mkl
// source out stream will activate stream; turn off superfluous warning for 'param' command
//
// Revision 1.18  1999/02/22 23:41:39  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.17  1999/01/21 00:01:59  mkl
// added minor convenience functions 'hasSource/Sink'
//
// Revision 1.16  1998/11/09 19:33:11  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.15  1998/09/08 19:24:12  mkl
// clean up for warning messages from cxx 6.0
//
// Revision 1.14  1998/07/28 15:53:17  mkl
// ripple effect: needed to include set
//
// Revision 1.13  1998/06/23 20:15:40  mkl
// minor bug fixes
//
// Revision 1.12  1997/10/20 17:11:07  mkl
// fix for sink with unspecified streams
//
// Revision 1.11  1997/10/07 19:25:22  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.10  1997/10/07 04:19:03  mkl
// report --> cout for INFO messages
//
// Revision 1.9  1997/09/18 21:26:55  cdj
// changed Boolean to DABoolean
//
// Revision 1.8  1997/09/10 01:52:35  mkl
// replaced \n by end
//
// Revision 1.7  1997/09/04 06:38:52  mkl
// moved StringUtilities, STL_AlgoString, and STL_SharedObject to better places
//
// Revision 1.6  1997/09/03 05:57:49  mkl
// moved from 'const string kFacilityString' to 'static const char* const'
//
// Revision 1.5  1997/09/03 02:38:50  mkl
// restructuring suez libraries
//
// Revision 1.4  1997/08/29 04:21:57  mkl
// simplify JobControl: remove FileInput/Output files, bug flag changes, handling of suffix .gz etc.
//
// Revision 1.3  1997/08/22 06:27:32  mkl
// beauty
//
// Revision 1.2  1997/08/20 07:27:17  mkl
// minor fixes to make cxx5.4-6 happy
//
// Revision 1.1  1997/08/20 06:23:37  mkl
// symmetrized sinks with sources in terms of user interface
//
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "JobControl/SinkManager.h"
#include "CommandPattern/StringUtilities.h"
#include "DataStorage/DataSinkBinder.h"
#include "DataHandler/StreamSet.h"

// STL classes
#include <vector>
#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#  include <map>
#  include <multimap.h>
#else
#  include <map>
#endif
#include <set>         

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.SinkManager";

typedef OrderedMap< SinkManager::SinkName, DataSinkBinder* > SinkMap;
typedef SinkMap SinkInUseMap;

//
// static data member definitions
//

//
// constructors and destructor
//
SinkManager::SinkManager( )
   : Module( "SinkManager", "SinkManager" ),
     m_command( "sink", this ),
     m_sinkMap( *new SinkMap ),
     m_sinkInUseMap( *new SinkInUseMap )
{
   if(    0 == &m_sinkMap
       || 0 == &m_sinkInUseMap
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

// SinkManager::SinkManager( const SinkManager& )
// {
// }

SinkManager::~SinkManager()
{
   // clear out maps and delete contained objects!
   removeAllSinks();
   delete &m_sinkMap;
   delete &m_sinkInUseMap;
}

//
// assignment operators
//
// const SinkManager& SinkManager::operator=( const SinkManager& )
// {
// }

//
// member functions
//
DABoolean
SinkManager::addSink( DataSinkBinder* iBinder )
//---------------------------------------------------------------
// adds sinks to be used.
{
   DABoolean status = true;

   // check that pointer not null
   if( 0 == iBinder )
   {
      report( ERROR, kFacilityString )
	 << "pBinder == 0" << endl;
      return( status = false );
   }

   // get name
   const SinkName& name = iBinder->dataSinkID();

   // if sink already exists, don't allow it to be added
   // 1.) in Map 
   SinkMap::iterator sinkIter = m_sinkMap.find( name );
   if( m_sinkMap.end() != sinkIter )
   {
      report( ERROR, kFacilityString ) 
	 << "A Sink with that name already exists!" << endl;
      return( status = false );
   }
   // 2.) or in InUseMap
   SinkInUseMap::iterator sinkInUseIter = m_sinkInUseMap.find( name );
   if( m_sinkInUseMap.end() != sinkInUseIter )
   {
      report( ERROR, kFacilityString ) 
	 << "A Sink with that name already exists!" << endl;
      return( status = false );
   }

   // name not in use --> new sinkBinder

   // add sink info to map
   m_sinkMap.insert( SinkMap::value_type( name, iBinder ) ); 

   addedSink.emit(name);
   return status;
}

DABoolean
SinkManager::useSinks()
// -------------------------------------------------------------
// hand over all sinks in our sinksMap to FD
// -------------------------------------------------------------
{
   DABoolean success = true;

   SinkMap::iterator itEnd = m_sinkMap.end();
   for( SinkMap::iterator sink = m_sinkMap.begin();
	sink != itEnd;
	++sink )
   {
      m_sinkInUseMap.insert( (*sink) );
   } // loop over sinks

   m_sinkMap.erase(m_sinkMap.begin(), m_sinkMap.end());

   return success;
}

DABoolean
SinkManager::removeSink( const SinkName& iName )
{
   DABoolean success = false;
   DABoolean sinkInUseMap=true;
   DABoolean sinkInMap=true;

   // find sink with name

   // 1.) in SinkMap
   SinkMap::iterator sinkIter = m_sinkMap.find( iName );
   if( m_sinkMap.end() == sinkIter  ) 
   {
      sinkInMap = false;
   }
   else
   {
      DABoolean canRemove = true;
      requestToRemoveSink.emit(iName, canRemove );
      if( canRemove ) {
         // delete object and get rid of entry in map
         removingSink.emit(iName);
         delete (*sinkIter).second;
         m_sinkMap.erase( sinkIter );
         
         cout << "Removed sink \"" 
            << iName << "\"." << endl;
         success = true;
      } else {
         report(SYSTEM,kFacilityString)<<"Sink "<<iName<<" is being used so can not be removed.\n"
         " First remove any path that contains "<<iName<<endl;
         return false;
      }
   }

   // 2.) in SinkInUseMap
   SinkInUseMap::iterator nameInUseIter = m_sinkInUseMap.find( iName );
   if( m_sinkInUseMap.end() == nameInUseIter  ) 
   {
      sinkInUseMap = false;
   }
   else
   {
      DABoolean canRemove = true;
      requestToRemoveSink.emit(iName, canRemove );
      if( canRemove ) {
         sinkInUseMap = removeSinkInUse( iName );
         success = true;
      } else {
         report(SYSTEM,kFacilityString)<<"Sink "<<iName<<" is being used so can not be removed.\n"
         " First remove any path that contains "<<iName<<endl;
         return false;
      }
   }

   // check if sink was in either map
   if(    !sinkInMap
       && !sinkInUseMap )
   {
      report( WARNING, kFacilityString ) 
	 << "Can't remove unknown sink \"" << iName << "\"." << endl;
      success = false;
   }

   return success;
}

DABoolean
SinkManager::removeSinkInUse( const SinkName& iName )
{
   DABoolean success = true;

   // find sink with name
   SinkInUseMap::iterator sinkInUseIter = m_sinkInUseMap.find( iName );
   if( m_sinkInUseMap.end() == sinkInUseIter  ) 
   {
      report( WARNING, kFacilityString ) 
	 << "Can't remove sink-in-use \"" << iName << "\"." << endl;

      success = false;
   }
   else
   {
 
      cout 
	 << "Taken sink \"" << iName << "\" out of use." << endl;
      
      // delete object and remove entry in map
      removingSinkInUse.emit(iName);
      delete (*sinkInUseIter).second;
      m_sinkInUseMap.erase( sinkInUseIter );
      
      
      success = true;
   }

   return success;
}

DABoolean
SinkManager::removeAllSinks()
{
   DABoolean status = true;

   // clear all sinks from our internal maps; 
   //   make sure to delete the sinks!
   SinkMap::iterator endIt = m_sinkMap.end();
   for( SinkMap::iterator it = m_sinkMap.begin();
        it != endIt;
        ++it )
   {
      removingSink.emit( (*it).first);
      delete (*it).second;
   }
   m_sinkMap.erase( m_sinkMap.begin(), m_sinkMap.end() );

   SinkInUseMap::iterator inUseEndIt = m_sinkInUseMap.end();
   for( SinkInUseMap::iterator inUseIt = m_sinkInUseMap.begin();
        inUseIt != inUseEndIt;
        ++inUseIt )
   {
      removingSinkInUse.emit( (*inUseIt).first);
      delete (*inUseIt).second;
   }
   m_sinkInUseMap.erase( m_sinkInUseMap.begin(), m_sinkInUseMap.end() );

   return status;
}

DABoolean
SinkManager::bindStreamsToSink( const SinkName& iName, 
				const StreamSet& iStreams ) 
{
   DABoolean status = true;

   // if name is in use, don't allow adding
   SinkInUseMap::iterator nameInUseIter = m_sinkInUseMap.find( iName );
   if( m_sinkInUseMap.end() != nameInUseIter )
   {
      report( ERROR, kFacilityString ) 
	 << "Already have written to sink; need to remove the sink and reload." << endl;
      return( status = false );
   }
   // name not in use

   // find entry in map and rebind new streams to binder
   SinkMap::iterator sinkIter = m_sinkMap.find( iName );
   if( m_sinkMap.end() != sinkIter )
   {
      DataSinkBinder* binder = (*sinkIter).second;
      binder->bindStreams( iStreams );
   }      

   return status;
}

DABoolean
SinkManager::useSink(const DataSinkBinder* iBinder )
{
   const SinkName& name = iBinder->dataSinkID();
   
   SinkMap::iterator itSink = m_sinkMap.find( name );
   if( itSink == m_sinkMap.end() ) {
      return false;
   }
   m_sinkInUseMap.insert( (*itSink) );
      
   m_sinkMap.erase(itSink);
   return true;
}
//
// const member functions
//
DataSinkBinder*
SinkManager::binderFor( const SinkName& iName ) const
{
   SinkMap::iterator nameIter = m_sinkMap.find( iName );
   if( nameIter != m_sinkMap.end() ) {
      return (*nameIter).second;
   }

   SinkInUseMap::iterator nameInUseIter = m_sinkInUseMap.find( iName );
   if( m_sinkInUseMap.end() != nameInUseIter ) 
   {
      return (*nameInUseIter).second;
   }
   return 0;
}

STL_VECTOR(string)
SinkManager::unusedSinks() const
{
   STL_VECTOR(string) returnValue;
   
   SinkMap::const_iterator lastName( m_sinkMap.end() );
   for( SinkMap::const_iterator nameIter = m_sinkMap.begin();
	nameIter != lastName;
	++nameIter )
   {
      returnValue.push_back( (*nameIter).first );
   }
   return returnValue;
}


DABoolean
SinkManager::hasSink( const SinkName& iName ) const
{
   return checkIfSinkExists( iName );
}

DABoolean
SinkManager::checkIfSinkExists( const SinkName& iName ) const
{
   DABoolean exists = false;

   // check sinkMap
   SinkMap::iterator nameIter = m_sinkMap.find( iName );
   if( m_sinkMap.end() != nameIter ) 
   {
      exists = true;
   }

   // check sinkInUseMap
   SinkInUseMap::iterator nameInUseIter = m_sinkInUseMap.find( iName );
   if( m_sinkInUseMap.end() != nameInUseIter ) 
   {
      exists = true;
   }

   return exists;
}

DABoolean
SinkManager::isUnused(const SinkName& iName ) const
{
   return m_sinkMap.end() != m_sinkMap.find( iName );
}

string
SinkManager::list( const SinkName& iName ) const
{
   string resultString;
   //resultString += string( "Listing sink \"" );
   resultString += iName + string( "\":\n" );

   resultString += listSink( iName );
   resultString += listSinkInUse( iName );

   return resultString;
}

string
SinkManager::listAllSinks() const
{
   string resultString;
   
   if( true == m_sinkMap.empty() && true == m_sinkInUseMap.empty() )
   {
      resultString += string( "\n" );
   }
   else
   {
      //resultString += string( "\nListing all Sinks:\n" );
      
      SinkMap::const_iterator lastName( m_sinkMap.end() );
      for( SinkMap::const_iterator nameIter = m_sinkMap.begin();
	   nameIter != lastName;
	   ++nameIter )
      {
	 resultString += listSink( (*nameIter).first );
      }
      
      SinkInUseMap::const_iterator lastNameInUse( m_sinkInUseMap.end() );
      for( SinkInUseMap::const_iterator nameInUseIter 
	      = m_sinkInUseMap.begin();
	   nameInUseIter != lastNameInUse;
	   ++nameInUseIter )
      {
	 resultString += listSinkInUse( (*nameInUseIter).first );
      }
   }

   return resultString;
}

string
SinkManager::listSink( const SinkName& iName ) const
{
   string resultString;

   SinkMap::iterator sink = m_sinkMap.find( iName );
   if( m_sinkMap.end() == sink )
   {
      resultString += string( "\n" );
   }
   else
   {
      const DataSinkBinder* binder = (*sink).second;
      
      resultString += string( "  " ) + iName;

      resultString += string( "   streams: " );
      const StreamSet& streams = binder->boundStreams();
      if( true == streams.empty() ) 
      {
	 resultString += string( " will default to active streams" );
      }
      StreamSet::const_iterator endStream = streams.end();
      for( StreamSet::const_iterator j = streams.begin();
	   j != endStream;
	   ++j )
      {
	 resultString += string( " " ) + (*j).value();
      }
      resultString += string( "\n" );
   }
   
   return resultString;
}

string
SinkManager::listSinkInUse( const SinkName& iName ) const
{
   string resultString;

   SinkInUseMap::iterator sinkInUse = m_sinkInUseMap.find( iName );
   if( m_sinkInUseMap.end() == sinkInUse )
   {
      resultString += string( "\n" );
   }
   else
   {
      const DataSinkBinder* binder = (*sinkInUse).second;
      
      resultString += string( " * " ) + iName;

      resultString += string( "    streams: " );
      const StreamSet& streams = binder->boundStreams();
      StreamSet::const_iterator endStream = streams.end();
      for( StreamSet::const_iterator j = streams.begin();
	   j != endStream;
	   ++j )
      {
	 resultString += string( " " ) + (*j).value();
      }
      resultString += string( "\n" );
   }

   return resultString;
}

const StreamSet
SinkManager::streamsToBeActivated() const
{
   StreamSet streams;

   // Algorithm
   // loop over all sinks 
   //        (that aren't in use yet; a sink in use has
   //         already caused a stream activation!)
   // and insert streams
   SinkInUseMap::const_iterator lastSink( m_sinkInUseMap.end() );
   for( SinkInUseMap::const_iterator sinkIter = m_sinkInUseMap.begin();
	sinkIter != lastSink;
	++sinkIter )
   {
      const StreamSet& boundStreams = (*sinkIter).second->boundStreams();

      StreamSet::const_iterator streamEnd = boundStreams.end();
      for( StreamSet::const_iterator streamIt = boundStreams.begin();
	   streamIt != streamEnd;
	   ++streamIt )
      {
	 streams.insert( *streamIt );
      }
   }
      
   return streams;
}

#if 0 /* not used anymore: streams of sinks are automatically activated */
DABoolean 
SinkManager::checkIfStreamsOfSinkAreActive( 
   const DataSinkBinder& iBinder ) const
{
   DABoolean status = true;

   // need to get a handle on FrameDeliverer to find 
   // out which streams are active
   const StreamSet& activeStreams = m_frameDeliverer.activeStreams();

   // loop over bound streams for this binder and check if stream is active.
   const StreamSet& boundStreams = iBinder.boundStreams();
   StreamSet::const_iterator streamEnd = boundStreams.end();
   for( StreamSet::const_iterator streamIt = boundStreams.begin();
	streamIt != streamEnd;
	++streamIt )
   {
      StreamSet::const_iterator foundStream = activeStreams.find( *streamIt );

      // if streams is not among active, take action:
      // Shall we:
      // 1.) just notify user, drop stream, and keep going?
      // 2.) notify user and stop, so that user can take action.
      // For now I go with 2.)
      if( activeStreams.end() == foundStream )
      {
	 report( ERROR, kFacilityString ) 
	    << "Stream \"" << (*streamIt).value() 
	    << "\" cannot be written\n"
	    << "      since only active streams can be written!" << endl;
	 status = false;
	 break;
      }
   }

   return status;
}
#endif

//
// static member functions
//




