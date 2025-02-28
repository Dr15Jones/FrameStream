#if !defined(JOBCONTROL_REPORTMODULECOMMAND_H)
#define JOBCONTROL_REPORTMODULECOMMAND_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      ReportModuleCommand
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon Aug 23 10:55:06 EDT 1999
// RC(Id)
//
// Revision history
//
// $Log: ReportModuleCommand.h,v $
// Revision 1.2  1999/08/27 02:45:23  mkl
// added list and status options for 'report file' command
//
// Revision 1.1  1999/08/25 21:23:29  mkl
// ReportModule allows setting of report level and logging to files
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations
class ReportModule;

class ReportModuleCommand : public Command
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ReportModuleCommand( const Command::Name& iName, 
		      ReportModule* target );
      virtual ~ReportModuleCommand();

      // ---------- member functions ---------------------------
      virtual int execute( int argc, char* argv[] );

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual int helpHandler();
      virtual int setReportLevelHandler();
      virtual int printReportLevelHandler();
      virtual int printAllReportLevelsHandler();

      virtual int logfileOpenHandler();
      virtual int logfileLevelHandler();
      virtual int logfileOffHandler();
      virtual int logfileOnHandler();
      virtual int logfileCloseHandler();
      virtual int logfileListHandler();
      virtual int logfileStatusHandler();

      ReportModule* target();
      const ReportModule* target() const;

   private:
      // ---------- Constructors and destructor ----------------
      ReportModuleCommand( const ReportModuleCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ReportModuleCommand& operator=( const ReportModuleCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "JobControl/Template/ReportModuleCommand.cc"
//#endif

#endif /* JOBCONTROL_REPORTMODULECOMMAND_H */
