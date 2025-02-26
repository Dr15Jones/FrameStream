#if !defined(PROCESSOR_ACTIONCOMMAND_H)
#define PROCESSOR_ACTIONCOMMAND_H
// -*- C++ -*-
//
// Package:     Processor
// Module:      ActionCommand
// 
// Description: Command to deal with Actions (disable/enable etc.)
//              See ActionCommand.cc for description of available 
//              subcommands.
//
// Environment:
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon Mar 15 13:05:19 EST 1999
// $Id: ActionCommand.h,v 1.1 1999/03/15 18:44:28 mkl Exp $
//
// Revision history
//
// $Log: ActionCommand.h,v $
// Revision 1.1  1999/03/15 18:44:28  mkl
// ActionCommand allows to list and en/disable actions at runtime
//
//
// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations
class Processor;

class ActionCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      ActionCommand( const Name& name, Processor* target );
      virtual ~ActionCommand();

      // member functions
      virtual int execute( int argc, char* argv[] );  // executer

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual int helpHandler        ();
      virtual int listHandler        ();
      virtual int switchOnOffHandler ( DABoolean iOnOff );

      Processor* target();

      // protected const member functions
      const Processor* target() const;

   private:
      // Constructors and destructor
      ActionCommand( const ActionCommand& );

      // assignment operator(s)
      const ActionCommand& operator=( const ActionCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* PROCESSOR_ACTIONCOMMAND_H */
