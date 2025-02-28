#if !defined(COMMANDPATTERN_RUNCOMMANDFILECOMMAND_H)
#define COMMANDPATTERN_RUNCOMMANDFILECOMMAND_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      RunCommandFileCommand
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon Sep 13 15:47:34 EST 1999
// $Id: RunCommandFileCommand.h,v 1.1 1999/09/14 18:39:00 mkl Exp $
//
// Revision RunCommandFile
//
// $Log: RunCommandFileCommand.h,v $
// Revision 1.1  1999/09/14 18:39:00  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"


// forward declarations
class Module;


class RunCommandFileCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      RunCommandFileCommand( const Name& name, Module* iTarget );
      virtual ~RunCommandFileCommand( );

      // member functions

      // Handler
      //virtual int execute( int argc, char* argv[] );
      virtual int helpHandler();
      virtual int defaultWithArgsHandler( int iArgc, char* iArgv[] ); 

      //virtual int printInfoHandler();

      // const member functions

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      // stop default
      RunCommandFileCommand();
      // stop default
      RunCommandFileCommand( const RunCommandFileCommand& );

      // assignment operator(s)
      // stop default
      const RunCommandFileCommand& operator=( const RunCommandFileCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* COMMANDPATTERN_RUNCOMMANDFILECOMMAND_H */
