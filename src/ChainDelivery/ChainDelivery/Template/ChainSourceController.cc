#if !defined(CHAINDELIVERY_CHAINSOURCECONTROLLER_CC)
#define CHAINDELIVERY_CHAINSOURCECONTROLLER_CC
// -*- C++ -*-
//
// Package:     ChainDelivery
// Module:      ChainSourceController
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Fri Jul 25 14:09:28 EDT 1997
// $Id: ChainSourceController.cc,v 1.16 2003/04/09 14:37:14 cdj Exp $
//
// Revision history
//
// $Log: ChainSourceController.cc,v $
// Revision 1.16  2003/04/09 14:37:14  cdj
// cleaned up the code
//
// Revision 1.15  2003/04/08 14:20:48  tom
// Fixed placement of else statement to get code to compile
//
// Revision 1.14  2003/04/08 14:10:12  cdj
// attempt to improve chaining of Driver sources
//
// Revision 1.13  2003/04/02 19:50:16  cdj
// tried to improve findNextRecord to work better with DriverDelivery
//
// Revision 1.12  2001/05/31 16:55:18  cdj
// fixed memory leak
//
// Revision 1.11  1998/10/21 15:31:13  marsh
// Protected against multiple inclusion.
//
// Revision 1.10  1998/09/16 21:45:19  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.9  1998/07/29 02:27:04  mkl
// switch to static const char* const kFacilityString
//
// Revision 1.8  1997/09/18 20:50:59  cdj
// Changed Boolean to DABoolean
//
// Revision 1.7  1997/09/03 20:06:52  sjp
// Uses CPP macros for STL containers
//
// Revision 1.6  1997/09/01 15:35:47  sjp
// Changed report include to be in Experiment
//
// Revision 1.5  1997/08/27 03:41:16  sjp
// Updated to new name for bug flags
//
// Revision 1.4  1997/08/14 11:44:05  sjp
// Mods to run under CW Pro 1
//
// Revision 1.3  1997/08/08 17:07:46  cdj
// Updated to work with Proxies
//
// Revision 1.2  1997/07/26 19:52:42  cdj
// Fixed a bug in synchronization which caused an infinitely loop when it
// was at the end of one source but shouldn't yet go to the next source.
//
// Revision 1.1.1.1  1997/07/25 23:35:24  cdj
// First submission. Compiles but untested
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <deque>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h" // For error report
#include "ChainDelivery/ChainSourceController.h"

// STL classes

//
// constants, enums and typedefs
//
static const char* const 
kChainSourceControllerFacilityString = "ChainDelivery.ChainSourceController" ;

//
// static data member definitions
//

//
// constructors and destructor
//

template< class Binder >
ChainSourceController<Binder>::ChainSourceController( 
				const std::string& iName,
#if defined(TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG)
				const _chainsourcebinder_binders_& iBinders ,
#else
				const ChainSourceBinder< Binder >::Binders& iBinders,
#endif /* TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG */
				const Stream::Set& iReadStreams ):
   m_binders( *(new _chainsourcecontroller_deque_(iBinders.begin(),
						  iBinders.end() )) ),
   m_name( iName ),
   m_controller(0),
   m_deliverer(0),
   m_ownsDeliverer(true),
   m_waitingToUseNextSource(false),
   m_recordTypeOfNextSource( Stream::kNone )
{
   if( 0 == &m_binders){
      report(EMERGENCY,kChainSourceControllerFacilityString) 
	 <<"Out of Memory"<<std::endl;
      assert(false);
      exit(1);
   }

   //Create the first Controller in order to get a Deliverer
   Controller* tempController= 
      (Controller* ) m_binders.front().createDataSourceController();
   
   if( 0 == tempController ){
      report(EMERGENCY,kChainSourceControllerFacilityString) 
	 <<"Out of Memory"<<std::endl;
      assert(false);
      exit(1);
   }
   m_deliverer = (Deliverer*) (*tempController).createProxyDeliverer();
   if( 0 == m_deliverer ){
      report(EMERGENCY,kChainSourceControllerFacilityString) 
	 <<"Out of Memory"<<std::endl;
      assert(false);
      exit(1);
   }

   //Now get rid of the tempController
   delete tempController;

   //Using the new deliverer, create the first controller
   m_controller = m_binders.front().createSourceController( m_deliverer );
   if( 0 == m_controller ){
      report(EMERGENCY,kChainSourceControllerFacilityString) 
	 <<"Out of Memory"<<std::endl;
      assert(false);
      exit(1);
   }

   (*m_deliverer).changeSourceController( *m_controller );
   //Is everything OK?
   setInitializationStatus( (*m_controller).initializationStatus());
   if( kInitNoError != (*m_controller).initializationStatus() ){
      return;
   }

   if( ! setRecordsToRetrieve( iReadStreams ) ){
      //Note: should never get here since if this fails, it should have
      //      failed when we initialized m_controller;
      setInitializationStatus( 
	 DataSourceController::kInitInvalidStopsForSource );
   }

   setIsSequentiallyAccessing( (*m_controller).isSequentiallyAccessing() );
   
}

// ChainSourceController::ChainSourceController( const ChainSourceController& )
// {
// }

template< class Binder >
ChainSourceController<Binder>::~ChainSourceController()
{
   delete m_controller;
   if( m_ownsDeliverer ){
      delete m_deliverer;
   }
   delete &m_binders;
}

//
// assignment operators
//
// const ChainSourceController& ChainSourceController::operator=( const ChainSourceController& )
// {
// }

//
// member functions
//
template< class Binder >
DataSourceController::SyncStatus
ChainSourceController<Binder>::synchronizeSource( const SyncValue& iSyncTo )
{
  SyncStatus syncStatus( kSyncNoError);
  if( iSyncTo != currentSyncValue() ){
    if( !m_waitingToUseNextSource ) {
      //Haven't looked at next source yet so synchronize
      syncStatus = (*m_controller).synchronizeSource( iSyncTo );
      
      DABoolean noMoreSources(false);
      
      while( kSyncWarningAtEndOfSource == syncStatus && !noMoreSources ){
        //See if we should go to the next source
        m_waitingToUseNextSource=true; 
        SearchStatus searchStatus = findNextRecord( 
                                                   m_syncValueOfNextSource,
                                                   m_recordTypeOfNextSource );
        
        if( kSearchNoError == searchStatus ) {
	   if ( m_syncValueOfNextSource <= iSyncTo ){
             syncStatus = (*m_controller).synchronizeSource( iSyncTo );
	   } else {
	     //Next Records sync value is too large so use present record
	     syncStatus = kSyncNoError;
	   }
        } else {
          if( kSearchEndOfSource == searchStatus ){
            //There are no more sources
	     noMoreSources = true;
	     syncStatus = kSyncWarningAtEndOfSource;
          } else {
            //Some unknown problem
            syncStatus = kSyncProblemWithSource;
          }
        }
      }
    } else {
      //do we need to synchronize to the next source yet?
      if( m_syncValueOfNextSource <= iSyncTo ) {
        m_waitingToUseNextSource = false;
        syncStatus = synchronizeSource( iSyncTo );
      }
    }
  }
  
  setSyncValue( (*m_controller).currentSyncValue() );
  setCurrentStop( (*m_controller).currentStop() );

  return syncStatus;
}


template< class Binder >
DataSourceController::SearchStatus
ChainSourceController<Binder>::findNextRecord(
                                 SyncValue& oSyncValueOfNextRecord,
				 Stream::Type& oRecordTypeOfNextRecord )
{
   SearchStatus searchStatus = 
          (*m_controller).findNextRecord( oSyncValueOfNextRecord,
					  oRecordTypeOfNextRecord);

   while( kSearchEndOfSource == searchStatus ){
      //Get info on next source
      if( m_binders.size() == 1 || ! switchToNextSource () ){
	 if( m_binders.size() == 1 ) {
	    return kSearchEndOfSource;
	 }
	 //Had problem
	 return kSearchProblemWithSource;
      } else {
	 searchStatus = 
          (*m_controller).findNextRecord( oSyncValueOfNextRecord,
					  oRecordTypeOfNextRecord);
      }
   }
   return searchStatus;
   
}

template< class Binder >
DataSourceController::SearchStatus
ChainSourceController<Binder>::gotoNextRecord( void )
{

   SearchStatus searchStatus = (*m_controller).gotoNextRecord();

   DABoolean lastSource( false );
   //Need while just incase we have a source that has no records
   while( kSearchEndOfSource == searchStatus  && !lastSource ){
      if( 1 != m_binders.size() ){
	 //switch to the next source
	 if( ! switchToNextSource () ){
	    //Had problem
	    return kSearchProblemWithSource;
	 } else {
	    searchStatus = (*m_controller).gotoNextRecord();
	 }
      } else {
	 //Out of sources
	 lastSource = true;
      }
   }

   setSyncValue( (*m_controller).currentSyncValue() );
   setCurrentStop( (*m_controller).currentStop() );
   return searchStatus;
}

template< class Binder >
void
ChainSourceController<Binder>::addSource( const Binder& iBinder )
{
   m_binders.push_back( iBinder );
}

template< class Binder >
void 
ChainSourceController<Binder>::removeSource( const DataSourceDescriptor&
					     //iDescriptor
                                                          )
{

}


template< class Binder >
void
ChainSourceController<Binder>::implementSetForcedSequentialAccess( 
   DABoolean iFlag )
{
    (*m_controller).setForcedSequentialAccess( iFlag );
}


template< class Binder >
DABoolean
ChainSourceController<Binder>::switchToNextSource( void )
{
   //First, remove old source
   delete m_controller;
   m_binders.pop_front();

   m_controller = 0;
   if( m_binders.empty() ){
      //Can't switch since no more sources
      return false;
   }

   //Now create the new source
   m_controller = m_binders.front().createSourceController(m_deliverer );

   if( 0 == m_controller ){
      report(EMERGENCY,kChainSourceControllerFacilityString) 
	 <<"Out of Memory"<<std::endl;
      assert(false);
      exit(1);
   }

   (*m_deliverer).changeSourceController( *m_controller );

   (*m_controller).setForcedSequentialAccess( forcedSequentialAccess() );

   setIsSequentiallyAccessing( (*m_controller).isSequentiallyAccessing() );

   //Is everything OK?
   if( kInitNoError != (*m_controller).initializationStatus() ){
      return false;
   }

   //Everything went fine
   return true;
}

//
// const member functions
//

template< class Binder >
DABoolean
ChainSourceController<Binder>::canRandomAccess( void ) const
{
   return (*m_controller).canRandomAccess();
}

template< class Binder >
string
ChainSourceController<Binder>::dataSourceID( void ) const
{
   return m_name;
}

template< class Binder >
string
ChainSourceController<Binder>::parameters( void ) const
{
   returnstd::string("");
}

template< class Binder >
const std::string&
ChainSourceController<Binder>::name( void ) const
{
   return m_name;
}

template< class Binder >
ProxyDeliverer*
ChainSourceController<Binder>::createProxyDeliverer( void ) const
{
   (*((ChainSourceController<Binder>*) this)).m_ownsDeliverer = false;
   return m_deliverer;
}		     

//
// static member functions
//



#endif /* CHAINDELIVERY_CHAINSOURCECONTROLLER_CC */
