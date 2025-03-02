// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      EchoCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Mon Oct 27 12:19:44 EST 1997
// $Id: EchoCommand.cc,v 1.3 2000/06/01 17:49:26 mkl Exp $
//
// Revision history
//
// $Log: EchoCommand.cc,v $
// Revision 1.3  2000/06/01 17:49:26  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.2  1998/03/12 15:10:36  mkl
// fixed comparison between signed and unsigned
//
// Revision 1.1  1997/10/27 19:25:42  mkl
// EchoCommand to echo messages
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/EchoCommand.h"
#include "CommandPattern/Module.h"


// STL classes
#include <cstring>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "CommandPattern.EchoCommand" ;

static const string helpMessage = 
string( "                                               \n" )+
string( "// Description: Echo Command                   \n" )+
string( "//              \"echo\" echos an info message.\n" );

//
// static data member definitions
//

//
// constructors and destructor
//
EchoCommand::EchoCommand( const Command::Name& iCommand,
			  Module* iTarget )
   : Command( iCommand, iTarget )
{
}

// EchoCommand::EchoCommand( const EchoCommand& )
// {
// }

EchoCommand::~EchoCommand()
{
}

//
// assignment operators
//
// const EchoCommand& EchoCommand::operator=( const EchoCommand& )
// {
// }

//
// member functions
//
int
EchoCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   // expect no or many arguments: "echo" or "echo hello how are you"
   if( 2 == argc ) 
   {
      if ( 0 == strcmp( argv[1], "help" ) )
      {
	 result = helpHandler();
      } 
   }

   //ostream& os = report( INFO );
   ostream& os = cout;
   for( int i=1; i<argc; ++i )
   {
      os << argv[i] << " ";
   }
   os << endl;

   return result;
}

int
EchoCommand::helpHandler()
{
   // print help from header
   report( SYSTEM, kFacilityString ) << "\n" << helpMessage << endl;

   return COMMAND_OK;
}

//
// const member functions
//

//
// static member functions
//
