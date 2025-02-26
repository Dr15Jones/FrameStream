#if !defined(BLANKRECORDDELIVERY_BLANKRECORDMANYRUNSSTOP_H)
#define BLANKRECORDDELIVERY_BLANKRECORDMANYRUNSSTOP_H
// -*- C++ -*-
//
// Package:     BlankRecordDelivery
// Module:      BlankRecordManyRunsStop
// 
// Description: A type of BlankRecordStopsBase that stops on different
//              run boundaries
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Tue Dec  1 13:28:07 EST 1998
// $Id: BlankRecordManyRunsStop.h,v 1.1 1998/12/02 19:31:11 cdj Exp $
//
// Revision history
//
// $Log: BlankRecordManyRunsStop.h,v $
// Revision 1.1  1998/12/02 19:31:11  cdj
// first submission
//

// system include files

// user include files
#include "BlankRecordDelivery/BlankRecordStopsBase.h"

// forward declarations

class BlankRecordManyRunsStop : public BlankRecordStopsBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      BlankRecordManyRunsStop( unsigned int iStartNumber,
			       unsigned int iNumberOfRecords );
      virtual ~BlankRecordManyRunsStop();

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
      BlankRecordManyRunsStop() ; //stop default
      BlankRecordManyRunsStop( const BlankRecordManyRunsStop& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const BlankRecordManyRunsStop& operator=( const BlankRecordManyRunsStop& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      unsigned int m_start;
      unsigned int m_nRecords;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "BlankRecordDelivery/Template/BlankRecordManyRunsStop.cc"
//#endif

#endif /* BLANKRECORDDELIVERY_BLANKRECORDMANYRUNSSTOP_H */
