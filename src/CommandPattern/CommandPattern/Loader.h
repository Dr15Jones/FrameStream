#if !defined(COMMANDPATTERN_LOADER_H)
#define COMMANDPATTERN_LOADER_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      Loader
// 
// Description: Loader based on LoaderBase class and provide the same
//              functionality.
//              All T items must have a static string T::factorySymbol() 
//              function.
//
// Usage:

// Author:      Martin  Lohner
// Created:     Mon Oct 26 15:48:09 EST 1998
// $Id: Loader.h,v 1.11 2003/03/12 21:34:01 vk Exp $
//
// Revision history (at end of file)
//

// system include files
#include <utility>

// user include files
#include "CommandPattern/LoaderBase.h"
#include "DynamicLoader/DLFactoryManager.h"

// forward declarations

template< class T >
class Loader : public LoaderBase<T>
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      Loader( const string& environment );

      // member functions
      virtual DABoolean load( const string& iName );
      virtual pair<string,string> disassembleName(const string& iName) const;

      // static factory

      // static member functions

   protected:
      // protected member functions

      // warning/error messages
      virtual string makeErrorMesg( const string& iName ) const;

      // protected const member functions

   private:
      // Constructors and destructor
      Loader( const Loader&); // stop default
      const Loader& operator=(const Loader&); // stop default
      
      // assignment operator(s)

      // private member functions

      // private const member functions

      // data members

};

// inline function definitions

// Uncomment the following lines, if your class is templated
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "CommandPattern/Template/Loader.cc"
#endif                                


// ---------------------------------------------------------------
// Revision history
//
// $Log: Loader.h,v $
// Revision 1.11  2003/03/12 21:34:01  vk
// Redesign loader class into LoaderBase, Loader (single loader) and MultiLoader
//
// Revision 1.10  2000/12/01 20:23:22  cdj
// now uses DynamicLoader package
//
// Revision 1.9  1999/10/08 21:45:18  mkl
// put in hooks for pattern searching in loading (if we ever decide to use it)
//
// Revision 1.8  1999/09/14 22:33:14  mkl
// fix 'proc reorder' command to not unload processors first
//
// Revision 1.7  1999/09/14 18:38:58  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
// Revision 1.6  1999/02/22 23:40:48  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.5  1998/11/12 02:23:50  mkl
// minor cleanup
//
// Revision 1.4  1998/11/10 23:21:58  mkl
// static linking of proc/ducers/source-/sink-formats/modules whatever; and cleanup
//
// Revision 1.3  1998/11/10 03:53:03  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.2  1998/11/09 21:24:42  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.1  1998/11/09 19:31:32  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
//

#endif /* COMMANDPATTERN_LOADER_H */
