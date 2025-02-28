#if !defined(INTERPRETER_INTERPRETER_H)
#define INTERPRETER_INTERPRETER_H
// -*- C++ -*-
//
// Package:     <Interpreter>
// Module:      Interpreter
// 
// Description: Interpreter, an abstract class, shields the Suez Framework 
//              from the concrete interpreter, e.g. Tcl or Python.
//              Implemented as singleton.
//              (Design based on BaBar/CDF Framework, Liz Sexton-Kennedy)
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Mar  5 18:03:39 GMT 1998
// $Id: Interpreter.h,v 1.10 2003/09/05 18:13:49 cdj Exp $
//
// Revision history (at end of file)
//

// system include files

// user include files

// forward declarations
class Command;
class Module;
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"

class Interpreter
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      enum StatusCode { OK = 0, ERROR = 1, CONTINUE = 2 };
      
      // ---------- Constructors and destructor ----------------
      virtual ~Interpreter();

      // ---------- member functions ---------------------------
      virtual void initialize( DABoolean gui=false,
			       int argc=0, char* argv[]=0 ) = 0;
      virtual void loop() = 0;
      virtual void createCommand( const Command* command ) = 0;

      virtual void deleteCommand( const char* commandName ) = 0;
      virtual int  runCommandFile( const char* filename ) = 0;                
      virtual int  runCommand( char* command ) = 0;
      virtual int  runCommand( int argc, char* argv[] ) = 0;
      virtual void setResult( const char* result ) = 0;

      // history stuff
      virtual void readHistory() = 0;
      virtual void saveHistory() = 0;
      virtual void setHistoryLength( Count iLength ) = 0;
      virtual void setHistoryFile( const string& iFile ) = 0;
      virtual void printHistoryInfo() const = 0;
      virtual void printHistory() const = 0;

      void setCommandPrompt( const char* const thePrompt );

      void pushActiveModule( Module* );
      void popActiveModule();
       const Module* activeModule() const;
       unsigned int activeModuleStackSize() const;
      // ---------- const member functions ---------------------
      virtual StatusCode parseArgs( const string formalCmd, 
				    int argc, 
				    char *argv[] ) const = 0;

      const char* commandPrompt( ) const;

      // ---------- static member functions --------------------
      static DABoolean isInitialized();
      static void setInterpreter( Interpreter* );
      static Interpreter* interpreter();

   protected:
      // ---------- protected member functions -----------------
      Interpreter();
      Module* activeModule();
      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      Interpreter( const Interpreter& );

      // ---------- assignment operator(s) ---------------------
      const Interpreter& operator=( const Interpreter& );

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      char* m_commandPrompt;
      STL_VECTOR(Module*) m_activeModuleStack;

      // ---------- static data members ------------------------
      static Interpreter* m_interpreter;
};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "Interpreter/Template/Interpreter.cc"
//#endif

// ---------------------------------------------------------------
// Revision history
//
// $Log: Interpreter.h,v $
// Revision 1.10  2003/09/05 18:13:49  cdj
// made active module stack size accessible and const
//
// Revision 1.9  2002/01/03 19:58:27  cdj
// fixed bugs in Tcl command handling
//
// Revision 1.8  1999/09/14 18:38:57  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
// Revision 1.7  1999/09/10 01:04:55  mkl
// 1) new smarter history command.
// 2) new "uppercase" function, since our compilers don't support it yet.
// 3) moved "Conversion" class to CommandPattern (needed by HistoryCommand).
//
// Revision 1.6  1998/09/08 19:12:31  mkl
// removed superfluous const qualifier
//
// Revision 1.5  1998/05/07 21:42:37  mkl
// clean up of code changes for history mechism
//
// Revision 1.4  1998/05/07 15:37:23  mkl
// additional virtual functions to allow abstraction of executing commands
//
// Revision 1.3  1998/04/01 18:07:59  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.2  1998/03/23 23:33:15  mkl
// added runCommand method
//
// Revision 1.1  1998/03/11 19:11:51  mkl
// base class for all interpreters

#endif /* INTERPRETER_INTERPRETER_H */

