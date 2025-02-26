#if !defined(BLANKRECORDDELIVERY_BLANKRECORDONESTOP_H)
#define BLANKRECORDDELIVERY_BLANKRECORDONESTOP_H
// -*- C++ -*-
//
// Package:     BlankRecordDelivery
// Module:      BlankRecordOneStop
// 
// Description: A type of BlankRecordStopsBase that only has one Stop
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Sun Mar 29 11:58:20 EST 1998
// $Id: BlankRecordOneStop.h,v 1.3 2000/02/25 20:59:28 cdj Exp $
//
// Revision history
//
// $Log: BlankRecordOneStop.h,v $
// Revision 1.3  2000/02/25 20:59:28  cdj
// default time is now run=1 event=0
//
// Revision 1.2  1998/04/09 20:47:40  mkl
// declare implemented destructor
//
// Revision 1.1.1.1  1998/03/31 21:21:19  cdj
// first submission
//

// system include files

// user include files
#include "BlankRecordDelivery/BlankRecordStopsBase.h"
#include "DataHandler/SyncValue.h"

// forward declarations

class BlankRecordOneStop : public BlankRecordStopsBase
{
      // friend classes and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      BlankRecordOneStop( const SyncValue& iStop = 
	                                 SyncValue(1,0) );
      virtual ~BlankRecordOneStop();

      // member functions

      // const member functions
      virtual DataSourceController::SyncStatus  
                     synchronizeTo( const SyncValue& iSyncTo,
				    SyncValue& oNewSyncValue ) const;
      virtual DataSourceController::SearchStatus
                     findNext( const SyncValue& iPresentValue,
			       SyncValue& oNewSyncValue ) const;

      virtual BlankRecordStopsBase* clone() const;
      
      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      //BlankRecordOneStop();
      BlankRecordOneStop( const BlankRecordOneStop& );

      // assignment operator(s)
      const BlankRecordOneStop& operator=( const BlankRecordOneStop& );

      // private member functions

      // private const member functions

      // data members
      SyncValue m_stop;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "BlankRecordDelivery/Template/BlankRecordOneStop.cc"
//#endif

#endif /* BLANKRECORDDELIVERY_BLANKRECORDONESTOP_H */
