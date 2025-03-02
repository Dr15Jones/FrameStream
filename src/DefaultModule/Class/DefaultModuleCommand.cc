// -*- C++ -*-
//
// Package:     DefaultModule
// Module:      DefaultModuleCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Thu Feb 18 23:00:13 EST 1999
// $Id: DefaultModuleCommand.cc,v 1.3 2000/06/01 17:50:56 mkl Exp $
//
// Revision history
//
// $Log: DefaultModuleCommand.cc,v $
// Revision 1.3  2000/06/01 17:50:56  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.2  1999/04/26 18:42:15  mkl
// improved help documentation
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
#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "DefaultModule/DefaultModuleCommand.h"
#include "DefaultModule/DefaultModule.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#include <cstring>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "DefaultModule.DefaultModuleCommand" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DefaultModuleCommand.cc,v 1.3 2000/06/01 17:50:56 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
DefaultModuleCommand::DefaultModuleCommand( const Command::Name& iName, 
					    DefaultModule* target )
   : Command( iName, target, false ) // "false" to make it external command
{
}

// DefaultModuleCommand::DefaultModuleCommand( const DefaultModuleCommand& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

DefaultModuleCommand::~DefaultModuleCommand()
{
}

//
// assignment operators
//
// const DefaultModuleCommand& DefaultModuleCommand::operator=( const DefaultModuleCommand& rhs )
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
DefaultModuleCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   // expect two arguments: "print" or "help"
   setArgs( argc, argv );
   if( 2 <= argc )
   {
      if( 0 == strcmp( argv[1], "help" ) )
      {
         result = helpHandler();
      } else
      if( 0 == strcmp( argv[1], "prompt" ) )
      {
	 result = promptHandler();
      }
      else { // bad command argument!
         report( SYSTEM, kFacilityString ) << "invalid command arg" << endl;
	 helpHandler();
         result = COMMAND_ERROR;
      }
   }
   else // number of arguments
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      helpHandler();
      result = COMMAND_ERROR;
   }


   return result;
}

int
DefaultModuleCommand::helpHandler()
{
   // print help from header
   static const string helpMessage =
      string( " Toggle various 'defaults' options                           \n" )+
      string( "                                                             \n" )+
      string( " Subcommands are:                                            \n" )+
      string( "    help               print this help page                  \n" )+
      string( "    prompt on/off      turn prompting on/off                 \n" )+
      string( "      Always use first in list of entries:                   \n" )+
      string( "      e.g. first shared module with same name                \n" )+
      string( "      e.g. first source supplying same active stream         \n" );

   report( SYSTEM, kFacilityString )
      << "\n\nDescription: " << name() << "\n\n"
      << helpMessage
      << endl;

   return COMMAND_OK;
}

int
DefaultModuleCommand::promptHandler()
{
   int returnValue = COMMAND_OK;

   // call "saySomething" function of DefaultModule
   if( 3 == m_argc )
   {
      string switchString( m_argv[2] );
      Switch::OnOff setting( Switch::toSwitch( switchString ) );
      Switch::OnOff result = target()->setPrompting( setting );
      string resultString = Switch::toString( result );
      setResult( resultString );
   }

   return COMMAND_OK;
}

DefaultModule*
DefaultModuleCommand::target()
{
   return (DefaultModule*)Command::target();
}

//
// const member functions
//
const DefaultModule*
DefaultModuleCommand::target() const
{
   return (const DefaultModule*)Command::target();
}

//
// static member functions
//
