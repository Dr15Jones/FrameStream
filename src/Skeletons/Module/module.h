// -*- C++ -*-
#if !defined(MODNAME_MODNAME_H)
#define MODNAME_MODNAME_H
//
// Package:     Modname
// Module:      Modname
//
/**\class Modname Modname.h Modname/Modname.h
 
 Description: (dynamically-loadable) module

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
#include "CommandPattern/Module.h"
#include "Modname/ModnameCommand.h"
#include "Modname/ModnameInternalCommand.h"

// forward declarations

class Modname : public Module
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      Modname();
      virtual ~Modname();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      void printNumber( int iNumber ) const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      Modname( const Modname& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const Modname& operator=( const Modname& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      // NOTE: if you want a command (or commands) to be available 
      //       upon loading of the module, you need an external 
      //       command (or commands);
      //       and you can have any number of internal commands...
      ModnameCommand m_command;
      ModnameInternalCommand m_internalCommand;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "Modname/Template/Modname.cc"
//#endif

#endif /* MODNAME_MODNAME_H */
