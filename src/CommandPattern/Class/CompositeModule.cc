// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      CompositeModule
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin  Lohner
// Created:     Fri Oct 23 15:48:55 EST 1998
// $Id: CompositeModule.cc,v 1.9 2002/08/16 14:15:15 cleo3 Exp $
//
// Revision history (end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <iostream>
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/CompositeModule.h"
#include "CommandPattern/JobContext.h"
#include "CommandPattern/Command.h"

// STL classes
#include <vector>
#include <map>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "CommandPattern.CompositeModule";

typedef _compmodule_container_ Modules;

//
// static data member definitions
//

//
// constructors and destructor
//
//CompositeModule::CompositeModule()
//{
//}
CompositeModule::CompositeModule( const Module::Name& iName, 
				  const Module::Name& iDescription )
   : Module( iName, iDescription ),
     m_modules( *new Modules )
{
}

// CompositeModule::CompositeModule( const CompositeModule& )
// {
// }

CompositeModule::~CompositeModule()
{
   // ------- delete in reverse order ----------
   // delete modules
   clearModules();
   delete &m_modules;
}

//
// assignment operators
//
// const CompositeModule& CompositeModule::operator=( const CompositeModule& )
// {
// }

//
// member functions
//

void 
CompositeModule::addModule( Module* iModule, DABoolean iOwnMemory )
{ 
   // register modules
   m_modules.push_back( ModuleInfo( iModule, iOwnMemory ) );

   // register with JobContext
   JobContext::instance()->registerObject( iModule->name(), iModule );

   // and bind commands
   if( true == iModule->commands().empty() ) {
      report( WARNING, kFacilityString )
	 << "no command(s) for module " << iModule->name() << std::endl;
   }
   Module::Commands::const_iterator itEnd = iModule->commands().end();
   for( Module::Commands::const_iterator it = iModule->commands().begin();
	it != itEnd;
	++it )
   {
      Command* command = (*it).second;
      bindInternalCommand( command );
      command->enable(); // register with interpreter
   }
}

DABoolean 
CompositeModule::removeModule( const Module::Name& iName )
{  
   DABoolean returnValue = false;

   // unregister with JobContext
   JobContext::instance()->deregisterObject( iName );

   Modules::iterator modIt = m_modules.begin();
   for( ;
	modIt != m_modules.end();
        ++modIt )
   {
      ModuleInfo& info = *modIt;
      Module* module = info.m_module;
      if( module->name() == iName ) 
      {
	 break;
      }
   }

   if( m_modules.end() != modIt )
   {
      ModuleInfo& info    = *modIt;
      Module* module      = info.m_module;
      DABoolean ownMemory = info.m_ownMemory;

      // unregister commands
      Module::Commands::const_iterator comEnd = module->commands().end();
      for( Module::Commands::const_iterator comIt 
	      = module->commands().begin();
	   comIt != comEnd;
	   ++comIt )
      {
	 Command* command = (*comIt).second;
	 command->disable(); // unregister with interpreter
	 unbindInternalCommand( command );
      }

      if( true == ownMemory ) {
	 delete module;
      }
      m_modules.erase( modIt );

      returnValue = true; // found it: success!
   }

   return returnValue;
}

DABoolean 
CompositeModule::clearModules()
{  
   DABoolean returnValue = true;

   // erase in opposite order from addition (because of dependencies)
   Modules::reverse_iterator ritEnd = m_modules.rend();
   for( Modules::reverse_iterator rit = m_modules.rbegin();
	rit != ritEnd;
	++rit )
   {
      ModuleInfo& info = *rit;

      //// unregister with JobContext
      //JobContext::instance()->deregisterObject( info.m_module->name() );

      if( true == info.m_ownMemory ) {
	 report( DEBUG, kFacilityString )
	    << "explicitly deleting module " << info.m_module->name() << std::endl;
	 delete info.m_module;
      }
   }

   // now just get rid of all entries
   m_modules.erase( m_modules.begin(), m_modules.end() );

   return returnValue;
}

Module*
CompositeModule::fetchModule( const Module::Name& iName )
{
   Module* returnValue = 0;

   for( Modules::const_iterator modIter = m_modules.begin();
        modIter != m_modules.end();
        ++modIter )
   {
      const ModuleInfo& info = *modIter;
      if( info.m_module->name() == iName ) {
	 returnValue = info.m_module;
	 break;
      }
   }

   return returnValue;
}

//
// const member functions
//
const Module*
CompositeModule::fetchModule( const Module::Name& iName ) const
{
   const Module* returnValue = 0;

   for( Modules::const_iterator modIter = m_modules.begin();
        modIter != m_modules.end();
        ++modIter )
   {
      const ModuleInfo& info = *modIter;
      if( info.m_module->name() == iName ) {
	 returnValue = info.m_module;
	 break;
      }
   }

   return returnValue;
}

std::string
CompositeModule::listModules() const
{
  std::string resultString;

   resultString += name() 
      +std::string( " contains: ('static' means you cannot remove)\n" );
   for( Modules::const_iterator modIter = m_modules.begin();
        modIter != m_modules.end();
        ++modIter )
   {
      const ModuleInfo& info = *modIter;
      const char* const ownMemoryString = ( info.m_ownMemory ) ? "static" : "";
      resultString += info.m_module->name() +std::string( " " )
	 + ownMemoryString +std::string( "\n" );
   }

   return resultString;
}

DABoolean 
CompositeModule::containsModule( const Module::Name& iName ) const
{
   DABoolean returnValue = false;

   for( Modules::const_iterator modIter = m_modules.begin();
        modIter != m_modules.end();
        ++modIter )
   {
      const ModuleInfo& info = *modIter;
      if( info.m_module->name() == iName ) {
	 returnValue = true;
	 break;
      }
   }

   return returnValue;
}

const Modules&
CompositeModule::modules() const
{
   return m_modules;
}

//
// static member functions
//


// -------------------------------------------------------
// History:
//
// $Log: CompositeModule.cc,v $
// Revision 1.9  2002/08/16 14:15:15  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.8  1999/12/15 20:28:10  mkl
// delete processors/producers before histogram module
//
// Revision 1.7  1999/06/07 19:07:24  mkl
// unload static modules AFTER dynamic modules
//
// Revision 1.6  1999/02/22 23:40:38  mkl
// setResult(std::string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.5  1999/01/22 04:33:43  mkl
// better printout for 'module ls'
//
// Revision 1.4  1998/11/12 22:23:03  mkl
// finish new module loading and unloading
//
// Revision 1.3  1998/11/12 02:23:43  mkl
// minor cleanup
//
// Revision 1.2  1998/11/09 21:24:31  mkl
// loadable classes know their own factorySymbolstd::string; improved user iface of ModuleCommand
//
// Revision 1.1  1998/11/09 19:30:55  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
//
