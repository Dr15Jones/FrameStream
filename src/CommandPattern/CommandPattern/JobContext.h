#if !defined(COMMANDPATTERN_JOBCONTEXT_H)
#define COMMANDPATTERN_JOBCONTEXT_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      JobContext
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Feb 18 18:35:05 EST 1999
// $Id: JobContext.h,v 1.2 2000/12/16 17:57:47 cdj Exp $
//
// Revision history
//
// $Log: JobContext.h,v $
// Revision 1.2  2000/12/16 17:57:47  cdj
// can now set instance for JobContext (needed for SubFrame)
//
// Revision 1.1  1999/02/22 23:40:48  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//

// system include files

// user include files
#include "CommandPattern/NamingService.h"
#include "CommandPattern/Module.h"

// forward declarations

class JobContext : public NamingService< Module >
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      virtual ~JobContext();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------
      static JobContext* instance();

   protected:
      // ---------- protected member functions -----------------
      JobContext();

      // ---------- protected const member functions -----------

      static void setInstance( JobContext* iJobContext ) {
	 m_instance = iJobContext;
      }

   private:
      // ---------- Constructors and destructor ----------------
      JobContext( const JobContext& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const JobContext& operator=( const JobContext& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------
      static JobContext* m_instance;
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "CommandPattern/Template/JobContext.cc"
//#endif

#endif /* COMMANDPATTERN_JOBCONTEXT_H */
