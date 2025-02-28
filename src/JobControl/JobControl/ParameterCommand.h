#if !defined(JOBCONTROL_PARAMETERCOMMAND_H)
#define JOBCONTROL_PARAMETERCOMMAND_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      ParameterCommand
// 
// Description: Command executer for the "Parameter" command.
//
//              See ParameterCommand.cc for a detailed description.
//
// Environment:
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon Mar 15 17:05:19 EST 1999
// $Id: ParameterCommand.h,v 1.2 1999/03/15 19:14:24 mkl Exp $
//
// Revision history
//
// $Log: ParameterCommand.h,v $
// Revision 1.2  1999/03/15 19:14:24  mkl
// InteractCommand
//
//
//


// system include files

// user include files
#include "JobControl/InteractCommand.h"

// forward declarations

class ParameterCommand : public InteractCommand
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      ParameterCommand( const Name& name, Module* target );
      virtual ~ParameterCommand();

      // member functions

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual int helpHandler();

      // protected const member functions

   private:
      // Constructors and destructor
      ParameterCommand( const ParameterCommand& );

      // assignment operator(s)
      const ParameterCommand& operator=( const ParameterCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* JOBCONTROL_PARAMETERCOMMAND_H */
