// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      HistoryCommand
// 
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Thu Sep 9 15:52:59 EST 1999
// $Id: HistoryCommand.cc,v 1.3 2000/06/01 17:49:27 mkl Exp $
//
// Revision history
//
// $Log: HistoryCommand.cc,v $
// Revision 1.3  2000/06/01 17:49:27  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.2  1999/12/11 19:10:08  mkl
// added more history command help info; minor fix-ups for Linux
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
#include "CommandPattern/HistoryCommand.h"
#include "CommandPattern/Module.h"
#include "CommandPattern/Interpreter.h"
#include "CommandPattern/Conversion.h"

// STL classes

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "CommandPattern.HistoryCommand";

static const std::string helpMessage = 
std::string( " Controls the history mechanism.                           \n" )+
std::string( "                                                           \n" )+
std::string( "                         prints history list               \n" )+
std::string( "    !<number>            execute numbered command in list  \n" )+
std::string( "    !!                   execute previous command          \n" )+
std::string( "                                                           \n" )+
std::string( " Subcommands:                                              \n" )+
std::string( "    length <number>      control how many entries are saved\n" )+
std::string( "    file   <filename>    set filename                      \n" )+
std::string( "    save                 save history                      \n" )+
std::string( "    read                 read history                      \n" )+
std::string( "    status               print status info                 \n" );

//
// static data member definitions
//

//
// constructors and destructor
//
//HistoryCommand::HistoryCommand()
//{
//}
HistoryCommand::HistoryCommand( const Command::Name& iCommand, 
			  Module* iTarget )
   : Command( iCommand, iTarget )
{
   addSubcommand( 
      new Subcommand< HistoryCommand >(
         "help", 2, 2,
         &HistoryCommand::helpHandler,
         this )
      );
   addSubcommand( 
      new Subcommand< HistoryCommand >(
         "file", 3, 3,
         &HistoryCommand::setHistoryFileHandler,
         this )
      );
   addSubcommand( 
      new Subcommand< HistoryCommand >(
         "length", 3, 3,
         &HistoryCommand::setHistoryLengthHandler,
         this )
      );
   addSubcommand( 
      new Subcommand< HistoryCommand >(
         "save", 2, 2,
         &HistoryCommand::saveHistoryHandler,
         this )
      );
   addSubcommand( 
      new Subcommand< HistoryCommand >(
         "read", 2, 2,
         &HistoryCommand::readHistoryHandler,
         this )
      );
   addSubcommand( 
      new Subcommand< HistoryCommand >(
         "status", 2, 2,
         &HistoryCommand::printHistoryInfoHandler,
         this )
      );
}

// HistoryCommand::HistoryCommand( const HistoryCommand& )
// {
// }

HistoryCommand::~HistoryCommand()
{
}

//
// assignment operators
//
// const HistoryCommand& HistoryCommand::operator=( const HistoryCommand& )
// {
// }

//
// member functions
//
int
HistoryCommand::helpHandler()
{
   // print help from header
   report( SYSTEM, kFacilityString ) 
      << "\n\nDescription: " << name() << "\n\n"
      << helpMessage << "\n" 
      << std::endl;

   return COMMAND_OK;
}

int
HistoryCommand::defaultHandler()
{
   // get ahold of Interpreter
   Interpreter* interp = Interpreter::interpreter();

   interp->printHistory();

   return COMMAND_OK;
}

int
HistoryCommand::setHistoryLengthHandler()
{
   int result = COMMAND_OK;

   assert( m_argc == 3 );

   DABoolean isNumber;
   int historyLength = Conversion::stringToDigit( m_argv[2], isNumber );

   if( true == isNumber )
   {
      // get ahold of Interpreter
      Interpreter* interp = Interpreter::interpreter();
      interp->setHistoryLength( historyLength );
      
      result = COMMAND_OK;
   }
   else
   {
      report( SYSTEM, kFacilityString ) << "bad numerical value" << std::endl;
      result = COMMAND_ERROR;
   }

   return result;
}

int
HistoryCommand::setHistoryFileHandler()
{
   assert( m_argc == 3 );
  std::string filename( m_argv[2] );

   // get ahold of Interpreter
   Interpreter* interp = Interpreter::interpreter();

   interp->setHistoryFile( filename );

   return COMMAND_OK;
}

int
HistoryCommand::saveHistoryHandler()
{
   assert( m_argc == 2 );

   // get ahold of Interpreter
   Interpreter* interp = Interpreter::interpreter();

   interp->saveHistory();

   return COMMAND_OK;
}

int
HistoryCommand::readHistoryHandler()
{
   assert( m_argc == 2 );

   // get ahold of Interpreter
   Interpreter* interp = Interpreter::interpreter();

   interp->readHistory();

   return COMMAND_OK;
}

int
HistoryCommand::printHistoryInfoHandler()
{
   assert( m_argc == 2 );

   // get ahold of Interpreter
   Interpreter* interp = Interpreter::interpreter();

   interp->printHistoryInfo();

   return COMMAND_OK;
}

//
// const member functions
//

//
// static member functions
//
