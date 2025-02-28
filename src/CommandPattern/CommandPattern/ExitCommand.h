#if !defined(COMMANDPATTERN_EXITCOMMAND_H)
#define COMMANDPATTERN_EXITCOMMAND_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      ExitCommand
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Mar 18 15:47:34 EST 1997
// $Id: ExitCommand.h,v 1.2 1997/10/27 19:25:55 mkl Exp $
//
// Revision history
//
// $Log: ExitCommand.h,v $
// Revision 1.2  1997/10/27 19:25:55  mkl
// EchoCommand to echo messages
//
// Revision 1.1.1.1  1997/09/03 02:39:58  mkl
// imported CommandPattern sources
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"


// forward declarations
class Module;


class ExitCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      ExitCommand( const Name& name, Module* iTarget );
      virtual ~ExitCommand( );

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
      ExitCommand();                                     // stop default
      ExitCommand( const ExitCommand& );                 // stop default

      // assignment operator(s)
      const ExitCommand& operator=( const ExitCommand& );// stop default

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* COMMANDPATTERN_EXITCOMMAND_H */
