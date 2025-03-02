// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      QuitCommand
// 
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:       Martin  Lohner
// Created:     Tue Mar 18 15:52:59 EST 1997
// $Id: QuitCommand.cc,v 1.8 2002/01/03 19:58:24 cdj Exp $
//
// Revision history
//
// $Log: QuitCommand.cc,v $
// Revision 1.8  2002/01/03 19:58:24  cdj
// fixed bugs in Tcl command handling
//
// Revision 1.7  2000/06/01 17:49:27  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.6  1999/02/22 23:40:43  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.5  1998/06/17 18:17:17  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.4  1997/10/07 19:25:33  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.3  1997/09/10 01:41:21  mkl
// replaced \n by end
//
// Revision 1.2  1997/09/05 02:35:18  mkl
// tried to unify error handling with tcl way
//
// Revision 1.1.1.1  1997/09/03 02:39:57  mkl
// imported CommandPattern sources
//
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "CommandPattern/QuitCommand.h"
#include "CommandPattern/Module.h"
#include "Experiment/report.h"


// STL classes
#include <cstring>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "CommandPattern.QuitCommand";

const string helpMessage = 
string( "              \"quit\" exists module in a quick way.\n" );

//
// static data member definitions
//

//
// constructors and destructor
//
//QuitCommand::QuitCommand()
//{
//}
QuitCommand::QuitCommand( const Command::Name& iCommand, 
			  Module* iTarget )
   : Command( iCommand, iTarget )
{
}

// QuitCommand::QuitCommand( const QuitCommand& )
// {
// }

QuitCommand::~QuitCommand()
{
}

//
// assignment operators
//
// const QuitCommand& QuitCommand::operator=( const QuitCommand& )
// {
// }

//
// member functions
//
int
QuitCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_EXIT;

   // expect one or two arguments: "quit" or "quit help"
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
	 report( SYSTEM, kFacilityString ) << "invalid command arg" << endl;
	 helpHandler();
	 result = COMMAND_ERROR;
      }
   }
   else // number of arguments 
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      helpHandler();
      result = COMMAND_ERROR;
   }


   return result;
}

int
QuitCommand::helpHandler()
{
   // print help from header
   report( SYSTEM, kFacilityString ) 
      << "\n\nDescription: " << name() << "\n\n"
      << helpMessage << "\n" 
      << endl;

   return COMMAND_OK;
}

//
// const member functions
//

//
// static member functions
//
