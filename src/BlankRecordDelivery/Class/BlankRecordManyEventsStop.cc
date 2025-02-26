// -*- C++ -*-
//
// Package:     <BlankRecordDelivery>
// Module:      BlankRecordManyEventsStop
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D. Jones
// Created:     Wed Dec  2 10:54:43 EST 1998
// $Id: BlankRecordManyEventsStop.cc,v 1.1 1998/12/02 19:31:17 cdj Exp $
//
// Revision history
//
// $Log: BlankRecordManyEventsStop.cc,v $
// Revision 1.1  1998/12/02 19:31:17  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "BlankRecordDelivery/BlankRecordManyEventsStop.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "BlankRecordDelivery.BlankRecordManyEventsStop" ;

//
// static data member definitions
//

//
// constructors and destructor
//
BlankRecordManyEventsStop::BlankRecordManyEventsStop( 
   unsigned int iRunNumber,
   unsigned int iNumberOfRecords) :
   m_runNumber( iRunNumber ),
   m_nRecords( iNumberOfRecords )
{
}

// BlankRecordManyEventsStop::BlankRecordManyEventsStop( const BlankRecordManyEventsStop& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

BlankRecordManyEventsStop::~BlankRecordManyEventsStop()
{
}

//
// assignment operators
//
// const BlankRecordManyEventsStop& BlankRecordManyEventsStop::operator=( const BlankRecordManyEventsStop& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//

//
// const member functions
//
DataSourceController::SyncStatus  
BlankRecordManyEventsStop::synchronizeTo( const SyncValue& iSyncTo,
				       SyncValue& oNewSyncValue ) const
{
   if( iSyncTo.runNumber() < m_runNumber ||
      ( (iSyncTo.runNumber() == m_runNumber) && 
	(iSyncTo.eventNumber() == 0 ) ) ) {
      oNewSyncValue=SyncValue::kUndefined;
      return DataSourceController::kSyncFailedToSync;
   }

   if( iSyncTo.runNumber() > m_runNumber ) {
      oNewSyncValue = SyncValue( m_runNumber, m_nRecords );
      return DataSourceController::kSyncWarningAtEndOfSource;
   }

   if( iSyncTo.eventNumber() >= m_nRecords ) {
      oNewSyncValue = SyncValue( m_runNumber, m_nRecords );
      return DataSourceController::kSyncWarningAtEndOfSource;
   }
      
   oNewSyncValue = iSyncTo;
   return DataSourceController::kSyncNoError;
}

DataSourceController::SearchStatus
BlankRecordManyEventsStop::findNext( const SyncValue& iPresentValue,
				     SyncValue& oNewSyncValue ) const
{
   if( iPresentValue.runNumber() < m_runNumber ) {
      oNewSyncValue = SyncValue( m_runNumber, 1 );
   } else {
      if( iPresentValue.runNumber() == m_runNumber ) {
	 oNewSyncValue = SyncValue( iPresentValue.runNumber(),
				    iPresentValue.eventNumber() +1 );
      
	 if( oNewSyncValue.eventNumber() > m_nRecords ) {
	    oNewSyncValue= SyncValue( m_runNumber,
				      m_nRecords );
	    return DataSourceController::kSearchEndOfSource;
	 }
      } else {
	 oNewSyncValue = SyncValue( m_runNumber, m_nRecords );
	 return DataSourceController::kSearchEndOfSource;
      }
   }
   return DataSourceController::kSearchNoError;
}

BlankRecordStopsBase* 
BlankRecordManyEventsStop::clone() const
{
   return new BlankRecordManyEventsStop( m_runNumber, m_nRecords );
}

//
// static member functions
//
