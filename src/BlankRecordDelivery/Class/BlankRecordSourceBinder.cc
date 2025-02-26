// -*- C++ -*-
//
// Package:     <BlankRecordDelivery>
// Module:      BlankRecordSourceBinder
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D. Jones
// Created:     Thu Mar 26 14:06:51 EST 1998
// $Id: BlankRecordSourceBinder.cc,v 1.1.1.1 1998/03/31 21:21:19 cdj Exp $
//
// Revision history
//
// $Log: BlankRecordSourceBinder.cc,v $
// Revision 1.1.1.1  1998/03/31 21:21:19  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "BlankRecordDelivery/BlankRecordSourceBinder.h"
#include "BlankRecordDelivery/BlankRecordSourceController.h"
#include "BlankRecordDelivery/BlankRecordStopsBase.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "BlankRecordDelivery.BlankRecordSourceBinder" ;

//
// static data member definitions
//

//
// constructors and destructor
//
BlankRecordSourceBinder::BlankRecordSourceBinder( 
                              const string& iSourceName,
			      const Stream::Set& iUseStreams,
			      BlankRecordStopsBase* iStops ) :
   DataSourceBinder( iSourceName,
		     BlankRecordSourceController::buildParameters(iUseStreams),
		     iUseStreams ),
   m_stops( iStops )
{
}

// BlankRecordSourceBinder::BlankRecordSourceBinder( const BlankRecordSourceBinder& )
// {
// }

BlankRecordSourceBinder::~BlankRecordSourceBinder()
{
   delete m_stops;
}

//
// assignment operators
//
// const BlankRecordSourceBinder& BlankRecordSourceBinder::operator=( const BlankRecordSourceBinder& )
// {
// }

//
// member functions
//

//
// const member functions
//
DataSourceController*
BlankRecordSourceBinder::createDataSourceController( void ) const
{
   return new BlankRecordSourceController( dataSourceID(),
					   boundStreams(),
					   m_stops->clone() );
}

//
// static member functions
//
