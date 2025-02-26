#if !defined(COMMANDPATTERN_QUITCOMMAND_H)
#define COMMANDPATTERN_QUITCOMMAND_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      QuitCommand
// 
// Description: quick way to exit!
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Mar 18 15:47:34 EST 1997
// $Id: QuitCommand.h,v 1.2 1997/10/27 19:25:58 mkl Exp $
//
// Revision history
//
// $Log: QuitCommand.h,v $
// Revision 1.2  1997/10/27 19:25:58  mkl
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


class QuitCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      QuitCommand( const Name& name, Module* iTarget );
      virtual ~QuitCommand( );

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
      QuitCommand();                                     // stop default
      QuitCommand( const QuitCommand& );                 // stop default

      // assignment operator(s)
      const QuitCommand& operator=( const QuitCommand& );// stop default

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* COMMANDPATTERN_QUITCOMMAND_H */
