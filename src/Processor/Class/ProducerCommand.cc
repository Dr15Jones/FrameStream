// -*- C++ -*-
//
// Package:     Processor
// Module:      ProducerCommand
// 
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Thu Jan 15 13:05:15 EST 1998
// $Id: ProducerCommand.cc,v 1.8 2003/08/13 15:13:27 vk Exp $
//
// Revision history
//
// $Log: ProducerCommand.cc,v $
// Revision 1.8  2003/08/13 15:13:27  vk
// Fix help output (Reorder producers).
//
// Revision 1.7  2003/03/14 20:10:38  vk
// Adjust Processor classes wrt to Loader/MultiLoader
//
// Revision 1.6  2000/06/01 17:48:10  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.5  1999/10/07 17:45:30  mkl
// setDefaultDir per processor/producer based on name
//
// Revision 1.4  1999/09/07 21:22:07  mkl
// make cxx happy
//
// Revision 1.3  1998/11/10 03:52:32  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.2  1998/11/09 21:25:18  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.1  1998/11/09 19:34:41  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.2  1998/03/11 19:07:29  mkl
// new implementation of 'inter' command to interact with processor/producer
//
// Revision 1.1  1998/01/16 23:34:31  mkl
// added MasterProducer for selecting Producers at run time
//
//

#include "Experiment/Experiment.h"
// system include files
#include <stdlib.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
//#include <vector>
#include <map>
//#include <utility>
//#include <algorithm>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "Processor/ProducerCommand.h"
#include "Processor/MasterProducer.h"

#include "CommandPattern/Interpreter.h"

// STL classes
// STL classes
//#include <vector>
#include <map>
//#include <utility>
//#include <algorithm>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.ProducerCommand";

//
// static data member definitions
//

//
// constructors and destructor
//
ProducerCommand::ProducerCommand( const Command::Name& name,
				  MasterProducer* target )
   : MultiLoaderCommand< MasterProducer >( name, target, false )
{
}

// ProducerCommand::ProducerCommand( const ProducerCommand& )
// {
// }

ProducerCommand::~ProducerCommand()
{
}

//
// assignment operators
//
// const ProducerCommand& ProducerCommand::operator=( const ProducerCommand& )
// {
// }

//
// member functions
//
int
ProducerCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   setArgs( argc, argv );

   if( 2 <= argc && 0 == strcmp( argv[1], "reorder" ) ) {
	 result = reorderHandler();
   }
   else {
      result = MultiLoaderCommand< MasterProducer >::execute( argc, argv );
   }

   return result;
}

int
ProducerCommand::helpHandler( )
{
   int result = COMMAND_OK;

   result = MultiLoaderCommand< MasterProducer >::helpHandler();
   
   report( SYSTEM, kFacilityString ) 
      << "\n//  " << name()
      << " reorder <prod1> <prod2> [..] Reorder producers" << std::endl;

   return COMMAND_OK;
}

int
ProducerCommand::reorderHandler()
{
   int result = COMMAND_OK;

   if( m_argc <= 2 )
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << std::endl;
      return result = COMMAND_ERROR;
   }
   // correct number of args

   MasterProducer* masterProducer = (MasterProducer*)target();

   // get rid of old active producer list
   masterProducer->unloadAll();

   const char* arg;
   int index = 2;
   while ( 0 != ( arg = getArgument( index++ ) ) )
   {
      std::string name( arg );

      if( masterProducer->load( name ) ) 
      {
	 result = COMMAND_OK;
      }
      else 
      {
	 report( SYSTEM, kFacilityString ) 
	    << "No producer " << name << "." << std::endl;
	 result = COMMAND_ERROR;
      }
   }
      
   return result;
}

//
// const member functions
//

//
// static member functions
//
