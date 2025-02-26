#if !defined(DEFAULTMODULE_DEFAULTMODULEINTERNALCOMMAND_H)
#define DEFAULTMODULE_DEFAULTMODULEINTERNALCOMMAND_H
// -*- C++ -*-
//
// Package:     <DefaultModule>
// Module:      DefaultModuleInternalCommand
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Feb 18 23:00:13 EST 1999
// $Id: DefaultModuleInternalCommand.h,v 1.1.1.1 1999/02/22 22:44:37 mkl Exp $
//
// Revision history
//
// $Log: DefaultModuleInternalCommand.h,v $
// Revision 1.1.1.1  1999/02/22 22:44:37  mkl
// imported sources
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations
class DefaultModule;

class DefaultModuleInternalCommand : public Command
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DefaultModuleInternalCommand( const Command::Name& iName, 
			      DefaultModule* target );
      virtual ~DefaultModuleInternalCommand();

      // ---------- member functions ---------------------------
      virtual int execute( int argc, char* argv[] );

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual int helpHandler();
      virtual int doHandler();

      DefaultModule* target();
      const DefaultModule* target() const;

   private:
      // ---------- Constructors and destructor ----------------
      DefaultModuleInternalCommand( const DefaultModuleInternalCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DefaultModuleInternalCommand& operator=( 
	 const DefaultModuleInternalCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DefaultModule/Template/DefaultModuleInternalCommand.cc"
//#endif

#endif /* DEFAULTMODULE_DEFAULTMODULEINTERNALCOMMAND_H */
