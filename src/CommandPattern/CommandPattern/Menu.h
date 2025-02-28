#if !defined(COMMANDPATTERN_MENU_H)
#define COMMANDPATTERN_MENU_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Menu
// 
// Description: Menu for categorizing Commands
//              (based on CDF/BaBar design)
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Wed Mar 11 12:29:55 EST 1998
// $Id: Menu.h,v 1.6 2003/09/05 18:14:06 cdj Exp $
//
// Revision history
//
// $Log: Menu.h,v $
// Revision 1.6  2003/09/05 18:14:06  cdj
// fixed problem when call a menu without an argument from the param command
//
// Revision 1.5  1999/02/04 23:06:02  mkl
// fixed up Menu and Parameter commands to work together
//
// Revision 1.4  1998/03/28 20:16:20  mkl
// do implicit bind of Parameter/Command to Module
//
// Revision 1.3  1998/03/28 18:12:42  mkl
// forward protected Module::bind
//
// Revision 1.2  1998/03/23 23:33:02  mkl
// first implementation of Menu
//
// Revision 1.1  1998/03/14 01:52:57  mkl
// added default value
//

// system include files
#include <string>

// user include files
#include "CommandPattern/Command.h"
#include "CommandPattern/Module.h"

// forward declarations


class Menu : public Command, public Module
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      Menu( const Command::Name& iName="Menu", Module* iTarget=0 );
      virtual ~Menu();

      // ---------- member functions ---------------------------
      virtual int execute( int argc, char* argv[] );

      //virtual void exit();

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual int helpHandler();
      virtual int menuHandler();
      virtual int menuInterHandler();
      virtual int listParmsHandler();

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      Menu( const Menu& );

      // ---------- assignment operator(s) ---------------------
      const Menu& operator=( const Menu& );

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      string m_parentPrompt;

      // ---------- static data members ------------------------

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "CommandPattern/Template/Menu.cc"
//#endif

#endif /* COMMANDPATTERN_MENU_H */
