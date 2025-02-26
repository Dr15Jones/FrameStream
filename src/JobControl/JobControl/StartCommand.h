#if !defined(JOBCONTROL_STARTCOMMAND_H)
#define JOBCONTROL_STARTCOMMAND_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      StartCommand
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Mar 18 15:47:34 EST 1997
// $Id: StartCommand.h,v 1.4 1997/09/03 02:39:11 mkl Exp $
//
// Revision history
//
// $Log: StartCommand.h,v $
// Revision 1.4  1997/09/03 02:39:11  mkl
// restructuring suez libraries
//
// Revision 1.3  1997/07/11 06:55:56  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.2  1997/06/06 06:18:36  mkl
// handle --> execute and other minor stuff
//
// Revision 1.1  1997/03/27 18:12:37  mkl
// had to rename GoCommand to StartCommand because of g++ compiler bug?
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"


// forward declarations
class Module;


class StartCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      StartCommand( const Name& name, Module* iTarget );
      virtual ~StartCommand( );

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
      StartCommand( const StartCommand& );

      // assignment operator(s)
      const StartCommand& operator=( const StartCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* JOBCONTROL_STARTCOMMAND_H */
