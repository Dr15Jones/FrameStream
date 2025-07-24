// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      RunCommandFileCommand
// 
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Thu Sep 9 15:52:59 EST 1999
// $Id: RunCommandFileCommand.cc,v 1.3 2000/06/01 17:49:27 mkl Exp $
//
// Revision history
//
// $Log: RunCommandFileCommand.cc,v $
// Revision 1.3  2000/06/01 17:49:27  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.2  1999/10/05 20:29:54  mkl
// fix up minor typo
//
// Revision 1.1  1999/09/14 18:38:52  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
// Revision 1.1  1999/09/10 01:04:36  mkl
// 1) new smarter history command.
// 2) new "uppercase" function, since our compilers don't support it yet.
// 3) moved "Conversion" class to CommandPattern (needed by HistoryCommand).
//
//

#include "Experiment/Experiment.h"
// system include files
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "CommandPattern/RunCommandFileCommand.h"
#include "CommandPattern/Module.h"
#include "CommandPattern/Interpreter.h"
#include "CommandPattern/Conversion.h"

// STL classes

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "CommandPattern.RunCommandFileCommand";

static const std::string helpMessage = 
std::string( " Allows to process commands in file:                       \n" )+
std::string( "    <argument>             filename to be processed        \n" );

//
// static data member definitions
//

//
// constructors and destructor
//
//RunCommandFileCommand::RunCommandFileCommand()
//{
//}
RunCommandFileCommand::RunCommandFileCommand( const Command::Name& iCommand, 
			  Module* iTarget )
   : Command( iCommand, iTarget )
{
   addSubcommand( 
      new Subcommand< RunCommandFileCommand >(
         "help", 2, 2,
         &RunCommandFileCommand::helpHandler,
         this )
      );
}

// RunCommandFileCommand::RunCommandFileCommand( const RunCommandFileCommand& )
// {
// }

RunCommandFileCommand::~RunCommandFileCommand()
{
}

//
// assignment operators
//
// const RunCommandFileCommand& RunCommandFileCommand::operator=( const RunCommandFileCommand& )
// {
// }

//
// member functions
//
int
RunCommandFileCommand::helpHandler()
{
   // print help from header
   report( SYSTEM, kFacilityString ) 
      << "\n\nDescription: " << name() << "\n\n"
      << helpMessage << "\n" 
      << std::endl;

   return COMMAND_OK;
}

int
RunCommandFileCommand::defaultWithArgsHandler( int iArgc, char* iArgv[] )
{
   int result = COMMAND_OK;

   // coded-in assumption
   assert( iArgc > 1 );

   // but if more args, something's wrong
   if( iArgc > 2 )
   {
      report( SYSTEM, kFacilityString )
	 << "wrong # of args" << std::endl;
      helpHandler();
    
      result = COMMAND_ERROR;
   }
   else
   {
      std::string filename( iArgv[1] );
      
      // get ahold of Interpreter
      Interpreter* interp = Interpreter::interpreter();
      result = interp->runCommandFile( filename.c_str() );
   }

   return result;
}

//
// const member functions
//

//
// static member functions
//
