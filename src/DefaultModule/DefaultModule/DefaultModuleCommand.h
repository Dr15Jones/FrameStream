#if !defined(DEFAULTMODULE_DEFAULTMODULECOMMAND_H)
#define DEFAULTMODULE_DEFAULTMODULECOMMAND_H
// -*- C++ -*-
//
// Package:     <DefaultModule>
// Module:      DefaultModuleCommand
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Feb 18 23:00:13 EST 1999
// RC(Id)
//
// Revision history
//
// $Log: DefaultModuleCommand.h,v $
// Revision 1.1.1.1  1999/02/22 22:44:37  mkl
// imported sources
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations
class DefaultModule;

class DefaultModuleCommand : public Command
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DefaultModuleCommand( const Command::Name& iName, 
			    DefaultModule* target );
      virtual ~DefaultModuleCommand();

      // ---------- member functions ---------------------------
      virtual int execute( int argc, char* argv[] );

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual int helpHandler();
      virtual int promptHandler();

      DefaultModule* target();
      const DefaultModule* target() const;

   private:
      // ---------- Constructors and destructor ----------------
      DefaultModuleCommand( const DefaultModuleCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DefaultModuleCommand& operator=( const DefaultModuleCommand& ); 
                                                           // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DefaultModule/Template/DefaultModuleCommand.cc"
//#endif

#endif /* DEFAULTMODULE_DEFAULTMODULECOMMAND_H */
