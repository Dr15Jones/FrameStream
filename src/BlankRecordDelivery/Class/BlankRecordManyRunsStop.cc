// -*- C++ -*-
//
// Package:     <BlankRecordDelivery>
// Module:      BlankRecordManyRunsStop
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D. Jones
// Created:     Tue Dec  1 13:31:20 EST 1998
// $Id: BlankRecordManyRunsStop.cc,v 1.1 1998/12/02 19:31:19 cdj Exp $
//
// Revision history
//
// $Log: BlankRecordManyRunsStop.cc,v $
// Revision 1.1  1998/12/02 19:31:19  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "BlankRecordDelivery/BlankRecordManyRunsStop.h"
#include "DataHandler/SyncValue.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "BlankRecordDelivery.BlankRecordManyRunsStop" ;

//
// static data member definitions
//

//
// constructors and destructor
//
BlankRecordManyRunsStop::BlankRecordManyRunsStop( 
   unsigned int iStartNumber,
   unsigned int iNumberOfRecords) :
   m_start( iStartNumber ),
   m_nRecords( iNumberOfRecords )
{
}

// BlankRecordManyRunsStop::BlankRecordManyRunsStop( const BlankRecordManyRunsStop& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

BlankRecordManyRunsStop::~BlankRecordManyRunsStop()
{
}

//
// assignment operators
//
// const BlankRecordManyRunsStop& BlankRecordManyRunsStop::operator=( const BlankRecordManyRunsStop& rhs )
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
BlankRecordManyRunsStop::synchronizeTo( const SyncValue& iSyncTo,
				       SyncValue& oNewSyncValue ) const
{
   if( iSyncTo.runNumber() < m_start ) {
      oNewSyncValue=SyncValue::kUndefined;
      return DataSourceController::kSyncFailedToSync;
   }

   if( iSyncTo.runNumber() >= m_start+m_nRecords ) {
      oNewSyncValue = SyncValue( m_start+m_nRecords - 1 );
      return DataSourceController::kSyncWarningAtEndOfSource;
   }

   oNewSyncValue = SyncValue( iSyncTo.runNumber() );
   return DataSourceController::kSyncNoError;
}

DataSourceController::SearchStatus
BlankRecordManyRunsStop::findNext( const SyncValue& iPresentValue,
				  SyncValue& oNewSyncValue ) const
{
   if( iPresentValue.runNumber() < m_start ) {
      oNewSyncValue = SyncValue( m_start );
   } else {
      oNewSyncValue = SyncValue( iPresentValue.runNumber() + 1 );

      if( oNewSyncValue.runNumber() > m_start+m_nRecords-1 ) {
	 oNewSyncValue= SyncValue( m_start+m_nRecords - 1 );
	 return DataSourceController::kSearchEndOfSource;
      }
   }
   return DataSourceController::kSearchNoError;
}

BlankRecordStopsBase* 
BlankRecordManyRunsStop::clone() const
{
   return new BlankRecordManyRunsStop( m_start, m_nRecords );
}

//
// static member functions
//
