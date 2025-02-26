#if !defined(COMMANDPATTERN_SUBCOMMANDBASE_H)
#define COMMANDPATTERN_SUBCOMMANDBASE_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      SubcommandBase
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Fri Sep  3 17:54:44 EDT 1999
// $Id: SubcommandBase.h,v 1.1 1999/09/06 21:28:54 mkl Exp $
//
// Revision history
//
// $Log: SubcommandBase.h,v $
// Revision 1.1  1999/09/06 21:28:54  mkl
// new subcommand handling
//

// system include files
#include <string>

// user include files

// forward declarations

class SubcommandBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SubcommandBase( const string& iName,
		      Count iMinArgs,
		      Count iMaxArgs );
      virtual ~SubcommandBase();

      // ---------- member functions ---------------------------
      virtual int execute() = 0;

      // ---------- const member functions ---------------------
      const string& name() const { return m_name; }
      Count minArgs() const { return m_minArgs; }
      Count maxArgs() const { return m_maxArgs; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SubcommandBase( const SubcommandBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SubcommandBase& operator=( const SubcommandBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      string m_name;
      Count m_minArgs;
      Count m_maxArgs;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "CommandPattern/Template/SubcommandBase.cc"
//#endif

#endif /* COMMANDPATTERN_SUBCOMMANDBASE_H */
