#if !defined(COMMANDPATTERN_HISTORYCOMMAND_H)
#define COMMANDPATTERN_HISTORYCOMMAND_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      HistoryCommand
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Sep 9 15:47:34 EST 1999
// $Id: HistoryCommand.h,v 1.1 1999/09/10 01:04:55 mkl Exp $
//
// Revision history
//
// $Log: HistoryCommand.h,v $
// Revision 1.1  1999/09/10 01:04:55  mkl
// 1) new smarter history command.
// 2) new "uppercase" function, since our compilers don't support it yet.
// 3) moved "Conversion" class to CommandPattern (needed by HistoryCommand).
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"


// forward declarations
class Module;


class HistoryCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      HistoryCommand( const Name& name, Module* iTarget );
      virtual ~HistoryCommand( );

      // member functions

      // Handler
      //virtual int execute( int argc, char* argv[] );
      virtual int helpHandler();
      virtual int defaultHandler(); // without subcommand: what to do 

      virtual int setHistoryLengthHandler();
      virtual int setHistoryFileHandler();
      virtual int saveHistoryHandler();
      virtual int readHistoryHandler();
      virtual int printHistoryInfoHandler();

      // const member functions

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      HistoryCommand();                                     // stop default
      HistoryCommand( const HistoryCommand& );                 // stop default

      // assignment operator(s)
      const HistoryCommand& operator=( const HistoryCommand& );// stop default

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* COMMANDPATTERN_HISTORYCOMMAND_H */
