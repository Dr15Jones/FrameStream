#if !defined(JOBCONTROL_SKIPCOMMAND_H)
#define JOBCONTROL_SKIPCOMMAND_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      SkipCommand
// 
// Description: skip specified number of events
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Jul 13 15:47:34 EST 1998
// $Id: SkipCommand.h,v 1.1 1998/07/13 22:22:09 mkl Exp $
//
// Revision history
//
// $Log: SkipCommand.h,v $
// Revision 1.1  1998/07/13 22:22:09  mkl
// added skip command
//
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"


// forward declarations
class Module;


class SkipCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      SkipCommand( const Name& name, Module* iTarget );
      virtual ~SkipCommand( );

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
      SkipCommand( const SkipCommand& );

      // assignment operator(s)
      const SkipCommand& operator=( const SkipCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* JOBCONTROL_SKIPCOMMAND_H */
