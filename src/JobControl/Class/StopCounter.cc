// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      StopCounter
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Mon Jul 27 19:12:49 EDT 1998
// $Id: StopCounter.cc,v 1.7 2000/12/05 18:30:17 cdj Exp $
//
// Revision history
//
// $Log: StopCounter.cc,v $
// Revision 1.7  2000/12/05 18:30:17  cdj
// improved output of previous change
//
// Revision 1.6  2000/12/05 18:25:55  cdj
// improved error message when users ask to 'go' using a non-active stream
//
// Revision 1.5  2000/01/17 21:30:17  mkl
// StopCounter: have to check for active streams as precaution AFTER streams are activated
//
// Revision 1.4  1999/06/18 19:21:09  mkl
// changed 'go 10' to be 10 events; 'go 10 any' goes 10 of any active stream
//
// Revision 1.3  1998/07/28 15:37:54  mkl
// forward declare stl container
//
// Revision 1.2  1998/07/28 14:51:10  mkl
// needed to include string first for g++
//
// Revision 1.1  1998/07/27 23:31:34  mkl
// skip command: need to process streams with higher or equal priority (which are not included in skip set
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "JobControl/StopCounter.h"

// STL classes
#include <string>
#include <set>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.StopCounter" ;

//
// static data member definitions
//

//
// constructors and destructor
//
StopCounter::StopCounter( long iCounter ) 
   : m_counter( iCounter ), 
     m_skipLogic( false )
{
}

// StopCounter::StopCounter( const StopCounter& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

StopCounter::~StopCounter()
{
}

//
// assignment operators
//
// const StopCounter& StopCounter::operator=( const StopCounter& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
void 
StopCounter::setSkipLogic( DABoolean skipOrNot ) 
{ 
   m_skipLogic = skipOrNot; 
}

void 
StopCounter::addStream( const Stream::Type& iStream ) 
{
   m_streams.insert( iStream );
}

void 
StopCounter::clearStreams()
{
   m_streams.erase( m_streams.begin(), m_streams.end() );
}

long& 
StopCounter::operator()( const Stream::Type& iStream ) 
{
   if( true == m_streams.empty()
       || true == find( iStream ) ) {
      return m_counter;
   }
   else {
      return m_tempCounter=-1; // negative number signals: keep going
   }
}

long& 
StopCounter::operator()() 
{
   return m_counter;
}

DABoolean 
StopCounter::skipThisStop( const Stream::Type& iStream ) 
{
   DABoolean returnValue = false;
   
   if( true == m_skipLogic ) {
      returnValue = true;

      // stream not found; need to compare priorities
      if( false == find( iStream ) ) {

	 StreamSet::const_iterator itEnd = m_streams.end();
	 for( StreamSet::const_iterator it = m_streams.begin();
	      it != itEnd;
	      ++it ) 
	 {
	    // if iStream is higher or equal priority than any one, don't skip
	    if( iStream.priority() >= (*it).priority() ) {
	       returnValue = false;
	       break;
	    }
	 }
      }
   }
   
   return returnValue;
}

DABoolean 
StopCounter::find( const Stream::Type iStream ) 
{
   DABoolean returnValue = false;

   StreamSet::iterator which = m_streams.find( iStream );

   if( m_streams.end() != which ) {
      returnValue = true;
   }

   return returnValue;
}

DABoolean
StopCounter::checkAllStreamsToBeActive( const StreamSet& iStreams ) const
{
   DABoolean returnValue = true;

   if( false == iStreams.contains( m_streams ) ) {
      ostream& reportStream = report( ERROR, kFacilityString );
      reportStream <<"can only stop on active Streams: ";

      {
	 StreamSet::const_iterator itEnd = iStreams.end();
	 for( StreamSet::const_iterator itStream = iStreams.begin();
	      itStream != itEnd;
	      ++itStream ) {
	    reportStream << (*itStream).value() << " " ;
	 }
      }

      //print out which streams are the problem
      StreamSet::const_iterator itEnd = m_streams.end();
      for( StreamSet::const_iterator itStream = m_streams.begin();
	   itStream != itEnd;
	   ++itStream ) {
	 if( ! iStreams.contains( *itStream ) ) {
	    reportStream << "\n \""
			 << (*itStream).value() 
			 <<"\" is not an active Stream";
	 }
      }
      reportStream << endl;
      returnValue = false;
   }

   return returnValue;
}

//
// const member functions
//

//
// static member functions
//
