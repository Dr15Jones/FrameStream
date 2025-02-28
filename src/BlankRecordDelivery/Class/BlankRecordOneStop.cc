// -*- C++ -*-
//
// Package:     <BlankRecordDelivery>
// Module:      BlankRecordOneStop
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D. Jones
// Created:     Sun Mar 29 12:06:29 EST 1998
// $Id: BlankRecordOneStop.cc,v 1.1.1.1 1998/03/31 21:21:19 cdj Exp $
//
// Revision history
//
// $Log: BlankRecordOneStop.cc,v $
// Revision 1.1.1.1  1998/03/31 21:21:19  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "BlankRecordDelivery/BlankRecordOneStop.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "BlankRecordDelivery.BlankRecordOneStop" ;

//
// static data member definitions
//

//
// constructors and destructor
//
BlankRecordOneStop::BlankRecordOneStop( const SyncValue& iStop ) :
   m_stop( iStop )
{
}

// BlankRecordOneStop::BlankRecordOneStop( const BlankRecordOneStop& )
// {
// }

BlankRecordOneStop::~BlankRecordOneStop()
{
}

//
// assignment operators
//
// const BlankRecordOneStop& BlankRecordOneStop::operator=( const BlankRecordOneStop& )
// {
// }

//
// member functions
//

DataSourceController::SyncStatus  
BlankRecordOneStop::synchronizeTo( const SyncValue& iSyncTo,
				   SyncValue& oNewSyncValue ) const
{
   if( iSyncTo < m_stop ){
      oNewSyncValue = SyncValue::kUndefined;
      return DataSourceController::kSyncFailedToSync;
   } 
   oNewSyncValue = m_stop;
   if( iSyncTo > m_stop ){
      //this is what should be done, but suez can't handle it
      //return DataSourceController::kSyncWarningAtEndOfSource;
   }
   return DataSourceController::kSyncNoError;
}

DataSourceController::SearchStatus
BlankRecordOneStop::findNext( const SyncValue& iPresentValue,
			      SyncValue& oNewSyncValue ) const
{
   oNewSyncValue = m_stop;
   if( iPresentValue < m_stop ){
      return DataSourceController::kSearchNoError;
   }
   return DataSourceController::kSearchEndOfSource;
}

BlankRecordStopsBase* 
BlankRecordOneStop::clone() const
{
   return new BlankRecordOneStop( m_stop );
}
//
// const member functions
//

//
// static member functions
//
