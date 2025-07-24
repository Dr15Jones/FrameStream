// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      ExitCommand
// 
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue Mar 18 15:52:59 EST 1997
// $Id: ExitCommand.cc,v 1.10 2002/01/03 19:58:23 cdj Exp $
//
// Revision history
//
// $Log: ExitCommand.cc,v $
// Revision 1.10  2002/01/03 19:58:23  cdj
// fixed bugs in Tcl command handling
//
// Revision 1.9  2000/06/01 17:49:26  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.8  1999/09/10 01:04:36  mkl
// 1) new smarter history command.
// 2) new "uppercase" function, since our compilers don't support it yet.
// 3) moved "Conversion" class to CommandPattern (needed by HistoryCommand).
//
// Revision 1.7  1999/02/22 23:40:39  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.6  1998/06/17 18:17:14  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.5  1997/10/27 19:25:43  mkl
// EchoCommand to echo messages
//
// Revision 1.4  1997/10/07 19:25:32  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.3  1997/09/10 01:41:20  mkl
// replaced \n by end
//
// Revision 1.2  1997/09/05 02:35:17  mkl
// tried to unify error handling with tcl way
//
// Revision 1.1.1.1  1997/09/03 02:39:58  mkl
// imported CommandPattern sources
//
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "Experiment/report.h"
#include "CommandPattern/ExitCommand.h"
#include "CommandPattern/Module.h"


// STL classes
#include <cstring>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "CommandPattern.ExitCommand";

static const std::string helpMessage = 
std::string( "              \"exit\" exits module.\n" );

//
// static data member definitions
//

//
// constructors and destructor
//
//ExitCommand::ExitCommand()
//{
//}
ExitCommand::ExitCommand( const Command::Name& iCommand, 
			  Module* iTarget )
   : Command( iCommand, iTarget )
{
}

// ExitCommand::ExitCommand( const ExitCommand& )
// {
// }

ExitCommand::~ExitCommand()
{
}

//
// assignment operators
//
// const ExitCommand& ExitCommand::operator=( const ExitCommand& )
// {
// }

//
// member functions
//
int
ExitCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_EXIT;

   // expect one or two arguments: "exit" or "exit help"
   setArgs( argc, argv );
   if( 1 == argc )
   {
      target()->exit();
   } else
   if( 2 == argc ) 
   {
      if ( 0 == strcmp( argv[1], "help" ) )
      {
	 result = helpHandler();
      } 
      else { // bad command argument!
	 report( SYSTEM, kFacilityString ) << "invalid command arg" << std::endl;
	 helpHandler();
	 result = COMMAND_ERROR;
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
ExitCommand::helpHandler()
{
   // print help from header
   report( SYSTEM, kFacilityString ) 
      << "\n\nDescription: " << name() << "\n\n"
      << helpMessage << "\n" 
      << std::endl;

   return COMMAND_OK;
}

//
// const member functions
//

//
// static member functions
//
