// -*- C++ -*-
//
// Package:     Processor
// Module:      ActionCommand
// 
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Mon Mar 15 13:05:15 EST 1999
// $Id: ActionCommand.cc,v 1.4 2002/08/16 15:46:36 cleo3 Exp $
//
// Revision history (at end of file)
//
#include "Experiment/Experiment.h"
// system include files
#include "C++Std/iostream.h"
#include <stdlib.h>
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
//#include <vector>
#include <map>
//#include <algorithm>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "Processor/ActionCommand.h"
#include "Processor/Processor.h"

// STL classes
//#include <vector>
#include <map>
//#include <algorithm>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.ActionCommand";

typedef _processor_stream2actions_ ActionMap;

const string helpMessage = 
string( "                                                                \n" )+
string( "// Description: ProxyCommand                                    \n" )+
string( "//                                                              \n" )+
string( "//  Valid subcommands are:                                      \n" )+
string( "//                                                              \n" )+
string( "//  action help                    see this help page           \n" )+
string( "//  action list                    List Action                  \n" )+
string( "//  action ls                      Synonym: \"list\"            \n" )+
string( "//  action enable  <stream>        enable action tied to stream \n" )+
string( "//  action disable <stream>        disable action tied to stream\n" )+
string( "                                                                \n" );

//
// static data member definitions
//

//
// constructors and destructor
//
ActionCommand::ActionCommand( const Command::Name& name,
			      Processor* target )
   : Command( name, target )
{
}

// ActionCommand::ActionCommand( const ActionCommand& )
// {
// }

ActionCommand::~ActionCommand()
{
}

//
// assignment operators
//
// const ActionCommand& ActionCommand::operator=( const ActionCommand& )
// {
// }

//
// member functions
//
int
ActionCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   setArgs( argc, argv );
   if ( 2 == argc ) {
      if( 0 == strcmp( argv[1], "help" ) ) {
	 result = helpHandler();
      } else 
      if( 0 == strcmp( argv[1], "list" ) ) {
	 result = listHandler();
      } else 
      if( 0 == strcmp( argv[1], "ls" ) ) {
	 result = listHandler();
      }
      else {
	 report( SYSTEM, kFacilityString ) << "invalid command arg" << endl;
	 helpHandler();
	 result = COMMAND_ERROR;
      }
   } else
   if ( 3 == argc ) {
      if( 0 == strcmp( argv[1], "enable" ) ) {
	 result = switchOnOffHandler( true );
      } else 
      if( 0 == strcmp( argv[1], "disable" ) ) {
	 result = switchOnOffHandler( false );
      }
      else {
	 report( SYSTEM, kFacilityString ) << "invalid command arg" << endl;
	 helpHandler();
	 result = COMMAND_ERROR;
      }
   } // wrong # of args
   else 
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      helpHandler();
      result = COMMAND_ERROR;
   }

   return result;
}

int
ActionCommand::helpHandler( )
{
   report( SYSTEM, kFacilityString ) << "\n" << helpMessage << endl;
   return COMMAND_OK;
}

int
ActionCommand::listHandler()
{
   int result = COMMAND_OK;

   string resultString;

   // list all Actions in Processor
   const ActionMap& actionMap = target()->actions();
   
   ActionMap::const_iterator endAct = actionMap.end();
   for( ActionMap::const_iterator actIt = actionMap.begin();
	actIt != endAct;
	++actIt )
   {
      string stream = (*actIt).first.value(); 
      string setting = ( true == (*actIt).second.shouldUse() ) ? "on":"off";
      resultString += stream + string(" : ") + setting + string("\n");

   }
   setResult( resultString );

   return result;
}

int
ActionCommand::switchOnOffHandler( DABoolean iOnOff )
{
   int result = COMMAND_OK;
   string resultString;

   // assume "action enable/disable <stream> 
   assert( 3 == m_argc );
   string stream( m_argv[2] );

   // list all Actions in Processor
   ActionMap& actionMap = target()->actions();
   
   ActionMap::iterator actionIter = actionMap.find( stream );
   if( actionMap.end() != actionIter )
   {
      (*actionIter).second.shouldUse() = iOnOff;
      string onOffString = ( true == iOnOff ) ? "on" : "off";
      resultString += stream + string( " : " ) + onOffString + string("\n");
   }
   else
   {
      report( SYSTEM, kFacilityString )
	 << "no action bound to stream " << stream
	 << endl;
   }

   setResult( resultString );
   return result;
}

Processor*
ActionCommand::target()
{
   return (Processor*)Command::target();
}

//
// const member functions
//
const Processor*
ActionCommand::target() const
{
   return (const Processor*)Command::target();
}

//
// static member functions
//


// -------------------------------------------------
// Revision history
//
// $Log: ActionCommand.cc,v $
// Revision 1.4  2002/08/16 15:46:36  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.3  2000/06/01 17:48:09  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.2  1999/03/15 19:15:34  mkl
// make SunOS CC happy
//
// Revision 1.1  1999/03/15 18:44:24  mkl
// ActionCommand allows to list and en/disable actions at runtime
//
//
//
