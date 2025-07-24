// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      ModuleCommand
// 
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Fri Oct 23 12:37:14 EST 1998
// $Id: ModuleCommand.cc,v 1.8 2002/08/16 14:15:16 cleo3 Exp $
//
// Revision history
//
// $Log: ModuleCommand.cc,v $
// Revision 1.8  2002/08/16 14:15:16  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.7  2000/12/01 20:01:27  cdj
// now includes map
//
// Revision 1.6  1999/03/12 21:40:45  mkl
// missed calling 'setResult( resultString )' in ModuleCommand
//
// Revision 1.5  1999/02/22 23:40:43  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.4  1999/01/22 04:33:45  mkl
// better printout for 'module ls'
//
// Revision 1.3  1998/11/10 03:52:48  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.2  1998/11/09 21:24:35  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.1  1998/11/09 19:31:05  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
//

#include "Experiment/Experiment.h"
// system include files
#include <iostream>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/ModuleCommand.h"
#include "CommandPattern/Interpreter.h"

// STL classes
#include <vector>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "CommandPattern.ModuleCommand";

//
// static data member definitions
//

//
// constructors and destructor
//
ModuleCommand::ModuleCommand( const Command::Name& commandName,  
			      LoaderModule* target )
    : LoaderCommand< LoaderModule >( commandName, target )
{
}

// ModuleCommand::ModuleCommand( const ModuleCommand& )
// {
// }

ModuleCommand::~ModuleCommand()
{
}

//
// assignment operators
//
// const ModuleCommand& ModuleCommand::operator=( const ModuleCommand& )
// {
// }

//
// member functions
//
int
ModuleCommand::listSelectedHandler()
{
   DABoolean result = COMMAND_OK;

   std::string resultString;
   //// don't do that -- duplicated:  resultString += target()->listLoaded();
   resultString += target()->listModules();
   setResult( resultString );
   
   return result;
}
LoaderModule*
ModuleCommand::target()
{
   return (LoaderModule*)Command::target();
}

//
// const member functions
//
const LoaderModule*
ModuleCommand::target() const
{
   return (const LoaderModule*)Command::target();
}

//
// static member functions
//
