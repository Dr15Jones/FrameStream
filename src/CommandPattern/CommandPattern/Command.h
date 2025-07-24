#if !defined(COMMANDPATTERN_COMMAND_H)
#define COMMANDPATTERN_COMMAND_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      Command
// 
// Description: The abstract parent of all command classes. 
//
//      Based loosely on the Command Pattern (Design Patterns, p.233)
//
//      Each descendant class executes a single command, either for the 
//      CLI or GUI framework itself, or for one of its modules. 
//      A command has a target upon which it acts, and can be enabled 
//      or disabled.
//
//      Please note: there are two types of commands, internal and external
//                   with respect to the module there are defined for.
//                   By default (ctor default arg) commands are internal,
//                   unless specified otherwise: 
//                      MyCommand( <name>, <target>, false);
//                   Please see the Module.h header for more details.
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Mar 18 15:46:02 EST 1997
// $Id: Command.h,v 1.14 2003/09/21 02:00:37 cdj Exp $
//
// Revision history
//
// $Log: Command.h,v $
// Revision 1.14  2003/09/21 02:00:37  cdj
// made Command::setResult() public (needed for Keyword::NoArgReturnResult)
//
// Revision 1.13  2002/01/03 19:58:27  cdj
// fixed bugs in Tcl command handling
//
// Revision 1.12  2000/12/01 20:03:29  cdj
// now includes map
//
// Revision 1.11  2000/08/03 22:05:25  mkl
// parameters now have optional call-back mechanism
//
// Revision 1.10  1999/09/14 18:38:56  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
// Revision 1.9  1999/09/10 01:04:53  mkl
// 1) new smarter history command.
// 2) new "uppercase" function, since our compilers don't support it yet.
// 3) moved "Conversion" class to CommandPattern (needed by HistoryCommand).
//
// Revision 1.8  1999/09/06 21:28:53  mkl
// new subcommand handling
//
// Revision 1.7  1999/02/22 23:40:47  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.6  1998/11/09 19:31:23  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.5  1998/04/01 18:07:58  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.4  1998/03/14 01:52:11  mkl
// added setHelpString() and helpString() functions
//
// Revision 1.3  1998/03/11 19:10:37  mkl
// new Parameter sources
//
// Revision 1.2  1997/10/27 19:25:51  mkl
// EchoCommand to echo messages
//
// Revision 1.1.1.1  1997/09/03 02:39:58  mkl
// imported CommandPattern sources
//

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
// user include files
#include "CommandPattern/SubcommandBase.h"
#include "CommandPattern/Subcommand.h"

// STL include
#if defined(OLD_CXX_STRING_CLASS_BUG)
#include <string>
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */

// forward declarations
class Module;
#include <map>
#if !defined(command_subcommandmap)
#define command_subcommandmap std::map< std::string, SubcommandBase* >
#endif

class Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      enum CommandResult { COMMAND_OK = 0, COMMAND_ERROR = 1,
                           COMMAND_EXIT = 1000};              
      typedef CommandResult Result;
      typedef std::string Name;

      // Constructors and destructor
      Command( const Name& iName="command", 
	       Module* iTarget=0,
	       DABoolean iInternalCommand=true );
      virtual ~Command();

      // member functions

      virtual int execute( int argc, char* argv[] );
      virtual int helpHandler() = 0;
      // derived *Commands may override: without subcommand -- the default
      virtual int defaultHandler(); 
      // derived *Commands may override: with args -- the default
      virtual int defaultWithArgsHandler( int argc, char* argv[] ); 

      virtual void disable();
      virtual void enable ();
 
      void addSubcommand( SubcommandBase* iSubcommand );

      //virtual 
      Module* target();

      void setHelpString( const std::string& helpText );

      // const member functions
      const Name& name() const;
      void setResult( const std::string& iResult ) const;

      //virtual 
      const Module* target() const;

      const std::string& helpString() const;

      // static member functions

   protected:
      // protected member functions
      void setArgs( int argc, char* argv[] );
      
      // protected const member functions
      const char* getArgument ( int  index ) const;


      // protected data
      int    m_argc;
      char** m_argv;

   private:
      // Constructors and destructor
      Command();                                 // stop default
      Command( const Command& );                 // stop default

      // assignment operator(s)
      const Command& operator=( const Command& );// stop default

      // private member functions

      // private const member functions

      // data members
      Name m_name;
      Module* m_target;
      DABoolean m_isEnabled;

      std::string m_helpString;

      // subcommand handling
      command_subcommandmap& m_subcommandMap;

      // static data members

};

// inline function definitions
inline
void 
Command::setHelpString( const std::string& helpText )
{
   m_helpString = helpText;
}

inline
const std::string& 
Command::helpString() const
{
   return m_helpString;
}

#endif /* COMMANDPATTERN_COMMAND_H */
