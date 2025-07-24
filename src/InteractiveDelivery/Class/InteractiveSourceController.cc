// -*- C++ -*-
//
// Package:     InteractiveDelivery
// Module:      InteractiveSourceController
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Sat Apr 19 14:31:57 EDT 1997
// $Id: InteractiveSourceController.cc,v 1.9 2003/11/22 20:22:25 cdj Exp $
//
// Revision history
//
// $Log: InteractiveSourceController.cc,v $
// Revision 1.9  2003/11/22 20:22:25  cdj
// can now specify what stream should be used
//
// Revision 1.8  1998/09/26 19:56:21  cdj
// removed #include <assert.h> from within a #if defined block
//
// Revision 1.7  1997/09/18 21:25:23  cdj
// changed Boolean to DABoolean
//
// Revision 1.6  1997/09/01 15:35:22  sjp
// Changed report include to be in Experiment
//
// Revision 1.5  1997/08/27 03:39:40  sjp
// Updated to new name for bug flags
//
// Revision 1.4  1997/08/06 16:30:28  sjp
// Modified to use ProxyDeliverer
//
// Revision 1.3  1997/07/09 19:22:06  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.2  1997/05/02 20:32:46  cdj
// Conforms to new DataSourceController interface
//
// Revision 1.1.1.1  1997/04/21 19:30:11  cdj
// First submission
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h> // for exit
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "DataHandler/StreamSet.h"
#include "InteractiveDelivery/InteractiveSourceController.h"
#include "InteractiveDelivery/InteractiveSource.h"
#include "InteractiveDelivery/InteractiveProxyDeliverer.h"

// STL classes

//
// constants, enums and typedefs
//

//
// static data member definitions
//
const char* const
InteractiveSourceController::kID("interactive");

//
// constructors and destructor
//
InteractiveSourceController::InteractiveSourceController( InteractiveSource*
                                                          iSource ):
   m_source(iSource)
{
   Stream::Set streamSet;
   streamSet.add( iSource->stream() );
   setRecordsToRetrieve( streamSet );
   (*m_source).setSequentialAccess( false );
   setIsSequentiallyAccessing( false ); //Can do random accesses
}

// InteractiveSourceController::InteractiveSourceController( const InteractiveSourceController& )
// {
// }

InteractiveSourceController::~InteractiveSourceController()
{
}

//
// assignment operators
//
// const InteractiveSourceController& InteractiveSourceController::operator=( const InteractiveSourceController& )
// {
// }

//
// member functions
//
DataSourceController::SyncStatus
InteractiveSourceController::synchronizeSource( const SyncValue& )
{
   return DataSourceController::kSyncNoError;
}

DataSourceController::SearchStatus
InteractiveSourceController::findNextRecord( SyncValue& oSyncValueOfNextRecord,
			      Stream::Type& oRecordTypeOfNextRecord)
{
   DataSourceController::SearchStatus oStatus( kSearchNoError );
   SyncValue tempSync = (*m_source).syncValue();

   oRecordTypeOfNextRecord = m_source->stream();
   oSyncValueOfNextRecord = tempSync;
   if( forcedSequentialAccess() ){
      if( tempSync < currentSyncValue() ){
	 //User tried to go backwards when we are in 
	 //  forced sequential access mode
	 oStatus = DataSourceController::kSearchProblemWithSource;
      }
   }
   return oStatus;
}

DataSourceController::SearchStatus
InteractiveSourceController::gotoNextRecord( void )
{
   DataSourceController::SearchStatus oStatus( kSearchNoError);
   SyncValue tempSync = (*m_source).syncValue();

   if( forcedSequentialAccess() ){
      if( tempSync < currentSyncValue() ){
	 //User tried to go backwards when we are in 
	 //  forced sequential access mode
	 oStatus = DataSourceController::kSearchProblemWithSource;
	 return oStatus;
      }
   }
   oStatus = DataSourceController::kSearchNoError;
   setSyncValue( tempSync);
   setCurrentStop( m_source->stream() );
   return oStatus;
}

void
InteractiveSourceController::implementSetForcedSequentialAccess( DABoolean iFlag )
{
   //Tell source 
   (*m_source).setSequentialAccess( iFlag );
}
//
// const member functions
//
DABoolean
InteractiveSourceController::canRandomAccess( void ) const
{
   return true;
}

ProxyDeliverer*
InteractiveSourceController::createProxyDeliverer( void ) const
{
   ProxyDeliverer* returnValue = new InteractiveProxyDeliverer(m_source->stream());

   return returnValue;
}

std::string
InteractiveSourceController::dataSourceID( void ) const
{
   return std::string(kID);
}

std::string
InteractiveSourceController::parameters( void ) const
{
   return std::string("");
}

//
// static member functions
//


