#if !defined(BLANKRECORDDELIVERY_BLANKRECORDMANYEVENTSSTOP_H)
#define BLANKRECORDDELIVERY_BLANKRECORDMANYEVENTSSTOP_H
// -*- C++ -*-
//
// Package:     BlankRecordDelivery
// Module:      BlankRecordManyEventsStop
// 
// Description: A type of BlankRecordStopsBase that stops on different
//               event numbers within a given run number
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Wed Dec  2 10:50:49 EST 1998
// $Id: BlankRecordManyEventsStop.h,v 1.1 1998/12/02 19:31:09 cdj Exp $
//
// Revision history
//
// $Log: BlankRecordManyEventsStop.h,v $
// Revision 1.1  1998/12/02 19:31:09  cdj
// first submission
//

// system include files

// user include files
#include "BlankRecordDelivery/BlankRecordStopsBase.h"

// forward declarations

class BlankRecordManyEventsStop : public BlankRecordStopsBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      BlankRecordManyEventsStop( unsigned int iRunNumber,
				 unsigned int iNumberOfRecords );
      virtual ~BlankRecordManyEventsStop();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual DataSourceController::SyncStatus  
                     synchronizeTo( const SyncValue& iSyncTo,
				    SyncValue& oNewSyncValue ) const;
      virtual DataSourceController::SearchStatus
                     findNext( const SyncValue& iPresentValue,
			       SyncValue& oNewSyncValue ) const;

      virtual BlankRecordStopsBase* clone() const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      BlankRecordManyEventsStop( const BlankRecordManyEventsStop& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const BlankRecordManyEventsStop& operator=( const BlankRecordManyEventsStop& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      unsigned int m_runNumber;
      unsigned int m_nRecords;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "BlankRecordDelivery/Template/BlankRecordManyEventsStop.cc"
//#endif

#endif /* BLANKRECORDDELIVERY_BLANKRECORDMANYEVENTSSTOP_H */
