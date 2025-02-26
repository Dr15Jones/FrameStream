#if !defined(JOBCONTROL_SINKFORMATMODULE_H)
#define JOBCONTROL_SINKFORMATMODULE_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      SinkFormatModule
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Dec  1 22:45:02 EST 1998
// $Id: SinkFormatModule.h,v 1.1 1998/12/02 05:55:32 mkl Exp $
//
// Revision history
//
// $Log: SinkFormatModule.h,v $
// Revision 1.1  1998/12/02 05:55:32  mkl
// towards interacting with Source- and SinkFormats
//

// system include files

// user include files
#include "DataStorage/SinkFormat.h"
#include "CommandPattern/Module.h"

// forward declarations

class SinkFormatModule : public SinkFormat, public Module
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SinkFormatModule();
      virtual ~SinkFormatModule();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------
      static string factorySymbol();
      
   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SinkFormatModule( const SinkFormatModule& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SinkFormatModule& operator=( const SinkFormatModule& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "JobControl/Template/SinkFormatModule.cc"
//#endif

#endif /* JOBCONTROL_SINKFORMATMODULE_H */
