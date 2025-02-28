#if !defined(COMMANDPATTERN_MULTILOADERCOMMAND_H)
#define COMMANDPATTERN_MULTILOADERCOMMAND_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      MultiLoaderCommand
// 
// Description: Command to interface with MultiLoadable "Things" (MultiLoader)
//
// Usage:
//    <usage>
//
// Author:      Valentine Kouznetsov
// Created:     Tue Mar  4 09:43:21 EST 2003
// $Id: MultiLoaderCommand.h,v 1.1 2003/03/12 21:34:03 vk Exp $
//
// Revision history
//
// $Log: MultiLoaderCommand.h,v $
// Revision 1.1  2003/03/12 21:34:03  vk
// Redesign loader class into LoaderBase, Loader (single loader) and MultiLoader
//
//
//


// system include files

// user include files
#include "CommandPattern/LoaderCommand.h"

// forward declarations

template< class T >
class MultiLoaderCommand : public LoaderCommand<T>
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      MultiLoaderCommand( const Command::Name& name, 
		     T* target, 
		     DABoolean iInternalCommand=true );
      virtual ~MultiLoaderCommand();

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
      virtual int loadHandler();

      // protected const member functions

   private:
      // Constructors and destructor
      MultiLoaderCommand( const MultiLoaderCommand& );

      // assignment operator(s)
      const MultiLoaderCommand& operator=( const MultiLoaderCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

// Uncomment the following lines, if your class is templated
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "CommandPattern/Template/MultiLoaderCommand.cc"
#endif                                


#endif /* COMMANDPATTERN_MULTILOADERCOMMAND_H */
