#if !defined(BLANKRECORDDELIVERY_BLANKRECORDSTOPSBASE_H)
#define BLANKRECORDDELIVERY_BLANKRECORDSTOPSBASE_H
// -*- C++ -*-
//
// Package:     BlankRecordDelivery
// Module:      BlankRecordStopsBase
// 
// Description: Abstract base value for classes used to set the SyncValues
//               for the Records made by BlankRecordSourceController
//
// Usage:
//    Since this class is only used by BlankRecordSourceController, I'll
//    discuss how to make a class that inherits from this one rather than
//    discuss how to use the class.
//
//    Inheriting classes must define three methods
//      1) synchronizeTo
//      2) findNext
//      3) clone
//
//    Requirements on 'synchronizeTo'
//      This function determines the SyncValue for the source that is closest
//      to but not larger than iSyncTo.  
//       - If all the source's SyncValues are greater than iSyncTo then set 
//         oNewSyncValue=SyncValue::kUndefined and return 
//         DataSourceController::kSyncFailedToSync.
//       - If iSyncTo is larger than the largest source's SyncValue, return
//         DataSourceController::kSyncWarningAtEndOfSource
//       - On all other cases return DataSourceController::kSyncNoError
//     
//    Requirements on 'findNext'
//      This function determines the SyncValue for the source that is closest
//      to but not smaller than or equal to iPresentValue.  The value of
//      iPresentValue will normally be the last value returned by either
//      findNext or synchronizeTo.
//       - If the found SyncValue is the last SyncValue for the source,
//         return DataSourceController::kSearchEndOfSource
//       - else return DataSourceController::kSearchNoError 
//
//    Requirments on 'clone'
//      This function returns a newly created instance of the class which
//      has the exact same state as the instance that created it.  I.e. it
//      creates a perfect clone of the class instance.
//
// Author:      Chris D. Jones
// Created:     Sun Mar 29 11:28:09 EST 1998
// $Id: BlankRecordStopsBase.h,v 1.1.1.1 1998/03/31 21:21:18 cdj Exp $
//
// Revision history
//
// $Log: BlankRecordStopsBase.h,v $
// Revision 1.1.1.1  1998/03/31 21:21:18  cdj
// first submission
//

// system include files

// user include files
#include "DataDelivery/DataSourceController.h"

// forward declarations
class SyncValue;

class BlankRecordStopsBase
{
      // friend classes and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      BlankRecordStopsBase() {}
      virtual ~BlankRecordStopsBase();

      // member functions

      // const member functions
      virtual DataSourceController::SyncStatus  
                     synchronizeTo( const SyncValue& iSyncTo,
				    SyncValue& oNewSyncValue ) const = 0;
      virtual DataSourceController::SearchStatus
                     findNext( const SyncValue& iPresentValue,
			       SyncValue& oNewSyncValue ) const = 0;

      virtual BlankRecordStopsBase* clone() const = 0;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      BlankRecordStopsBase( const BlankRecordStopsBase& );

      // assignment operator(s)
      const BlankRecordStopsBase& operator=( const BlankRecordStopsBase& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "BlankRecordDelivery/Template/BlankRecordStopsBase.cc"
//#endif

#endif /* BLANKRECORDDELIVERY_BLANKRECORDSTOPSBASE_H */
