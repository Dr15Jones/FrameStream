// -*- C++ -*-
//
// Package:     DataDelivery
// Module:      DataSourceController
// 
// Description: Abstract base class for classes used to read
//              from different data sources
//
// Implimentation:
//     At the moment, findNextEvent and gotoNextEvent are give a Stream::Set
//     containing which of their streams are Active.  Since in the present
//     implementation Stream::Type is a string, this could requires a number
//     of string compares to be done each time find/gotoNextEvent is called.
//     To alleviate this overhead, we could add a method setActiveStreams
//     so that the DataSourceController can no its active streams up front
//     that way it might be able to optimize its search.
//
// Author:      Chris D. Jones
// Created:     Sun Mar 16 13:25:11 EST 1997
// $Id: DataSourceController.cc,v 1.11 1997/09/18 21:07:07 cdj Exp $
//
// Revision history
//
// $Log: DataSourceController.cc,v $
// Revision 1.11  1997/09/18 21:07:07  cdj
// changed Boolean to DABoolean
//
// Revision 1.10  1997/08/27 03:39:23  sjp
// Updated to new name for bug flags
//
// Revision 1.9  1997/08/06 16:17:35  sjp
// Changed to use ProxyDeliverer
//
// Revision 1.8  1997/08/06 15:55:33  sjp
// Added required bug flag
//
// Revision 1.7  1997/07/25 23:24:28  cdj
// Modified to work with ChainSourceController
//
// Revision 1.6  1997/07/09 18:00:39  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.5  1997/06/29 20:03:21  cdj
// Initializes m_currentStop to Stream::kNone since Stream::kNoStops no longer
// exists
//
// Revision 1.4  1997/05/02 19:56:07  cdj
// 1) now knows about Active Streams
// 2) now base class manages ProxyDeliverer
// 3) simplified some method interfaces
// 4) moved some implementations into the base class
// 5) improved documentation
//
// Revision 1.3  1997/04/10 01:11:40  sjp
// Removed extra include file that is not required
//
// Revision 1.2  1997/04/01 16:00:40  sjp
// Correct initialisation order in constructor
//
// Revision 1.1  1997/03/20 22:46:40  cdj
// First submission
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataDelivery/ProxyDeliverer.h"
#include "DataDelivery/DataSourceController.h"
#include "DataHandler/StreamSet.h"


// STL classes

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DataSourceController::DataSourceController( void ) :
   m_currentStop( Stream::kNone ),
   m_readStreams( *( new Stream::Set) ),
   m_activeStreams( *( new Stream::Set) ),
   m_initializationStatus( DataSourceController::kInitNoError ),
   m_forcedSequentialAccess( false ) ,
   m_isSequentiallyAccessing( false ),
   m_proxyDeliverer( 0 ),
   m_ownsDeliverer(true)
{
   assert( 0 != &m_readStreams);
   assert( 0 != &m_activeStreams);
 
}

DataSourceController::DataSourceController(ProxyDeliverer* iDeliverer ) :
   m_currentStop( Stream::kNone ),
   m_readStreams( *( new Stream::Set) ),
   m_activeStreams( *( new Stream::Set) ),
   m_initializationStatus( DataSourceController::kInitNoError ),
   m_forcedSequentialAccess( false ) ,
   m_isSequentiallyAccessing( false ),
   m_proxyDeliverer( iDeliverer ),
   m_ownsDeliverer(false)
{
   assert( 0 != &m_readStreams);
   assert( 0 != &m_activeStreams);
 
}

// DataSourceController::DataSourceController( const DataSourceController& )
// {
// }

DataSourceController::~DataSourceController()
{
   delete &m_readStreams;
   delete &m_activeStreams;
   if( m_ownsDeliverer ){
      delete m_proxyDeliverer;
   }
}

//
// assignment operators
//
// const DataSourceController& DataSourceController::operator=( const DataSourceController& )
// {
// }

//
// member functions
//
DABoolean
DataSourceController::setRecordsToRetrieve( const Stream::Set& iRetrieve )
{
   //Check to make sure that the source can deliver all the records that
   //  are being requested
   DABoolean isOK( potentialRecordsToRetrieve().contains( iRetrieve ) );

   if( isOK ){
      m_readStreams = iRetrieve;
   } else {
      clearRecordsToRetrieve();
   }

   return isOK;
}

void
DataSourceController::clearRecordsToRetrieve( void )
{
   m_readStreams.erase( m_readStreams.begin(),
			m_readStreams.end());
   m_readStreams.insert( Stream::kNone );
}

DABoolean
DataSourceController::setActiveStreams( const Stream::Set& iActive )
{
   //Check to make sure that the source can deliver all the records that
   //  are being requested
   DABoolean isOK( recordsToRetrieve().contains( iActive ) );

   if( isOK ){
      m_activeStreams = iActive;
      callWhenActiveStreamsChange();
   } else {
      clearActiveStreams();
   }

   return isOK;
}

void
DataSourceController::clearActiveStreams( void )
{
   m_activeStreams.erase( m_activeStreams.begin(),
			  m_activeStreams.end());
   m_activeStreams.insert( Stream::kNone );

   callWhenActiveStreamsChange();
}

void
DataSourceController::setForcedSequentialAccess( DABoolean iFlag )
{
   m_forcedSequentialAccess = iFlag;
   implementSetForcedSequentialAccess( iFlag );

   if( iFlag ){
      setIsSequentiallyAccessing( true );
   }
}

void
DataSourceController::setSyncValue( const SyncValue& iSynch )
{
   m_syncValue = iSynch;
}

void 
DataSourceController::setCurrentStop( const Stream::Type& iStop )
{
   m_currentStop = iStop;
}

void 
DataSourceController::setInitializationStatus( 
   DataSourceController::InitializationStatus iStatus )
{
   m_initializationStatus = iStatus;
}

void
DataSourceController::setIsSequentiallyAccessing( DABoolean iFlag )
{
   if( iFlag || canRandomAccess() ) {
      
      m_isSequentiallyAccessing = iFlag;
   } 
}

void
DataSourceController::callWhenActiveStreamsChange( void )
{
//Default is to do nothing
}
//
// const member functions
//

const Stream::Set
DataSourceController::potentialRecordsToRetrieve( void ) const
{
   //Get this info from the ProxyDeliverer
   return (*(proxyDeliverer())).supplies();
}

const Stream::Set&
DataSourceController::recordsToRetrieve( void ) const
{
   return m_readStreams;
}

const Stream::Set&
DataSourceController::activeStreams( void ) const
{
   return m_activeStreams;
}

DABoolean
DataSourceController::isSequentiallyAccessing( void ) const
{
   return m_isSequentiallyAccessing;
}

DABoolean
DataSourceController::forcedSequentialAccess( void ) const
{
   return m_forcedSequentialAccess;
}

const SyncValue&
DataSourceController::currentSyncValue( void ) const
{
   return m_syncValue;
}

const Stream::Type&
DataSourceController::currentStop( void ) const
{
   return m_currentStop;
}

DataSourceController::InitializationStatus
DataSourceController::initializationStatus( void ) const
{
   return m_initializationStatus;
}

ProxyDeliverer*
DataSourceController::proxyDeliverer( void ) const
{
   if( 0 == m_proxyDeliverer ){
      //until mutable, we need to cast away the const
      (*((DataSourceController*) this)).m_proxyDeliverer =
	 createProxyDeliverer();
      assert( 0 != m_proxyDeliverer);
      //Since we created it, we own it
      (*((DataSourceController*) this)).m_ownsDeliverer = true;
   }
   return m_proxyDeliverer;
}
//
// static member functions
//

