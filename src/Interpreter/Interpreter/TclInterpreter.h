#if !defined(INTERPRETER_TCLINTERPRETER_H)
#define INTERPRETER_TCLINTERPRETER_H
// -*- C++ -*-
//
// Package:     <Interpreter>
// Module:      TclInterpreter
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
// Created:     Thu Mar  5 19:10:43 GMT 1998
// $Id: TclInterpreter.h,v 1.17 2004/02/26 02:22:23 cdj Exp $
//
// Revision history
//
// $Log: TclInterpreter.h,v $
// Revision 1.17  2004/02/26 02:22:23  cdj
// changed sourceCommand to sourceCommandHandler to avoid name confusion when using Tcl 8.4
//
// Revision 1.16  2004/02/18 20:25:13  cdj
// can once again use exit in a run_file command
//
// Revision 1.15  2004/02/16 15:10:25  cdj
// added code to trap exit Tcl return code before it gets to the 'top' application layer (needed for Tcl8.4)
//
// Revision 1.14  2003/03/31 21:15:46  cdj
// made files names more unique to avoid problems on OS X (Darwin)
//
// Revision 1.13  2002/02/19 19:02:33  cdj
// Made the run_file command do immediate execution and added more state info on command prompt
//
// Revision 1.12  1999/10/05 20:23:16  mkl
// kludge run_file to work properly in nested calls
//
// Revision 1.11  1999/09/14 18:35:31  mkl
// new run_file command wants to replace tcl_source
//
// Revision 1.10  1999/09/10 01:24:47  mkl
// new history command
//
// Revision 1.9  1998/09/08 19:18:44  mkl
// removed superfluous const qualifiers
//
// Revision 1.8  1998/05/11 19:33:16  mkl
// make history-file mechanism more fool-proof
//
// Revision 1.7  1998/05/07 21:42:28  mkl
// clean up of code changes for history mechism
//
// Revision 1.6  1998/05/07 15:34:13  mkl
// implement history mechanism; implement proper tcl_source command
//
// Revision 1.5  1998/04/01 19:20:09  mkl
// minor typo fix
//
// Revision 1.4  1998/04/01 18:22:49  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.3  1998/03/26 20:01:16  mkl
// added gnu readline support
//
// Revision 1.2  1998/03/23 23:29:44  mkl
// added gnu readline support to TclInterpreter; added runCommand method
//
// Revision 1.1.1.1  1998/03/11 18:52:18  mkl
// imported Interpreter sources
//

// system include files
#include "Interpreter/Tcl_c++_wrapper.h"             

// user include files
#include "CommandPattern/Interpreter.h"

// forward declarations
#include <string>
#include <vector>


class TclInterpreter : public Interpreter
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef std::string CommandName;

      // ---------- Constructors and destructor ----------------
      TclInterpreter();
      virtual ~TclInterpreter();

      // ---------- member functions ---------------------------
      virtual void initialize( DABoolean gui=false, 
			       int argc=0, char* argv[]=0 );
      virtual void loop();

      virtual void createCommand( const Command* command );

      virtual void deleteCommand( const char* commandName );
      virtual int  runCommandFile( const char* filename );
      virtual int  runCommand( char* command );
      virtual int  runCommand( int argc, char* argv[] );
      virtual void setResult( const char* result );

      // history stuff
      virtual void readHistory();
      virtual void saveHistory();
      virtual void setHistoryLength( Count iLength );
      virtual void setHistoryFile( const std::string& iFile );
      virtual void printHistoryInfo() const;
      virtual void printHistory() const; 
      
      Tcl_Interp* tclInterpreter();

      // ---------- const member functions ---------------------
      virtual StatusCode parseArgs( const std::string formalCmd, 
				    int argc, 
				    char *argv[] ) const ;

      const Tcl_Interp* tclInterpreter() const;

      // ---------- static member functions --------------------
      static int commandHandler( ClientData clientData, 
				 Tcl_Interp* tcl_interp,
                                 int argc, char* argv[] );

      static int sourceCommandHandler( ClientData clientData, 
				       Tcl_Interp* interp,
				       int argc, char* argv[] );
      int sourceCommand( const char* iFileName);

      int catchExit();
   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      TclInterpreter( const TclInterpreter& );

      // ---------- assignment operator(s) ---------------------
      const TclInterpreter& operator=( const TclInterpreter& );

      // ---------- private member functions -------------------
      void assembleHistoryFile();

      int processCommandLine(const char* iCommandLine, Tcl_DString& ioCommands); 
      DABoolean incompleteCommand(Tcl_DString& iCommands) const;
      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      Tcl_Interp* m_tclInterpreter;                  

      std::vector< CommandName >& m_tclCommandNames;

      std::string m_historyFile;
      Count m_historyLength;
      unsigned int m_sizeOfStackForExit;

      // used for trapping the exit condition
      Tcl_DString* m_requestedCommands;
      DABoolean m_exitRequested;
      unsigned int m_sizeOfStackForCatchExit;
      // ---------- static data members ------------------------

      static const char* const s_sourceCommandString;
      static const char* const s_fileCommandString;
      static const char* const s_procCommandString;
};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "CommandPattern/Template/TclInterpreter.cc"
//#endif

#endif /* INTERPRETER_TCLINTERPRETER_H */
