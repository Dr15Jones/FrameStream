// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      BinaryRawEventProxy
// 
// Description: Constructs and fills a RawEventData for binary reads
//
// Implimentation:
//     
//
// Author:      David L. Kreinick
// Created:     Mon Nov  9 12:11:51 EST 1998
// $Id: BinaryRawEventProxy.cc,v 1.3 1999/12/10 16:20:30 cdj Exp $
//
// Revision history
//
// $Log: BinaryRawEventProxy.cc,v $
// Revision 1.3  1999/12/10 16:20:30  cdj
// updated to work with extract exceptions
//
// Revision 1.2  1999/04/15 19:11:40  dlk
// DLK Major revision
// 	The EventHeader must be the first raw data unit inside the event
// 	The 6-word binary header is no longer made -- I use EventHeader
// 	The code supports all record types
// 		BeginRun, StartData, Event, Pause, EndRun ...
// 	Currently, the code currently works for bigendian machines only
//
// Revision 1.1  1998/12/01 19:50:51  dlk
// DLK: New proxy for creating RawEventData from a binary input file
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#include <vector>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "BinaryDelivery/BinaryRawEventProxy.h"
#include "BinaryDelivery/BDRecordBuffer.h"
#include "RawData/RawEventData.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "BinaryDelivery.BinaryRawEventProxy" ;
const DABoolean kDontTakeOwnership = false ;  //We want to own m_BinaryRawEvent

//
// static data member definitions
//

//
// constructors and destructor
//
BinaryRawEventProxy::BinaryRawEventProxy( BinaryProxyDeliverer& iDeliver ):
   m_BinaryRawEvent( 0 ),
   m_BinaryProxyDeliverer( &iDeliver )
{
}

// BinaryRawEventProxy::BinaryRawEventProxy( const BinaryRawEventProxy& iproxy )
// {
//   *this = iproxy;
// }

BinaryRawEventProxy::~BinaryRawEventProxy()
{
   invalidateCache() ;
//   delete m_BinaryProxyDeliverer ;
}

//
// assignment operators
//
// const BinaryRawEventProxy& BinaryRawEventProxy::operator=( const BinaryRawEventProxy& iproxy )
// {
//   if( this != &iproxy ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iproxy );
//   }
//
//   return *this;
// }

//
// member functions
//
void
BinaryRawEventProxy::invalidateCache()
{
   delete m_BinaryRawEvent ;
   m_BinaryRawEvent = 0 ;
}

const BinaryRawEventProxy::value_type*
BinaryRawEventProxy::faultHandler( const Record& iRecord,
				   const DataKey& iKey )
// We have no need here for either of the arguments.  They are for
//  compatibility with faultHandlers for other proxies.
{
   // be assertive: there should be no cached data at this point
   // If there is, someone forgot to call invalidateCache
   assert( 0 == m_BinaryRawEvent );

// Locate the record buffer for the event stream
// We are assured that this buffer will not be altered until cache
//  is invalidated, so there's no need for a private copy of the data 
   BDRecordBuffer* buffer = (*m_BinaryProxyDeliverer).buffer( Stream::kEvent );

// Now build a RawEvent and serve it up to the caller
   m_BinaryRawEvent = new RawEventData( (*buffer).beginOfBuffer(),
					kDontTakeOwnership );
   if( 0 == m_BinaryRawEvent )
   {
      report( EMERGENCY, kFacilityString )
	 << "can't allocate memory; aborting" << std::endl;
      assert( false );
      ::exit( 1 );
   }
   
   return ( m_BinaryRawEvent ) ;
}

//
// const member functions
//

//
// static member functions
//


