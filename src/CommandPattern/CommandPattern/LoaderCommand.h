#if !defined(COMMANDPATTERN_LOADERCOMMAND_H)
#define COMMANDPATTERN_LOADERCOMMAND_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      LoaderCommand
// 
// Description: Command to interface with Loadable "Things"
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon Nov 9 12:37:10 EST 1998
// $Id: LoaderCommand.h,v 1.2 2003/03/12 21:34:02 vk Exp $
//
// Revision history
//
// $Log: LoaderCommand.h,v $
// Revision 1.2  2003/03/12 21:34:02  vk
// Redesign loader class into LoaderBase, Loader (single loader) and MultiLoader
//
// Revision 1.1  1998/11/10 03:53:34  mkl
// unify producer/processor/module/source_format/sink_format commands
//
//


// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations

template< class T >
class LoaderCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef typename Command::Name Name;

      // Constructors and destructor
      LoaderCommand( const Name& name, 
		     T* target, 
		     DABoolean iInternalCommand=true );
      virtual ~LoaderCommand();

      // member functions
      virtual int execute( int argc, char* argv[] ); // executer

      //virtual 
      T* target();

      // const member functions
      //virtual 
      const T* target() const;

      // static member functions

   protected:
      // protected member functions
      virtual int helpHandler();
      virtual int listHandler();
      virtual int listSelectedHandler();
      virtual int loadHandler();
      virtual int unloadHandler();
      virtual int clearHandler();
      virtual int interactHandler();

      // protected const member functions

   private:
      // Constructors and destructor
      LoaderCommand( const LoaderCommand& );

      // assignment operator(s)
      const LoaderCommand& operator=( const LoaderCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

// Uncomment the following lines, if your class is templated
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "CommandPattern/Template/LoaderCommand.cc"
#endif                                


#endif /* COMMANDPATTERN_LOADERCOMMAND_H */
