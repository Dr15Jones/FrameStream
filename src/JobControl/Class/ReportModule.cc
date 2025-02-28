// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      ReportModule
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Mon Aug 23 10:55:06 EDT 1999
// $Id: ReportModule.cc,v 1.11 2002/08/21 18:46:47 cleo3 Exp $
//
// Revision history
//
// $Log: ReportModule.cc,v $
// Revision 1.11  2002/08/21 18:46:47  cleo3
// removed improper use of uppercase iomanipulator
//
// Revision 1.10  2002/08/16 15:07:02  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.9  2000/01/14 19:49:28  mkl
// fix string.compare bug on OSF1
//
// Revision 1.8  1999/12/11 19:07:30  mkl
// added 'source status' command; use bug flag for linux string compare function problem
//
// Revision 1.7  1999/09/10 01:08:50  mkl
// For HistoryCommand had to move Conversion class.
// My own "uppercase" function implementation is easier on the user when
// changing report levels (partial matching allowed, mixed case ok).
//
// Revision 1.6  1999/08/30 17:42:58  mkl
// print out down to the debug level (I thought I had committed that -- bad boy)
//
// Revision 1.5  1999/08/27 14:08:46  mkl
// make cxx happy (most recent change)
//
// Revision 1.4  1999/08/27 02:45:12  mkl
// added list and status options for 'report file' command
//
// Revision 1.3  1999/08/26 18:36:07  mkl
// added NO_UPPERCASE_MANIP_BUG flag
//
// Revision 1.2  1999/08/26 01:49:56  mkl
// make cxx happy (with respect to recent ReportModule submission)
//
// Revision 1.1  1999/08/25 21:23:20  mkl
// ReportModule allows setting of report level and logging to files
//
//

#include "Experiment/Experiment.h"

// system include files
#include "C++Std/iostream.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
//#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "JobControl/ReportModule.h"
#include "CommandPattern/StringUtilities.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
//#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.ReportModule" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: ReportModule.cc,v 1.11 2002/08/21 18:46:47 cleo3 Exp $";
static const char* const kTagString = "$Name:  $";


typedef reportmodule_loggers LoggerMap;

//
// static data member definitions
//

//
// constructors and destructor
//
ReportModule::ReportModule( Severity iReportLevel )
   : Module( "ReportModule", "This is my module" ),
     m_command( "report", this ),
     m_logger( iReportLevel, cout ),
     m_defaultLogLevel( iReportLevel ),
     m_fileLoggers( *new LoggerMap )
{
   // check for out-of-memory
   if(    0 == &m_fileLoggers 
      )
   {
      report( EMERGENCY, kFacilityString )
	 << "Unable to allocate memory"
	 << endl ;
      assert(false);
      ::exit( 1 );
   }

   // tie main logger
   MessageLog::Tie( ".", m_logger );
}

// ReportModule::ReportModule( const ReportModule& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

ReportModule::~ReportModule()
{
   // Remember: loggers automatically untie from MessageLog when deleted
   // and the main/default logger is embedded and doesn't need to be 
   // deleted explicitly!

   // close down all file loggers
   closeAllFileLoggers();

   delete &m_fileLoggers;
}

//
// assignment operators
//
// const ReportModule& ReportModule::operator=( const ReportModule& rhs )
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
FrameLogger& 
ReportModule::logger()
{
   return m_logger;
}

DABoolean
ReportModule::setReportLevel( const string& iSeverityString, 
			      FrameLogger* iLogger )
{
   DABoolean returnValue = false;

   // to easily reuse functions for all loggers switch based on parameter
   FrameLogger* logger = ( 0 == iLogger ) ? &m_logger : iLogger;

   // The comparison algorithm here allows:
   // 1.) partial matching
   // 2.) upper/lower case mixed

   // convert to upper case to make comparisons trivial and be easy on user
   string uppercaseSeverityString( 
      StringUtil::toUppercase( iSeverityString ) );

   if( 0 == string( "DEFAULT" ).compare( uppercaseSeverityString ) )
   {
	 logger->setSeverity( m_defaultLogLevel );
	 returnValue = true;
   }
   else
   {
      for( Severity severe = EMERGENCY; 
	   severe <= DEBUG; 
	   severe=Severity(severe+1) )
      {
	 const char* severityLevelString
	    = MessageLog::Logger::SeverityString( severe );

	 if( 0 == strncmp( severityLevelString,
			   uppercaseSeverityString.c_str(),
			   strlen( uppercaseSeverityString.c_str() ) ) )
	 {
	    logger->setSeverity( severe );
	    returnValue = true;
	    break;
	 }
      }
   }

   // if returnValue still false, we didn't get a match
   if( returnValue == false )
   {
      report( ERROR, kFacilityString )
	 << "no severity level match for \"" 
	 << iSeverityString << "\"" << endl;
   }

   return returnValue;
}

DABoolean
ReportModule::openFileLogger( const string& iLogfile, 
			      const string& iSeverityString )
{
   DABoolean returnValue = true;

   // first check if we already have entry
   LoggerMap::iterator findLogger = m_fileLoggers.find( iLogfile );
   if( m_fileLoggers.end() != findLogger )
   {
      report( INFO, kFacilityString )
	 << "logger for \"" << iLogfile << "\" already exists" << endl;
      return returnValue = false;
   }

   // create output stream
   ofstream* outputStream = new ofstream( iLogfile.c_str() );
   if( 0 == outputStream )
   {
      report( EMERGENCY, kFacilityString )
	 << "Unable to allocate memory"
	 << endl ;
      assert(false);
      ::exit( 1 );
   }

   if( !*outputStream ) 
   {
      report( INFO, kFacilityString )
	 << "can't open file \"" << iLogfile << "\"" << endl;
      delete outputStream;
      return returnValue = false;
   }

   FrameLogger* logger = new FrameLogger( m_defaultLogLevel, 
					  *outputStream );
   if( 0 == logger )
   {
      report( EMERGENCY, kFacilityString )
	 << "Unable to allocate memory"
	 << endl ;
      assert(false);
      ::exit( 1 );
   }

   // and reset report level properly
   if( iSeverityString != string( "" ) )
   {
      returnValue = setReportLevel( iSeverityString, logger );
   }

   // tie to MessageLog facility
   MessageLog::Tie( ".", *logger );

   // keep track of things in struct
   LogAndStreamStruct entry;
   entry.m_logger       = logger;
   entry.m_outputStream = outputStream;
   entry.m_isActive     = true;

   m_fileLoggers.insert(
      LoggerMap::value_type( iLogfile,
			     entry )
      );

   return returnValue;
}

DABoolean
ReportModule::closeFileLogger( const string& iLogfile )
{
   DABoolean returnValue = true;

   // first check if we already have entry
   LoggerMap::iterator findLogger = m_fileLoggers.find( iLogfile );
   if( m_fileLoggers.end() == findLogger )
   {
      report( INFO, kFacilityString )
	 << "no logger found for " << iLogfile << endl;
      return returnValue = false;
   }

   // delete Logger (which automatically unties from MessageLog), and close file
   LogAndStreamStruct& entry = (*findLogger).second;
   delete entry.m_logger;
   entry.m_outputStream->close();
   delete entry.m_outputStream;

   // and erase from map
   m_fileLoggers.erase( findLogger );

   return returnValue;
}

void
ReportModule::closeAllFileLoggers()
{
   LoggerMap::iterator itEnd = m_fileLoggers.end();
   for( LoggerMap::iterator it = m_fileLoggers.begin();
	it != itEnd;
	++it )
   {
      closeFileLogger( (*it).first );
   }
}

DABoolean
ReportModule::setReportLevelOnFileLogger( const string& iLogfile,
					  const string& iReportLevel )
{
   DABoolean returnValue = true;

   // first check if we already have entry
   LoggerMap::iterator findLogger = m_fileLoggers.find( iLogfile );
   if( m_fileLoggers.end() == findLogger )
   {
      report( INFO, kFacilityString )
	 << "no logger found for \"" << iLogfile << "\"" << endl;
      return returnValue = false;
   }

   // set report level
   LogAndStreamStruct& entry = (*findLogger).second;
   returnValue = setReportLevel( iReportLevel, entry.m_logger );

   return returnValue;
}

DABoolean
ReportModule::turnOffFileLogger( const string& iLogfile )
{
   DABoolean returnValue = true;

   // first check if we already have entry
   LoggerMap::iterator findLogger = m_fileLoggers.find( iLogfile );
   if( m_fileLoggers.end() == findLogger )
   {
      report( INFO, kFacilityString )
	 << "no logger found for \"" << iLogfile << "\"" << endl;
      return returnValue = false;
   }

   // Untie from MessageLog facility
   LogAndStreamStruct& entry = (*findLogger).second;
   entry.m_outputStream->flush();
   MessageLog::UnTie( *entry.m_logger );
   entry.m_isActive = false;

   return returnValue;
}

DABoolean
ReportModule::turnOnFileLogger( const string& iLogfile )
{
   DABoolean returnValue = true;

   // first check if we already have entry
   LoggerMap::iterator findLogger = m_fileLoggers.find( iLogfile );
   if( m_fileLoggers.end() == findLogger )
   {
      report( INFO, kFacilityString )
	 << "no logger found for \"" << iLogfile << "\"" << endl;
      return returnValue = false;
   }

   // Untie from MessageLog facility
   LogAndStreamStruct& entry = (*findLogger).second;
   MessageLog::Tie( ".", *entry.m_logger );
   entry.m_isActive = true;

   return returnValue;
}

//
// const member functions
//
const FrameLogger& 
ReportModule::logger() const
{
   return m_logger;
}

string
ReportModule::printReportLevel() const
{
   return MessageLog::Logger::SeverityString( m_logger.getSeverity() );
}

string
ReportModule::printAllReportLevels() const
{
   string returnValue;
   for( Severity severe = EMERGENCY; severe <= DEBUG; severe=Severity(severe+1) )
   {
      returnValue += string(
	 MessageLog::Logger::SeverityString( severe ) )
	 + string( "\n" );
   }

   return returnValue;
}

DABoolean
ReportModule::printInfoFileLogger( const string& iLogfile, 
				   ostream& iOs, 
				   DABoolean iFlush ) const
{
   DABoolean returnValue = true;

   // first check if we already have entry
   LoggerMap::iterator findLogger = m_fileLoggers.find( iLogfile );
   if( m_fileLoggers.end() == findLogger )
   {
      report( INFO, kFacilityString )
	 << "no logger found for \"" << iLogfile << "\"" << endl;
      return returnValue = false;
   }
   
   const char* severityString = MessageLog::Logger::SeverityString( 
      (*findLogger).second.m_logger->getSeverity() 
      );
   string activeOrNot = ( (*findLogger).second.m_isActive == true ) ? "on":"off";
   iOs << "  " << (*findLogger).first 
       << "  " << severityString 
       << "  " << activeOrNot
       << "\n";
   if( true == iFlush ) 
   {
      iOs << flush;
   }

   return returnValue;
}

void
ReportModule::printInfoAllFileLoggers() const
{
   if( m_fileLoggers.begin() == m_fileLoggers.end() )
   {
      report( INFO, kFacilityString )
	 << "No File Loggers" << endl;
      return;
   }

   ostream& os = report( INFO, kFacilityString );
   os << "File Loggers:\n";
   LoggerMap::const_iterator itEnd = m_fileLoggers.end();
   for( LoggerMap::const_iterator it = m_fileLoggers.begin();
	it != itEnd;
	++it )
   {
      printInfoFileLogger( (*it).first, os, false );
   }
   os << endl;
}

//
// static member functions
//
