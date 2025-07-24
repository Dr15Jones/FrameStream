#if !defined(COMMANDPATTERN_CPCOMMANDWITHKEYWORDS_H)
#define COMMANDPATTERN_CPCOMMANDWITHKEYWORDS_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      CPCommandWithKeywords
// 
/**\class CPCommandWithKeywords CPCommandWithKeywords.h CommandPattern/CPCommandWithKeywords.h

 Description: A command that can be decomposed into a set of keywords

 Usage:
    This Command is attached to a Module. In the constructor of the Module
     you use 'add' to attach new CommandPattern::Keyword::Base objects which 
     handle the parsing and execution of the command.

   A CommandPattern::Keyword::Base with a blank ("") name will be used in 
     the case where no keyword matches the user's input

*/
//
// Author:      Chris D Jones
// Created:     Fri Jul 18 13:49:28 EDT 2003
// $Id: CPCommandWithKeywords.h,v 1.1 2003/09/19 20:45:38 cdj Exp $
//
// Revision history
//
// $Log: CPCommandWithKeywords.h,v $
// Revision 1.1  2003/09/19 20:45:38  cdj
// first submission
//

// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations
namespace CommandPattern {
   namespace Keyword{
      class Base;
      class Composite;
   }
}

class CPCommandWithKeywords : public Command
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      CPCommandWithKeywords(const std::string& iName,
			    Module* iModule,
			    DABoolean iInternalCommand,
			    const std::string& iHelpString );

      virtual ~CPCommandWithKeywords();

      // ---------- member functions ---------------------------

      /** takes ownership of the keyword object
	   if a previous keyword has been registered with the same
	   name, the old keyword is deleted and the new one is added
	   */
      void add(CommandPattern::Keyword::Base* );

      virtual int execute( int argc, char* argv[] );

      virtual int helpHandler();

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      CPCommandWithKeywords( const CPCommandWithKeywords& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const CPCommandWithKeywords& operator=( const CPCommandWithKeywords& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      CommandPattern::Keyword::Composite* m_keywords;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "CommandPattern/Template/CPCommandWithKeywords.cc"
//#endif

#endif /* COMMANDPATTERN_CPCOMMANDWITHKEYWORDS_H */
