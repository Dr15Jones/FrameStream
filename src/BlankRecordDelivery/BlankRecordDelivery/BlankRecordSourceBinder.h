#if !defined(BLANKRECORDDELIVERY_BLANKRECORDSOURCEBINDER_H)
#define BLANKRECORDDELIVERY_BLANKRECORDSOURCEBINDER_H
// -*- C++ -*-
//
// Package:     BlankRecordDelivery
// Module:      BlankRecordSourceBinder
// 
// Description: Creates a BlankRecordSourceController
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Thu Mar 26 13:46:20 EST 1998
// $Id: BlankRecordSourceBinder.h,v 1.1.1.1 1998/03/31 21:21:18 cdj Exp $
//
// Revision history
//
// $Log: BlankRecordSourceBinder.h,v $
// Revision 1.1.1.1  1998/03/31 21:21:18  cdj
// first submission
//

// system include files

// user include files
#include "DataDelivery/DataSourceBinder.h"
#include "DataHandler/SyncValue.h"

// forward declarations
class BlankRecordStopsBase;

class BlankRecordSourceBinder : public DataSourceBinder
{
      // friend classes and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      BlankRecordSourceBinder( const string& iSourceName,
			       const Stream::Set& iUseStreams,
			       BlankRecordStopsBase* iStops );
      virtual ~BlankRecordSourceBinder();

      // member functions

      // const member functions
      virtual DataSourceController*
        createDataSourceController( void ) const;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      BlankRecordSourceBinder();
      BlankRecordSourceBinder( const BlankRecordSourceBinder& );

      // assignment operator(s)
      const BlankRecordSourceBinder& operator=( const BlankRecordSourceBinder& );

      // private member functions

      // private const member functions

      // data members
      BlankRecordStopsBase* m_stops;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "BlankRecordDelivery/Template/BlankRecordSourceBinder.cc"
//#endif

#endif /* BLANKRECORDDELIVERY_BLANKRECORDSOURCEBINDER_H */
