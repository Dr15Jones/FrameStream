// -*- C++ -*-
//
// Package:     JobControl
// Module:      GotoCommand
// 
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Sat May 3 15:52:59 EST 1997
// $Id: GotoCommand.cc,v 1.23 2003/11/21 20:09:15 cdj Exp $
//
// Revision history
//
// $Log: GotoCommand.cc,v $
// Revision 1.23  2003/11/21 20:09:15  cdj
// goto command now takes an optional argument that sets the Record type (default is event if event#> 0 else beginrun)
//
// Revision 1.22  2000/10/11 19:45:01  mkl
// turn error code from JobControl::eventLoop into interpreter return code
//
// Revision 1.21  2000/06/01 17:48:43  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.20  2000/03/09 19:13:10  mkl
// SourceCommand: dont need to force provider reload; GotoCommand: fix up help page
//
// Revision 1.19  2000/03/07 22:22:04  mkl
// update goto help page with change of behavior (no more processing of goto-ed run/event)
//
// Revision 1.18  1999/09/10 01:08:49  mkl
// For HistoryCommand had to move Conversion class.
// My own "uppercase" function implementation is easier on the user when
// changing report levels (partial matching allowed, mixed case ok).
//
// Revision 1.17  1998/04/13 16:07:26  mkl
// bug fix: bad numerical value
//
// Revision 1.16  1997/10/07 19:25:15  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.15  1997/09/18 21:26:50  cdj
// changed Boolean to DABoolean
//
// Revision 1.14  1997/09/10 01:52:30  mkl
// replaced \n by end
//
// Revision 1.13  1997/09/05 02:35:59  mkl
// tried to unify error handling with tcl way
//
// Revision 1.12  1997/09/03 05:57:43  mkl
// moved from 'const string kFacilityString' to 'static const char* const'
//
// Revision 1.11  1997/09/03 02:38:41  mkl
// restructuring suez libraries
//
// Revision 1.10  1997/08/22 04:21:48  mkl
// standardize error messages from commands
//
// Revision 1.9  1997/07/11 06:55:33  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.8  1997/07/02 02:48:57  mkl
// and a few fixes to make g++ happy again
//
// Revision 1.7  1997/07/02 01:40:28  mkl
// fixes to allow CXX version 5.4
//
// Revision 1.6  1997/07/01 03:16:32  mkl
// moved typedef map statements to .cc files
//
// Revision 1.5  1997/06/06 06:18:08  mkl
// handle --> execute and other minor stuff
//
// Revision 1.4  1997/06/04 05:23:39  mkl
// misc
//
// Revision 1.3  1997/06/03 18:41:15  mkl
// changed over to kFacilityString
//
// Revision 1.2  1997/05/16 05:51:40  mkl
// cleaning up.
//
// Revision 1.1  1997/05/06 18:35:47  mkl
// added GotoCommand and ReprocessCommand
//
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "Experiment/report.h"
#include "JobControl/GotoCommand.h"
#include "JobControl/JobControl.h"
#include "CommandPattern/Conversion.h"

// STL classes
#include <cstring>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.GotoCommand";

const std::string helpMessage = 
std::string( "                                                                   \n" )+
std::string( "// Description: Goto Command                                       \n" )+
std::string( "//                                                                 \n" )+
std::string( "// Usage:                                                          \n" )+
std::string( "//  goto <runnumber> <eventnumber> [stream]  will proceed to a     \n" )+
std::string( "//                                           given run/event number\n" )+
std::string( "//                                           skipping all stops in \n" )+
std::string( "//                                           between.              \n" )+
std::string( "//  Please note: NO processing of that run/event takes place.      \n" )+
std::string( "//               You will have to do:                              \n" )+
std::string( "//                    \"go 1\" or \"go\"     to actually process it\n" )+
std::string( "//                                                                 \n" );

//
// static data member definitions
//

//
// constructors and destructor
//
//GotoCommand::GotoCommand()
//{
//}
GotoCommand::GotoCommand( const Command::Name& iCommand, 
			  Module* iTarget )
   : Command( iCommand, iTarget )
{
}

// GotoCommand::GotoCommand( const GotoCommand& )
// {
// }

GotoCommand::~GotoCommand()
{
}

//
// assignment operators
//
// const GotoCommand& GotoCommand::operator=( const GotoCommand& )
// {
// }

//
// member functions
//
int
GotoCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   JobControl* jobControl = (JobControl*)target();

   // expect either one or two arguments: "goto 10" or "goto 36422 10"
   // for now only allow "goto <run> <event>"!
   setArgs( argc, argv );
   if( 2 == argc )
   {
      if ( 0 == strcmp( argv[1], "help" ) )
      {
	 result = helpHandler( );
      } 
      else // assume numerical value
      {    // for now only allow "goto <run> <event>"!
	 report( SYSTEM, kFacilityString ) 
	    << "Need <run> AND <event> numbers!" << std::endl;
	 result = COMMAND_ERROR;
      }
   } else
   if( 3 == argc || 4 == argc ) // assume numerical value
   {
      DABoolean isNumber;
      int runNumber = Conversion::stringToDigit( argv[1], isNumber );

      if( false == isNumber )
      {
	 report( SYSTEM, kFacilityString ) 
	    << "bad numerical value: " << argv[1] << std::endl;
	 result = COMMAND_ERROR;
      } 
      else // good runnumber
      {
	 int eventNumber = Conversion::stringToDigit( argv[2], isNumber );

	 if( false == isNumber ) // bad numerical value
	 {
	    report( SYSTEM, kFacilityString ) 
	       << "bad numerical value: " << argv[2] << std::endl;
	    result = COMMAND_ERROR;
	 }
	 else // ... and good event number
	 {
	    StreamType streamType = Stream::kEvent;
	    if( eventNumber== 0 ) {
	       streamType = Stream::kBeginRun;
	    }
	    if( 4 == argc ) {
	       streamType = StreamType( argv[3] );
	       if( ! streamType.isStandard() ) {
		  report( SYSTEM, kFacilityString ) 
		     << "unknown stream: "<< argv[3] << std::endl;
		  result = COMMAND_ERROR;
	       }
	    } 
	    if (COMMAND_OK == result) {
	       
	       DABoolean returnStatus = jobControl->goTo( runNumber, eventNumber, streamType );
	       result = (true==returnStatus)?COMMAND_OK:COMMAND_ERROR;
	    }
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
GotoCommand::helpHandler()
{
   // print help from header
   report( INFO, kFacilityString ) << "\n" << helpMessage << std::endl;

   return COMMAND_OK;
}

//
// const member functions
//

//
// static member functions
//
