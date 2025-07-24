#if !defined(COMMANDPATTERN_LOADERMODULE_H)
#define COMMANDPATTERN_LOADERMODULE_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      LoaderModule
// 
// Description: LoaderModule is a module for loading up other modules
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Fri Oct 23 15:47:12 EST 1998
// $Id: LoaderModule.h,v 1.7 1999/10/08 21:45:18 mkl Exp $
//
// Revision history (at end of file)
//

// system include files

// user include files
#include "CommandPattern/CompositeModule.h"
#include "CommandPattern/Loader.h"

// forward declarations
class ModuleCommand;

class LoaderModule : public CompositeModule, public Loader< Module >
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      LoaderModule( const Module::Name& iName, 
		    const Module::Name& iDescription,
		    const std::string& environment = "C3_SHLIB" );
      virtual ~LoaderModule( void );

      // member functions
      virtual Module* fetch( const std::string& iName );

      virtual DABoolean clearModules();

      // const member functions
      virtual const Module* fetch( const std::string& iName ) const;

      // pattern for listings
      virtual std::string listAvailablePatternString() const { 
	 //return std::string( "Mod*" ); 
	 return std::string( "" ); 
      }

      // static member functions

   protected:
      // protected member functions

      // give derived class a change to perform specific actions
      virtual void initialize( const std::string& iName, Module& );
      virtual void finalize  ( const std::string& iName, Module& );

      // protected const member functions

      // error/warning messages
      virtual std::string makeErrorMesg( const std::string& iName ) const;

      // static data members

   private:
      // Constructors and destructor
      LoaderModule( const LoaderModule& );

      // assignment operator(s)
      const LoaderModule& operator=( const LoaderModule& );

      // ---------- data members ---------------
      ModuleCommand& m_moduleCommand;

      // static data members

};

// inline function definitions

// Revision history
//
// $Log: LoaderModule.h,v $
// Revision 1.7  1999/10/08 21:45:18  mkl
// put in hooks for pattern searching in loading (if we ever decide to use it)
//
// Revision 1.6  1999/09/14 18:38:58  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
// Revision 1.5  1999/06/07 19:07:27  mkl
// unload static modules AFTER dynamic modules
//
// Revision 1.4  1998/11/12 02:23:51  mkl
// minor cleanup
//
// Revision 1.3  1998/11/10 03:53:34  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.2  1998/11/09 21:24:43  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.1  1998/11/09 19:31:36  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//

#endif /* COMMANDPATTERN_LOADERMODULE */
