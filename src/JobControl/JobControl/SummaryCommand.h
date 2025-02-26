#if !defined(JOBCONTROL_SUMMARYCOMMAND_H)
#define JOBCONTROL_SUMMARYCOMMAND_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      SummaryCommand
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Fri Jul 24 10:42:52 EDT 1998
// $Id: SummaryCommand.h,v 1.3 1999/02/22 23:41:50 mkl Exp $
//
// Revision history
//
// $Log: SummaryCommand.h,v $
// Revision 1.3  1999/02/22 23:41:50  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.2  1998/07/29 20:06:54  mkl
// new summary command implemented
//
// Revision 1.1  1998/07/28 15:53:22  mkl
// ripple effect: needed to include set
//

// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations

class SummaryCommand : public Command
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SummaryCommand( const Name& name, Module* target );
      virtual ~SummaryCommand();

      // ---------- member functions ---------------------------
      virtual int execute( int argc, char* argv[] ); // executer

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual int helpHandler ();
      virtual int resetHandler();
      virtual int listHandler();

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SummaryCommand( const SummaryCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SummaryCommand& operator=( const SummaryCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "JobControl/Template/SummaryCommand.cc"
//#endif

#endif /* JOBCONTROL_SUMMARYCOMMAND_H */
