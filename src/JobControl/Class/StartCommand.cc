// -*- C++ -*-
//
// Package:     JobControl
// Module:      StartCommand
//
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue Mar 18 15:52:59 EST 1997
// $Id: StartCommand.cc,v 1.25 2000/10/11 19:45:03 mkl Exp $
//
// Revision history
//
// $Log: StartCommand.cc,v $
// Revision 1.25  2000/10/11 19:45:03  mkl
// turn error code from JobControl::eventLoop into interpreter return code
//
// Revision 1.24  2000/06/01 17:48:46  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.23  2000/01/17 21:30:17  mkl
// StopCounter: have to check for active streams as precaution AFTER streams are activated
//
// Revision 1.22  1999/09/10 01:08:52  mkl
// For HistoryCommand had to move Conversion class.
// My own "uppercase" function implementation is easier on the user when
// changing report levels (partial matching allowed, mixed case ok).
//
// Revision 1.21  1999/06/18 19:21:09  mkl
// changed 'go 10' to be 10 events; 'go 10 any' goes 10 of any active stream
//
// Revision 1.20  1998/07/30 19:29:53  mkl
// check if stream is active; if not, fail
//
// Revision 1.19  1998/07/30 18:58:19  mkl
// prompt when user specifies non-standard stream
//
// Revision 1.18  1998/07/28 22:13:45  mkl
// change StopCounter from pass-by-value to pass-by-ref in event loop
//
// Revision 1.17  1998/07/21 16:21:59  mkl
// added histogram closing; new ActionResult::kStopProcessLoop
//
// Revision 1.16  1998/05/12 20:55:23  mkl
// allow more than one stream types for go command
//
// Revision 1.15  1998/05/08 22:13:58  mkl
// deprecated nextstop in favor of fancier go command
//
// Revision 1.14  1997/10/07 19:25:25  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.13  1997/09/10 01:52:38  mkl
// replaced \n by end
//
// Revision 1.12  1997/09/05 02:36:05  mkl
// tried to unify error handling with tcl way
//
// Revision 1.11  1997/09/03 02:38:53  mkl
// restructuring suez libraries
//
// Revision 1.10  1997/08/22 04:21:54  mkl
// standardize error messages from commands
//
// Revision 1.9  1997/07/11 06:55:41  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.8  1997/07/02 02:49:03  mkl
// and a few fixes to make g++ happy again
//
// Revision 1.7  1997/07/02 01:40:36  mkl
// fixes to allow CXX version 5.4
//
// Revision 1.6  1997/06/06 06:18:18  mkl
// handle --> execute and other minor stuff
//
// Revision 1.5  1997/06/04 05:23:55  mkl
// misc
//
// Revision 1.4  1997/06/03 18:41:23  mkl
// changed over to kFacilityString
//
// Revision 1.3  1997/05/29 14:58:47  mkl
// beautification of help text
//
// Revision 1.2  1997/05/16 05:51:46  mkl
// cleaning up.
//
// Revision 1.1  1997/03/27 18:11:58  mkl
// had to rename GoCommand to StartCommand because of g++ compiler bug?
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <set>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "JobControl/StartCommand.h"
#include "JobControl/JobControl.h"
#include "DataDelivery/FrameDeliverer.h"
#include "JobControl/SourceManager.h"
#include "Processor/MasterProcessor.h"

#include "CommandPattern/Conversion.h"
#include "JobControl/StopCounter.h"

// STL classes
#include <vector>
#include <set>
#include <map>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.StartCommand";

const std::string helpMessage = 
std::string( "                                                   \n" )+
std::string( "// Description: Go Command                         \n" )+
std::string( "//   \"go\" will process stops until the end of an \n" )+
std::string( "//          active stream is reached.              \n" )+
std::string( "//                                                 \n" )+
std::string( "//   \"go 10\" will process the next 10 events     \n" )+
std::string( "//             A negative number has the same      \n" )+
std::string( "//             effect as no number.                \n" )+
std::string( "//                                                 \n" )+
std::string( "//   \"go 10 any\" will process the next 10 stop   \n" )+
std::string( "//                                                 \n" )+
std::string( "//   \"go 10 event\" will process 10 event stops.  \n" )+
std::string( "//   \"go 10 event beginrun\" will process 10 event\n" )+
std::string( "//                          or beginrun stops.     \n" )+
std::string( "//     etc...                                      \n" );

//
// static data member definitions
//

//
// constructors and destructor
//
//StartCommand::StartCommand()
//{
//}
StartCommand::StartCommand( const Command::Name& iCommand, 
			      Module* iTarget )
   : Command( iCommand, iTarget )
{
}

// StartCommand::StartCommand( const StartCommand& )
// {
// }

StartCommand::~StartCommand()
{
}

//
// assignment operators
//
// const StartCommand& StartCommand::operator=( const StartCommand& )
// {
// }

//
// member functions
//
int
StartCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   JobControl* jobControl = (JobControl*)target();

   // expect one or two arguments: "go" or "go help"
   setArgs( argc, argv );
   if( 1 == argc )
   {
      StopCounter all( -1 );  // process entire file
      DABoolean returnStatus = jobControl->eventLoop( all );
      result = (returnStatus==true)?COMMAND_OK:COMMAND_ERROR;
   } else
   if( 2 <= argc ) 
   {
      if ( 0 == strcmp( argv[1], "help" ) )
      {
	 result = helpHandler( );
      } 
      else // assume 1) numerical value, 2) streamtype
      {      
	 DABoolean isNumber;
	 int numberOfStops = Conversion::stringToDigit( argv[1], isNumber );

	 if( true == isNumber )
	 {
	    StopCounter counter( numberOfStops );

	    // the default is "events"
	    if( argc <= 2 ) {
	       counter.addStream( Stream::kEvent );
	    }
	    else {

	       // if "stops" is specified, go 10 any; 
	       // else make note of which stops
	       for( int i = 2; i<argc; ++i ) {
		
		  if( std::string( argv[i] ) == std::string( "any" ) ) {
		     counter.clearStreams();
		     break;
		  }
  
		  Stream::Type stream( argv[i] );
		  // should check that counter streams are all active
		  // but now has to be done in JobControl::eventLoop()
		  counter.addStream( stream );
	       }
	    }
	    DABoolean returnStatus = jobControl->eventLoop( counter );
	    result = (returnStatus==true)?COMMAND_OK:COMMAND_ERROR;
	 }
	 else
	 {
	    report( SYSTEM, kFacilityString ) << "bad numerical value" << std::endl;
	    result = COMMAND_ERROR;
	 }
      }
   }
   else // number of arguments 
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << std::endl;
      helpHandler();
      result = COMMAND_ERROR;
   }


   return result;
}

int
StartCommand::helpHandler()
{
   // print help from header
   report( SYSTEM, kFacilityString ) << "\n" << helpMessage << std::endl;

   return COMMAND_OK;
}

//
// const member functions
//

//
// static member functions
//
