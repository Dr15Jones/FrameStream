#if !defined(JOBCONTROL_SUMMARYMODULE_H)
#define JOBCONTROL_SUMMARYMODULE_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      SummaryModule
// 
// Description: keep statistics of processed stops
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Fri Jul 24 10:42:46 EDT 1998
// $Id: SummaryModule.h,v 1.5 2003/09/19 21:03:48 cdj Exp $
//
// Revision history
//
// $Log: SummaryModule.h,v $
// Revision 1.5  2003/09/19 21:03:48  cdj
// use new Keyword Command method
//
// Revision 1.4  1999/02/22 23:41:50  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.3  1998/11/09 19:33:30  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.2  1998/07/29 20:06:54  mkl
// new summary command implemented
//
// Revision 1.1  1998/07/28 15:53:22  mkl
// ripple effect: needed to include set
//

// system include files
#include <map>
#include <map>

// user include files
#include "CommandPattern/Module.h"
#include "DataHandler/Stream.h"
#include "CommandPattern/CPCommandWithKeywords.h"

// forward declarations
#if !defined( _summarymodule_counter_ )
#define _summarymodule_counter_ std::map< Stream::Type, Count >
#endif

class SummaryModule : public Module
{
      // ---------- friend classes and function ------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SummaryModule();
      virtual ~SummaryModule();

      // ---------- member functions ---------------------------
      void reset();
      Count& operator[]( const Stream::Type& iStreamType );

      // ---------- const member functions ---------------------
      std::string list();

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SummaryModule( const SummaryModule& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SummaryModule& operator=( const SummaryModule& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      CPCommandWithKeywords m_command;

      _summarymodule_counter_& m_counter;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "JobControl/Template/SummaryModule.cc"
//#endif

#endif /* JOBCONTROL_SUMMARYMODULE_H */
