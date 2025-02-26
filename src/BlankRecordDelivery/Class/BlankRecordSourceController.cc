// -*- C++ -*-
//
// Package:     BlankRecordDelivery
// Module:      BlankRecordSourceController
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D. Jones
// Created:     Thu Mar 26 14:06:44 EST 1998
// $Id: BlankRecordSourceController.cc,v 1.2 2001/09/07 18:44:27 cleo3 Exp $
//
// Revision history
//
// $Log: BlankRecordSourceController.cc,v $
// Revision 1.2  2001/09/07 18:44:27  cleo3
// switched to using NO_STL_TEMPLATED_MEMBER_FUNCTIONS_BUG
//
// Revision 1.1.1.1  1998/03/31 21:21:19  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif /* MULTISET_IS_SEPARATE_FILE_BUG */
#include <map>
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "BlankRecordDelivery/BlankRecordSourceController.h"
#include "BlankRecordDelivery/BlankRecordProxyDeliverer.h"
#include "BlankRecordDelivery/BlankRecordStopsBase.h"
#include "STLUtility/fwd_set.h"
#include "DataHandler/StreamSet.h"
#include "DataHandler/StreamPriorityGreater.h"
// STL classes
#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif /* MULTISET_IS_SEPARATE_FILE_BUG */
#include <map>

//
// constants, enums and typedefs
//


static const char* const kFacilityString = "BlankRecordDelivery.BlankRecordSourceController" ;

//
// static data member definitions
//

//
// constructors and destructor
//

BlankRecordSourceController::BlankRecordSourceController( 
         const string& iName, 
	 const Stream::Set& iStreams, 
	 BlankRecordStopsBase* iStops ) :
   DataSourceController( (ProxyDeliverer*) 0 ),
   m_name( iName ),
#if defined(__DECCXX)
   m_makeRecords( *(new Stream::Set ) ),
#else 
   m_makeRecords( *(new Stream::Set( iStreams ) ) ),
#endif
   m_stops( iStops ),
   m_presentRecordSyncValue( SyncValue::kUndefined)
{
   assert( &m_makeRecords != 0 );

#if defined(__DECCXX)
   //NOTE: cxx would ignore this function if I tried to create m_makeRecords
   //       like m_makeRecords( *(new Stream::Set( iStreams ) ) )
   m_makeRecords = iStreams;
#endif

   setRecordsToRetrieve( iStreams );
   setIsSequentiallyAccessing( false );
   
   setInitializationStatus( kInitNoError );
}

//BlankRecordSourceController::BlankRecordSourceController( int )
//{
//}
// BlankRecordSourceController::BlankRecordSourceController( const BlankRecordSourceController& )
// {
// }

BlankRecordSourceController::~BlankRecordSourceController()
{
   delete &m_makeRecords;
   delete m_stops;
}

//
// assignment operators
//
// const BlankRecordSourceController& BlankRecordSourceController::operator=( const BlankRecordSourceController& )
// {
// }

//
// member functions
//
DataSourceController::SyncStatus
BlankRecordSourceController::synchronizeSource( const SyncValue& iSyncTo )
{
   if( iSyncTo != currentSyncValue() ){
      SyncValue newSyncValue;
      DataSourceController::SyncStatus status = 
	 m_stops->synchronizeTo( iSyncTo, newSyncValue );
      
      if( DataSourceController::kSyncFailedToSync == status ){
	 //We are trying to get records before there are any records
	 setCurrentStop( Stream::kNone );
	 setSyncValue( iSyncTo );
	 
	 //Tell the ProxyProvider that the data is bad
	 clearRecords();
	 
	 //reset status to ok
	 status = DataSourceController::kSyncNoError;
      } else {
	 
	 if( m_presentRecordSyncValue != newSyncValue ) {
	    
	    //Find the highest priority Stream we are reading
#if defined(NO_STL_TEMPLATED_MEMBER_FUNCTIONS_BUG)
	    STL_MULTISET_COMP(Stream::Type, StreamPriorityGreater ) 
	       orderedStreams;
	    //fill the stream
	    Stream::Set::const_iterator itEnd = recordsToRetrieve().end();
	    for( Stream::Set::const_iterator itStream = 
		    recordsToRetrieve().begin();
		 itStream != itEnd;
		 ++itStream ) {
	       orderedStreams.insert( *itStream );
	    }
#else 
	    STL_MULTISET_COMP(Stream::Type, StreamPriorityGreater ) 
	       orderedStreams( recordsToRetrieve().begin(),
			       recordsToRetrieve().end() );
#endif	  
	    setCurrentStop( *(orderedStreams.begin()) );
	    
	    //All records can be used
	    readRecords( newSyncValue );
	 }
	 
	 //update sync value
	 setSyncValue( iSyncTo );
      }
      return status;

   }

   return kSyncNoError;
}

DataSourceController::SearchStatus
BlankRecordSourceController::findNextRecord(SyncValue& oSyncValueOfNextRecord,
			      Stream::Type& oRecordTypeOfNextRecord )
{

   if( m_presentRecordSyncValue != SyncValue::kUndefined  &&
       m_presentRecordSyncValue == currentSyncValue() ) {
      
      //We have already read at least one Record from this SyncValue
      //Now we have to work our way down the stream priorities
      // for the active streams
      
      //organize the streams by priority
      STL_MULTISET_COMP(Stream::Type, StreamPriorityGreater ) 
#if defined(NO_STL_TEMPLATED_MEMBER_FUNCTIONS_BUG)
         prioritizedStreams;
      //fill the stream
      Stream::Set::const_iterator itEnd = activeStreams().end();
      for( Stream::Set::const_iterator itActiveStream = 
	      activeStreams().begin();
	   itActiveStream != itEnd;
	   ++itActiveStream ) {
	 prioritizedStreams.insert( *itActiveStream );
      }
#else 
      prioritizedStreams( activeStreams().begin(),
			  activeStreams().end() );
#endif	  
      
      //Check to see if the last Record we stopped on is from the
      // lowest priority Stream.  If not, then we continue down the
      // priority list.  If so, then need to go to next Sync Value
      if( currentStop() != *(prioritizedStreams.rbegin()) ) {
	 //get the first element that has the same priority as the currentStop
	 STL_MULTISET_COMP(Stream::Type, StreamPriorityGreater)::iterator
	    itStream = prioritizedStreams.lower_bound( currentStop() );

	 if( activeStreams().contains( currentStop() ) ){
	    //advance the iterator until we find our current stop
	    while( currentStop() != *itStream ){
	       ++itStream;
	    }
	    //need to go to the next stop
	    ++itStream;
	 }
      
	 if( itStream != prioritizedStreams.end() ){
	    oSyncValueOfNextRecord = m_presentRecordSyncValue;
	    oRecordTypeOfNextRecord = *itStream ;
	    return kSearchNoError;
	 } else {
	    //This should not be possible
	    return kSearchUnknownError;
	 }
      }
   }

   //we are at a point where we know we have to advance to the next
   // SyncValue
   
   DataSourceController::SearchStatus status =
      m_stops->findNext( m_presentRecordSyncValue, oSyncValueOfNextRecord );
      
   if( kSearchEndOfSource == status ) {
      oRecordTypeOfNextRecord = Stream::kNone ;
   } else {
      //Find the highest priority activeStream
      
      STL_MULTISET_COMP(Stream::Type, StreamPriorityGreater ) 
#if defined(NO_STL_TEMPLATED_MEMBER_FUNCTIONS_BUG)
	 prioritizedStreams;
      //fill the stream
      Stream::Set::const_iterator itEnd = activeStreams().end();
      for( Stream::Set::const_iterator itStream = 
	      activeStreams().begin();
	   itStream != itEnd;
	   ++itStream ) {
	 prioritizedStreams.insert( *itStream );
      }
#else 
      prioritizedStreams( activeStreams().begin(),
			  activeStreams().end() );
#endif
      
      oRecordTypeOfNextRecord =  *(prioritizedStreams.begin()) ;
   }

   return status;
}

DataSourceController::SearchStatus 
BlankRecordSourceController::gotoNextRecord( void )
{
   //Make find next record do all the work
   SyncValue recordSyncValue;
   Stream::Type recordStream;
   SearchStatus status = findNextRecord( recordSyncValue,
					 recordStream );

   if( kSearchEndOfSource != status ){
      //If we are not at the end of the source, set the values
      setSyncValue( recordSyncValue );
      setCurrentStop( recordStream );

      //Since all of the Records have the same sync value, if we read one
      //  we read them all
      //   readRecords() also makes sure that once a record is read, it
      //   will not be reread.

      readRecords( recordSyncValue );

   }
   return status;
}

void 
BlankRecordSourceController::implementSetForcedSequentialAccess( DABoolean )
{}

void
BlankRecordSourceController::readRecords( const SyncValue& iSyncValue )
{
   //First make sure that the records haven't already been read
   if( m_presentRecordSyncValue != iSyncValue ){
      //Tell the ProxyProvider that the data is good
      Stream::Set::const_iterator itEnd = recordsToRetrieve().end();
      for( Stream::Set::const_iterator itStream = 
	      recordsToRetrieve().begin();
	   itStream != itEnd;
	   ++itStream ) 
      {
	 proxyDeliverer()->reset( *itStream, iSyncValue );
      }
      m_presentRecordSyncValue = iSyncValue;
   }
}

void
BlankRecordSourceController::clearRecords()
{
   if( m_presentRecordSyncValue != SyncValue::kUndefined ){
      //Tell the ProxyProvider that the data is bad
      Stream::Set::const_iterator itEnd = recordsToRetrieve().end();
      for( Stream::Set::const_iterator itStream = recordsToRetrieve().begin();
	   itStream != itEnd;
	   ++itStream ) {
	 proxyDeliverer()->reset( *itStream, SyncValue::kUndefined );
      }
      //Remember that we have flushed the records
      m_presentRecordSyncValue = SyncValue::kUndefined;
   }
}
//
// const member functions
//

DABoolean 
BlankRecordSourceController::canRandomAccess( void ) const
{
   return true;
}

string 
BlankRecordSourceController::dataSourceID( void ) const 
{
   return m_name;
}

string 
BlankRecordSourceController::parameters( void ) const
{
   //Build a string containing all the names of the Streams
   return buildParameters( recordsToRetrieve() );
}

ProxyDeliverer* 
BlankRecordSourceController::createProxyDeliverer( void ) const 
{
   return new BlankRecordProxyDeliverer( m_makeRecords );
}
//
// static member functions
//

string
BlankRecordSourceController::buildParameters( const Stream::Set& iStreams )
{
   //I'll figure out how to do this some other time
   return string();
}
