#if !defined(COMMANDPATTERN_SUBCOMMAND_H)
#define COMMANDPATTERN_SUBCOMMAND_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Subcommand
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Fri Sep  3 17:54:39 EDT 1999
// $Id: Subcommand.h,v 1.1 1999/09/06 21:28:54 mkl Exp $
//
// Revision history
//
// $Log: Subcommand.h,v $
// Revision 1.1  1999/09/06 21:28:54  mkl
// new subcommand handling
//

// system include files

// user include files
#include "CommandPattern/SubcommandBase.h"

// forward declarations

template< class T >
class Subcommand : public SubcommandBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef int(T::*SubcommandFunction)();

      // ---------- Constructors and destructor ----------------
      Subcommand( const std::string& iName,
		  Count iMinArgs,
		  Count iMaxArgs,
		  SubcommandFunction iFunction,
		  T* iCommand )
	 : SubcommandBase( iName, 
			   iMinArgs,
			   iMaxArgs ),
	   m_subcomfunc( iFunction ),
	   m_command( iCommand )
      {
      }

      virtual ~Subcommand() {}

      // ---------- member functions ---------------------------
      virtual int execute() {
	 return (m_command->*m_subcomfunc)();
      }

      // ---------- const member functions ---------------------
      
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      Subcommand( const Subcommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const Subcommand& operator=( const Subcommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      SubcommandFunction m_subcomfunc;
      T* m_command;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "CommandPattern/Template/Subcommand.cc"
//#endif

#endif /* COMMANDPATTERN_SUBCOMMAND_H */
