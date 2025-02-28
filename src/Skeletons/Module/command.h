// -*- C++ -*-
#if !defined(MODNAME_MODNAMECOMMAND_H)
#define MODNAME_MODNAMECOMMAND_H
//
// Package:     <Modname>
// Module:      ModnameCommand
//
/**\class ModnameCommand ModnameCommand.h Modname/ModnameCommand.h
 
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

class ModnameCommand : public Command
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ModnameCommand( const Command::Name& iName, 
		      Modname* target );
      virtual ~ModnameCommand();

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
      ModnameCommand( const ModnameCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ModnameCommand& operator=( const ModnameCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "Modname/Template/ModnameCommand.cc"
//#endif

#endif /* MODNAME_MODNAMECOMMAND_H */
