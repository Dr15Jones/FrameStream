#if !defined(JOBCONTROL_REPORTMODULE_H)
#define JOBCONTROL_REPORTMODULE_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      ReportModule
// 
// Description: (dynamically-loadable) module
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon Aug 23 10:55:06 EDT 1999
// $Id: ReportModule.h,v 1.5 2002/11/21 21:11:17 cleo3 Exp $
//
// Revision history
//
// $Log: ReportModule.h,v $
// Revision 1.5  2002/11/21 21:11:17  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.4  2002/08/16 15:07:05  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.3  1999/08/27 02:45:21  mkl
// added list and status options for 'report file' command
//
// Revision 1.2  1999/08/26 01:49:59  mkl
// make cxx happy (with respect to recent ReportModule submission)
//
// Revision 1.1  1999/08/25 21:23:27  mkl
// ReportModule allows setting of report level and logging to files
//
//

// system include files
#include "C++Std/iostream.h"
#include "C++Std/fstream.h"

// user include files
#include "CommandPattern/Module.h"
#include "JobControl/ReportModuleCommand.h"
#include "DataHandler/FrameLogger.h"

// forward declarations
#include <string>

#include "STLUtility/fwd_map.h"
#if !defined(reportmodule_loggers)
#define reportmodule_loggers STL_MAP( string, ReportModule::LogAndStreamStruct )
#endif

class ReportModule : public Module
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      // for internal bookkeeping (could be private but problem with typedef)
      struct LogAndStreamStruct { 
	 FrameLogger* m_logger;
	 ofstream* m_outputStream;
	 DABoolean m_isActive;
      };

      // ---------- Constructors and destructor ----------------
      ReportModule( Severity iReportLevel=INFO );
      virtual ~ReportModule();

      // ---------- member functions ---------------------------
      FrameLogger& logger();
      DABoolean setReportLevel( const string& iReportLevel, 
				FrameLogger* iLogger=0 );

      DABoolean openFileLogger( const string& iLogfile, 
				const string& iReportLevel=string("") );
      DABoolean closeFileLogger( const string& iLogfile );
      void closeAllFileLoggers();
      DABoolean setReportLevelOnFileLogger( const string& iLogfile,
					    const string& iReportLevel );
      DABoolean turnOffFileLogger( const string& iLogfile );
      DABoolean turnOnFileLogger( const string& iLogfile );

      // ---------- const member functions ---------------------
      const FrameLogger& logger() const;
      string printReportLevel() const;
      string printAllReportLevels() const;

      DABoolean printInfoFileLogger( const string& iLogfile, 
				     ostream& os=cout,
				     DABoolean iFlush=true ) const;
      void printInfoAllFileLoggers() const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      ReportModule( const ReportModule& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ReportModule& operator=( const ReportModule& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      // NOTE: you need at least one external command
      //       to be able to call your module;
      //       the number of internal commands is up to you...
      ReportModuleCommand m_command;

      // actual data members
      FrameLogger m_logger;
      Severity m_defaultLogLevel;

      // file loggers created on the fly
      reportmodule_loggers& m_fileLoggers;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "JobControl/Template/ReportModule.cc"
//#endif

#endif /* JOBCONTROL_REPORTMODULE_H */
