// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      Module
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:       Martin  Lohner
// Created:     Tue Mar 18 15:53:48 EST 1997
// $Id: Module.cc,v 1.28 2003/01/27 19:12:05 cdj Exp $
//
// Revision history
//
// $Log: Module.cc,v $
// Revision 1.28  2003/01/27 19:12:05  cdj
// get iomanip from C++Std package
//
// Revision 1.27  2002/08/16 14:15:15  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.26  2002/01/03 20:17:00  cdj
// code clean up from last check in
//
// Revision 1.25  2002/01/03 19:58:23  cdj
// fixed bugs in Tcl command handling
//
// Revision 1.24  2000/09/05 17:53:25  mkl
// added verbose messages: loading modules and adding commands
//
// Revision 1.23  2000/06/01 18:02:23  mkl
// shorten some system-level kFacilityStrings to 'Suez' for better readability
//
// Revision 1.22  2000/06/01 17:49:27  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.21  1999/09/14 18:38:51  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
// Revision 1.20  1999/09/10 01:04:37  mkl
// 1) new smarter history command.
// 2) new "uppercase" function, since our compilers don't support it yet.
// 3) moved "Conversion" class to CommandPattern (needed by HistoryCommand).
//
// Revision 1.19  1999/08/26 03:48:50  mkl
// ctrl-c signal: give option to completely exit out of suez (the fast way) or just stop the event loop
//
// Revision 1.18  1999/05/02 02:45:01  mkl
// use new Signal library
//
// Revision 1.17  1999/04/30 03:35:23  mkl
// bug in CC compiler: def of var in for loop scope clashes with external var
//
// Revision 1.16  1999/04/28 21:04:32  mkl
// use more generic algo to figure out placement of command listings
//
// Revision 1.15  1999/04/26 20:03:08  mkl
// better Module::help page printout
//
// Revision 1.14  1999/02/22 23:40:42  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.13  1998/11/12 22:23:07  mkl
// finish new module loading and unloading
//
// Revision 1.12  1998/11/12 02:23:45  mkl
// minor cleanup
//
// Revision 1.11  1998/11/09 21:24:33  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.10  1998/11/09 19:31:04  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.9  1998/07/02 00:59:23  mkl
// delete in reverse order to allocation (shouldnt make a diff here)
//
// Revision 1.8  1998/03/28 20:16:11  mkl
// do implicit bind of Parameter/Command to Module
//
// Revision 1.7  1998/03/16 23:17:43  mkl
// use bind instead of commands().push_back()
//
// Revision 1.6  1998/03/11 19:10:34  mkl
// new Parameter sources
//
// Revision 1.5  1997/11/24 18:35:53  mkl
// new StringWrapper class to get around g++ proboem with map<string, string>
//
// Revision 1.4  1997/11/01 21:58:32  mkl
// delete vector<Command*> properly
//
// Revision 1.3  1997/10/07 19:25:33  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.2  1997/09/10 01:41:20  mkl
// replaced \n by end
//
// Revision 1.1.1.1  1997/09/03 02:39:57  mkl
// imported CommandPattern sources
//
//

#include "Experiment/Experiment.h"

// system include files
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <stdlib.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "CommandPattern/Module.h"
#include "CommandPattern/Command.h"
#include "CommandPattern/Interpreter.h"

#include "Signal/SignalHandler.h"
#include "Signal/SIGINT_Handler.h"

// STL classes
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

//
// constants, enums and typedefs
//
const char* const kFacilityString = "CommandPattern.Module";

typedef _module_containerOfCommands_ Commands;

//
// static data member definitions
//

//
// constructors and destructor
//
//Module::Module()
//{
//}
Module::Module( const Module::Name& iName, const Module::Name& iDescription )
   : m_name( iName ),
     m_description( iDescription ),
     m_callInit     ( true  ),
     m_callTerminate( false ),
     m_commands( *new Commands ),
     m_internalCommands( *new Commands ),
     m_exitCommand( "exit", this ),
     m_quitCommand( "quit", this ),
     m_helpCommand( "help", this ),
     m_echoCommand( "echo", this ),
     m_historyCommand( "history", this ),
     m_runCommandFileCommand( "run_file", this )
{
}


// Module::Module( const Module& )
// {
// }

Module::~Module()
{
   // delete container (NOT its contents!)
   delete &m_internalCommands;
   delete &m_commands;
}


//
// assignment operators
//
// const Module& Module::operator=( const Module& )
// {
// }

//
// member functions
//
void
Module::interact()
// ----------------------------------------------
// this is the main command loop
// ----------------------------------------------
{
   assert( Interpreter::isInitialized() );
   

   // create commands and register with interpreter
   //  NOTE: exit command will undo this
   Interpreter::interpreter()->pushActiveModule(this);

   // install an interrupt handler
   DABoolean callExit;
   static SIGINT_Handler sigint_handler( callExit=true );
   EventHandler* oldHandler = 
      SignalHandler::instance()->registerHandler( SignalHandler::kSigInt, 
						  &sigint_handler );

   // main command loop
   Interpreter::interpreter()->loop();

   SignalHandler::instance()->registerHandler( SignalHandler::kSigInt,
					       oldHandler );
}

void
Module::exit()
{
   Interpreter::interpreter()->popActiveModule();
}

void
Module::quit()
{
   Module::exit();
}

void
Module::help()
{
  std::ostream& os = report( SYSTEM, "Suez" );

   os << "The following commands are available:\n";

   // first figure out the largest command name and use that 
   // to arrange in columns
   unsigned int largestSize = 10;
   Commands::const_iterator comIter;
   for( comIter = internalCommands().begin(); 
	comIter != internalCommands().end(); 
	++comIter )
   {
      unsigned int size = (*comIter).first.length();
      largestSize = (size > largestSize)? size:largestSize;
   }
   unsigned int nOfColumns = 55/largestSize;

   // now print them in columns
   int i;
   for( i=1, comIter = internalCommands().begin(); 
	comIter != internalCommands().end(); 
	++comIter, ++i )
   {
      if( 1 == (i % nOfColumns) ) os << "  ";
      // os.setf( ios::left, ios::adjustfield );
      os << std::setiosflags( std::ios::left )
	   << std::setw( largestSize ) << (*comIter).first << "\t";
      if( 0 == (i % nOfColumns) ) os << "\n";
   }
   os << "\nType \"<command> help\" to get specific help." << std::endl;
}

void
Module::enableCommands()
{
   Commands::const_iterator itEnd = internalCommands().end();
   for( Commands::const_iterator iter = internalCommands().begin(); 
	iter != itEnd;
	++iter )
   {
      (*iter).second->enable();
   }
}

void
Module::disableCommands()
{
   Commands::const_iterator itEnd = internalCommands().end();
   for( Commands::const_iterator iter = internalCommands().begin(); 
	iter != itEnd;
	++iter )
   {
      (*iter).second->disable();
   }
}

void
Module::setName( const Module::Name& iName )
{
   m_name = iName;
}

Commands& 
Module::commands() 
{ 
   return m_commands; 
}

Commands& 
Module::internalCommands() 
{ 
   return m_internalCommands; 
}

void
Module::setCallInit( DABoolean iValue )
{
   m_callInit = iValue;
}

void
Module::setCallTerminate( DABoolean iValue )
{
   m_callTerminate = iValue;
}

void 
Module::init( void ) 
{
}

void 
Module::terminate( void ) 
{
}

void
Module::bindCommand( Command* iCommand )
{ 
//   std::pair< Commands::iterator, DABoolean > result = 
   std::pair< Commands::iterator, DABoolean > result = 
      commands().insert( Commands::value_type( iCommand->name(), 
					       iCommand ) );
   if( false == result.second ) {
      report( ERROR, kFacilityString )
	 << "cannot insert command " << iCommand->name() << std::endl;
   }
   else {
      report( SYSTEM, "Module" )
	 << "added command \"" << iCommand->name() << "\" from " << name() 
	 << std::endl;
   }
}

void
Module::bindInternalCommand( Command* iCommand )
{ 
   assert( 0 != iCommand );
   std::pair< Commands::iterator, DABoolean > result = 
      internalCommands().insert( Commands::value_type( iCommand->name(), 
						       iCommand ) );
   if( false == result.second ) {
      report( ERROR, kFacilityString )
	 << "cannot insert command " << iCommand->name() << std::endl;
   }
   //else {
   //  report( SYSTEM, kFacilityString )
   // << "added command \"" << iCommand->name() << "\" from " << name() 
   // << std::endl;
   //}
}

void
Module::unbindInternalCommand( Command* iCommand )
{ 
   assert( 0 != iCommand );
   Commands::size_type result = internalCommands().erase( iCommand->name() );
   if( 0 == result ) {
      report( ERROR, kFacilityString )
	 << "cannot erase command " << iCommand->name() << std::endl;
   }
}

// interface conforming to CompositePattern
void 
Module::addModule( Module* iModule, DABoolean iOwnMemory )
{ 
   report( ERROR, kFacilityString )
      << "I am a module; can't add other modules" << std::endl;
}

DABoolean 
Module::removeModule( const Module::Name& iName )
{  
   DABoolean returnValue = false;
   report( ERROR, kFacilityString )
      << "I am a module; can't add other modules" << std::endl;
   return returnValue;
}

DABoolean 
Module::clearModules()
{  
   DABoolean returnValue = true;
   report( ERROR, kFacilityString )
      << "I am a module; can't add other modules" << std::endl;
   return returnValue;
}

//
// const member functions
//
const Module::Name&
Module::name() const
{
   return m_name;
}

DABoolean
Module::callInit() const
{
   return m_callInit;
}

DABoolean
Module::callTerminate() const
{
   return m_callTerminate;
}

Module*
Module::fetchModule( const Module::Name& iName )
{
   Module* returnValue = 0;
   report( ERROR, kFacilityString )
      << "I am a module; can't contain other modules" << std::endl;
   return returnValue;
}

// interface conforming to CompositePattern
std::string
Module::listModules() const
{
   std::string resultString( "\n" );
   report( EMERGENCY, kFacilityString )
      << "I am a module; can't contain other modules" 
      << std::endl;
   assert( false );
   ::exit( 1 );
   return resultString;
}

DABoolean 
Module::containsModule( const Module::Name& iName ) const
{
   DABoolean returnValue = false;
   report( ERROR, kFacilityString )
      << "I am a module; can't contain other modules" << std::endl;
   return returnValue;
}

const Module*
Module::fetchModule( const Module::Name& iName ) const
{
   const Module* returnValue = 0;
   report( ERROR, kFacilityString )
      << "I am a module; can't contain other modules" << std::endl;
   return returnValue;
}

//
// static member functions
//
std::string
Module::factorySymbol()
{
   return "makeModule"; 
}
