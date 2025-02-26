#if !defined(JOBCONTROL_EXCEPTIONCONTROLCOMMAND_H)
#define JOBCONTROL_EXCEPTIONCONTROLCOMMAND_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      ExceptionControlCommand
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Feb 29 18:10:23 EDT 2000
// RC(Id)
//
// Revision history
//
// $Log: ExceptionControlCommand.h,v $
// Revision 1.1  2000/03/01 00:08:54  mkl
// control if should continue event loop in case of DataAccess Exceptions: exception command
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations
class JobControl;

class ExceptionControlCommand : public Command
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ExceptionControlCommand( const Command::Name& iName, 
			       JobControl* target );
      virtual ~ExceptionControlCommand();

      // ---------- member functions ---------------------------
      //virtual int execute( int argc, char* argv[] );

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual int helpHandler();
      virtual int continueEventLoopHandler();
      virtual int printStatusHandler();

      JobControl* target();
      const JobControl* target() const;

   private:
      // ---------- Constructors and destructor ----------------
      ExceptionControlCommand( const ExceptionControlCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ExceptionControlCommand& operator=( const ExceptionControlCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "JobControl/Template/ExceptionControlCommand.cc"
//#endif

#endif /* JOBCONTROL_EXCEPTIONCONTROLCOMMAND_H */
