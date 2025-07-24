// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      BinaryProxyDeliverer
// 
// Description: <one line class summary>
//
// Implementation:
//     Nearly all of this was cribbed from C.Jones' RoarProxyDeliverer
//
// Author:      David L. Kreinick
// Created:     Wed Oct 28 16:39:35 EST 1998
// $Id: BinaryProxyDeliverer.cc,v 1.7 2001/08/24 20:13:44 cleo3 Exp $
//
// Revision history
//
// $Log: BinaryProxyDeliverer.cc,v $
// Revision 1.7  2001/08/24 20:13:44  cleo3
// removed improper use of class
//
// Revision 1.6  2000/06/30 19:12:59  cdj
// removed ProxyDict dependencies
//
// Revision 1.5  1999/10/24 14:44:00  cdj
// removed inappropriate use of typename
//
// Revision 1.4  1999/09/13 18:51:28  dlk
// DLK: Tomasz Skwarnicki reported problems when working with events
//      as large as 750 kBytes.  Duh!  I forgot to expand the buffer
//      if it was too small to hold the incoming event.  I also improved
//      the error message to make clearer what is failing.
//
//      BinaryProxyDeliverer has only a couple cosmetic changes.
//
// Revision 1.3  1999/05/19 21:04:28  dlk
// DLK: BinaryProxyDeliverer.cc
// 	Add startRun and pauseRun, but kluge out pauseRun, which won't
// 	function properly because of a conceptual flaw in the system
// 	for assigning stream priorities.  Since almost no one will
// 	want to stop on pauseRun records, this shouldn't matter for now.
// DLK: BinarySourceController.cc
// 	Add startRun and pauseRun streams
// 	Add informative error message if user requests an unimplemented
// 	stream (like pauserun, for example)
//
// Revision 1.2  1998/12/01 18:06:04  dlk
// DLK: Repaired STL bug with <set>
//      Code now executes in suez
//
// Revision 1.1.1.1  1998/11/03 20:46:41  dlk
// importing new BinaryDelivery sources
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <set>
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "DataHandler/RecordMethods.h"
#include "BinaryDelivery/BinaryProxyDeliverer.h"
#include "BinaryDelivery/BinaryRawEventProxy.h"
#include "BinaryDelivery/BDRecordBuffer.h"

// STL classes
#include <vector>
#include <map>

//
// constants, enums and typedefs
//
typedef map< Stream::Type, BDRecordBuffer*, 
             less<Stream::Type> > StreamToBufferMap;
typedef vector< DABoolean > AvailableList ;

static const char* const kFacilityString = "BinaryDelivery.BinaryProxyDeliverer" ;

//
// static data member definitions
//

//
// constructors and destructor
//
BinaryProxyDeliverer::BinaryProxyDeliverer() :
   ProxyDeliverer( "Binary" ),
   m_streamToBufferMap( *( new StreamToBufferMap ) ),
   m_available( *(new AvailableList ) )
{
   if( (0 == &m_streamToBufferMap) ||
       (0 == &m_available ) ){
      report( ERROR ,
              kFacilityString )
                 << "Out of memory"
                 << std::endl ;
      assert( 0 != &m_streamToBufferMap ) ;
      assert( 0 != &m_available ) ;
      exit( 1 );
   }

   //Register the streams that we can read

   registerStream( Stream::kEvent );
   registerStream( Stream::kBeginRun );
   registerStream( Stream::kEndRun );
   registerStream( Stream::kStartRun );
//   KLUGE ALERT!!  KLUGE ALERT!!  -- dlk 5/19/1999
//   Due to a logical flaw in the record priority system, we cannot
//    properly deliver pauseRun records
//   That's why I have commented out the registration (the rest of
//    the pauseRun handling has been left in place)
//   Here's the problem.  PauseRun is given a priority just below
//    startrun and higher than event.  The first event in general
//    comes well before the first pauseRun, hence the frame will be
//    incomplete, lacking a pauseRun record.  Error condition aborts job.
//    We could get around this by issuing a phony pauseRun immediately
//    after the startRun, but that is ugly!!  If we lower the pauseRun
//    priority below that of an event, then a run starting with an
//    immediate HV trip would have the same trouble since the frame would
//    lack an event record.  For now, I choose to disallow stops on
//    pauseruns, which very few users would ever want to use anyhow.
//    To repair this involves replacing the priority system with
//    something which understands the dependencies of records on each other.

//   registerStream( Stream::kPauseRun );

}

// BinaryProxyDeliverer::BinaryProxyDeliverer( const BinaryProxyDeliverer& rhs )
// }

BinaryProxyDeliverer::~BinaryProxyDeliverer()
{
   //Get rid of the buffers
   StreamToBufferMap::iterator itEnd = m_streamToBufferMap.end();
   for( StreamToBufferMap::iterator itBuffer = m_streamToBufferMap.begin();
        itBuffer != itEnd;
        ++itBuffer ){
      delete (*itBuffer).second;
   }
   delete &m_streamToBufferMap;
   delete &m_available;
}

//
// assignment operators
//
// const BinaryProxyDeliverer& BinaryProxyDeliverer::operator=( const BinaryProxyDeliverer& rhs )
// {
// }

//
// member functions
//
void 
BinaryProxyDeliverer::registerProxies(const StreamType & iStream, 
				      vector<KeyedProxy> & iProxies)
{
   //Need to add an entry in m_available
   Count max_size( iStream.index() );
   while( m_available.size() <= max_size ){
      m_available.push_back( false );
   }
   m_available[ max_size ] = false;

//
// events
//
   if( iStream == Stream::kEvent ) {

      // proxy for binary raw event data
      BinaryRawEventProxy* proxy = new BinaryRawEventProxy( *this );
      
      if( 0 != proxy ) {
	 iProxies.push_back( 
	    KeyedProxy( 
	       RecordMethods< BinaryRawEventProxy::value_type >::makeKey(
		  UsageTag(), ProductionTag()),
	       proxy
	       ) 
	    );
      }
   }
// 
// beginruns
//
   else if( iStream == Stream::kBeginRun ) {
   }
//
// endruns
//
   else if( iStream == Stream::kEndRun ) {
   }
//
// startruns
//
   else if( iStream == Stream::kStartRun ) {
   }
//
// pauseruns
//
   else if( iStream == Stream::kPauseRun ) {
   }
}

void 
BinaryProxyDeliverer::resetCache( const Stream::Type& aStream )
{
//
// set availablity
//
   m_available[ aStream.index() ] = !false ;
//
// Not needed
//   if ( Stream::kBeginRun == aStream ) {
//      m_available[ Stream::kEvent.index() ] = false ;
//   }

   //Called by ProxyDeliverer::reset(...)
   // This doesn't need to do anything since its functionality is superceded by
   // finishedWritingToBuffer(...)
}

void
BinaryProxyDeliverer::disable( const Stream::Type& aStream )
{
   //Shouldn't read from this Stream
   m_available[ aStream.index() ] = false ;
}

void 
BinaryProxyDeliverer::enable( const Stream::Type& aStream )
{
   //Can now read from this Stream
   m_available[ aStream.index() ] = !false ;
}

void
BinaryProxyDeliverer::changeSourceController( BinarySourceController& )
{
   //We don't have to do anything
}

BDRecordBuffer* 
BinaryProxyDeliverer::buffer( const Stream::Type& iStream )
{
   StreamToBufferMap::iterator itBuffer = m_streamToBufferMap.find( iStream);
   if( itBuffer != m_streamToBufferMap.end() ){
      //found one
      return (*itBuffer).second;
   } else {
      //We need to make one
      const unsigned int kInitialBufferSize(10000);
      BDRecordBuffer* buffer = 
         new BDRecordBuffer( iStream, kInitialBufferSize );

      if( 0 == buffer ){
         report( ERROR ,
                 kFacilityString )
                    << "Out of memory"
                    << std::endl ;
         assert( 0 != buffer );
         exit( 1 );
      }

      m_streamToBufferMap.insert( StreamToBufferMap::value_type( iStream,
                                                                 buffer ) );
      return buffer;
   }
}

DABoolean 
BinaryProxyDeliverer::finishedWritingToBuffer( const Stream::Type& iStream )
{
   StreamToBufferMap::iterator itBuffer = m_streamToBufferMap.find( iStream);
   assert( itBuffer != m_streamToBufferMap.end() );
   return ( itBuffer != m_streamToBufferMap.end() ) ;
}


//
// const member functions
//
DABoolean
BinaryProxyDeliverer::available( const Stream::Type& aStream ) const
{
   return( m_available[ aStream.index() ] ) ;
}


//
// static member functions
//
