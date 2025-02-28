// -*- C++ -*-
#if !defined(MODNAME_MODNAMEINTERNALCOMMAND_H)
#define MODNAME_MODNAMEINTERNALCOMMAND_H
//
// Package:     <Modname>
// Module:      ModnameInternalCommand
//
/**\class ModnameInternalCommand ModnameInternalCommand.h Modname/InternalCommand.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      John Doe
// Created:     day-mon-xx
// RCS(Id)
//
// Revision history
//
// RCS(Log)
//

// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations
class Modname;

class ModnameInternalCommand : public Command
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ModnameInternalCommand( const Command::Name& iName, 
			      Modname* target );
      virtual ~ModnameInternalCommand();

      // ---------- member functions ---------------------------
      // You may override the base class's execute method, but it's
      // easier to use the "Subcommand" class to handle subcommands.
      // (Have a look at the command::ctor for an example.)
      //virtual int execute( int argc, char* argv[] );

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual int helpHandler();
      virtual int printHandler();

      Modname* target();
      const Modname* target() const;

   private:
      // ---------- Constructors and destructor ----------------
      ModnameInternalCommand( const ModnameInternalCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ModnameInternalCommand& operator=( 
	 const ModnameInternalCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "Modname/Template/ModnameInternalCommand.cc"
//#endif

#endif /* MODNAME_MODNAMEINTERNALCOMMAND_H */
