#if !defined(DATADELIVERY_FRAMEDELIVERER_H)
#define DATADELIVERY_FRAMEDELIVERER_H
// -*- C++ -*-
//
// Package:     DataDelivery
// Module:      FrameDeliverer
// 
// Description: Handles the retrieval of data from multiple sources.
//
// Usage:
// SETTING UP THE EVENT LOOP
//
//    FrameDeliverer FD;
//
//
//    //Tell FrameDeliverer what data sources to use.
//    // FrameDeliverer uses the DataBinder to create the appropriate
//    //  DataSourceController to use with the data source you specify.
//    // You also specify what records you want to read from the DataSource
//
//    Stream::Set readStreams;
//    readStreams.insert( Stream::kEvent );
//    My1SourceBinder my1Binder( readStreams);
//
//    readStreams.insert( Stream::kBeginRun );
//    DriverSourceBinder driverBinder("myskim.rp", readStreams);
//
//    FrameDeliverer::AddSourceStatus status;
//    // addDataSource returns FrameDeliverer::kAddSourceNoError if 
//    // data source was openned sucessfully
//    // To determine what caused a failure, look at status.
//
//    //Read from the users source
//    if( FrameDeliverer::kAddSourceNoError != 
//                 (status = FD.addSource(my1Binder) )){
//      exit(1);
//    }
//
//    //Read from the roar file
//    if( FrameDeliverer::kAddSourceNoError != 
//                 (status = FD.addSource(driverBinder) ) ){
//      exit(1);
//    }
//
//
//    //Before reading the data, we must tell FrameDeliverer where to stop.
//    // In this case, we only stop when we find a new event or begin run 
//    // in the roar file.
//   
//    FrameDeliverer::AddActiveSourceStatus activeSourceStatus;
//    // addDataSource returns FrameDeliverer::kAddActiveSourceNoError 
//    // if data source was openned sucessfully
//    // To determine what caused a failure, look at activeSourceStatus.
//
//    DriverSourceBinder activeStreamBinder( driverBinder );
//
//    FD.removeAllActiveSources();
//    if( FrameDeliverer::kAddActiveSourceStatus ! =
//        ( activeSourceStatus = FD.addActiveSource( activeStreamBinder)) ){
//      exit(1);
//    }
//
//    //Now we can loop through all the events
//    DABoolean isDone = false;
//    while( !isDone ) {
//
//      //Tell FrameDeliverer to goto the next stop, which in our case
//      // is a new event.
//      FrameDeliverer::NextStopStatus nextStopStatus;
//      nextStopStatus = FD.gotoNextStop( ); 
//
//      Stream::Type currentStop = FD.currentStop();
//      if( Stream::kNone == currentStop ) {
//         //No more events, should stop looping
//         isDone = true;
//         //Should check nextStopStatus to determine exactly what happenned
//      } else 
//      if( Stream::kBeginRun == currentStop ) {
//         //Do what ever action you want for a begin run
//         //  Hand the frame to the routine
//         myBeginRun( FD.currentFrame() );
//      } else
//      if( Stream::kEvent == currentStop ){
//         //Do what ever action you want for an event
//         //  Hand the frame to the routine
//         myEvent( FD.currentFrame() );
//      } else {
//         // Something has gone very wrong! Should never get here
//         report(ERROR,"JobControl")
//                <<"FrameDeliverer stopped at the wrong type of record"<<endl;
//      }
//    }     
//
// Author:      Chris D Jones
// Created:     Wed Mar 12 12:27:46 EST 1997
// $Id: FrameDeliverer.h,v 1.23 1998/07/18 20:02:31 mkl Exp $
//
// Revision history
//
// $Log: FrameDeliverer.h,v $
// Revision 1.23  1998/07/18 20:02:31  mkl
// solaris gets confused by pointer as key
//
// Revision 1.22  1998/02/03 21:28:12  mkl
// switch over to STLUtility library
//
// Revision 1.21  1997/11/19 15:27:29  sjp
// Modifier to use FrameProvider class
//
// Revision 1.20  1997/09/18 21:07:17  cdj
// changed Boolean to DABoolean
//
// Revision 1.19  1997/09/03 20:06:38  sjp
// Uses CPP macros for STL containers
//
// Revision 1.18  1997/08/27 03:38:53  sjp
// Updated to new name for bug flags
//
// Revision 1.17  1997/08/14 11:43:14  sjp
// Mods to run under CW Pro 1
//
// Revision 1.16  1997/08/06 15:58:12  sjp
// Modified to use ProxyProviders
//
// Revision 1.15  1997/07/24 19:01:15  cdj
// Added resynchronize() method, which is needed when you add a new source
//  to an already running job.
//
// Revision 1.14  1997/07/09 18:01:00  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.13  1997/07/02 19:27:42  sjp
// Changed `list' to be `vector'
//
// Revision 1.12  1997/06/29 20:09:18  cdj
// 1) Now handles the case when multiple Records have the same SyncValue
// 2)  Moved duplicate error handling code in gotoNextStop to a new routine
//
// Revision 1.11  1997/06/03 17:31:23  sjp
// Modified to handle DataProviders
//
// Revision 1.10  1997/05/07 19:00:20  sjp
// Fixed less<Stream::Type> so can be used as usual
//
// Revision 1.9  1997/05/02 20:16:52  cdj
// 1) Made naming more consistant
//    a) changed Error to Status
//    b) changed ActiveStreams to ActiveSources
//    c) changed DataSource to Source
// 2) Changed nextStop(...) to gotoNextStop(...)
// 3) Methods return status instead of using an argument
// 4) added sources() method
//
// Revision 1.8  1997/04/29 20:05:52  cdj
// replaced less< Stream::Type> with Stream::TypeLess
//
// Revision 1.7  1997/04/21 19:21:50  cdj
// Added several new member functions to determine the state of FrameDeliverer
// 1)statusOfSources() : returns list of the status of all sources
// 2)activeSources() : returns a list of all the active sources
// Replaced DataSourceBinder with DataSourceDescriptor in all methods except
// addDataSource(...).
//
// Revision 1.6  1997/04/16 19:59:53  cdj
// added code to allow multiple active sources
//
// Revision 1.5  1997/04/01 16:07:34  sjp
// CLeaned out obselete lines
//
// Revision 1.4  1997/03/20 22:28:25  cdj
// Added status return arguement to nextStop(...)
//
// Revision 1.3  1997/03/20 01:35:29  cdj
// 1) More and better named error codes
// 2) Consistant naming of data and methods for sequential access
// 3) Addition of removeAllDataSources
//
// Revision 1.2  1997/03/18 16:21:58  cdj
// 1) Corrected syntax errors
// 2) Added methods for controlling sequential access
//
// Revision 1.1  1997/03/13 21:51:44  cdj
// First submission.
// NOTE: No compilation has been attempted on this file so syntax errors are
// possible/likely.
//


// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataHandler/SyncValue.h"
#include "DataHandler/Stream.h"
#include "DataHandler/StreamSet.h"
#include "DataHandler/Frame.h"
#include "DataHandler/FrameProvider.h"
#include "DataDelivery/DataSourceDescriptor.h"
#include "DataDelivery/DataSourceController.h"


// forward declarations
class DataSourceBinder;
class ProxyProvider ;
class StreamPriorityGreater;

#include "STLUtility/fwd_map.h"
#include "STLUtility/fwd_multimap.h"
#include "STLUtility/fwd_vector.h"
#include <vector>

#if !defined(_framedeliverer_sourcecontrollers_)
#  define _framedeliverer_sourcecontrollers_ STL_VECTOR( DataSourceController* )
typedef DataSourceController* SourceStatusKey;
#  define _framedeliverer_sourcesstatus_ STL_MAP( SourceStatusKey, FrameDeliverer::SourceStatus )
//#  define _framedeliverer_sourcesstatus_ STL_MAP( DataSourceController*, FrameDeliverer::SourceStatus )
#  define _framedeliverer_keyedsourcecontrollers_ STL_MULTIMAP_COMP( Stream::Type , DataSourceController* , StreamPriorityGreater )
#endif /* _framedeliverer_sourcecontrollers_ */

class FrameDeliverer : public FrameProvider
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      enum AddSourceStatus  { kAddSourceNoError = 0,
			      kAddSourceBinderFailedToMakeController,
			      kAddSourceInvalidStopsForSource ,
			      kAddSourceSourceInaccessible,
			      kAddSourceBadParameters,
			      kAddSourceUnknownError
      };

      enum AddProviderStatus { kAddProviderNoError = 0 ,
			       kAddProviderUnknownError
      } ;

      enum RemoveSourceStatus { kRemoveSourceNoError = 0,
				kRemoveSourceNoMatchingSource
      };

      enum RemoveProviderStatus { kRemoveProviderNoError = 0 ,
				  kRemoveProviderUnknownError
      } ;

      enum AddActiveSourceStatus { kAddActiveSourceNoError = 0,
				   kAddActiveSourceDataSourceNotPresent,
				   kAddActiveSourceInvalidStreamsForSource
      };

      enum NextStopStatus { kNextStopNoError =0,
			    kNextStopReachedEndOfAPassiveSource,
			    kNextStopReachedEndOfAnActiveSource,
			    kNextStopNoActiveStreams,
			    kNextStopFailedToSyncAllSources,
			    kNextStopProblemWithASource,
			    kNextStopUnknownError
      };

      enum SourceStatus { kSourceNoError = 0,
			  kSourceReachedEnd,
			  kSourceProblemWithSource,
			  kSourceFailedToSync,
			  kSourceUnknownError
      };

      typedef STL_VECTOR( DataSourceDescriptor ) DataSourceDescriptors ;
      typedef STL_MULTIMAP( FrameDeliverer::SourceStatus , DataSourceDescriptor ) StatusOfSources ;

      // Constructors and destructor
      FrameDeliverer( void );
      virtual ~FrameDeliverer();

      // member functions
      FrameDeliverer::AddActiveSourceStatus
         addActiveSource( const DataSourceDescriptor& iActiveSource);
      void removeAllActiveSources( void );

      FrameDeliverer::AddSourceStatus
        addSource( const DataSourceBinder& iAddSourceBinder); 
      FrameDeliverer::RemoveSourceStatus
        removeSource( const DataSourceDescriptor& iCloseSourceBinder);
      void removeAllSources( void );

      FrameDeliverer::AddProviderStatus
        addProvider( ProxyProvider& aProvider ) ;
      FrameDeliverer::RemoveProviderStatus
        removeProvider( ProxyProvider& aProvider ) ;
      FrameDeliverer::AddProviderStatus
        addProvider( ProxyProvider& aProvider ,
		     const Stream::Set& aStreamsToAdd ) ;
      FrameDeliverer::RemoveProviderStatus
        removeProvider( ProxyProvider& aProvider ,
			const Stream::Set& aStreamsToRemove ) ;

      void setForcedSequentialAccess( DABoolean iFlag );

      FrameDeliverer::NextStopStatus gotoNextStop( void );
      //call resynchronize when you add a source to a job already 
      //  in progress
      FrameDeliverer::NextStopStatus resynchronize( void );

      // const member functions
      StatusOfSources statusOfSources( void ) const;

      Stream::Set activeStreams( void ) const;
      DataSourceDescriptors activeSources( void ) const;
      DataSourceDescriptors sources( void ) const;
                                   

      DABoolean isSequentiallyAccessing( void ) const;
      DABoolean forcedSequentialAccess( void ) const;
      //NOTE: it is possible for isSequentiallyAccessing to be true when
      //      forcedSequentialAccess is false. This can occur when we are
      //      accessing in any order, but we just happen to know that the
      //      that the order just happens to be sequential.
      DABoolean mustSequentiallyAccess( void ) const;
      //NOTE: mustSequentiallyAccess can be true when forcedSequentialAccess
      //      is false.  This occurs when the user doesn't care if the
      //      Streams are in sequence, but one of the DataSources can ONLY
      //      deliver Records in sequence (i.e. a sequential data source).

      Stream::Type currentStop( void ) const;
      DABoolean isValidStop( void ) const;

      const SyncValue& currentSyncValue( void ) const;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      FrameDeliverer( const FrameDeliverer& );

      // assignment operator(s)
      const FrameDeliverer& operator=( const FrameDeliverer& );

      // private member functions
      DABoolean updateIsSequentiallyAccessing( void ); 
      DABoolean updateMustSequentiallyAccess( void );
      _framedeliverer_sourcecontrollers_::iterator
            findDataSourceController( const DataSourceDescriptor& iBinder );

      void setSourceStatus( DataSourceController* iController,
			    const DataSourceController::SearchStatus& 
			    iSearchStatus);
      void setSourceStatus( DataSourceController* iController,
			    const DataSourceController::SyncStatus&
			    iSyncStatus);
      FrameDeliverer::NextStopStatus cleanupAfterSearchError(
	 DataSourceController* iController,
	 const DataSourceController::SearchStatus& iSearchStatus );

      FrameDeliverer::NextStopStatus
                   findStopWithMultipleNonSequentialActiveSources( void );
      FrameDeliverer::NextStopStatus
                   gotoNextRecordAtCurrentSyncValue( void );
      void invalidateStop() ;

      // private const member functions

      // data members
      _framedeliverer_sourcesstatus_& m_sourcesStatus;
      _framedeliverer_keyedsourcecontrollers_& m_activeSourcesWithRecordsAtCurrentSyncValue;
      _framedeliverer_sourcecontrollers_& m_dataSourceControllers;
      _framedeliverer_sourcecontrollers_& m_activeSources;

      DABoolean m_isValidStop;

      SyncValue m_currentSyncValue;
      Stream::Type m_currentStop;

      DABoolean m_forcedSequentialAccess;
      DABoolean m_mustSequentiallyAccess;
      DABoolean m_isSequentiallyAccessing;

      DABoolean m_severalActiveSourcesWithRecordsAtCurrentSyncValue;
      // static data members

};

// inline function definitions

#endif /* DATADELIVERY_FRAMEDELIVERER_H */
