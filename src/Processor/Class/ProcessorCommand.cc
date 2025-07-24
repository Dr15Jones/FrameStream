// -*- C++ -*-
//
// Package:     Processor
// Module:      ProcessorCommand
// 
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Wed Mar 19 13:05:15 EST 1997
// $Id: ProcessorCommand.cc,v 1.7 2003/03/14 20:10:37 vk Exp $
//
// Revision history (at end of file)
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

#include "Processor/ProcessorCommand.h"
#include "Processor/MasterProcessor.h"

#include "CommandPattern/Interpreter.h"

// STL classes
//#include <vector>
#include <map>
//#include <utility>
//#include <algorithm>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.ProcessorCommand";

//
// static data member definitions
//

//
// constructors and destructor
//
ProcessorCommand::ProcessorCommand( const Command::Name& name,
				    MasterProcessor* target )
   : MultiLoaderCommand< MasterProcessor >( name, target, false )
{
}

// ProcessorCommand::ProcessorCommand( const ProcessorCommand& )
// {
// }

ProcessorCommand::~ProcessorCommand()
{
}

//
// assignment operators
//
// const ProcessorCommand& ProcessorCommand::operator=( const ProcessorCommand& )
// {
// }

//
// member functions
//
int
ProcessorCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   setArgs( argc, argv );

   if( 2 <= argc && 0 == strcmp( argv[1], "reorder" ) ) {
	 result = reorderHandler();
   }
   else {
      result = MultiLoaderCommand< MasterProcessor >::execute( argc, argv );
   }

   return result;
}

int
ProcessorCommand::helpHandler( )
{
   int result = COMMAND_OK;

   result = MultiLoaderCommand< MasterProcessor >::helpHandler();
   
   report( SYSTEM, kFacilityString ) 
      << "\n//  " << name()
      << " reorder <proc1> <proc2> [..] Reorder processors" << std::endl;;

   return COMMAND_OK;
}

int
ProcessorCommand::reorderHandler()
{
   int result = COMMAND_OK;

   if( m_argc <= 2 )
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << std::endl;
      return result = COMMAND_ERROR;
   }
   // correct number of args

   MasterProcessor* masterProcessor = (MasterProcessor*)target();

   const char* arg;
   int index = 2;
   std::string listString;
   while ( 0 != ( arg = getArgument( index++ ) ) )
   {
      std::string name( arg );
      listString += name + std::string( " " );
   }

   // reorder 
   if( false == masterProcessor->reorder( listString ) )
   {
      report( SYSTEM, kFacilityString )
	 << "problem reordering: \n"
	 << listString
	 << std::endl;
      result = COMMAND_ERROR;
   }

   return result;
}

//
// const member functions
//

//
// static member functions
//


// -------------------------------------------------
// Revision history
//
// $Log: ProcessorCommand.cc,v $
// Revision 1.7  2003/03/14 20:10:37  vk
// Adjust Processor classes wrt to Loader/MultiLoader
//
// Revision 1.6  2000/06/01 17:48:09  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.5  1999/09/14 22:32:35  mkl
// fix 'proc reorder' command to not unload processors first
//
// Revision 1.4  1999/09/07 21:22:07  mkl
// make cxx happy
//
// Revision 1.3  1998/11/10 03:52:32  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.2  1998/11/09 21:25:17  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.1  1998/11/09 19:34:41  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.22  1998/04/08 19:50:20  mkl
// improved help page
//
// Revision 1.21  1998/03/11 19:07:28  mkl
// new implementation of 'inter' command to interact with processor/producer
//
// Revision 1.20  1998/01/16 23:34:30  mkl
// added MasterProducer for selecting Producers at run time
//
// Revision 1.19  1997/10/07 19:25:19  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.18  1997/09/10 01:52:33  mkl
// replaced \n by end
//
// Revision 1.17  1997/09/05 02:36:01  mkl
// tried to unify error handling with tcl way
//
// Revision 1.16  1997/09/03 05:57:47  mkl
// moved from 'const string kFacilityString' to 'static const char* const'
//
// Revision 1.15  1997/09/03 02:38:46  mkl
// restructuring suez libraries
//
// Revision 1.14  1997/08/22 04:21:51  mkl
// standardize error messages from commands
//
// Revision 1.13  1997/07/22 05:19:32  mkl
// replaced data() back to c_str() for g++
//
// Revision 1.12  1997/07/11 06:55:38  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.11  1997/07/02 02:49:00  mkl
// and a few fixes to make g++ happy again
//
// Revision 1.10  1997/07/02 01:40:32  mkl
// fixes to allow CXX version 5.4
//
// Revision 1.9  1997/06/06 06:18:13  mkl
// handle --> execute and other minor stuff
//
// Revision 1.8  1997/06/04 05:23:49  mkl
// misc
//
// Revision 1.7  1997/06/03 18:41:19  mkl
// changed over to kFacilityString
//
// Revision 1.6  1997/05/23 20:22:29  mkl
// separated Processor stuff from Processor
//
// Revision 1.5  1997/05/16 05:51:43  mkl
// cleaning up.
//
// Revision 1.4  1997/05/15 17:41:39  mkl
// MasterProcessor now contains a SharedObjectHandler. Added "processor
// reorder" command.
//
// Revision 1.3  1997/05/14 17:14:57  mkl
// added capability to load/unload shared objects.
//
// Revision 1.2  1997/03/31 22:59:35  mkl
// fixed up some documentation.
//
// Revision 1.1  1997/03/27 06:53:08  mkl
// imported sources.
//
