// -*- C++ -*-
//
// Package:     JobControl
// Module:      InteractCommand
//
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue Jul 22 17:05:15 EST 1997
// $Id: InteractCommand.cc,v 1.5 2003/09/05 18:12:31 cdj Exp $
//
// Revision history
//
// $Log: InteractCommand.cc,v $
// Revision 1.5  2003/09/05 18:12:31  cdj
// fixed problem when call a menu without an argument from the param command
//
// Revision 1.4  2002/01/03 21:03:37  cdj
// updated to work with new Interpreter handling
//
// Revision 1.3  2000/08/30 21:07:26  mkl
// interact command has to look for modules (as well as processors and producers)
//
// Revision 1.2  2000/06/01 17:48:43  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.1  1999/03/15 19:14:15  mkl
// InteractCommand
//
// Revision 1.6  1999/03/11 22:02:39  mkl
// source out stream will activate stream; turn off superfluous warning for 'param' command
//
// Revision 1.5  1999/02/22 23:41:37  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.4  1999/02/04 23:05:18  mkl
// fixed up Menu and Interact commands to work together
//
// Revision 1.3  1998/07/28 15:53:15  mkl
// ripple effect: needed to include set
//
// Revision 1.2  1998/05/07 15:39:12  mkl
// check producers for interacts
//
// Revision 1.1  1998/03/28 20:16:03  mkl
// do implicit bind of Interact/Command to Module
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "JobControl/InteractCommand.h"
#include "JobControl/JobControl.h"
#include "Processor/MasterProcessor.h"
#include "Processor/MasterProducer.h"
#include "CommandPattern/Interpreter.h"

// STL classes
#include <vector>
#include <map>
#include <set>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.InteractCommand";
 
const std::string helpMessage = 
std::string( "// Description: ParameterCommand                              \n" )+
std::string( "//                                                            \n" )+
std::string( "//  inter <Module> <command> [<arg1> <arg2> ...]              \n" )+
std::string( "                                                              \n" );

//
// static data member definitions
//

//
// constructors and destructor
//
InteractCommand::InteractCommand( const Command::Name& name,
				  Module* target )
   : Command( name, target )
{
}

// InteractCommand::InteractCommand( const InteractCommand& )
// {
// }

InteractCommand::~InteractCommand()
{
}

//
// assignment operators
//
// const InteractCommand& InteractCommand::operator=( const InteractCommand& )
// {
// }

//
// member functions
//
int
InteractCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   setArgs( argc, argv );
   if ( 2 <= argc ) {
      if( 0 == strcmp( argv[1], "help" ) ) {
	 result = helpHandler();
      }
      else {
	 result = moduleHandler();
      }
   } 
   else {
      report( SYSTEM, kFacilityString ) << "wrong # args" << std::endl;
      helpHandler();
      result = COMMAND_ERROR;
   }

   return result;
}

int
InteractCommand::helpHandler()
{
   // print help from ModuleCommand.h header
   report( SYSTEM, kFacilityString ) << "\n" << helpMessage << std::endl;

   return COMMAND_OK;
}

int
InteractCommand::moduleHandler()
{
   int result = COMMAND_OK;

   JobControl* jobControl = (JobControl*)target();

   // get ahold of Module with name <modulename>
   std::string name( m_argv[1] );
   // look for processors
   Module* module = jobControl->masterProcessor().fetch( name );
   if( 0 == module ) { // look for producers
      module = jobControl->masterProducer().fetch( name );
   }
   if( 0 == module ) { // look for modules
      module = jobControl->fetch( name );
   }
   if( 0 != module )
   {
      unsigned int moduleStackSize = Interpreter::interpreter()->activeModuleStackSize();
      Interpreter::interpreter()->pushActiveModule(module);    
      // command is list of arguments with index+2 and on
      if( 0 == m_argc-2 )
      {
	 Interpreter::interpreter()->runCommand( "help" );
      }
      else
      {
	 Interpreter::interpreter()->runCommand( m_argc-2, &m_argv[2] );
      }
      //Make sure users didn't type 'exit' or 'quit'
      const Interpreter* cInterpreter = Interpreter::interpreter();
      while(moduleStackSize < Interpreter::interpreter()->activeModuleStackSize() ) {
         Interpreter::interpreter()->popActiveModule();
      }
   }
   else
   {
      report( SYSTEM, kFacilityString )
	 << "no module " << name << std::endl;
      result = COMMAND_ERROR;
   }

   return result;
}

//
// const member functions
//

//
// static member functions
//
