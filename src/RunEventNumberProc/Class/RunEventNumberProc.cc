// -*- C++ -*-
//
// Package:     Processor
// Module:      RunEventNumberProc
// 
// Description: prints run and event number via CleoDB/DBEventHeader
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Wed Sep 10 01:42:58 EDT 1997
// $Id: RunEventNumberProc.cc,v 1.8 2001/07/08 14:40:01 cdj Exp $
//
// Revision history
//
// $Log: RunEventNumberProc.cc,v $
// Revision 1.8  2001/07/08 14:40:01  cdj
// removed parameter for beginrun binding since can already do that on suez command line and it broke tests
//
// Revision 1.7  2001/07/06 21:36:09  ajm36
// provide parameter to keep from binding to beginrun
//
// Revision 1.6  2001/05/02 17:12:46  ajm36
// add a parameter to set frequency of printout
//
// Revision 1.5  1999/12/10 16:36:56  cdj
// updated to work with extract exceptions
//
// Revision 1.4  1999/07/09 23:32:49  mkl
// print DBRunHeader in beginrun method
//
// Revision 1.3  1998/07/14 14:21:22  mkl
// check for invalid data
//
// Revision 1.2  1998/02/10 03:52:11  mkl
// got rid of obsolete HbookManager
//
// Revision 1.1.1.1  1998/01/13 18:18:10  mkl
// imported RunEventNumberProc sources
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "RunEventNumberProc/RunEventNumberProc.h"
#include "Experiment/report.h"

#include "CleoDB/DBEventHeader.h"
#include "CleoDB/DBRunHeader.h"

#include "FrameAccess/FAItem.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"          

#include "DAException/DANoDataException.h"

// STL classes

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.RunEventNumberProc" ;

//
// static data member definitions
//

//
// constructors and destructor
//
RunEventNumberProc::RunEventNumberProc( void )               // anal1
   : Processor( "RunEventNumberProc" ),
     m_frequency( "Frequency", this, 1)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &RunEventNumberProc::event,    Stream::kEvent );
   bind( &RunEventNumberProc::beginRun, Stream::kBeginRun );

   m_frequency.setHelpString("Frequency of event printout");
   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

// RunEventNumberProc::RunEventNumberProc( const RunEventNumberProc& )
// {
// }

RunEventNumberProc::~RunEventNumberProc()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// assignment operators
//
// const RunEventNumberProc& RunEventNumberProc::operator=( const RunEventNumberProc& )
// {
// }

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
RunEventNumberProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
RunEventNumberProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
RunEventNumberProc::hist_book( TBHistoManager& )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
RunEventNumberProc::event( Frame& aFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   static int eventCount(0);
   ++eventCount;
   if( eventCount >= m_frequency.value() )
   {
      eventCount = 0;
      try
      {
         FAItem< DBEventHeader > eventHeader ;
         extract( aFrame.record( Stream::kEvent ) ,
                  eventHeader ) ;
         
         report( NOTICE, kFacilityString )
            << "Run: "   << (*eventHeader).run() << " "
            << "Event: " << (*eventHeader).number()
            << endl;
      }
      catch( NO_ITEM_EXCEPTION(DBEventHeader)& iException )
      {
         report( ERROR, kFacilityString ) << iException.what() << endl;
      }
   }
   return ActionBase::kPassed;
}

ActionBase::ActionResult
RunEventNumberProc::beginRun( Frame& aFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   try {
      FAItem< DBRunHeader > runHeader ;
      extract( aFrame.record( Stream::kBeginRun ) ,
	       runHeader ) ;

      report( NOTICE, kFacilityString )
	 << "Run: " << (*runHeader).number()
	 << endl;
   }
   catch( NO_ITEM_EXCEPTION(DBRunHeader)& iException) {
      report( ERROR, kFacilityString ) << iException.what() << endl;
   }

   return ActionBase::kPassed;
}

//
// const member functions
//

//
// static member functions
//
