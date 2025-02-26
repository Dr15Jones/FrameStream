#if !defined(BLANKRECORDDELIVERY_BLANKRECORDSOURCECONTROLLER_H)
#define BLANKRECORDDELIVERY_BLANKRECORDSOURCECONTROLLER_H
// -*- C++ -*-
//
// Package:     BlankRecordDelivery
// Module:      BlankRecordSourceController
// 
// Description: Puts blank Records into the Frame
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Thu Mar 26 13:46:16 EST 1998
// $Id: BlankRecordSourceController.h,v 1.1.1.1 1998/03/31 21:21:18 cdj Exp $
//
// Revision history
//
// $Log: BlankRecordSourceController.h,v $
// Revision 1.1.1.1  1998/03/31 21:21:18  cdj
// first submission
//

// system include files

// user include files
#include "DataDelivery/DataSourceController.h"

// forward declarations
class BlankRecordStopsBase;

class BlankRecordSourceController : public DataSourceController
{
      // friend classes and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      BlankRecordSourceController( const string& iName,
	                           const Stream::Set& iStreams,
				   BlankRecordStopsBase* iStops );
      virtual ~BlankRecordSourceController();

      // member functions
      
      DataSourceController::SyncStatus
        synchronizeSource( const SyncValue& iSyncTo ) ;

      virtual DataSourceController::SearchStatus
               findNextRecord(SyncValue& oSyncValueOfNextRecord,
			      Stream::Type& oRecordTypeOfNextRecord );

      virtual DataSourceController::SearchStatus 
               gotoNextRecord( void );


      // const member functions
      virtual DABoolean canRandomAccess( void ) const;

      virtual string dataSourceID( void ) const ;

      virtual string parameters( void ) const ;
      // static member functions

      static string buildParameters( const Stream::Set& iStreams );

   protected:
      // protected member functions
      virtual void implementSetForcedSequentialAccess( DABoolean iFlag );

      // protected const member functions
      virtual ProxyDeliverer* createProxyDeliverer( void ) const ;

   private:
      // Constructors and destructor
      BlankRecordSourceController();
      BlankRecordSourceController( const BlankRecordSourceController& );

      // assignment operator(s)
      const BlankRecordSourceController& operator=( const BlankRecordSourceController& );

      // private member functions
      void readRecords( const SyncValue& iRecordsSyncValue );
      void clearRecords();

      // private const member functions

      // data members
      string m_name;
      Stream::Set& m_makeRecords;
      BlankRecordStopsBase* m_stops;
      SyncValue m_presentRecordSyncValue;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "BlankRecordDelivery/Template/BlankRecordSourceController.cc"
//#endif

#endif /* BLANKRECORDDELIVERY_BLANKRECORDSOURCECONTROLLER_H */
