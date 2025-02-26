#if !defined(JOBCONTROL_SOURCEFORMATMODULE_H)
#define JOBCONTROL_SOURCEFORMATMODULE_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      SourceFormatModule
// 
// Description: allow loading and interaction with SourceFormats
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Dec  1 22:45:13 EST 1998
// $Id: SourceFormatModule.h,v 1.1 1998/12/02 05:55:36 mkl Exp $
//
// Revision history
//
// $Log: SourceFormatModule.h,v $
// Revision 1.1  1998/12/02 05:55:36  mkl
// towards interacting with Source- and SinkFormats
//

// system include files

// user include files
#include "DataDelivery/SourceFormat.h"
#include "CommandPattern/Module.h"
#include "JobControl/BinderType.h"  

// forward declarations

class SourceFormatModule : public SourceFormat, public Module
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SourceFormatModule(  BinderType iType );
      virtual ~SourceFormatModule();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------
      static string factorySymbol();

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SourceFormatModule( const SourceFormatModule& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SourceFormatModule& operator=( const SourceFormatModule& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "JobControl/Template/SourceFormatModule.cc"
//#endif

#endif /* JOBCONTROL_SOURCEFORMATMODULE_H */
