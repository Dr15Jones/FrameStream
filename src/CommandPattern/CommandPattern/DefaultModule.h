#if !defined(DEFAULTMODULE_DEFAULTMODULE_H)
#define DEFAULTMODULE_DEFAULTMODULE_H
// -*- C++ -*-
//
// Package:     DefaultModule
// Module:      DefaultModule
// 
// Description: (dynamically-loadable) module
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Feb 18 23:00:13 EST 1999
// $Id: DefaultModule.h,v 1.1.1.1 1999/02/22 22:44:37 mkl Exp $
//
// Revision history
//
// $Log: DefaultModule.h,v $
// Revision 1.1.1.1  1999/02/22 22:44:37  mkl
// imported sources
//
//

// system include files

// user include files
#include "CommandPattern/Module.h"
#include "CommandPattern/DefaultModuleCommand.h"
#include "CommandPattern/DefaultModuleInternalCommand.h"
#include "CommandPattern/Switch.h"

// forward declarations

class DefaultModule : public Module
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DefaultModule();
      virtual ~DefaultModule();

      // ---------- member functions ---------------------------
      Switch::OnOff setPrompting( Switch::OnOff iSetting );

      // ---------- const member functions ---------------------
      Switch::OnOff usePrompting() const;
      
      // ---------- static member functions --------------------
      static DefaultModule const *instance();

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      DefaultModule( const DefaultModule& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DefaultModule& operator=( const DefaultModule& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      // NOTE: you need at least one external command
      //       to be able to call your module;
      //       the number of internal commands is up to you...
      DefaultModuleCommand m_command;
      //DefaultModuleInternalCommand m_internalCommand;

      // switches for various options
      Switch m_prompting;  // prompt when more than one possible option
                           // or use always first option 
 
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DefaultModule/Template/DefaultModule.cc"
//#endif

#endif /* DEFAULTMODULE_DEFAULTMODULE_H */
