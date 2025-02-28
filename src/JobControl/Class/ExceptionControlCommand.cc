// -*- C++ -*-
//
// Package:     JobControl
// Module:      ExceptionControlCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Tue Feb 29 18:10:06 EDT 2000
// $Id: ExceptionControlCommand.cc,v 1.4 2002/08/21 18:46:46 cleo3 Exp $
//
// Revision history
//
// $Log: ExceptionControlCommand.cc,v $
// Revision 1.4  2002/08/21 18:46:46  cleo3
// removed improper use of uppercase iomanipulator
//
// Revision 1.3  2000/06/01 17:48:42  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.2  2000/03/01 19:25:21  mkl
// further refinement of ExceptionControl command; no new features
//
// Revision 1.1  2000/03/01 00:08:52  mkl
// control if should continue event loop in case of DataAccess Exceptions: exception command
//
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "JobControl/ExceptionControlCommand.h"
#include "JobControl/JobControl.h"
#include "CommandPattern/StringUtilities.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.ExceptionControlCommand" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: ExceptionControlCommand.cc,v 1.4 2002/08/21 18:46:46 cleo3 Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//
static const string helpMessage =
string( " Subcommands are:                                                  \n" )+
string( "  help                                                             \n" )+
string( "                                                                   \n" )+
string( "  continueEventLoop [on/off*]      set flag to continue the event  \n" )+
string( "                                   loop for Data Access Exceptions \n" )+
string( "                                                                   \n" )+
string( "  status                           print out current settings      \n" )+
string( "                                                                   \n" );

//
// constructors and destructor
//
ExceptionControlCommand::ExceptionControlCommand( const Command::Name& iName, 
						  JobControl* target )
   : Command( iName, target )
{
   // The arguments are: 
   // 1.) command name (what you will type at the Suez command line)
   // 2.) minimum number of arguments expected
   // 3.) maxiumu number of arguments expected
   // 4.) pointer to a member function which will handle the subcommand
   // 5.) the "this" pointer to point to this command object.
   addSubcommand( 
      new Subcommand< ExceptionControlCommand >(
         "help", 2, 2,
         &ExceptionControlCommand::helpHandler,
         this )
      );
   addSubcommand( 
      new Subcommand< ExceptionControlCommand >(
         "continueEventLoop", 2, 3,
         &ExceptionControlCommand::continueEventLoopHandler,
         this )
      );
   addSubcommand( 
      new Subcommand< ExceptionControlCommand >(
         "status", 2, 2,
         &ExceptionControlCommand::printStatusHandler,
         this )
      );
}

// ExceptionControlCommand::ExceptionControlCommand( const ExceptionControlCommand& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

ExceptionControlCommand::~ExceptionControlCommand()
{
}

//
// assignment operators
//
// const ExceptionControlCommand& ExceptionControlCommand::operator=( const ExceptionControlCommand& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
//int
//ExceptionControlCommand::execute( int argc, char* argv[] )
//{
//   int returnValue = COMMAND_ERROR;
//
//   setArgs( argc, argv );
//   if ( 2 <= argc ) {
//      if( 0 == strcmp( argv[1], "help" ) ) {
//       returnValue = helpHandler();
//      }
//      else 
//      {
//       report( ERROR, kFacilityString ) << "invalid command arg" << endl;
//       helpHandler();
//       returnValue = COMMAND_ERROR;
//      }
//   } 
//   else {
//      report( ERROR, kFacilityString ) << "wrong # args" << endl;
//      helpHandler();
//      returnValue = COMMAND_ERROR;
//   }
//
//   return returnValue;
//}

int
ExceptionControlCommand::helpHandler()
{
   // print help from header
   report( SYSTEM, kFacilityString )
      << "\n\nDescription: " << name() << "\n\n"
      << helpMessage
      << endl;

   return COMMAND_OK;
}

int
ExceptionControlCommand::printStatusHandler()
{
   report( SYSTEM, kFacilityString ) 
      << "continueEventLoop :" << 
      ( target()->continueEventLoopAfterException() ? "on" : "off" )
      << endl;

   return COMMAND_OK;
}

int
ExceptionControlCommand::continueEventLoopHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;

   assert( m_argc >=2 && m_argc <= 3 );

   if( m_argc == 2 ) {
      string resultString = 
	 ( target()->continueEventLoopAfterException() ? "on" : "off" );
      setResult( resultString );
   }
   else if( m_argc >= 3 ) {
      // second argument is report level
      string setting( m_argv[2] );
      
      // convert to upper case to make comparison trivial
      string uppercaseSetting( 
	 StringUtil::toUppercase( setting ) );
      
      if( 0 == string( "ON" ).compare( uppercaseSetting ) )
      {
	 target()->setContinueEventLoopAfterException( true );
	 setResult( "on" );
      }
      else if ( 0 == string( "OFF" ).compare( uppercaseSetting ) )
      {
	 target()->setContinueEventLoopAfterException( false );
	 setResult( "off" );
      }
      else
      {
	 report( SYSTEM, kFacilityString )
	    << "Unknown setting \"" << setting << "\"" << endl;
	 returnValue = Command::COMMAND_ERROR;
      }
   }

   return returnValue;
}

JobControl*
ExceptionControlCommand::target()
{
   return (JobControl*)Command::target();
}

//
// const member functions
//
const JobControl*
ExceptionControlCommand::target() const
{
   return (const JobControl*)Command::target();
}

//
// static member functions
//
