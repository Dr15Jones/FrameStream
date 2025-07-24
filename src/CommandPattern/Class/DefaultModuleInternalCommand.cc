// -*- C++ -*-
//
// Package:     <DefaultModule>
// Module:      DefaultModuleInternalCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Thu Feb 18 23:00:13 EST 1999
// $Id: DefaultModuleInternalCommand.cc,v 1.2 2000/06/01 17:50:56 mkl Exp $
//
// Revision history
//
// $Log: DefaultModuleInternalCommand.cc,v $
// Revision 1.2  2000/06/01 17:50:56  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.1.1.1  1999/02/22 22:44:38  mkl
// imported sources
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/DefaultModuleInternalCommand.h"
#include "CommandPattern/DefaultModule.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#include <cstring>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "DefaultModule.DefaultModuleInternalCommand" ;

// ---- cvs-based std::strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DefaultModuleInternalCommand.cc,v 1.2 2000/06/01 17:50:56 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
DefaultModuleInternalCommand::DefaultModuleInternalCommand( const Command::Name& iName, 
						DefaultModule* target )
   : Command( iName, target, true ) // "false" to make it external command
{
}

// DefaultModuleInternalCommand::DefaultModuleInternalCommand( 
//      const DefaultModuleInternalCommand& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

DefaultModuleInternalCommand::~DefaultModuleInternalCommand()
{
}

//
// assignment operators
//
// const DefaultModuleInternalCommand& DefaultModuleInternalCommand::operator=( 
//       const DefaultModuleInternalCommand& rhs )
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
DefaultModuleInternalCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   // expect two arguments: "print" or "help"
   setArgs( argc, argv );
   if( 2 == argc )
   {
      if( 0 == strcmp( argv[1], "help" ) )
      {
         result = helpHandler();
      } else
      if( 0 == strcmp( argv[1], "do" ) )
      {
	 result = doHandler();
      }
      else { // bad command argument!
         report( SYSTEM, kFacilityString ) << "invalid command arg" << std::endl;
	 helpHandler();
         result = COMMAND_ERROR;
      }
   }
   else // number of arguments
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << std::endl;
      helpHandler();
      result = COMMAND_ERROR;
   }


   return result;
}

int
DefaultModuleInternalCommand::helpHandler()
{
   // print help from header
   static const std::string helpMessage =
      std::string( " calls DefaultModule.\n" )+
      std::string( "                    \n" )+
      std::string( " Subcommands are:   \n" )+
      std::string( "    help            \n" )+
      std::string( "    do              \n" );

   report( SYSTEM, kFacilityString )
      << "\n\nDescription: " << name() << "\n\n"
      << helpMessage
      << std::endl;

   return COMMAND_OK;
}

int
DefaultModuleInternalCommand::doHandler()
{
   // call "saySomething" function of DefaultModule
   //target()->doSomething();

   return COMMAND_OK;
}

DefaultModule*
DefaultModuleInternalCommand::target()
{
   return (DefaultModule*)Command::target();
}

//
// const member functions
//
const DefaultModule*
DefaultModuleInternalCommand::target() const
{
   return (const DefaultModule*)Command::target();
}

//
// static member functions
//
