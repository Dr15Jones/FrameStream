#if !defined(COMMANDPATTERN_MODULECOMMAND_H)
#define COMMANDPATTERN_MODULECOMMAND_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      ModuleCommand
// 
// Description: Command to interface with Modules
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Fri Oct 23 12:37:10 EST 1998
// $Id: ModuleCommand.h,v 1.3 1998/11/10 03:53:35 mkl Exp $
//
// Revision history
//
// $Log: ModuleCommand.h,v $
// Revision 1.3  1998/11/10 03:53:35  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.2  1998/11/09 21:24:46  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.1  1998/11/09 19:31:40  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
//


// system include files

// user include files
#include "CommandPattern/LoaderCommand.h"
#include "CommandPattern/LoaderModule.h"

// forward declarations

class ModuleCommand : public LoaderCommand< LoaderModule >
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      ModuleCommand( const Name& name, LoaderModule* target );
      virtual ~ModuleCommand();

      // member functions

      //virtual 
      LoaderModule* target();

      // const member functions
      //virtual 
      const LoaderModule* target() const;

      // static member functions

   protected:
      // protected member functions
      virtual int listSelectedHandler();

      // protected const member functions

   private:
      // Constructors and destructor
      ModuleCommand( const ModuleCommand& );

      // assignment operator(s)
      const ModuleCommand& operator=( const ModuleCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* COMMANDPATTERN_MODULECOMMAND_H */
