#if !defined(COMMANDPATTERN_COMPOSITEMODULE_H)
#define COMMANDPATTERN_COMPOSITEMODULE_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      CompositeModule
// 
// Description: CompositeModule is a module that may contain other modules;
//              based on the CompositePattern
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Fri Oct 23 15:47:12 EST 1998
// $Id: CompositeModule.h,v 1.5 1999/02/22 23:40:48 mkl Exp $
//
// Revision history (at end of file)
//

// system include files

// user include files
#include "CommandPattern/Module.h"

// forward declarations
class ModuleCommand;
#include "STLUtility/fwd_vector.h"
#if !defined(_compmodule_container_)
#define _compmodule_container_ STL_VECTOR( CompositeModule::ModuleInfo ) 
#endif
#include "C++Std/fwd_ostream.h"


class CompositeModule : public Module
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      struct ModuleInfo {
            ModuleInfo() {}
            ModuleInfo( Module* iModule, 
			DABoolean iOwnMemory = true )
               : m_module( iModule ), 
                 m_ownMemory( iOwnMemory ) {}
            Module* m_module;
            DABoolean m_ownMemory;
      };

      // Constructors and destructor
      CompositeModule( const Module::Name& iName, 
		       const Module::Name& iDescription );
      virtual ~CompositeModule( void );

      // member functions

      // interface conforming to CompositePattern
      virtual void addModule( Module* module, DABoolean iOwnMemory=true );
      virtual DABoolean removeModule( const Module::Name& name );
      virtual DABoolean clearModules();
      virtual Module* fetchModule( const Module::Name& name );

      // const member functions

      // interface conforming to CompositePattern
      virtual string listModules() const;
      virtual DABoolean containsModule( const Module::Name& name ) const;
      virtual const Module* fetchModule( const Module::Name& name ) const;
      const _compmodule_container_& modules( void ) const;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

      // static data members

   private:
      // Constructors and destructor
      CompositeModule( const CompositeModule& );

      // assignment operator(s)
      const CompositeModule& operator=( const CompositeModule& );

      // ---------- data members ---------------
      
      // modules mape
      _compmodule_container_& m_modules;

      // static data members

};

// inline function definitions

// Revision history
//
// $Log: CompositeModule.h,v $
// Revision 1.5  1999/02/22 23:40:48  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.4  1998/11/12 22:23:25  mkl
// finish new module loading and unloading
//
// Revision 1.3  1998/11/12 02:23:49  mkl
// minor cleanup
//
// Revision 1.2  1998/11/09 21:24:40  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.1  1998/11/09 19:31:25  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//

#endif /* COMMANDPATTERN_COMPOSITEMODULE */
