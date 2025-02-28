#if !defined(JOBCONTROL_STREAMCOMMAND_H)
#define JOBCONTROL_STREAMCOMMAND_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      StreamCommand
// 
// Description: Command executer for the "Stream" command.
//
//              See StreamCommand.cc for a detailed description.
//
// Environment:
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Wed Aug 6 14:05:19 EST 1997
// $Id: StreamCommand.h,v 1.3 1997/09/03 02:39:12 mkl Exp $
//
// Revision history
//
// $Log: StreamCommand.h,v $
// Revision 1.3  1997/09/03 02:39:12  mkl
// restructuring suez libraries
//
// Revision 1.2  1997/08/13 07:11:14  mkl
// Chains of Sources, new activation of streams, and ProxyDict
//
// Revision 1.1  1997/08/08 05:21:33  mkl
// first attempt at chains-of-files
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"


// forward declarations

class StreamCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      StreamCommand( const Name& name, Module* target );
      virtual ~StreamCommand();

      // member functions
      virtual int execute( int argc, char* argv[] );  // executer

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual int helpHandler         ();
      virtual int activateHandler     ();
      virtual int listHandler         ();
      virtual int bindHandler         ();
      virtual int useHandler          (); // undocumented feature; 
                                          // for testing only

      // protected const member functions

   private:
      // Constructors and destructor
      StreamCommand( const StreamCommand& );

      // assignment operator(s)
      const StreamCommand& operator=( const StreamCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* JOBCONTROL_STREAMCOMMAND_H */
