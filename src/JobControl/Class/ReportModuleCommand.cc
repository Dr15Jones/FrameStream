// -*- C++ -*-
//
// Package:     JobControl
// Module:      ReportModuleCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Mon Aug 23 10:55:06 EDT 1999
// $Id: ReportModuleCommand.cc,v 1.5 2003/09/19 21:05:08 cdj Exp $
//
// Revision history
//
// $Log: ReportModuleCommand.cc,v $
// Revision 1.5  2003/09/19 21:05:08  cdj
// send result to Tcl command line
//
// Revision 1.4  2000/06/01 17:48:44  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.3  1999/09/10 01:08:51  mkl
// For HistoryCommand had to move Conversion class.
// My own "uppercase" function implementation is easier on the user when
// changing report levels (partial matching allowed, mixed case ok).
//
// Revision 1.2  1999/08/27 02:45:17  mkl
// added list and status options for 'report file' command
//
// Revision 1.1  1999/08/25 21:23:21  mkl
// ReportModule allows setting of report level and logging to files
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
#include "JobControl/ReportModuleCommand.h"
#include "JobControl/ReportModule.h"

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
static const char* const kFacilityString = "JobControl.ReportModuleCommand" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: ReportModuleCommand.cc,v 1.5 2003/09/19 21:05:08 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//
static const string helpMessage =
string( " Subcommands are:                                                  \n" )+
string( "  help                                                             \n" )+
string( "                                                                   \n" )+
string( "  level [<level>]                  set or print level              \n" )+
string( "                                   where <level> is: \"default\"   \n" )+
string( "                                   or any of \"printlevels\"       \n" )+
string( "                                   (partial match, upper/lowercase)\n" )+
string( "                                                                   \n" )+
string( "  printlevels                      print available levels          \n" )+
string( "                                                                   \n" )+
string( "  file open   <logfile> [<level>]  create new logfile logger       \n" )+
string( "  file level  <logfile> <level>    change level in logger          \n" )+
string( "  file off    <logfile>            temporarily switch off logging  \n" )+
string( "  file on     <logfile>            resume logging                  \n" )+
string( "  file close  <logfile>            close logfile, remove logger    \n" )+
string( "  file status <logfile>            print status of logger          \n" )+
string( "  file list                        list all file loggers           \n" )+
string( "                                                                   \n" );

//
// constructors and destructor
//
ReportModuleCommand::ReportModuleCommand( const Command::Name& iName, 
				ReportModule* target )
   : Command( iName, target, false ) // "false" to make it external command
{
}

// ReportModuleCommand::ReportModuleCommand( const ReportModuleCommand& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

ReportModuleCommand::~ReportModuleCommand()
{
}

//
// assignment operators
//
// const ReportModuleCommand& ReportModuleCommand::operator=( const ReportModuleCommand& rhs )
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
int
ReportModuleCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   // expect two arguments: "print" or "help"
   setArgs( argc, argv );
   if( 2 <= argc )
   {
      if( 0 == strcmp( argv[1], "help" ) )
      {
         result = helpHandler();
      } else
      if( 0 == strcmp( argv[1], "printlevels" ) )
      {
         result = printAllReportLevelsHandler();
      } else
      if( 2 == argc && 0 == strcmp( argv[1], "level" ) )
      {
	 result = printReportLevelHandler();
      } else
      if( 3 == argc && 0 == strcmp( argv[1], "level" ) )
      {
	 result = setReportLevelHandler();
      } else
      if( 4 <= argc && 0 == strcmp( argv[1], "file" ) )
      {
	 if( 0 == strcmp( argv[2], "open" ) )
	 {
	    result = logfileOpenHandler();
	 } else
	 if( 0 == strcmp( argv[2], "level" ) )
	 {	
	    if( 5 != argc )
	    {
	       report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
	       result = COMMAND_ERROR;
	    }
	    else
	    {
	       result = logfileLevelHandler();
	    }
	 } else
	 if( 0 == strcmp( argv[2], "off" ) )
	 {
	    result = logfileOffHandler();
	 } else
         if( 0 == strcmp( argv[2], "on" ) )
	 {
	    result = logfileOnHandler();
	 } else
	 if( 0 == strcmp( argv[2], "close" ) )
	 {
	    result = logfileCloseHandler();
	 } else
	 if( 0 == strcmp( argv[2], "status" ) )
	 {
	    result = logfileStatusHandler();
	 }
	 else
	 {
	    report( SYSTEM, kFacilityString ) 
	       << "invalid command subargument " << argv[2] << endl;
	    result = COMMAND_ERROR;
	 }
      } else
      if( 3 == argc && 0 == strcmp( argv[1], "file" ) )
      {
	 if( 0 == strcmp( argv[2], "list" ) )
	 {
	    result = logfileListHandler();
	 }
	 else
	 {
	    report( SYSTEM, kFacilityString ) 
	       << "invalid command subargument " << argv[2] << endl;
	    result = COMMAND_ERROR;
	 }
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
ReportModuleCommand::helpHandler()
{
   // print help from header
   report( SYSTEM, kFacilityString )
      << "\n\nDescription: " << name() << "\n\n"
      << helpMessage
      << endl;

   return COMMAND_OK;
}

int
ReportModuleCommand::printReportLevelHandler()
{
   setResult( target()->printReportLevel() );

   return COMMAND_OK;
}

int
ReportModuleCommand::printAllReportLevelsHandler()
{
   setResult( target()->printAllReportLevels() );

   return COMMAND_OK;
}

int
ReportModuleCommand::setReportLevelHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;

   // second argument is report level
   string severity( m_argv[2] );
   DABoolean status = target()->setReportLevel( severity );
   if( true == status )
   {
      setResult( target()->printReportLevel() );
   }
   else
   {
      report( SYSTEM, kFacilityString )
	 << "Unknown severity \"" << severity << "\"" << endl;
      returnValue = Command::COMMAND_ERROR;
   }

   return returnValue;
}

int
ReportModuleCommand::logfileOpenHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;

   // command looks like: "report" "file" "open" "<logfile>" "[level]"
   assert( m_argc >= 4 );

   // logfile
   string logfile( m_argv[3] );
   DABoolean status;
   if( m_argc > 4 ) 
   {
      string severity( m_argv[4] );
      status = target()->openFileLogger( logfile, severity );
   }
   else
   {
      status = target()->openFileLogger( logfile );
   }
      
   if( true == status )
   {
      report( INFO, kFacilityString )
	 << "opened logfile \"" << logfile << "\"" << endl;
   }
   else
   {
      report( SYSTEM, kFacilityString )
	 << "problem with logfile \"" << logfile << "\"" << endl;
      returnValue = Command::COMMAND_ERROR;
   }

   return returnValue;
}

int
ReportModuleCommand::logfileLevelHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;

   // command looks like: "report" "file" "level" "<logfile>" "[level]"
   assert( m_argc == 5 );

   // logfile
   string logfile( m_argv[3] );
   string level  ( m_argv[4] );
   DABoolean status = target()->setReportLevelOnFileLogger( logfile, level );
   if( true == status )
   {
      report( INFO, kFacilityString )
	 << "reset report level for \"" 
	 << logfile << "\" to \"" << level << "\"" << endl;
   }
   else
   {
      report( SYSTEM, kFacilityString )
	 << "problem with logfile \"" << logfile << "\"" << endl;
      returnValue = Command::COMMAND_ERROR;
   }

   return returnValue;
}

int
ReportModuleCommand::logfileOffHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;

   // command looks like: "report" "file" "off" "<logfile>"
   assert( m_argc >= 4 );

   // logfile
   string logfile( m_argv[3] );
   DABoolean status = target()->turnOffFileLogger( logfile );
   if( true == status )
   {
      report( INFO, kFacilityString )
	 << "turned off \"" << logfile << "\"" << endl;
   }
   else
   {
      report( SYSTEM, kFacilityString )
	 << "problem with logfile \"" << logfile << "\"" << endl;
      returnValue = Command::COMMAND_ERROR;
   }

   return returnValue;
}

int
ReportModuleCommand::logfileOnHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;

   // command looks like: "report" "file" "on" "<logfile>"
   assert( m_argc >= 4 );

   // logfile
   string logfile( m_argv[3] );
   DABoolean status = target()->turnOnFileLogger( logfile );
   if( true == status )
   {
      report( INFO, kFacilityString )
	 << "turned on \"" << logfile << "\"" << endl;
   }
   else
   {
      report( SYSTEM, kFacilityString )
	 << "problem with logfile \"" << logfile << "\"" << endl;
      returnValue = Command::COMMAND_ERROR;
   }

   return returnValue;
}

int
ReportModuleCommand::logfileCloseHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;

   // command looks like: "report" "file" "close" "<logfile>"
   assert( m_argc >= 4 );

   // logfile
   string logfile( m_argv[3] );
   DABoolean status = target()->closeFileLogger( logfile );
   if( true == status )
   {
      report( INFO, kFacilityString )
	 << "closed \"" << logfile << "\"" << endl;
   }
   else
   {
      report( SYSTEM, kFacilityString )
	 << "problem with logfile \"" << logfile << "\"" << endl;
      returnValue = Command::COMMAND_ERROR;
   }

   return returnValue;
}

int
ReportModuleCommand::logfileStatusHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;

   // command looks like: "report" "file" "status" "<logfile>"
   assert( m_argc >= 4 );

   // logfile
   string logfile( m_argv[3] );
   DABoolean status = target()->printInfoFileLogger( logfile );
   if( false )
   {
      report( SYSTEM, kFacilityString )
	 << "problem with logfile \"" << logfile << "\"" << endl;
      returnValue = Command::COMMAND_ERROR;
   }

   return returnValue;
}

int
ReportModuleCommand::logfileListHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;

   // command looks like: "report" "file" "list"
   assert( m_argc == 3 );

   target()->printInfoAllFileLoggers();

   return returnValue;
}

ReportModule*
ReportModuleCommand::target()
{
   return (ReportModule*)Command::target();
}

//
// const member functions
//
const ReportModule*
ReportModuleCommand::target() const
{
   return (const ReportModule*)Command::target();
}

//
// static member functions
//
