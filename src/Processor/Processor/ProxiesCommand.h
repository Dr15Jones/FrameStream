#if !defined(PROCESSOR_PROXIESCOMMAND_H)
#define PROCESSOR_PROXIESCOMMAND_H
// -*- C++ -*-
//
// Package:     Processor
// Module:      ProxiesCommand
// 
// Description: Command to deal with proxies
//              See ProxiesCommand.cc for description of available 
//              subcommands.
//
// Environment:
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Sun Nov 1 13:05:19 EST 1998
// $Id: ProxiesCommand.h,v 1.1 1998/11/06 21:02:41 mkl Exp $
//
// Revision history
//
// $Log: ProxiesCommand.h,v $
// Revision 1.1  1998/11/06 21:02:41  mkl
// add ProxiesCommand to Producers
//
//
// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations
class Producer;

class ProxiesCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      ProxiesCommand( const Name& name, Producer* target );
      virtual ~ProxiesCommand();

      // member functions
      virtual int execute( int argc, char* argv[] );  // executer

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual int helpHandler        ();
      virtual int listHandler        ();

      // protected const member functions

   private:
      // Constructors and destructor
      ProxiesCommand( const ProxiesCommand& );

      // assignment operator(s)
      const ProxiesCommand& operator=( const ProxiesCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* PROCESSOR_PROXIESCOMMAND_H */
