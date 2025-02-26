#if !defined(JOBCONTROL_GOTOCOMMAND_H)
#define JOBCONTROL_GOTOCOMMAND_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      GotoCommand
// 
// Description: Goto Command 
//              "Goto [<runnumber>] <eventnumber>" will proceed to
//              given run and event number without processing stops 
//              in between.
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Sat May 3 15:47:34 EST 1997
// $Id: GotoCommand.h,v 1.4 1997/09/03 02:38:59 mkl Exp $
//
// Revision history
//
// $Log: GotoCommand.h,v $
// Revision 1.4  1997/09/03 02:38:59  mkl
// restructuring suez libraries
//
// Revision 1.3  1997/07/11 06:55:48  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.2  1997/06/06 06:18:25  mkl
// handle --> execute and other minor stuff
//
// Revision 1.1  1997/05/06 18:36:06  mkl
// added GotoCommand and ReprocessCommand
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"


// forward declarations
class Module;


class GotoCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      GotoCommand( const Name& iCommand, Module* iTarget );
      virtual ~GotoCommand();

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
      GotoCommand( const GotoCommand& );

      // assignment operator(s)
      const GotoCommand& operator=( const GotoCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* JOBCONTROL_GOTOCOMMAND_H */
