// -*- C++ -*-
//
// Package:     BlankRecordDelivery
// Module:      BlankRecordProxyDeliverer
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D. Jones
// Created:     Thu Mar 26 14:06:58 EST 1998
// $Id: BlankRecordProxyDeliverer.cc,v 1.1.1.1 1998/03/31 21:21:19 cdj Exp $
//
// Revision history
//
// $Log: BlankRecordProxyDeliverer.cc,v $
// Revision 1.1.1.1  1998/03/31 21:21:19  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "BlankRecordDelivery/BlankRecordProxyDeliverer.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "BlankRecordDelivery.BlankRecordProxyDeliverer" ;

//
// static data member definitions
//

//
// constructors and destructor
//
BlankRecordProxyDeliverer::BlankRecordProxyDeliverer( 
   const Stream::Set& iStreamsToRegister ) :
   ProxyDeliverer( "BlankRecordProxyDeliverer" )
{
   Stream::Set::const_iterator itEnd = iStreamsToRegister.end();
   for( Stream::Set::const_iterator itStream = iStreamsToRegister.begin();
	itStream != itEnd;
	++itStream ){
      registerStream( *itStream );
   }
}

// BlankRecordProxyDeliverer::BlankRecordProxyDeliverer( const BlankRecordProxyDeliverer& )
// {
// }

BlankRecordProxyDeliverer::~BlankRecordProxyDeliverer()
{
}

//
// assignment operators
//
// const BlankRecordProxyDeliverer& BlankRecordProxyDeliverer::operator=( const BlankRecordProxyDeliverer& )
// {
// }

//
// member functions
//
void 
BlankRecordProxyDeliverer::disable( const Stream::Type& ) 
{}
void 
BlankRecordProxyDeliverer::enable( const Stream::Type& )
{}

void 
BlankRecordProxyDeliverer::resetCache( const Stream::Type& ) 
{}

void 
BlankRecordProxyDeliverer::registerProxies( const Stream::Type& ,
					    KeyedProxies& )
{}

//
// const member functions
//

//
// static member functions
//
