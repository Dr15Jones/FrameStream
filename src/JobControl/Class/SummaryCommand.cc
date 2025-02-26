// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      SummaryCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Fri Jul 24 10:42:56 EDT 1998
// $Id: SummaryCommand.cc,v 1.5 2000/06/01 17:48:47 mkl Exp $
//
// Revision history
//
// $Log: SummaryCommand.cc,v $
// Revision 1.5  2000/06/01 17:48:47  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.4  1999/02/22 23:41:43  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.3  1998/11/09 19:33:14  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.2  1998/07/29 20:06:48  mkl
// new summary command implemented
//
// Revision 1.1  1998/07/28 15:53:18  mkl
// ripple effect: needed to include set
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "JobControl/SummaryModule.h"
#include "JobControl/SummaryCommand.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.SummaryCommand" ;

static const string helpMessage = 
string( "                                                                \n" )+
string( "// Description: SummaryCommand                                  \n" )+
string( "//                                                              \n" )+
string( "//  Valid subcommands are:                                      \n" )+
string( "//                                                              \n" )+
string( "//                                         print statistics     \n" )+
string( "//  help                                   see this help page   \n" )+
string( "//  reset                                  reset counters       \n" );

//
// static data member definitions
//

//
// constructors and destructor
//
SummaryCommand::SummaryCommand( const Command::Name& name,
				Module* target )
   : Command( name, target, false )
{
}

// SummaryCommand::SummaryCommand( const SummaryCommand& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SummaryCommand::~SummaryCommand()
{
}

//
// assignment operators
//
// const SummaryCommand& SummaryCommand::operator=( const SummaryCommand& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
int
SummaryCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   setArgs( argc, argv );
   if( 1 == argc ) {
      result = listHandler();
   } else
   if( 2 == argc ) {
      if( 0 == strcmp( argv[1], "help" ) ) {
	 result = helpHandler();
      } else 
      if( 0 == strcmp( argv[1], "reset" ) ) {
	 result = resetHandler();
      }
      else {
	 report( SYSTEM, kFacilityString ) << "invalid command arg" << endl;
	 helpHandler();
	 result = COMMAND_ERROR;
      }
   } // wrong # of args
   else 
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      helpHandler();
      result = COMMAND_ERROR;
   }

   return result;
}

int
SummaryCommand::helpHandler( )
{
   // print help from ModuleCommand.h header
   report( SYSTEM, kFacilityString ) << "\n" << helpMessage << endl;

   return COMMAND_OK;
}

int
SummaryCommand::resetHandler( )
{
   int result = COMMAND_OK;

   SummaryModule* summaryModule = (SummaryModule*)target();
   summaryModule->reset();
   
   return result;
}

int
SummaryCommand::listHandler( )
{
   int result = COMMAND_OK;

   string resultString;
   SummaryModule* summaryModule = (SummaryModule*)target();
   resultString += summaryModule->list();
   setResult( resultString );

   return result;
}

//
// const member functions
//

//
// static member functions
//
