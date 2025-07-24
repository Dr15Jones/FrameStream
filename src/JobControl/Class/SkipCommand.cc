// -*- C++ -*-
//
// Package:     JobControl
// Module:      SkipCommand
//
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue Mar 18 15:52:59 EST 1997
// $Id: SkipCommand.cc,v 1.5 2000/10/11 19:45:02 mkl Exp $
//
// Revision history
//
// $Log: SkipCommand.cc,v $
// Revision 1.5  2000/10/11 19:45:02  mkl
// turn error code from JobControl::eventLoop into interpreter return code
//
// Revision 1.4  2000/06/01 17:48:45  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.3  1999/09/10 01:08:52  mkl
// For HistoryCommand had to move Conversion class.
// My own "uppercase" function implementation is easier on the user when
// changing report levels (partial matching allowed, mixed case ok).
//
// Revision 1.2  1998/07/27 23:31:34  mkl
// skip command: need to process streams with higher or equal priority (which are not included in skip set
//
// Revision 1.1  1998/07/13 22:22:17  mkl
// added skip command
//
//
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "Experiment/report.h"

#include "JobControl/SkipCommand.h"
#include "JobControl/JobControl.h"

#include "CommandPattern/Conversion.h"
#include "JobControl/StopCounter.h"

// STL classes
#include <cstring>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.SkipCommand";

const std::string helpMessage = 
std::string( "                                                     \n" )+
std::string( "// Description: Skip Command                         \n" )+
std::string( "//   \"skip 10\" will skip the next 10 stops.        \n" )+
std::string( "//                                                   \n" )+
std::string( "//   \"skip 10 event\" will skip 10 event stops.     \n" )+
std::string( "//   \"skip 10 event beginrun\" will skip 10 event   \n" )+
std::string( "//                          or beginrun stops.       \n" )+
std::string( "//     etc...                                        \n" );

//
// static data member definitions
//

//
// constructors and destructor
//
//SkipCommand::SkipCommand()
//{
//}
SkipCommand::SkipCommand( const Command::Name& iCommand, 
			      Module* iTarget )
   : Command( iCommand, iTarget )
{
}

// SkipCommand::SkipCommand( const SkipCommand& )
// {
// }

SkipCommand::~SkipCommand()
{
}

//
// assignment operators
//
// const SkipCommand& SkipCommand::operator=( const SkipCommand& )
// {
// }

//
// member functions
//
int
SkipCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   JobControl* jobControl = (JobControl*)target();

   // expect one or two arguments: "go" or "go help"
   setArgs( argc, argv );
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
	    // stop counter keeps track of if it's a skip counter or not
	    StopCounter counter( numberOfStops );
	    counter.setSkipLogic( true );

	    for( int i = 2; i<argc; ++i ) {

	       Stream::Type stream( argv[i] );
	       if( true != stream.isStandard() ) 
	       {
		  report( WARNING, kFacilityString )
		     << "You specified a non-standard Stream type!" 
		     << argv[i] << "." << std::endl;
	       }
	       counter.addStream( stream );
	    }
	    DABoolean returnStatus = jobControl->eventLoop( counter );
	    result = (true==returnStatus)?COMMAND_OK:COMMAND_ERROR;
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
SkipCommand::helpHandler()
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
