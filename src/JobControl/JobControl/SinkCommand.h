#if !defined(JOBCONTROL_SINKCOMMAND_H)
#define JOBCONTROL_SINKCOMMAND_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      SinkCommand
// 
// Description: Command executer for the "sink" command for
//              the SinkManager.
//
//              See SinkCommand.cc for a detailed description.
//
// Environment:
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Aug 19 16:35:19 EST 1997
// $Id: SinkCommand.h,v 1.3 2003/09/19 21:20:36 cdj Exp $
//
// Revision history
//
// $Log: SinkCommand.h,v $
// Revision 1.3  2003/09/19 21:20:36  cdj
// changes needed for Path implementation
//
// Revision 1.2  1997/09/03 02:39:08  mkl
// restructuring suez libraries
//
// Revision 1.1  1997/08/20 06:23:44  mkl
// symmetrized sinks with sources in terms of user interface
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"


// forward declarations

class SinkCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      SinkCommand( const Name& name, Module* target );
      virtual ~SinkCommand();

      // member functions
      virtual int execute( int argc, char* argv[] );  // executer

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual int helpHandler       ();
      virtual int listHandler       ();
      virtual int removeHandler     ();
      virtual int clearHandler      ();
      virtual int bindHandler       ();
      virtual int useHandler        (); // undocumented feature; for testing only

      // protected const member functions

   private:
      // Constructors and destructor
      SinkCommand( const SinkCommand& );

      // assignment operator(s)
      const SinkCommand& operator=( const SinkCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* JOBCONTROL_SINKCOMMAND_H */
