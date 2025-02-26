#if !defined(COMMANDPATTERN_ECHOCOMMAND_H)
#define COMMANDPATTERN_ECHOCOMMAND_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      EchoCommand
// 
// Description: Basic Command to echo Info Messages through the report function
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon Oct 27 12:19:41 EST 1997
// $Id: EchoCommand.h,v 1.1 1997/10/27 19:25:53 mkl Exp $
//
// Revision history
//
// $Log: EchoCommand.h,v $
// Revision 1.1  1997/10/27 19:25:53  mkl
// EchoCommand to echo messages
//

// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations
class Module;


class EchoCommand : public Command
{
      // friend classes and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      EchoCommand( const Name& name, Module* iTarget=0 );
      virtual ~EchoCommand();

      // member functions

      // Handler
      virtual int execute( int argc, char* argv[] );
      virtual int helpHandler();

      // const member functions

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      EchoCommand();                                     // stop default
      EchoCommand( const EchoCommand& );                 // stop default

      // assignment operator(s)
      const EchoCommand& operator=( const EchoCommand& );// stop default

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "CommandPattern/Template/EchoCommand.cc"
//#endif

#endif /* COMMANDPATTERN_ECHOCOMMAND_H */
