// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      LoaderModule
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin  Lohner
// Created:     Fri Oct 23 15:48:55 EST 1998
// $Id: LoaderModule.cc,v 1.10 2002/08/16 14:15:15 cleo3 Exp $
//
// Revision history (end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <iostream>
#include <assert.h>
#include <stdlib.h>

// user include files
#include "Experiment/report.h"
#include "CommandPattern/LoaderModule.h"
#include "CommandPattern/GloballyVisibleSymbols.h"
#include "CommandPattern/ModuleCommand.h"

// STL classes
#include <vector>
#include <map>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "CommandPattern.LoaderModule";

//
// static data member definitions
//

//
// constructors and destructor
//
//LoaderModule::LoaderModule()
//{
//}
LoaderModule::LoaderModule( const Module::Name& iName, 
			    const Module::Name& iDescription,
			    const std::string& iEnvironment )
   : CompositeModule( iName, iDescription ),
     Loader< Module >( iEnvironment ),
     m_moduleCommand( *new ModuleCommand( "module", this ) )
{
}

// LoaderModule::LoaderModule( const LoaderModule& )
// {
// }

LoaderModule::~LoaderModule()
{
   // need to unload here because of virtual finalize()
   clearModules();

   delete &m_moduleCommand;
}

//
// assignment operators
//
// const LoaderModule& LoaderModule::operator=( const LoaderModule& )
// {
// }

//
// member functions
//
DABoolean
LoaderModule::clearModules() 
{
   DABoolean returnValue = true;

   // clear out static modules AFTER dynamically-loaded modules
   Loader< Module >::unloadAll();      // dynamic
   CompositeModule::clearModules();    // static

   return returnValue;
}

// ------------- overridden Loader< T > method
void
LoaderModule::initialize( const std::string& iName, Module& iModule )
{
   // call globally visible symbol to make debugging easier
   modsel();
   
   // set name (important in case of shared Object module)
   iModule.setName( iName );

   // "register" with CompositeModule
   addModule( &iModule, false );
}

// ------------- overridden Loader< T > method
void
LoaderModule::finalize( const std::string& iName, Module& iModule )
{
   // "unregister" with CompositeModule
   removeModule( iName );
}

Module*
LoaderModule::fetch( const Module::Name& iName )
{
   Module* returnValue = 0;

   returnValue = CompositeModule::fetchModule( iName );
   if( 0 == returnValue ) {
      returnValue = Loader< Module >::fetch( iName );
   }

   return returnValue;
}

//
// const member functions
//
const Module*
LoaderModule::fetch( const Module::Name& iName ) const
{
   const Module* returnValue = 0;

   returnValue = CompositeModule::fetchModule( iName );
   if( 0 == returnValue ) {
      returnValue = Loader< Module >::fetch( iName );
   }

   return returnValue;
}

// ------------- overridden Loader< T > method
std::string
LoaderModule::makeErrorMesg( const std::string& iName ) const
{
   std::string returnValue = std::string( "Cannot make module; are you sure " )
      + iName + std::string( " is a Module?" );
   return returnValue;
}

//
// static member functions
//


// -------------------------------------------------------
// History:
//
// $Log: LoaderModule.cc,v $
// Revision 1.10  2002/08/16 14:15:15  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.9  1999/09/14 18:38:50  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
// Revision 1.8  1999/06/07 19:07:25  mkl
// unload static modules AFTER dynamic modules
//
// Revision 1.7  1999/02/22 23:40:41  mkl
// setResult( std::string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.6  1998/11/19 21:42:28  mkl
// reshuffled dtors to see if it helps Brian
//
// Revision 1.5  1998/11/12 22:23:05  mkl
// finish new module loading and unloading
//
// Revision 1.4  1998/11/12 02:23:45  mkl
// minor cleanup
//
// Revision 1.3  1998/11/10 03:52:47  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.2  1998/11/09 21:24:32  mkl
// loadable classes know their own factorySymbol std::string; improved user iface of ModuleCommand
//
// Revision 1.1  1998/11/09 19:31:02  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
//
