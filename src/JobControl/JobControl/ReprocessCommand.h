#if !defined(JOBCONTROL_REPROCESSCOMMAND_H)
#define JOBCONTROL_REPROCESSCOMMAND_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      ReprocessCommand
// 
// Description: reprocesses current stop
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon May 5 15:47:34 EST 1997
// $Id: ReprocessCommand.h,v 1.4 1997/09/03 02:39:07 mkl Exp $
//
// Revision history
//
// $Log: ReprocessCommand.h,v $
// Revision 1.4  1997/09/03 02:39:07  mkl
// restructuring suez libraries
//
// Revision 1.3  1997/07/11 06:55:55  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.2  1997/06/06 06:18:33  mkl
// handle --> execute and other minor stuff
//
// Revision 1.1  1997/05/06 18:36:09  mkl
// added GotoCommand and ReprocessCommand
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"


// forward declarations
class Module;


class ReprocessCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      ReprocessCommand( const Name& name, Module* iTarget );
      virtual ~ReprocessCommand();

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
      ReprocessCommand( const ReprocessCommand& );

      // assignment operator(s)
      const ReprocessCommand& operator=( const ReprocessCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* JOBCONTROL_REPROCESSCOMMAND_H */
