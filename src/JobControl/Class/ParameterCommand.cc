// -*- C++ -*-
//
// Package:     JobControl
// Module:      ParameterCommand
//
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Mon Mar 15 17:05:15 EST 1999
// $Id: ParameterCommand.cc,v 1.9 2000/06/01 17:48:44 mkl Exp $
//
// Revision history
//
// $Log: ParameterCommand.cc,v $
// Revision 1.9  2000/06/01 17:48:44  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.8  1999/09/14 18:41:43  mkl
// fixed up parameter help page
//
// Revision 1.7  1999/03/15 19:14:17  mkl
// InteractCommand
//
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
//#include <vector>
//#include <map>
//#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "JobControl/ParameterCommand.h"

// STL classes
//#include <vector>
//#include <map>
//#include <set>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.ParameterCommand";
 
static const std::string helpMessage = 
std::string( "// Description: ParameterCommand                             \n" )+
std::string( "//                                                           \n" )+
std::string( "//  param <Module> <parametername>                           \n" )+
std::string( "//  param <Module> <parametername> [<value> ...]             \n" )+
std::string( "//  param <Module> <menuname> <parametername> [<value> ...]  \n" )+
std::string( "                                                             \n" );

//
// static data member definitions
//

//
// constructors and destructor
//
ParameterCommand::ParameterCommand( const Command::Name& name,
				    Module* target )
   : InteractCommand( name, target )
{
}

// ParameterCommand::ParameterCommand( const ParameterCommand& )
// {
// }

ParameterCommand::~ParameterCommand()
{
}

//
// assignment operators
//
// const ParameterCommand& ParameterCommand::operator=( const ParameterCommand& )
// {
// }

//
// member functions
//
int
ParameterCommand::helpHandler()
{
   // print help from ModuleCommand.h header
   report( SYSTEM, kFacilityString ) << "\n" << helpMessage << std::endl;

   return COMMAND_OK;
}

//
// const member functions
//

//
// static member functions
//
