// -*- C++ -*-
//
// Package:     DataDelivery
// Module:      FrameDeliverer
// 
// Description: Handles the retrieval of data from multiple sources.
//
// Implimentation:
//     There are three booleans which govern sequential access
//     m_forcedSequentialAccess
//             true:  if user sets to true
//             false: if user sets to false
//     m_mustSequentiallyAccess
//             true:  if m_forcedSequentialAccess == true
//                       OR
//                    if one of the DataSources can only handle sequential
//                      access
//             false: if m_forcedSequentialAccess == false
//                       AND
//                    if all DataSources can random access
//     m_isSequentiallyAccessing
//             true:  if m_mustSequentiallyAccess == true
//                       OR
//                    if we know that the Records from the Active Streams 
//                       just happen to be in sequential order
//             false: if m_mustSequentiallyAccess == false
//                       AND
//                    if we don't know if the Records from the Active Steams
//                       just happen to be in sequential order  OR
//                       we know that they are in Random order
//                      
//
// Author:      Chris D. Jones
// Created:     Sun Mar 16 16:26:55 EST 1997
// $Id: FrameDeliverer.cc,v 1.29 2000/01/22 02:36:57 cdj Exp $
//
// Revision history
//
// $Log: FrameDeliverer.cc,v $
// Revision 1.29  2000/01/22 02:36:57  cdj
// FrameDeliverer now checks to see if it has the Provider before removing from a RecordProvider
//
// Revision 1.28  1999/04/09 18:33:55  cdj
// bug fix: the case when multiple active sources where all sources were
//          random accessable did not work correctly
//
// Revision 1.27  1998/02/03 21:28:10  mkl
// switch over to STLUtility library
//
// Revision 1.26  1997/11/19 15:27:31  sjp
// Modifier to use FrameProvider class
//
// Revision 1.25  1997/09/18 21:07:10  cdj
// changed Boolean to DABoolean
//
// Revision 1.24  1997/09/03 20:06:33  sjp
// Uses CPP macros for STL containers
//
// Revision 1.23  1997/09/01 15:35:20  sjp
// Changed report include to be in Experiment
//
// Revision 1.22  1997/08/27 03:39:27  sjp
// Updated to new name for bug flags
//
// Revision 1.21  1997/08/14 11:43:06  sjp
// Mods to run under CW Pro 1
//
// Revision 1.20  1997/08/06 16:17:38  sjp
// Changed to use ProxyDeliverer
//
// Revision 1.19  1997/08/06 15:56:32  sjp
// Modified to use ProxyProviders
//
// Revision 1.18  1997/07/28 18:02:53  sjp
// Fixed to work under cxx 5.6
//
// Revision 1.17  1997/07/24 19:01:12  cdj
// Added resynchronize() method, which is needed when you add a new source
//  to an already running job.
//
// Revision 1.16  1997/07/09 18:00:42  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.15  1997/07/02 19:28:52  sjp
// Changed `list' to be `vector'
// Move FindNextRecordInfo and SortFindNextRecordInfo into own files.
//
// Revision 1.14  1997/07/01 19:01:52  sjp
// Put in work around bug11_deccxx
//
// Revision 1.13  1997/06/29 20:09:16  cdj
// 1) Now handles the case when multiple Records have the same SyncValue
// 2)  Moved duplicate error handling code in gotoNextStop to a new routine
//
// Revision 1.12  1997/06/03 17:31:21  sjp
// Modified to handle DataProviders
//
// Revision 1.11  1997/05/07 19:00:24  sjp
// Fixed less<Stream::Type> so can be used as usual
//
// Revision 1.10  1997/05/02 20:16:49  cdj
// 1) Made naming more consistant
//    a) changed Error to Status
//    b) changed ActiveStreams to ActiveSources
//    c) changed DataSource to Source
// 2) Changed nextStop(...) to gotoNextStop(...)
// 3) Methods return status instead of using an argument
// 4) added sources() method
//
// Revision 1.9  1997/04/29 20:05:49  cdj
// replaced less< Stream::Type> with Stream::TypeLess
//
// Revision 1.8  1997/04/21 19:21:51  cdj
// Added several new member functions to determine the state of FrameDeliverer
// 1)statusOfSources() : returns list of the status of all sources
// 2)activeSources() : returns a list of all the active sources
// Replaced DataSourceBinder with DataSourceDescriptor in all methods except
// addDataSource(...).
//
// Revision 1.7  1997/04/17 15:56:33  mkl
// fix for missing multimap --> ToolBox/Include/bug9_g++.h.
//
// Revision 1.6  1997/04/16 19:59:51  cdj
// added code to allow multiple active sources
//
// Revision 1.5  1997/04/10 01:12:45  sjp
// Added assert include file as it is required
//
// Revision 1.4  1997/04/01 21:04:14  cdj
// When removing a DataSourceController that has an active stream, the
// DataSourceController is now removed from the active stream list
//
// Revision 1.3  1997/04/01 16:03:07  sjp
// use new function names. Correct when SyncValue is set
//
// Revision 1.2  1997/03/25 23:22:04  cdj
// Added code to manage RecordDeliverers and Frame
//
// Revision 1.1  1997/03/20 22:51:47  cdj
// First submission
// WARNING: Can only handle one Active source.  Does NOT produce a Frame.
//

#include "Experiment/Experiment.h"
// system include files
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <set>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "DataHandler/RecordProvider.h"
#include "DataDelivery/DataSourceBinder.h"
#include "DataDelivery/DataSourceController.h"
#include "DataDelivery/ProxyDeliverer.h"
#include "DataDelivery/FrameDeliverer.h"

#include "DataHandler/StreamPriorityGreater.h"

//The following classes are used by nextStop(...)
#include "DataDelivery/FindNextRecordInfo.h"
#include "DataDelivery/SortFindNextRecordInfo.h"


// STL classes
#include <algorithm>
#include <map>
#include <map> // to define CPP macros
#include <vector>
#include <set> // to define CPP macros

//
// constants, enums and typedefs
//

typedef _framedeliverer_sourcecontrollers_ DataSourceControllers;
typedef _framedeliverer_sourcesstatus_ SourcesStatus ;
typedef _framedeliverer_keyedsourcecontrollers_ StreamPriorities ;

typedef std::multimap< SyncValue, FindNextRecordInfo >
   SyncValuesOfNextRecords ;
typedef std::multiset< FindNextRecordInfo , SortFindNextRecordInfo >
   NextRecordSet ;

//
// local functions
//

static
FrameDeliverer::NextStopStatus
convertSearchStatusToNextStopStatus( const DataSourceController::SearchStatus&
				     iSearchStatus )
{
   FrameDeliverer::NextStopStatus oStatus;
   switch( iSearchStatus ){
      case DataSourceController::kSearchNoError:
        oStatus = FrameDeliverer::kNextStopNoError;
	break;
      case DataSourceController::kSearchEndOfSource:
        oStatus = FrameDeliverer::kNextStopReachedEndOfAnActiveSource;
	break;
      case DataSourceController::kSearchProblemWithSource:
        oStatus = FrameDeliverer::kNextStopProblemWithASource;
	break;
      case DataSourceController::kSearchUnknownError:
        oStatus = FrameDeliverer::kNextStopUnknownError;
	break;
      default:
        oStatus = FrameDeliverer::kNextStopUnknownError;
	break;
   }
   return oStatus;
}

static
FrameDeliverer::SourceStatus
convertSearchStatusToSourceStatus( const DataSourceController::SearchStatus&
				     iSearchStatus )
{
   FrameDeliverer::SourceStatus oStatus;
   switch( iSearchStatus ){
      case DataSourceController::kSearchNoError:
        oStatus = FrameDeliverer::kSourceNoError;
	break;
      case DataSourceController::kSearchEndOfSource:
        oStatus = FrameDeliverer::kSourceReachedEnd;
	break;
      case DataSourceController::kSearchProblemWithSource:
        oStatus = FrameDeliverer::kSourceProblemWithSource;
	break;
      case DataSourceController::kSearchUnknownError:
        oStatus = FrameDeliverer::kSourceUnknownError;
	break;
      default:
        oStatus = FrameDeliverer::kSourceUnknownError;
	break;
   }
   return oStatus;
}

static
FrameDeliverer::SourceStatus
convertSyncStatusToSourceStatus( const DataSourceController::SyncStatus&
				     iSyncStatus )
{
   FrameDeliverer::SourceStatus oStatus;
   switch( iSyncStatus ){
      case DataSourceController::kSyncNoError:
        oStatus = FrameDeliverer::kSourceNoError;
	break;
      case DataSourceController::kSyncWarningAtEndOfSource:
        oStatus = FrameDeliverer::kSourceReachedEnd;
	break;
      case DataSourceController::kSyncFailedToSync:
        oStatus = FrameDeliverer::kSourceFailedToSync;
	break;
      case DataSourceController::kSyncProblemWithSource:
        oStatus = FrameDeliverer::kSourceProblemWithSource;
	break;
      case DataSourceController::kSyncUnknownError:
        oStatus = FrameDeliverer::kSourceUnknownError;
	break;
      default:
        oStatus = FrameDeliverer::kSourceUnknownError;
	break;
   }
   return oStatus;
}

static
FrameDeliverer::NextStopStatus
convertSyncStatusToNextStopStatus( DataSourceController::SyncStatus iSyncStatus)
{
   FrameDeliverer::NextStopStatus oStatus;
   //Assign the proper status code
   switch( iSyncStatus ) {
      case DataSourceController::kSyncNoError:
      oStatus = FrameDeliverer::kNextStopNoError;
      break;
      case DataSourceController::kSyncWarningAtEndOfSource:
      oStatus = FrameDeliverer::kNextStopReachedEndOfAPassiveSource;
      break;
      case DataSourceController::kSyncFailedToSync:
      oStatus = FrameDeliverer::kNextStopFailedToSyncAllSources;
      break;
      case DataSourceController::kSyncUnknownError:
      oStatus = FrameDeliverer::kNextStopUnknownError;
      break;
      default:
      oStatus = FrameDeliverer::kNextStopUnknownError;
      break;
   }
   return oStatus;
}

//
// static data member definitions
//

//
// constructors and destructor
//
FrameDeliverer::FrameDeliverer( void ) :
   m_sourcesStatus( *(new SourcesStatus ) ),
   m_activeSourcesWithRecordsAtCurrentSyncValue( *(new StreamPriorities ) ) ,
   m_dataSourceControllers( *(new DataSourceControllers)),
   m_activeSources( *(new DataSourceControllers ) ),
   m_isValidStop(false),
   m_currentSyncValue(0,0,0),
   m_currentStop(Stream::kNone),
   m_forcedSequentialAccess(false),
   m_mustSequentiallyAccess(false),
   m_isSequentiallyAccessing(false),
   m_severalActiveSourcesWithRecordsAtCurrentSyncValue(false)
{
}

// FrameDeliverer::FrameDeliverer( const FrameDeliverer& )
// {
// }

FrameDeliverer::~FrameDeliverer()
{
   //delete the DataSourceControllers
   removeAllActiveSources();
   DataSourceControllers::iterator itDSCEnd = m_dataSourceControllers.end();
   for( DataSourceControllers::iterator itController =
	                                 m_dataSourceControllers.begin();
	itController != itDSCEnd;
	++itController){
      delete (*itController);
   }

   //Get rid of containers
   delete &m_dataSourceControllers;
   delete &m_activeSources;
   delete &m_sourcesStatus;
   delete &m_activeSourcesWithRecordsAtCurrentSyncValue;
}

//
// assignment operators
//
// const FrameDeliverer& FrameDeliverer::operator=( const FrameDeliverer& )
// {
// }

//
// member functions
//
FrameDeliverer::AddActiveSourceStatus
FrameDeliverer::addActiveSource( const DataSourceDescriptor& iActiveSource)
{
   FrameDeliverer::AddActiveSourceStatus oError = kAddActiveSourceNoError;

   //See if we have this source
   DataSourceController* controller(0);

   DataSourceControllers::iterator itController = 
      findDataSourceController( iActiveSource );

   if( itController != m_dataSourceControllers.end() ){
      controller = *itController;
   }
   if ( 0 == controller ){
      oError = kAddActiveSourceDataSourceNotPresent;
   } else {
      if( ! (*controller).setActiveStreams( iActiveSource.boundStreams() ) ){
	 oError = kAddActiveSourceInvalidStreamsForSource;
      } else {
	 //See if we already have this in our list of active streams
	 DABoolean foundSource(false);
	 DataSourceControllers::iterator itASEnd = m_activeSources.end();
	 for( DataSourceControllers::iterator itSource = m_activeSources.begin();
	      itSource != itASEnd;
	      ++itSource ){
	    if( controller == *itSource ){
	       foundSource = true;
	       break;
	    }
	 }
	 if( !foundSource ){
	    //Add it to the list
	    m_activeSources.push_back( controller );
	 }
      }
   }
   //Set sequential access if necessary
   if(mustSequentiallyAccess()){
      (*controller).setForcedSequentialAccess( true );
   }

   updateIsSequentiallyAccessing();
   return oError;
}

void
FrameDeliverer::removeAllActiveSources( void )
{
   m_activeSources.erase( m_activeSources.begin(),
			     m_activeSources.end() );

   //No active sources so this can't be true
   m_severalActiveSourcesWithRecordsAtCurrentSyncValue=false;

   updateIsSequentiallyAccessing();
}

FrameDeliverer::AddSourceStatus
FrameDeliverer::addSource( const DataSourceBinder& iAddSourceBinder)
{
   FrameDeliverer::AddSourceStatus oError = kAddSourceNoError;

   //See if we already have this source and if so remove it
   DataSourceControllers::iterator itController = 
      findDataSourceController( iAddSourceBinder );
   if( itController != m_dataSourceControllers.end() ){
      removeSource( iAddSourceBinder);
   }
   
   DataSourceController* controller = iAddSourceBinder.
                                        createDataSourceController();
   if( 0 == controller){
      oError = kAddSourceBinderFailedToMakeController;
   } else {
      // See if there was a problem initializing the source
      if( DataSourceController::kInitNoError != 
	  (*controller).initializationStatus() ){
	 switch( (*controller).initializationStatus() ){
	    case DataSourceController::kInitInvalidStopsForSource:
	      oError = kAddSourceInvalidStopsForSource;
	      break;
	    case DataSourceController::kInitSourceInaccessible:
	      oError = kAddSourceSourceInaccessible;
	      break;
	    case DataSourceController::kInitBadParameters:
	      oError = kAddSourceBadParameters;
	      break;
	    case DataSourceController::kInitUnknownError:
	      oError = kAddSourceUnknownError;
	      break;
	    default:
	      oError = kAddSourceUnknownError;
	      break;
	 }
      } else {
	 //Source is fine
	 m_dataSourceControllers.push_back( controller );
	 m_sourcesStatus.insert( 
	    SourcesStatus::value_type( controller,
				       FrameDeliverer::kSourceNoError));
	 
	 //Inform the necessary RecordProviders
	 addProvider( *(*controller).proxyDeliverer() ,
		      (*controller).recordsToRetrieve() ) ;

	 updateMustSequentiallyAccess();
      }
	    
   }
   return oError;
}

FrameDeliverer::AddProviderStatus
FrameDeliverer::addProvider( ProxyProvider& aProvider )
{
   return ( addProvider( aProvider ,
			 aProvider.supplies() ) ) ;
}

FrameDeliverer::AddProviderStatus
FrameDeliverer::addProvider( ProxyProvider& aProvider ,
			     const Stream::Set& aStreamsToAdd )
{
#if defined(CXX_TYPEDEFED_BEFORE_DEFINITION_BUG)
   StreamSet::const_iterator itEnd = aStreamsToAdd.end();
   for(StreamSet::const_iterator itStream = aStreamsToAdd.begin();
#else
   Stream::Set::const_iterator itEnd = aStreamsToAdd.end();
   for(Stream::Set::const_iterator itStream = aStreamsToAdd.begin();
#endif
       itStream != itEnd;
       ++itStream ){
      if( ! contains( *itStream ) ) {
	 //Need to make a new RecordProvider
	 RecordProvider* recProvider = new RecordProvider( *itStream );
	 assert( 0 != recProvider);
	 insert( recProvider ) ;
      }
      //Give RecordProvider the info
      
      recordProvider( *itStream ).add( aProvider );
      
   } //for(Stream::Set ... )
   return ( kAddProviderNoError ) ;
}
   
FrameDeliverer::RemoveSourceStatus
FrameDeliverer::removeSource( const DataSourceDescriptor& iCloseSourceBinder)
{
   FrameDeliverer::RemoveSourceStatus oError = kRemoveSourceNoError;

   //See if we already have this source and if so remove it
   DataSourceControllers::iterator itController = 
      findDataSourceController( iCloseSourceBinder );

   if( itController == m_dataSourceControllers.end() ){
      //No such controller
      oError = kRemoveSourceNoMatchingSource;
   } else {
      //See if Source has any active streams, if so, remove it from
      //  active stream list
      {
	 DataSourceControllers::iterator itASEnd = m_activeSources.end();
	 DataSourceControllers::iterator itFound = find(m_activeSources.begin(),
						itASEnd,
						*itController );	 
	 if( itFound != itASEnd ){
	    m_activeSources.erase( itFound );

	    //take care of a special goto next Stop case
	    if(m_severalActiveSourcesWithRecordsAtCurrentSyncValue){
	       StreamPriorities::iterator itSPMEnd =
		  m_activeSourcesWithRecordsAtCurrentSyncValue.end();
	       for( StreamPriorities::iterator itLoop =
		       m_activeSourcesWithRecordsAtCurrentSyncValue.begin();
		    itLoop != itSPMEnd;
		    ++itLoop){
		  if( *itController == (*itLoop).second ){
		     m_severalActiveSourcesWithRecordsAtCurrentSyncValue=false;
		     break;
		  }
	       }
	    }
	 }
      } //Taken care of Active Streams

      //Remove it from each RecordProvider

      DataSourceController* controller( *itController );
      removeProvider( *((*controller).proxyDeliverer()) ,
		      (*controller).recordsToRetrieve() ) ;

      //Remove it from the status list
      m_sourcesStatus.erase( *itController );
      //Now get rid of controller
      m_dataSourceControllers.erase( itController );
      delete controller; 
      updateMustSequentiallyAccess();
   }
   return oError;
}

FrameDeliverer::RemoveProviderStatus
FrameDeliverer::removeProvider( ProxyProvider& aProvider )
{
   return ( removeProvider( aProvider ,
			    aProvider.supplies() ) ) ;
}

FrameDeliverer::RemoveProviderStatus
FrameDeliverer::removeProvider( ProxyProvider& aProvider ,
				const Stream::Set& aStreamsToRemove )
{
   RemoveProviderStatus returnValue = kRemoveProviderUnknownError;

#if defined(CXX_TYPEDEFED_BEFORE_DEFINITION_BUG)
   StreamSet::const_iterator itEnd = aStreamsToRemove.end();
   for(StreamSet::const_iterator itStream = aStreamsToRemove.begin();
#else
   Stream::Set::const_iterator itEnd = aStreamsToRemove.end();
   for(Stream::Set::const_iterator itStream = aStreamsToRemove.begin();
#endif
       itStream != itEnd;
       ++itStream ){
      if ( contains( *itStream ) ) {
	 RecordProvider& recProvider = recordProvider( *itStream ) ;	 

	 if( recProvider.contains( aProvider ) ) {
	    returnValue = kRemoveProviderNoError;
	    //Tell RecordProvider to remove its reference
	    recProvider.remove( aProvider );
	 
	    //If No more Sources in RecordProvider, delete it
	    if( recProvider.isEmpty() ){
	       erase( *itStream );
	    }
	 }
      }
   } //for(Stream::Set ... )
   return returnValue ;
}

void
FrameDeliverer::removeAllSources( void )
{
   //Get rid of all RecordProviders
   eraseAll() ;

   //Erase the active sub stream list
   m_activeSources.erase( m_activeSources.begin(),
			     m_activeSources.end() );

   //Erase the status list
   m_sourcesStatus.erase( m_sourcesStatus.begin(),
			  m_sourcesStatus.end() );

   //Delete the Controllers
   DataSourceControllers::iterator itDSCEnd = m_dataSourceControllers.end();
   for(DataSourceControllers::iterator itController =
	  m_dataSourceControllers.begin();
       itController != itDSCEnd;
       ++itController ){
      delete *itController;
   }

   m_dataSourceControllers.erase( m_dataSourceControllers.begin(),
				  m_dataSourceControllers.end());

   //No sources so this can't be true
   m_severalActiveSourcesWithRecordsAtCurrentSyncValue=false;

   updateMustSequentiallyAccess();

}

void
FrameDeliverer::setForcedSequentialAccess( DABoolean iFlag )
{
   m_forcedSequentialAccess = iFlag;
   updateMustSequentiallyAccess();
}

FrameDeliverer::NextStopStatus
FrameDeliverer::gotoNextStop( void )
{
   FrameDeliverer::NextStopStatus oStatus = kNextStopNoError;

   m_isValidStop = true;

   //Clear the Frame

   if( 0 == m_activeSources.size() ){
      //This is an error
      invalidateStop() ;
      return kNextStopNoActiveStreams;
   }

   //Handle a special case where in the last call to gotoNextStop we had
   // several Active Sources which had Records for the Current SyncValue
   if( m_severalActiveSourcesWithRecordsAtCurrentSyncValue ){
      return gotoNextRecordAtCurrentSyncValue();
   }

   //First use Active Streams to find SyncValue of next stop
   
   if( 1 == m_activeSources.size() ){
      //With 1 active sub stream I can use gotoNextRecord()
      
      DataSourceController* controller = m_activeSources.back();
      
      //Goto next record until
      //  1) We find a record in one of the Active streams
      //  2) We reach the end of the source
      DABoolean isDone( false );
      DABoolean sourceIsFine(true);
      DataSourceController::SearchStatus searchStatus;
      do {
	 searchStatus = (*controller).gotoNextRecord();
	 
	 DABoolean isNewRecordFromActiveStream( 
	    (*controller).activeStreams().contains( 
	       (*controller).currentStop() ) );
	 
	 sourceIsFine=(searchStatus == DataSourceController::kSearchNoError );
	 
	 //Keep looping until
	 //  The New record is from an Active Stream OR
	 //  we have a problem with the source
	 isDone = (isNewRecordFromActiveStream ) || (! sourceIsFine ) ;
      } while( ! isDone );
      //If problem with source, stop now
      if( !sourceIsFine ) {
	 return cleanupAfterSearchError( controller, searchStatus );
      } 
      
      m_currentStop = (*controller).currentStop();
      m_currentSyncValue = (*controller).currentSyncValue();
   } else {
      //With multiple active sources, we need to choose which of the
      //  nextRecords we should stop on
      
      //Algorithm:
      //  1) find the active Record with the smallest SyncValue
      //  2) See if more than one sources has a Record with that SyncValue
      //  3) if yes 
      //      a) pick the one with the highest stream priority to be the 
      //         stop 
      //      b) set a flag to remember to loop through these Records on 
      //         the next call to nextStop
      //  4) synchronize all sources to the smallest SyncValue
      
      
      // Need to find the active Record with the smallest SyncValue
      //    
      //Algorithm:
      //  1) ask each active source to find their next record
      //  2) tell the active source who has the next record with the 
      //     smallest SyncValue or highest priority to goto that Record
      //  3) if
      //     a) that Record is from an active stream, then this is our
      //        SyncValue
      //     b) that Record is NOT from an active stream, have that
      //        controller find its next record and then goto 2)
      //    
      
      // Keep a list of active data sources and the info associated 
      //  with their next Record
      NextRecordSet nextRecordSet;
      
      //Loop over the active streams and fill in the above set
      
      DataSourceController* controller(0);
      SyncValue tempSyncValue;
#if defined(TEMPLATE_PARAMETERS_BREAK_TYEPDEFS_BUG)
      Stream::Type nextRecordType ;
      nextRecordType = Stream::kNone ;
#else
      Stream::Type nextRecordType(Stream::kNone);
#endif /* TEMPLATE_PARAMETERS_BREAK_TYEPDEFS_BUG */
      DABoolean isNewRecordFromActiveStream(false);
      DataSourceController::SearchStatus searchStatus;


      DataSourceControllers::iterator itEnd = m_activeSources.end();
      for( DataSourceControllers::iterator itSource = 
	      m_activeSources.begin();
	   itSource != itEnd;
	   ++itSource){
	 
	 controller = (*itSource);
	 const Stream::Set& activeStreams= (*controller).activeStreams();
	 isNewRecordFromActiveStream = false;
	 
	 if( DataSourceController::kSearchNoError == 
	     (searchStatus = (*controller).findNextRecord( tempSyncValue,
							   nextRecordType ))){
	    isNewRecordFromActiveStream = 
	       activeStreams.contains( nextRecordType );
	    nextRecordSet.insert(
	       FindNextRecordInfo( controller,
				   tempSyncValue,
				   nextRecordType,
				   isNewRecordFromActiveStream));
	    
	 } else {
	    if(DataSourceController::kSearchEndOfSource == searchStatus){
	       //Don't add this to the list, but do update source's status
	       setSourceStatus( controller, searchStatus );

	    } else {
	       // An error occured
	       return cleanupAfterSearchError( controller, searchStatus );
	    }
	 }
      }
      
      //If list is empty than all sources are at their end
      if( nextRecordSet.empty() ){
	 return cleanupAfterSearchError( controller, searchStatus );
      }

      //First determine what SyncValue we should stop at
      
      DABoolean isDone(false);
      while( !isDone ){
	 //Get record info from record with smallest sync value
	 const FindNextRecordInfo& recordInfo( 
	    *(nextRecordSet.begin())) ;
	 
	 //Make the source go to that Record
	 controller= recordInfo.controller;
	 
	 if(DataSourceController::kSearchNoError != 
	    ( searchStatus = (*controller).gotoNextRecord()) ){
	    
	    //Assign the correct status code
	    return cleanupAfterSearchError( controller, searchStatus );
	 }
	 if( !recordInfo.recordIsFromActiveStream ) {

	    //find the next record in this source
	    if( DataSourceController::kSearchNoError !=
		(searchStatus = (*controller).findNextRecord( tempSyncValue,
							    nextRecordType))){
	       if( DataSourceController::kSearchEndOfSource !=
		   searchStatus ){
		  //An error occured
		  return cleanupAfterSearchError( controller, searchStatus );
	       } else {
		  //Remove RecordInfo from map
		  nextRecordSet.erase( nextRecordSet.begin() );

		  //Record the source's status
		  setSourceStatus( controller, searchStatus );

		  //If the list is now empty, than all active sources are
		  // at their end
		  if( nextRecordSet.empty() ){
		     return cleanupAfterSearchError( controller, 
						     searchStatus );
		  }
	       }
	    } else { //found next Record

	       //Remove RecordInfo from map
	       nextRecordSet.erase( nextRecordSet.begin() );
	       	       
	       const Stream::Set& activeStreams=(*controller).activeStreams();
	       DABoolean isNewRecordFromActiveStream =  
		  activeStreams.contains(nextRecordType );
	    
	       //Insert the new Record's Info into the map
	       nextRecordSet.insert( 
		  FindNextRecordInfo( controller,
				      tempSyncValue,
				      nextRecordType,
				      isNewRecordFromActiveStream));
	    }// find next record
	 } else {//Record is from Active Stream
	    
	    //This is the SyncValue we want to stop at
	    m_currentSyncValue = (*controller).currentSyncValue();
	    isDone = true;
	    
	 }
      } //while(!isDone)
      
      // Need to find the active Record to stop on
      //    
      //There are three special cases
      //  1) Sequentially Accessing sources and only one source has a
      //     Record at that SyncValue
      //  2) Sequentially Accessing sources and several sources have a
      //     Record at that SyncValue (NOTE: some of these Streams maybe
      //     passive)
      //  3) Not sequentially Accessing sources
      
      
      if(isSequentiallyAccessing() ){
	 //This source is guaranteed to have the Record with the
	 // smallest SyncValue and highest priority
	 m_currentStop = (*controller).currentStop();
	 
	 //Is there more than one source with a record at 
	 // this syncvalue?
	 NextRecordSet::const_iterator firstRecord(
	    nextRecordSet.begin() );
	 NextRecordSet::const_iterator secondRecord(firstRecord);
	 ++secondRecord;
	 //Note: because we trimmed the list there may be only one
	 // Active source in nextRecordSet
	 if( (secondRecord != nextRecordSet.end()) &&
	     (*firstRecord).syncValue == (*secondRecord).syncValue ){
	    
	    //Add first source to list of sources with records at
	    // this syncvalue
	    m_activeSourcesWithRecordsAtCurrentSyncValue.erase(
	       m_activeSourcesWithRecordsAtCurrentSyncValue.begin(),
	       m_activeSourcesWithRecordsAtCurrentSyncValue.end());
	    
	    m_activeSourcesWithRecordsAtCurrentSyncValue.insert(
	       std::pair<const Stream::Type ,
	       DataSourceController*>(
		  (*firstRecord).stream,
		  (*firstRecord).controller));
	    
	    DABoolean checkedAllSources(false);
	    DABoolean advanceToNextSource(false);
	    
	    NextRecordSet::const_iterator itNextRecordEnd =
	       nextRecordSet.end();
	    NextRecordSet::const_iterator itNextRecord(secondRecord);
	    DABoolean isRecordFromActiveStream = 
	       (*itNextRecord).recordIsFromActiveStream;
	    controller = (*itNextRecord).controller;
	    nextRecordType = (*itNextRecord).stream;
	    
	    while(!checkedAllSources){
	       //goto that Record
	       if(DataSourceController::kSearchNoError != 
		  ( searchStatus = 
		    (*controller).
		    gotoNextRecord()) ){
		  
		  //Assign the correct status code
		  return cleanupAfterSearchError( controller, searchStatus );
	       }
	       
	       if( !isRecordFromActiveStream ){
		  //Peek at the next record
		  if( DataSourceController::kSearchNoError == 
		      (searchStatus = (*controller).findNextRecord( 
			 tempSyncValue,
			 nextRecordType ))){

		     const Stream::Set& activeStreams=
			(*controller).activeStreams();

		     isNewRecordFromActiveStream = 
			activeStreams.contains( nextRecordType );
		     
		     //If next Record doesn't have same SyncValue 
		     //  then try next source
		     if( tempSyncValue != m_currentSyncValue ) {
			advanceToNextSource=true;
		     }
		     
		  } else { //A special case occured for findNextRecord
		     if( DataSourceController::kSearchEndOfSource !=
			 searchStatus ){
			// An error occured
			return cleanupAfterSearchError( controller, 
							searchStatus );
		     } else { //At end of source
			//This is not fatal
			advanceToNextSource=true;

			//Record the source's status
			setSourceStatus( controller, searchStatus );
		     }
		  }
		  
	       } else {
		  //The Record is from an Active Stream
		  
		  //add to list
		  m_activeSourcesWithRecordsAtCurrentSyncValue.insert(
		     std::pair<const Stream::Type ,
		     DataSourceController*>(nextRecordType,controller));
		  
		  advanceToNextSource=true;
	       }//if( !isRecordFromActiveStream )
	       if(advanceToNextSource){
		  advanceToNextSource = false;
		  
		  ++itNextRecord;
		  
		  //Are we at the end?
		  if( itNextRecord != itNextRecordEnd ){
		     isNewRecordFromActiveStream = 
			(*itNextRecord).recordIsFromActiveStream;
		     controller = (*itNextRecord).controller;
		     nextRecordType = (*itNextRecord).stream;
		  } else {
		     checkedAllSources = true;
		  }
	       }
	    }// while(!checkedAllSources)
	    //Now we have a list of all active sources with Records
	    // at this SyncValue
	    
	    //Is there is more than one source in the list we must
	    // put FrameDeliverer into a special mode
	    if( 1 != 
		m_activeSourcesWithRecordsAtCurrentSyncValue.size() ){
	       m_severalActiveSourcesWithRecordsAtCurrentSyncValue=
		  true;
	    } else {
	       m_activeSourcesWithRecordsAtCurrentSyncValue.erase(
		  m_activeSourcesWithRecordsAtCurrentSyncValue.begin()
		  );
	    }
	 }
      } else {
	 //Need special algorithm to handle non-sequentially accessing
	 // multi-active sources
	 
	 oStatus = findStopWithMultipleNonSequentialActiveSources();
	 //See if an error occured
	 if(oStatus != kNextStopNoError && oStatus 
	    != kNextStopReachedEndOfAPassiveSource){
	    return oStatus;
	 }
      }//if( isSequentiallyAccessing() )
   }//if( 1== activeSources.size() )
   
   //Now synchronize the source
   return resynchronize();

}

FrameDeliverer::NextStopStatus
FrameDeliverer::resynchronize( void )
{
   NextStopStatus oStatus(kNextStopNoError);

   DABoolean syncSuccess(true);
   DataSourceController::SyncStatus syncStatus;
   DataSourceController::SyncStatus problemWithSyncStatus( 
      DataSourceController::kSyncNoError );
   
   DataSourceControllers::iterator itEnd = m_dataSourceControllers.end();
   for(DataSourceControllers::iterator itController = 
	  m_dataSourceControllers.begin();
       itController != itEnd;
       ++itController ){
      syncStatus = (*(*itController)).synchronizeSource( currentSyncValue());
      
      if( DataSourceController::kSearchNoError != syncStatus ){
	 if( DataSourceController::kSyncWarningAtEndOfSource != syncStatus){
	    syncSuccess = false;
	 }
	 problemWithSyncStatus = syncStatus;
	 
	 //Record source's status
	 setSourceStatus( *itController, syncStatus );
      }
   }
   if( DataSourceController::kSyncNoError != problemWithSyncStatus  ) {
      
      oStatus = convertSyncStatusToNextStopStatus( problemWithSyncStatus);
   }
   if( !syncSuccess  ) {
      invalidateStop() ;
   } else {
      // Since we have successfully synchronized, we need to fill the Frame

      //NOTE: This could move into the currentFrame() code so a Frame
      //      only is filled when it is requested
      //      This would require a new flag m_frameIsFull which is
      //        set to false in nextStop()
      //        set to true in currentFrame() when the Frame is filled
      frame( currentStop() ,
	     currentSyncValue() );
   }
   return oStatus;
}

FrameDeliverer::NextStopStatus
FrameDeliverer::gotoNextRecordAtCurrentSyncValue( void )
{
   NextStopStatus oStatus(kNextStopNoError);

   DABoolean isDone(false);
   SyncValue tempSyncValue;
#if defined(TEMPLATE_PARAMETERS_BREAK_TYEPDEFS_BUG)
   Stream::Type nextRecordType ;
   nextRecordType = Stream::kNone ;
#else
   Stream::Type nextRecordType(Stream::kNone);
#endif /* TEMPLATE_PARAMETERS_BREAK_TYEPDEFS_BUG */

   DataSourceController* controller(
      (*(m_activeSourcesWithRecordsAtCurrentSyncValue.begin())).second );
   
   const Stream::Set& activeStreams=(*controller).activeStreams();

   //Remove source from list
   m_activeSourcesWithRecordsAtCurrentSyncValue.erase(
      m_activeSourcesWithRecordsAtCurrentSyncValue.begin());

   DataSourceController::SearchStatus searchStatus;
   while(! isDone ){
      //Find its next record
      if( DataSourceController::kSearchNoError != 
	  (searchStatus = (*controller).findNextRecord( 
	     tempSyncValue,
	     nextRecordType ))){

	 if(DataSourceController::kSearchEndOfSource == searchStatus){
	    //Skip this one
	    isDone = true;
	    //update source's status
	    setSourceStatus( controller, searchStatus );

	    //We should not set oStatus to kNextStopWarningEndOfPassiveSource
	    // since this active source does have Records at this SyncValue
	    // so it did synchronize properly
	 } else {
	    //An error occured
	    m_severalActiveSourcesWithRecordsAtCurrentSyncValue=false;
	    return cleanupAfterSearchError( controller, searchStatus );
	 }
      }

      
      //If next Record doesn't have same SyncValue 
      //  then use next controller on list
      if(tempSyncValue != m_currentSyncValue ){
	 isDone=true;
      } else {
	 //Goto that Record
	 if(DataSourceController::kSearchNoError != 
	    ( searchStatus = (*controller).gotoNextRecord()) ){
	    
	    //Assign the correct status code
	    return cleanupAfterSearchError( controller, searchStatus );
	 }
	 
	 if(activeStreams.contains( nextRecordType) ){
	    isDone=true;
	    //Put it back on the list
	    m_activeSourcesWithRecordsAtCurrentSyncValue.insert(
	       std::pair<const Stream::Type ,
	       DataSourceController*>(nextRecordType, controller));	    
	 }
      }

   } //while(!isDone);

   //The top most source is now our stop
   m_currentStop = (*(m_activeSourcesWithRecordsAtCurrentSyncValue.begin()))
                                                                     .first;
   //If only one left, turn off special mode
   if( 1 == m_activeSourcesWithRecordsAtCurrentSyncValue.size() ){
      m_severalActiveSourcesWithRecordsAtCurrentSyncValue=false;
   }

   frame( currentStop() ,
	  currentSyncValue() ) ;
   return oStatus;
}

FrameDeliverer::NextStopStatus
FrameDeliverer::findStopWithMultipleNonSequentialActiveSources( void )
{
   //NOTE: Need to synchronize all active sources to the current SyncValue
   //      first because they are not serving Records in sequential order
   //      Eg.
   //        Key: | = Record    *| = next record for source
   //
   //            syncValue      1    2  3 4
   //            source 1      *|    |    |
   //            source 2       |      *|
   //
   //      source 1 and 2 both have a record at SyncValue=1 but source2's
   //      next Record points to SyncValue=3.  Therefore comparing
   //      next Records to see if they have the same SyncValue will not
   //      work to see if two sources have Records at a SyncValue.
   //
   //      So the only way we can find out if there are multiple Records
   //      at this SyncValue is to synchronize all active sources to the
   //      current SyncValue.

   //Algorithm:
   // 1) Synchronize all active sources to current SyncValue
   // 2) See if more than one source has a Record at this SyncValue
   // 3) if
   //    a) no 
   //       i)  set the one Record at SyncValue to currentStop 
   //       ii) exit
   //    b) yes
   //       i) fill in list of sources with Active Records at this SyncValue
   //       ii) see if list has more than one source
   //       iii) if
   //             1) no, 
   //                a) set the one Record at SyncValue to current Stop
   //             2) yes, 
   //                a) set highest priority Record at SyncValue to Stop
   //                b) set flag for special mode
   // 4) exit
   NextStopStatus oStatus(kNextStopNoError);

   //Clear the list
   m_activeSourcesWithRecordsAtCurrentSyncValue.erase(
      m_activeSourcesWithRecordsAtCurrentSyncValue.begin(),
      m_activeSourcesWithRecordsAtCurrentSyncValue.end());
   
   //make our life easier by making an alias to the above map
   StreamPriorities& 
      streamPriorities(m_activeSourcesWithRecordsAtCurrentSyncValue);
   
   DataSourceController* controller(0);
   SyncValue tempSyncValue;
#if defined(TEMPLATE_PARAMETERS_BREAK_TYEPDEFS_BUG)
   Stream::Type recordType ;
   recordType = Stream::kNone ;
#else
   Stream::Type recordType(Stream::kNone);
#endif /* TEMPLATE_PARAMETERS_BREAK_TYEPDEFS_BUG */
   
   DataSourceController::SyncStatus syncStatus;
   
   DataSourceControllers controllers;
   controllers.reserve( m_activeSources.size());
   
   DataSourceControllers::iterator itEnd = m_activeSources.end();
   for( DataSourceControllers::iterator itSource = 
	   m_activeSources.begin();
	itSource != itEnd;
	++itSource){
      
      controller = (*itSource);
      
      syncStatus = (*controller).synchronizeSource( m_currentSyncValue );
      
      //Check for an error
      if( syncStatus != DataSourceController::kSyncNoError ){
	 //Set source status	 
	 SourcesStatus::iterator itStatus = 
	    m_sourcesStatus.find(controller);
	 (*itStatus).second = 
	    convertSyncStatusToSourceStatus( syncStatus);
	 
	 if(DataSourceController::kSyncWarningAtEndOfSource ==syncStatus ){
	    //Not fatal
	    oStatus = kNextStopReachedEndOfAPassiveSource;
	 } else {
	    //Fatal
	    invalidateStop() ;
	    return convertSyncStatusToNextStopStatus( syncStatus );
	 }
      }

      //If Source's Record has current SyncValue, add it to our list
      const Stream::Set& activeStreams = controller->activeStreams();

      const Stream::Set::const_iterator itActiveStreamsEnd = 
	 activeStreams.end();
      for( Stream::Set::const_iterator itActiveStream = activeStreams.begin();
	   itActiveStream != itActiveStreamsEnd;
	   ++itActiveStream ) {

	 tempSyncValue = (*((*controller).proxyDeliverer()))
	    .syncValue( *itActiveStream);

	 if( tempSyncValue == m_currentSyncValue ){
	    controllers.push_back( controller);
	    break; //once found, can jump out of this loop
	 }
      }//Loop over the active streams
   }//Loop over active sources
   
   assert( ! controllers.empty() );
   
   if( 1 == controllers.size() ){
      //Is the stream an active stream?
      controller = controllers[0];
      recordType = (*controller).currentStop();
      if((*controller).activeStreams().contains( recordType )){
	 m_currentStop = recordType;
	 return oStatus;
      }
   }
   
   //Now loop over the list of Records at this SyncValue and remove all Records
   // that are not from active Streams.
   DABoolean advanceToNextSource(false);
   DataSourceController::SearchStatus searchStatus;
   
   DataSourceControllers::const_iterator itVDSCEnd = controllers.end();
   for(DataSourceControllers::const_iterator itController =
	  controllers.begin();
       itController != itVDSCEnd;
       ++itController){
      advanceToNextSource=false;
      
      controller = *itController;
      recordType = (*controller).currentStop();
      const Stream::Set& activeStreams= (*controller).activeStreams();
      do{
	 if( activeStreams.contains( recordType ) ){
	    //add to our list
	    streamPriorities.insert( std::pair<const Stream::Type,
				     DataSourceController*>(recordType,
							    controller));
	    advanceToNextSource=true;
	 } else { //Record not from  an active Stream
	    //Peek at the next record
	    if( DataSourceController::kSearchNoError != 
		(searchStatus = (*controller).findNextRecord( 
		   tempSyncValue,
		   recordType ))){
	       // An error occured
	       return cleanupAfterSearchError( controller, searchStatus );
	    }
	    
	    //If next Record doesn't have same SyncValue 
	    //  then try next source
	    if( tempSyncValue != m_currentSyncValue ) {
	       advanceToNextSource=true;
	    } else {
	       //Goto that Record
	       if(DataSourceController::kSearchNoError != 
		  ( searchStatus = (*controller).gotoNextRecord()) ){
		  
		  //Assign the correct status code
		  return cleanupAfterSearchError( controller, searchStatus );
	       }
	    }     
	 }//if( activeStreams.contains( recordType ) )
      } while( !advanceToNextSource );
   }//loop over sources
   
   assert( ! streamPriorities.empty() );
   
   if( 1 != streamPriorities.size() ){
      m_severalActiveSourcesWithRecordsAtCurrentSyncValue=true;
   }
   
   m_currentStop = (*(streamPriorities.begin())).first;
   return oStatus;   
   
}

DABoolean
FrameDeliverer::updateIsSequentiallyAccessing( void )
{
   if( ! m_mustSequentiallyAccess ){

      //If no ActiveStreams then false
      if( m_activeSources.size() == 0 ){
	 m_isSequentiallyAccessing= false;
      } else {
	 //See if all ActiveStreams are being accessed sequentially
	 DataSourceControllers::const_iterator itEnd = m_activeSources.end();
	 DABoolean isSequential(true);
	 for(DataSourceControllers::const_iterator itSource = 
		                                m_activeSources.begin();
	     itSource != itEnd;
	     ++itSource){
	    if(! (*(*itSource)).isSequentiallyAccessing() ){
	       isSequential = false;
	       break;
	    }
	 }
	  
	 m_isSequentiallyAccessing= isSequential;
      }
   } else {
      m_isSequentiallyAccessing= true;
   }
   
   return m_isSequentiallyAccessing;
}

DABoolean
FrameDeliverer::updateMustSequentiallyAccess( void )
{
   DABoolean oldValue( m_mustSequentiallyAccess );
   if( ! forcedSequentialAccess() ){
      if( m_dataSourceControllers.size() == 0 ){
	 //No controllers so ok to random access
	 m_mustSequentiallyAccess = false;
      } else {
	 //Loop over the controllers to see if any of them are incapable
	 // of sequential access
	 DABoolean sequentialIsRequired(false);
	 DataSourceControllers::const_iterator itEnd = 
	                                        m_dataSourceControllers.end();
	 for(DataSourceControllers::const_iterator itController = 
		                        m_dataSourceControllers.begin();
	     itController != itEnd;
	     ++itController){
	    if( ! (*(*itController)).canRandomAccess() ){
	       sequentialIsRequired = true;
	       break;
	    }
	 }
	 m_mustSequentiallyAccess = sequentialIsRequired;
      }    
   } else {
      m_mustSequentiallyAccess = true;
   }

   if( oldValue != m_mustSequentiallyAccess ){
      //Change the restriction on the Active Data Sources
      DataSourceControllers::iterator itASEnd = m_activeSources.end();
      for(DataSourceControllers::iterator itSubStreams = m_activeSources.begin();
	  itSubStreams != itASEnd;
	  ++itSubStreams){
	 (*(*itSubStreams) ).setForcedSequentialAccess( 
	    m_mustSequentiallyAccess );
      }
      updateIsSequentiallyAccessing();
   }
   return m_mustSequentiallyAccess;
}

DataSourceControllers::iterator
FrameDeliverer::findDataSourceController( const DataSourceDescriptor& iBinder )
{
   DataSourceControllers::iterator itEnd = m_dataSourceControllers.end();
   DataSourceControllers::iterator itController( 
      m_dataSourceControllers.begin());
   for( ;
	itController != itEnd;
	++itController){
      if( iBinder == *(*itController) ){
	 break;
      }
   }
   return itController;
}

FrameDeliverer::NextStopStatus
FrameDeliverer::cleanupAfterSearchError( 
   DataSourceController* iController,
   const DataSourceController::SearchStatus& iSearchStatus )
{
   //An error occured
   invalidateStop() ;

   //Record source's status
   setSourceStatus( iController, iSearchStatus);

   return convertSearchStatusToNextStopStatus( iSearchStatus);
}

void
FrameDeliverer::setSourceStatus( DataSourceController* iController,
				 const DataSourceController::SearchStatus&
				   iSearchStatus )
{
  SourcesStatus::iterator itStatus = 
      m_sourcesStatus.find(iController);

   (*itStatus).second = 
      convertSearchStatusToSourceStatus( iSearchStatus);
}

void
FrameDeliverer::setSourceStatus( DataSourceController* iController,
				 const DataSourceController::SyncStatus&
				   iSyncStatus )
{
   SourcesStatus::iterator itStatus = 
      m_sourcesStatus.find(iController);
   (*itStatus).second = 
      convertSyncStatusToSourceStatus( iSyncStatus);
}

void
FrameDeliverer::invalidateStop()
{
   m_isValidStop = false;
   m_currentStop = Stream::kNone;
   emptyFrame() ;
}

//
// const member functions
//

FrameDeliverer::StatusOfSources
FrameDeliverer::statusOfSources( void ) const
{
   StatusOfSources returnValue;
   //Loop through status of sources to produce output

   SourcesStatus::const_iterator itEnd = m_sourcesStatus.end();
   for( SourcesStatus::const_iterator itSource = m_sourcesStatus.begin();
	itSource != itEnd;
	++itSource ){

      returnValue.insert( StatusOfSources::value_type( 
	 (*itSource).second,
	 DataSourceDescriptor(*((*itSource).first)) ) );
   }

   return returnValue;
}

Stream::Set
FrameDeliverer::activeStreams( void ) const
{
   Stream::Set streams;
   DataSourceControllers::const_iterator itEnd = m_activeSources.end();
   for(DataSourceControllers::const_iterator itStreams = m_activeSources.begin();
       itStreams != itEnd;
       ++itStreams){
      streams.add( (*(*itStreams)).activeStreams() );
   }
   return streams;
}

FrameDeliverer::DataSourceDescriptors
FrameDeliverer::activeSources( void ) const
{
   DataSourceDescriptors returnValue;
   
   DataSourceControllers::const_iterator itEnd = m_activeSources.end();
   for( DataSourceControllers::const_iterator itStream = m_activeSources.begin();
	itStream != itEnd;
	++itStream){
      DataSourceDescriptor temp( *(*itStream) );
      temp.clearStreams();
      temp.bindStreams( (*(*itStream)).activeStreams() );
      returnValue.push_back( temp );
   }

   return returnValue;
}

FrameDeliverer::DataSourceDescriptors
FrameDeliverer::sources( void ) const
{
   DataSourceDescriptors returnValue;
   
   DataSourceControllers::const_iterator itEnd = m_dataSourceControllers.end();
   for( DataSourceControllers::const_iterator 
	   itController = m_dataSourceControllers.begin();
	itController != itEnd;
	++itController){
      DataSourceDescriptor temp( *(*itController) );
      returnValue.push_back( temp );
   }

   return returnValue;
}

DABoolean
FrameDeliverer::isSequentiallyAccessing( void ) const
{
   return m_isSequentiallyAccessing;
}

DABoolean
FrameDeliverer::forcedSequentialAccess( void ) const
{
   return m_forcedSequentialAccess;
}

DABoolean
FrameDeliverer::mustSequentiallyAccess( void ) const
{
   return m_mustSequentiallyAccess;
}

Stream::Type
FrameDeliverer::currentStop( void ) const
{
   return m_currentStop;
}

DABoolean
FrameDeliverer::isValidStop( void ) const
{
   return m_isValidStop;
}

const SyncValue&
FrameDeliverer::currentSyncValue( void ) const
{
   return m_currentSyncValue;
}

//
// static member functions
//


