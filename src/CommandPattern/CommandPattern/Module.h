#if !defined(COMMANDPATTERN_MODULE_H)
#define COMMANDPATTERN_MODULE_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      Module
// 
// Description: base class for anything and everything that can be executed
//         eg. processors, job control itself etc.
//
//         Modules are the receivers of (one or more) commands
//
//         Please note: "binding" of commands to modules is done 
//                       ONLY within the Command ctor. 
//                       That's because there are two kinds of commands:
//                       1.) internal: available during "interaction" mode.
//                       2.) external: available to calling module to be
//                           able to control "slave" module.
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Mar 18 15:48:15 EST 1997
// $Id: Module.h,v 1.19 2002/08/16 14:15:19 cleo3 Exp $
//
// Revision history
//
// $Log: Module.h,v $
// Revision 1.19  2002/08/16 14:15:19  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.18  2002/01/03 20:17:02  cdj
// code clean up from last check in
//
// Revision 1.17  2002/01/03 19:58:28  cdj
// fixed bugs in Tcl command handling
//
// Revision 1.16  2000/12/01 20:03:29  cdj
// now includes map
//
// Revision 1.15  1999/09/14 18:38:59  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
// Revision 1.14  1999/09/10 01:04:56  mkl
// 1) new smarter history command.
// 2) new "uppercase" function, since our compilers don't support it yet.
// 3) moved "Conversion" class to CommandPattern (needed by HistoryCommand).
//
// Revision 1.13  1999/02/22 23:40:50  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.12  1998/12/16 17:40:28  mkl
// need to include iostream to make g++2.7.2 happy
//
// Revision 1.11  1998/11/12 22:23:27  mkl
// finish new module loading and unloading
//
// Revision 1.10  1998/11/12 02:23:52  mkl
// minor cleanup
//
// Revision 1.9  1998/11/09 21:24:45  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.8  1998/11/09 19:31:38  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.7  1998/03/28 20:16:21  mkl
// do implicit bind of Parameter/Command to Module
//
// Revision 1.6  1998/03/16 23:17:45  mkl
// use bind instead of commands().push_back()
//
// Revision 1.5  1998/03/12 15:37:37  mkl
// moved member variable m_commands to be created first
//
// Revision 1.4  1998/03/11 19:10:38  mkl
// new Parameter sources
//
// Revision 1.3  1998/02/03 21:28:02  mkl
// switch over to STLUtility library
//
// Revision 1.2  1997/10/02 22:35:22  mkl
// made method 'vector<Command*>& commands()' proctected to disallow tampering
//
// Revision 1.1.1.1  1997/09/03 02:39:58  mkl
// imported CommandPattern sources
//
//

// system include files
#include "C++Std/iostream.h"
#include <string>
#include <map>

// user include files
// commands tied into every module
#include "CommandPattern/ExitCommand.h"
#include "CommandPattern/QuitCommand.h"
#include "CommandPattern/HelpCommand.h"
#include "CommandPattern/EchoCommand.h"
#include "CommandPattern/HistoryCommand.h"
#include "CommandPattern/RunCommandFileCommand.h"

// STL include
#include <string>

// forward declarations
#include "STLUtility/fwd_map.h"
#if !defined(_module_containerOfCommands_)
#define _module_containerOfCommands_ STL_MAP( string, Command* )
#endif


class Module
{
      // friend classses and functions
      friend class Command; // wide interface for Command

   public:
      // constants, enums and typedefs
      typedef string Name;
      typedef _module_containerOfCommands_ Commands;

      // Constructors and destructor
      Module( const Name& iName, const Name& iDescription );
      virtual ~Module();

      // member functions
      virtual void interact();
      virtual void exit();
      virtual void quit();
      virtual void help();

      // these apply to the "internal" commands!
      void disableCommands( );
      void enableCommands ( );

      void setName  ( const Name& iName );

      // standard methods for dynamic selection (replacing ctor/dtor)
      virtual void init( void );
      virtual void terminate( void );

      // interface conforming to CompositePattern
      virtual void addModule( Module* module, DABoolean iOwnMemory = true );
      virtual DABoolean removeModule( const Module::Name& name );
      virtual DABoolean clearModules();

      // calls for proper sequence of events
      void setCallInit     ( DABoolean iValue );
      void setCallTerminate( DABoolean iValue );

      // access to commands
      // external
      _module_containerOfCommands_& commands();
      // internal
      _module_containerOfCommands_& internalCommands();

      // const member functions
      const Name& name() const;

      // methods to insure proper sequence of events
      DABoolean callInit() const;
      DABoolean callTerminate() const;

      virtual Module* fetchModule( const Module::Name& name );

      // const member functions

      // interface conforming to CompositePattern
      virtual string listModules() const;
      virtual DABoolean containsModule( const Module::Name& name ) const;
      virtual const Module* fetchModule( const Module::Name& name ) const;

      // static member functions
      static string factorySymbol();

   protected:
      // protected member functions

      // register commands (only available to "friend" Command!)
      // external
      void bindCommand( Command* iCommand );
      // internal
      void bindInternalCommand( Command* iCommand );
      void unbindInternalCommand( Command* iCommand );
      
      // protected const member functions

   private:
      // Constructors and destructor
      Module( const Module& );

      // assignment operator(s)
      const Module& operator=( const Module& );

      // private member functions

      // private const member functions

      // data members
      Name m_name;
      Name m_description;
      
      // for proper sequence of events
      DABoolean m_callInit;
      DABoolean m_callTerminate;

      // store for all commands tied into this module
      // external
      _module_containerOfCommands_& m_commands;
      // internal
      _module_containerOfCommands_& m_internalCommands;

      // commands tied into every module (internal)
      ExitCommand           m_exitCommand;
      QuitCommand           m_quitCommand;
      HelpCommand           m_helpCommand;
      EchoCommand           m_echoCommand;
      HistoryCommand        m_historyCommand;
      RunCommandFileCommand m_runCommandFileCommand;

      // static data members

};

// inline function definitions

#endif /* COMMANDPATTERN_MODULE_H */
