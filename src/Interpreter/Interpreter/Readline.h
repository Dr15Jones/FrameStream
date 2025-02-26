#if !defined(INTERPRETER_READLINE_H)
#define INTERPRETER_READLINE_H
// -*- C++ -*-
//
// Package:     <Interpreter>
// Module:      Readline
// 
// Description: Namespace Wrapper around gnu readline
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Wed Mar 25 12:17:14 EST 1998
// $Id: Readline.h,v 1.7 1999/04/19 18:02:22 mkl Exp $
//
// Revision history
//
// $Log: Readline.h,v $
// Revision 1.7  1999/04/19 18:02:22  mkl
// added info on tcl via web pages
//
// Revision 1.6  1998/05/20 01:59:12  mkl
// fixed memory leak in history expansion
//
// Revision 1.5  1998/05/07 21:42:27  mkl
// clean up of code changes for history mechism
//
// Revision 1.4  1998/05/07 15:34:11  mkl
// implement history mechanism; implement proper tcl_source command
//
// Revision 1.3  1998/04/01 18:22:48  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.2  1998/03/28 17:43:52  mkl
// g++ wants set/string headers included for typedefs
//
// Revision 1.1  1998/03/26 20:01:15  mkl
// added gnu readline support
//

// system include files
#include <string>
#include <set>

// user include files
#include "Interpreter/readline.h"

// forward declarations
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_set.h"

class Readline
{
      // ---------- friend classes and functions ---------------
      friend class Dummy; // make g++ warnings go away 
                          // ("class has no ctor nor friends")

   public:

      // ---------- constants, enums and typedefs --------------
      typedef string CommandName;
      typedef STL_SET( CommandName ) Commands;

      // ---------- Constructors and destructor ----------------

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------
      static void  init();
      static char* readline( const char* iPrompt );
      static void  using_history();
      static void  read_history( const char* file );
      static void  write_history( const char* file );
      static void  history_truncate_file( const char* file, 
					  unsigned int nLines );
      static void  print_history_list();
      static void  addHistory( const char* iLine );
      static char* history_expand( const char* iLine );
      static void  registerCommand  ( const char* iCommand );
      static void  deregisterCommand( const char* iCommand );

      static void deleteLine( const char* iLine );

      static Commands& commands();

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      Readline();
      virtual ~Readline();

      Readline( const Readline& );

      // ---------- assignment operator(s) ---------------------
      const Readline& operator=( const Readline& );

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------
      static Commands s_commands;
};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "Interpreter/Template/Readline.cc"
//#endif

#endif /* INTERPRETER_READLINE_H */
