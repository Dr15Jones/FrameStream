// -*- C++ -*-
//
// Package:     <package>
// Module:      FrameStorer
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Sun May 25 15:28:15 EDT 1997
// $Id: FrameStorer.cc,v 1.12 1999/12/06 21:46:45 mkl Exp $
//
// Revision history
//
// $Log: FrameStorer.cc,v $
// Revision 1.12  1999/12/06 21:46:45  mkl
// added 'contains( StreamType )' method
//
// Revision 1.11  1998/07/18 20:14:08  mkl
// move to STL macros
//
// Revision 1.10  1997/09/18 21:13:12  cdj
// Changed Boolean to DABoolean
//
// Revision 1.9  1997/09/04 15:16:23  mkl
// moved to new bug flags
//
// Revision 1.8  1997/09/03 03:52:35  mkl
// renamed ToolBox/report to Experiment/report
//
// Revision 1.7  1997/08/18 18:00:03  mkl
// changed vector to list, because of problems with return type 'list<>::iterator' of function
//
// Revision 1.6  1997/08/17 03:53:49  mkl
// need multimap explicitly included for MULTIMAP_IS_SEPARATE_FILE_BUG
//
// Revision 1.5  1997/08/16 17:45:35  cdj
// Modified to work with Proxies
//
// Revision 1.4  1997/07/11 06:20:10  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.3  1997/07/02 20:16:49  mkl
// fixes for compile with cxx
//
// Revision 1.2  1997/05/31 20:47:20  cdj
// 1) storeFrame now gets status from RecordStorer
// 2) can now get the actual status of a sink
//
// Revision 1.1.1.1  1997/05/30 15:41:36  cdj
// First submission
//

#include "Experiment/Experiment.h"
// system include files
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <algorithm>
#include <map>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "DataStorage/DataSinkBinder.h"
#include "DataStorage/DataSinkController.h"
#include "DataStorage/ProxyStorer.h"
#include "DataStorage/RecordStorer.h"
#include "DataStorage/FrameStorer.h"


// STL classes
#include <algorithm>
#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#  include <map>
#  include <multimap.h>
#else
#  include <map>
#endif                  
#include <vector>

//
// constants, enums and typedefs
//
typedef _framestorer_statusofsinks_ OutputSinksStatus;
typedef _framestorer_sinkdescriptors_ DataSinkDescriptors;
typedef _framestorer_sinkcontrollers_ DataSinkControllers;
typedef _framestorer_recordstorers_ StreamToRecordStorerMap;

//
// static data member definitions
//

//
// constructors and destructor
//
FrameStorer::FrameStorer() :
   m_streamToRecordStorerMap( *(new StreamToRecordStorerMap )),
   m_dataSinkControllers( *(new DataSinkControllers)),
   m_mustSequentiallyStore(false)
{
   //make sure memory was assigned
   assert( 0 != &m_streamToRecordStorerMap );
   assert( 0 != &m_dataSinkControllers );

}


// FrameStorer::FrameStorer( const FrameStorer& )
// {
// }

FrameStorer::~FrameStorer()
{
   //Remove the RecordStorers
   StreamToRecordStorerMap::iterator itRDEnd = m_streamToRecordStorerMap
                                                    .end();
   for( StreamToRecordStorerMap::iterator itRStorer=
	                                 m_streamToRecordStorerMap.begin();
	itRStorer != itRDEnd;
	++itRStorer){
      delete (*itRStorer).second;
   }

   //delete the DataSinkControllers
   DataSinkControllers::iterator itDSCEnd = m_dataSinkControllers.end();
   for( DataSinkControllers::iterator itController =
	                                 m_dataSinkControllers.begin();
	itController != itDSCEnd;
	++itController){
      delete (*itController);
   }


   delete &m_streamToRecordStorerMap;
   delete &m_dataSinkControllers;
}

//
// assignment operators
//
// const FrameStorer& FrameStorer::operator=( const FrameStorer& )
// {
// }

//
// member functions
//
FrameStorer::AddSinkStatus
FrameStorer::addSink( const DataSinkBinder& iAddSinkBinder)
{
   FrameStorer::AddSinkStatus oError = kAddSinkNoError;

   //See if we already have this sink and if so remove it
   DataSinkControllers::iterator itController = 
      findDataSinkController( iAddSinkBinder );
   if( itController != m_dataSinkControllers.end() ){
      removeSink( iAddSinkBinder);
   }
   
   DataSinkController* controller = iAddSinkBinder.
                                        createDataSinkController();
   if( 0 == controller){
      oError = kAddSinkBinderFailedToMakeController;
   } else {
      // See if there was a problem initializing the sink
      if( DataSinkController::kInitNoError != 
	  (*controller).initializationStatus() ){
	 switch( (*controller).initializationStatus() ){
	    case DataSinkController::kInitInvalidStopsForSink:
	      oError = kAddSinkInvalidStopsForSink;
	      break;
	    case DataSinkController::kInitSinkInaccessible:
	      oError = kAddSinkSinkInaccessible;
	      break;
	    case DataSinkController::kInitBadParameters:
	      oError = kAddSinkBadParameters;
	      break;
	    case DataSinkController::kInitUnknownError:
	      oError = kAddSinkUnknownError;
	      break;
	    default:
	      oError = kAddSinkUnknownError;
	      break;
	 }
      } else {
	 //Sink is fine
	 m_dataSinkControllers.push_back( controller );

	 //Inform the necessary RecordStorers
	 const Stream::Set& readStreams = (*controller).recordsToStore();

	 RecordStorer* recordStorer(0);
#if defined(CXX_TYPEDEFED_BEFORE_DEFINITION_BUG)
	 StreamSet::const_iterator itEnd = readStreams.end();
	 for(StreamSet::const_iterator itStream = readStreams.begin();
#else
	 Stream::Set::const_iterator itEnd = readStreams.end();
	 for(Stream::Set::const_iterator itStream = readStreams.begin();
#endif
	     itStream != itEnd;
	     ++itStream ){
	    StreamToRecordStorerMap::iterator itRecord =
	       m_streamToRecordStorerMap.find( *itStream );
	    if( itRecord != m_streamToRecordStorerMap.end() ){
	       recordStorer = (*itRecord).second;
	    } else {
	       //Need to make a new RecordStorer
	       recordStorer = new RecordStorer( *itStream );
	       assert( 0 != recordStorer);
	       m_streamToRecordStorerMap.insert(
		  StreamToRecordStorerMap::value_type( *itStream,
							  recordStorer ) );
	    }
	    //Give RecordStorer the info

	    (*recordStorer).add( ( *(*controller).proxyStorer()) );

	 } //for(Stream::Set ... )
	 updateMustSequentiallyStore();
      }
	    
   }
   return oError;
}

FrameStorer::RemoveSinkStatus
FrameStorer::removeSink( const DataSinkDescriptor& iCloseSinkBinder)
{
   FrameStorer::RemoveSinkStatus oError = kRemoveSinkNoError;

   //See if we already have this sink and if so remove it
   DataSinkControllers::iterator itController = 
      findDataSinkController( iCloseSinkBinder );

   if( itController == m_dataSinkControllers.end() ){
      //No such controller
      oError = kRemoveSinkNoMatchingSink;
   } else {

      //Remove it from each RecordStorer

      DataSinkController* controller( *itController );
      const Stream::Set& readStreams = (*controller).recordsToStore();

      RecordStorer* recordStorer(0);

#if defined(CXX_TYPEDEFED_BEFORE_DEFINITION_BUG)
      StreamSet::const_iterator itEnd = readStreams.end();
      for(StreamSet::const_iterator itStream = readStreams.begin();
#else
      Stream::Set::const_iterator itEnd = readStreams.end();
      for(Stream::Set::const_iterator itStream = readStreams.begin();
#endif
	  itStream != itEnd;
	  ++itStream ){
	 StreamToRecordStorerMap::iterator itRecord =
	    m_streamToRecordStorerMap.find( *itStream );
	 if( itRecord != m_streamToRecordStorerMap.end() ){
	       recordStorer = (*itRecord).second;
	       
	       //Tell RecordStorer to remove its reference
	       (*recordStorer).
		  remove( *((*controller).proxyStorer()));

	       //If No more Sinks in RecordStorer, delete it
	       if( (*recordStorer).isEmpty() ){
		  m_streamToRecordStorerMap.erase( itRecord );
		  delete recordStorer ;
	       }
	 }

      } //for(Stream::Set ... )
      //Now get rid of controller
      m_dataSinkControllers.erase( itController );
      delete controller; 
      updateMustSequentiallyStore();
   }
   return oError;
}


void
FrameStorer::removeAllSinks( void )
{
   //Get rid of all RecordStorers
   StreamToRecordStorerMap::iterator itRSEnd = 
      m_streamToRecordStorerMap.end();
   
   for(StreamToRecordStorerMap::iterator itRecordStorer =
	  m_streamToRecordStorerMap.begin();
       itRecordStorer != itRSEnd;
       ++itRecordStorer){
      delete (*itRecordStorer).second;
   }
   m_streamToRecordStorerMap.erase( m_streamToRecordStorerMap.begin(),
				    itRSEnd );
   
   //Delete the Controllers
   DataSinkControllers::iterator itDSCEnd = m_dataSinkControllers.end();
   for(DataSinkControllers::iterator itController =
	  m_dataSinkControllers.begin();
       itController != itDSCEnd;
       ++itController ){
      delete *itController;
   }
   
   m_dataSinkControllers.erase( m_dataSinkControllers.begin(),
				m_dataSinkControllers.end());
   
   updateMustSequentiallyStore();
   
}


FrameStorer::StoreFrameStatus 
FrameStorer::storeFrame( const Frame& iFrame)
{
   FrameStorer::StoreFrameStatus returnValue(kStoreFrameNoError);

   //Find the correct RecordStorer
   StreamToRecordStorerMap::const_iterator itFound =
   m_streamToRecordStorerMap.find(iFrame.stopStream());

   if( itFound != m_streamToRecordStorerMap.end() ){
      //Need to check for errors here
      RecordStorer::StoreStatus status=(*((*itFound).second)).store( iFrame );
      if( RecordStorer::kStoreNoError != status){
	 switch( status ) {
	    case RecordStorer::kStoreProblemWithASink:
	      returnValue = kStoreFrameProblemWithASink;
	      break;
	    case RecordStorer::kStoreUnknownSinkError:
	      returnValue = kStoreFrameUnknownSinkError;
	      break;
	    case RecordStorer::kStoreUnknownError:
	      returnValue = kStoreFrameUnknownRecordError;
	      break;
	    default:
	      returnValue = kStoreFrameUnknownError;
	      break;
	 }
      }
   } else {
      returnValue = kStoreFrameWarningNoSinkForRecord;
   }
   return returnValue;
}

void 
FrameStorer::updateMustSequentiallyStore( void )
{
   if( m_dataSinkControllers.size() == 0 ){
      //No controllers so ok to random store
      m_mustSequentiallyStore = false;
   } else {
      //Loop over the controllers to see if any of them are incapable
      // of sequential store
      DABoolean sequentialIsRequired(false);
      DataSinkControllers::const_iterator itEnd = 
	 m_dataSinkControllers.end();
      for(DataSinkControllers::const_iterator itController = 
	     m_dataSinkControllers.begin();
	  itController != itEnd;
	  ++itController){
	 if( (*(*itController)).mustSequentiallyStore() ){
	    sequentialIsRequired = true;
	    break;
	 }
      }
      m_mustSequentiallyStore = sequentialIsRequired;
   }    
}

DataSinkControllers::iterator
FrameStorer::findDataSinkController( const DataSinkDescriptor& iBinder )
{
   DataSinkControllers::iterator itEnd = m_dataSinkControllers.end();
   DataSinkControllers::iterator itController( 
      m_dataSinkControllers.begin());
   for( ;
	itController != itEnd;
	++itController){
      if( iBinder == *(*itController) ){
	 break;
      }
   }
   return itController;
}

//
// const member functions
//

OutputSinksStatus
FrameStorer::statusOfSinks( void ) const
{
   OutputSinksStatus returnValue;
   //Loop through sinks to and check status

   DataSinkControllers::const_iterator itEnd = m_dataSinkControllers.end();
   for( DataSinkControllers::const_iterator itSink =
	                                  m_dataSinkControllers.begin();
	itSink != itEnd;
	++itSink){

      //Get the status
      ProxyStorer::StoreStatus status =
	 (*( ( *(*itSink) ).proxyStorer())).status();

      //Convert the status
      SinkStatus sinkStatus;
      switch( status ){
	 case ProxyStorer::kStoreNoError:
	   sinkStatus = kSinkNoError;
	   break;
	 case ProxyStorer::kStoreProblemWithSink:
	   sinkStatus = kSinkProblemWithSink;
	   break;
	 case ProxyStorer::kStoreUnknownError:
	   sinkStatus = kSinkUnknownSinkError;
	   break;
	 default:
	   sinkStatus = kSinkUnknownError;
	   break;
      }
      returnValue.insert( OutputSinksStatus::value_type(
	 sinkStatus,
	 DataSinkDescriptor(*(*itSink)) ) );
   }

   return returnValue;
}

DataSinkDescriptors
FrameStorer::sinks( void ) const
{
   DataSinkDescriptors returnValue;
   
   DataSinkControllers::const_iterator itEnd = m_dataSinkControllers.end();
   for( DataSinkControllers::const_iterator 
	   itController = m_dataSinkControllers.begin();
	itController != itEnd;
	++itController){
      DataSinkDescriptor temp( *(*itController) );
      returnValue.push_back( temp );
   }

   return returnValue;
}

DABoolean 
FrameStorer::mustSequentiallyStore( void ) const
{
   return m_mustSequentiallyStore;
}

DABoolean
FrameStorer::contains( const Stream::Type& aStream ) const
{
   return ( m_streamToRecordStorerMap.end() 
	    != m_streamToRecordStorerMap.find( aStream ) ) ;
}

//
// static member functions
//
