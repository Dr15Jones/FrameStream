// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      Test/test.cc
// 
// Description: test BinaryDelivery in stand-alone mode
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:    Martin  Lohner
// Created:   Wed Nov 4 15:48:55 EST 1998
// $Id: test.cc,v 1.5 2002/08/16 13:55:34 cleo3 Exp $
//
// Revision history
// $Log: test.cc,v $
// Revision 1.5  2002/08/16 13:55:34  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.4  1999/05/13 18:47:31  dlk
// DLK: 	Redefine decimal stream output after outputting hex
//
// Revision 1.3  1999/04/23 19:11:53  dlk
// DLK: New testing script exercises BinaryDelivery in suez, using a recent
//      online data file as input file.
//
// Revision 1.2  1999/04/15 19:11:43  dlk
// DLK Major revision
// 	The EventHeader must be the first raw data unit inside the event
// 	The 6-word binary header is no longer made -- I use EventHeader
// 	The code supports all record types
// 		BeginRun, StartData, Event, Pause, EndRun ...
// 	Currently, the code currently works for bigendian machines only
//
// Revision 1.1  1998/11/04 16:15:18  mkl
// added standalone test program
//
//

#include "Experiment/Experiment.h"

// system includes
#include <iostream>
#include <stdlib.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user includes
#include "Experiment/report.h"

// basic datadelivery 
#include "DataHandler/Stream.h"
#include "DataDelivery/FrameDeliverer.h"
#include "DataHandler/StreamSet.h"

// frame access
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "FrameAccess/extract.h"
#include "DataHandler/Frame.h"

// binary binder and source controller
#include "BinaryDelivery/BinarySourceBinder.h"
#include "BinaryDelivery/BinarySourceController.h"

// proxy item
#include "RawData/RawEventData.h"
#include "RawData/RawCCHits.h"

// stl inclues
#include <vector>
#include <map>

// statics
static const char* const kFacilityString = "BinaryDelivery.test";

// ---------- event processing routine -------------
void eventProcess( const Frame& iFrame)
{
   FAItem< RawEventData > iRawEvent;
   extract( iFrame.record( Stream::kEvent ), iRawEvent );

   if( iRawEvent.valid() )
   {
      report( INFO, kFacilityString ) 
	 << "Success extracting RawEvent from binary format" << std::endl;
      
      const RawEventData& rawEvent ( *iRawEvent ) ;
         if( rawEvent.valid() )
         {
            const RawCCHits& rawCCHits ( rawEvent.rawCCHits() ) ;
            if( rawCCHits.valid() )
            {
	       for( RawCCHits::const_iterator iCC ( rawCCHits.begin() ) ;
		    iCC != rawCCHits.end() ; ++iCC )
	       {
		  const UInt32 word ( *iCC ) ;
		  cout << hex << word << "  " ;
	       }
	       cout << dec << std::endl ;
	    }
	    else
	    {
	       report( INFO, kFacilityString )
		  << "rawCCHits validity check failed" << std::endl ;
	    }
	 }
	 else
	 {
	    report( INFO, kFacilityString )
	       <<  "RawEventData are invalid" << std::endl ;
	 }

   } 
   else 
   {
      report( INFO, kFacilityString ) 
	 << "No Success extracting RawEvent from binary format" << std::endl;
   }

   return;
}

// ------------------------- Main Program ---------------------------
int main( void )
{
   // setup message logger
   LogStream logger( INFO, cout );
   MessageLog::Tie( "." , logger );

   report( INFO, kFacilityString ) 
      << "here in main" << std::endl;

   FrameDeliverer::AddSourceStatus iAddError;
   FrameDeliverer::AddActiveSourceStatus iActiveError;

   // for now only try to read the event stream
   Stream::Set streams;
   streams.insert( Stream::kEvent    );
   streams.insert( Stream::kBeginRun );
   streams.insert( Stream::kEndRun   );

   report( INFO, kFacilityString )
      << "Please give filename to read" << std::endl;
  std::string filename;
   cin >> filename;
   report( INFO, kFacilityString )
      << "Will use " << filename << " to read from " << std::endl;

   report( INFO, kFacilityString ) 
      << "about to make a BinarySourceBinder" << std::endl;
   BinarySourceBinder binaryBinder( filename, streams );

   report( INFO, kFacilityString ) 
      << "defining FrameDeliverer" << std::endl;
   FrameDeliverer frameDeliverer;

   // declare binder for reading
   report( INFO, kFacilityString ) 
      << "Adding BinarySourceBinder" << std::endl;
   if( FrameDeliverer::kAddSourceNoError !=
       ( iAddError = frameDeliverer.addSource( binaryBinder ))) 
   {
      report( ERROR, kFacilityString ) 
	 <<"Add Data Source error:"<< iAddError <<std::endl;
      ::exit(1);
   }

   // declare binder for active streams
   report( INFO, kFacilityString ) 
      << "Declaring Binder for active streams" << std::endl;
   if( FrameDeliverer::kAddActiveSourceNoError != 
       (iActiveError = frameDeliverer.addActiveSource( binaryBinder ))){
      report( ERROR, kFacilityString ) 
	 <<"Add Active Stream error:"<< iActiveError <<std::endl;
      ::exit(1);
   }


   DABoolean isDone(false);
   FrameDeliverer::NextStopStatus nextStopStatus;

   report( INFO, kFacilityString ) 
      << "Entering event loop" << std::endl;
   int nEvents(0);
   while( !isDone )
   {
      report( INFO, kFacilityString ) 
	 << "FrameDeliverer::gotoNextStop()" << std::endl;
      nextStopStatus = frameDeliverer.gotoNextStop();

      report( INFO, kFacilityString ) 
	 << "FrameDeliverer::currentStop()" << std::endl;
      Stream::Type currentStop = frameDeliverer.currentStop();
      
      report( INFO, kFacilityString ) 
	 << "------------------------" << std::endl;
      report( INFO, kFacilityString ) 
	 << "NextStopStatus:" << nextStopStatus << std::endl;

      if( Stream::kNone == currentStop )
      {
	 isDone = true;
      } 
      else if ( Stream::kBeginRun == currentStop )
      {
	 report( INFO, kFacilityString ) 
	    <<"Begin Run"<<std::endl;
      } 
      else if ( Stream::kEvent == currentStop )
      {
	 ++nEvents;
	 report( INFO, kFacilityString ) 
	    << "Event" << nEvents << std::endl;
	 eventProcess( frameDeliverer.currentFrame() );

	 isDone = false;
      } 
      else if ( Stream::kEndRun == currentStop )
      {
	report( INFO, kFacilityString ) 
	   <<"End Run"<<std::endl;
	 isDone=true;
      } 
      else 
      {
	 report( ERROR, kFacilityString ) 
	    <<"Unknown Record:"<<currentStop<<std::endl;
	 isDone=true;
      }
   }
      
   report( INFO, kFacilityString ) 
      << "------------------------" << std::endl;
   report( INFO, kFacilityString ) 
      << "Next Stop Status ( End of Active Source="
      << FrameDeliverer::kNextStopReachedEndOfAnActiveSource
      << "):"
      <<nextStopStatus
      <<std::endl;

  
   report( INFO, kFacilityString ) << nEvents
				   << " events processed" << std::endl;

   return 0;
}


