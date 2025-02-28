// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      Command
// 
// Description: Abstract base class for all commands.
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue Mar 18 15:48:44 EST 1997
// $Id: Command.cc,v 1.15 2002/08/16 14:15:14 cleo3 Exp $
//
// Revision history
//
// $Log: Command.cc,v $
// Revision 1.15  2002/08/16 14:15:14  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.14  2000/06/01 17:49:26  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.13  1999/09/16 00:08:04  mkl
// delete subcommands in Command::dtor to avoid memory leak
//
// Revision 1.12  1999/09/14 18:38:50  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
// Revision 1.11  1999/09/10 01:04:34  mkl
// 1) new smarter history command.
// 2) new "uppercase" function, since our compilers don't support it yet.
// 3) moved "Conversion" class to CommandPattern (needed by HistoryCommand).
//
// Revision 1.10  1999/09/07 21:21:34  mkl
// make cxx happy
//
// Revision 1.9  1999/09/06 21:28:50  mkl
// new subcommand handling
//
// Revision 1.8  1999/02/22 23:40:38  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.7  1998/11/09 19:30:52  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.6  1998/03/28 20:16:10  mkl
// do implicit bind of Parameter/Command to Module
//
// Revision 1.5  1998/03/14 01:52:36  mkl
// added setHelpString() and helpString() functions
//
// Revision 1.4  1998/03/11 19:10:33  mkl
// new Parameter sources
//
// Revision 1.3  1997/10/07 19:25:31  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.2  1997/09/10 01:41:18  mkl
// replaced \n by end
//
// Revision 1.1.1.1  1997/09/03 02:39:57  mkl
// imported CommandPattern sources
//
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#include "C++Std/iostream.h"
#include <stdlib.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
//#include <vector>
#include <map>
//#include <utility>
//#include <algorithm>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/Command.h"
#include "CommandPattern/Module.h"
#include "CommandPattern/Interpreter.h"

// STL classes
//#include <vector>
#include <map>
//#include <utility>
//#include <algorithm>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "CommandPattern.Command";

typedef command_subcommandmap SubcommandMap;

//
// static data member definitions
//

//
// constructors and destructor
//
Command::Command( const Name& iName, 
		  Module* iTarget, 
		  DABoolean iInternalCommand )
   : m_name( iName ),
     m_target ( iTarget ),
     m_isEnabled( false ),
     m_helpString( "" ),
     m_subcommandMap( *new SubcommandMap )
{
   // check for out of memory errors
   if( 0 == &m_subcommandMap )
   {
      report( EMERGENCY, kFacilityString )
	 << "out of memory" << endl;
      assert( false );
      ::exit( 1 );
   }

   // bind this command to target
   if( 0 != iTarget ) {
      if( true == iInternalCommand ) {
	 iTarget->bindInternalCommand( this );
      }
      else {
	 iTarget->bindCommand( this );
      }
   }
}

// Command::Command( const Command& )
// {
// }

Command::~Command()
{
   // delete subcommand entries
   SubcommandMap::iterator it = m_subcommandMap.begin();
   SubcommandMap::iterator itEnd = m_subcommandMap.end();
   for( ; it != itEnd; ++it )
   {
      delete (*it).second;
   }
   m_subcommandMap.erase( m_subcommandMap.begin(), m_subcommandMap.end() );
   delete &m_subcommandMap;
}

//
// assignment operators
//
// const Command& Command::operator=( const Command& )
// {
// }

//
// member functions
//
void
Command::addSubcommand( SubcommandBase* iSubcommand )
{
   assert( 0 != iSubcommand );

   pair< SubcommandMap::iterator, DABoolean > result = 
      m_subcommandMap.insert( SubcommandMap::value_type( iSubcommand->name(),
							 iSubcommand ) );
   if( false == result.second ) {
      report( SYSTEM, kFacilityString )
         << "cannot insert subcommand \"" << iSubcommand->name() << "\"" << endl;
   }
}

int
Command::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   // "internalize" arguments to be able to access as "m_argc" and "m_argv"
   setArgs( argc, argv );

   // now handle args
   if( 1 >= argc )
   {
      defaultHandler();
   }
   else
   {
      string subcommandName( argv[1] );
      SubcommandMap::iterator subcommandIter 
	 = m_subcommandMap.find( subcommandName );
      if( m_subcommandMap.end() == subcommandIter )
      {
	 result = defaultWithArgsHandler( argc, argv );
      }
      else
      {
	 SubcommandBase& subcommand = *(*subcommandIter).second;

	 Count minArgs = subcommand.minArgs();
	 Count maxArgs = subcommand.maxArgs();
	 if( argc < minArgs || ( maxArgs >= minArgs && argc > maxArgs > 0 ) )
	 {
	    report( SYSTEM, kFacilityString )
	       << "wrong # of args " << endl;
	    result = COMMAND_ERROR;
	 }
	 else 
	 {
	    // execute the subcommand
	    result = subcommand.execute();
	 }
      }
   }

   return result;
}

int
Command::defaultHandler()
{
   return helpHandler();
}

int
Command::defaultWithArgsHandler( int iArgc, char* iArgv[] )
{
   int result = COMMAND_ERROR;
   string subcommandName( iArgv[1] );
   report( SYSTEM, kFacilityString )
      << "bad subcommand \"" << subcommandName << "\"" << endl;
   return result;
}

void
Command::enable()
{
   if( false == m_isEnabled ) {
      Interpreter::interpreter()->createCommand( this );
      m_isEnabled = true;
   }
}

void
Command::disable()
{
   if( true == m_isEnabled ) {
      Interpreter::interpreter()->deleteCommand( name().c_str() );
      m_isEnabled = false;
   }
}

void
Command::setArgs( int argc, char* argv[] )
{
   m_argc = argc;
   m_argv = argv;
}

Module*
Command::target()
{
   assert( 0 != m_target );
   return m_target;
}

//
// const member functions
//
const Command::Name&
Command::name() const
{
   return m_name;
}

const Module*
Command::target() const
{
   assert( 0 != m_target );
   return m_target;
}

const char*
Command::getArgument( int index ) const
{
   char* result = 0;

   if( index <= m_argc ) {
      result = m_argv[index];
   }
   return result;
}

void
Command::setResult( const string& iResult ) const
{
   Interpreter::interpreter()->setResult( iResult.c_str() );
}

//
// static member functions
//


