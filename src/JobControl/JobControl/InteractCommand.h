#if !defined(JOBCONTROL_INTERACTCOMMAND_H)
#define JOBCONTROL_INTERACTCOMMAND_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      InteractCommand
// 
// Description: Command executer for the "interact" command for
//              the InteractManager.
//
//              See InteractCommand.cc for a detailed description.
//
// Environment:
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Mar 19 17:05:19 EST 1998
// $Id: InteractCommand.h,v 1.1 1999/03/15 19:14:22 mkl Exp $
//
// Revision history
//
// $Log: InteractCommand.h,v $
// Revision 1.1  1999/03/15 19:14:22  mkl
// InteractCommand
//
// Revision 1.1  1998/03/28 20:16:07  mkl
// do implicit bind of Interact/Command to Module
//
//


// system include files

// user include files
#include "CommandPattern/Command.h"


// forward declarations

class InteractCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      InteractCommand( const Name& name, Module* target );
      virtual ~InteractCommand();

      // member functions
      virtual int execute( int argc, char* argv[] );  // executer

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual int helpHandler();
      virtual int moduleHandler();

      // protected const member functions

   private:
      // Constructors and destructor
      InteractCommand( const InteractCommand& );

      // assignment operator(s)
      const InteractCommand& operator=( const InteractCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* JOBCONTROL_INTERACTCOMMAND_H */
