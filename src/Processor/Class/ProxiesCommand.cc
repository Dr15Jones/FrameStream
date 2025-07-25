// -*- C++ -*-
//
// Package:     Processor
// Module:      ProxiesCommand
// 
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Sun Nov 1 13:05:15 EST 1998
// $Id: ProxiesCommand.cc,v 1.5 2002/08/16 15:46:37 cleo3 Exp $
//
// Revision history (at end of file)
//
#include "Experiment/Experiment.h"
// system include files
#include <iostream>
#include <stdlib.h>

// user include files
#include "Experiment/report.h"

#include "Processor/ProxiesCommand.h"
#include "Processor/Producer.h"
#include "DataHandler/DataKey.h"

// STL classes

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.ProxyCommand";

const std::string helpMessage = 
std::string( "                                                          \n" )+
std::string( "// Description: ProxyCommand                              \n" )+
std::string( "//                                                        \n" )+
std::string( "//  Valid subcommands are:                                \n" )+
std::string( "//                                                        \n" )+
std::string( "//  proxy help                    see this help page      \n" )+
std::string( "//  proxy list                    List proxies            \n" )+
std::string( "//  proxy ls                      Synonym: \"list\"       \n" )+
std::string( "                                                          \n" );

//
// static data member definitions
//

//
// constructors and destructor
//
ProxiesCommand::ProxiesCommand( const Command::Name& name,
				Producer* target )
   : Command( name, target )
{
}

// ProxiesCommand::ProxiesCommand( const ProxiesCommand& )
// {
// }

ProxiesCommand::~ProxiesCommand()
{
}

//
// assignment operators
//
// const ProxiesCommand& ProxiesCommand::operator=( const ProxiesCommand& )
// {
// }

//
// member functions
//
int
ProxiesCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   setArgs( argc, argv );
   if ( 2 <= argc ) {
      if( 0 == strcmp( argv[1], "help" ) ) {
	 result = helpHandler();
      } else 
      if( 0 == strcmp( argv[1], "list" ) ) {
	 result = listHandler();
      } else 
      if( 0 == strcmp( argv[1], "ls" ) ) {
	 result = listHandler();
      }
      else {
	 report( SYSTEM, kFacilityString ) << "invalid command arg" << std::endl;
	 helpHandler();
	 result = COMMAND_ERROR;
      }
   } // wrong # of args
   else 
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << std::endl;
      helpHandler();
      result = COMMAND_ERROR;
   }

   return result;
}

int
ProxiesCommand::helpHandler( )
{
   report( SYSTEM, kFacilityString ) << "\n" << helpMessage << std::endl;
   return COMMAND_OK;
}

int
ProxiesCommand::listHandler()
{
   int result = COMMAND_OK;

   // list all proxies in Processor
   Producer* producer = (Producer*)target();
   Stream::Set supplies = producer->supplies();
   Stream::Set::const_iterator itEnd = supplies.end();
   std::string resultString;
   for( Stream::Set::const_iterator it = supplies.begin();
	it != itEnd;
	++it ) {

      resultString += std::string( "Proxies for stream " ) 
	 + (*it).value() + std::string( ":\n" );
      typedef std::vector< DataKey > DataKeys;
      const DataKeys& proxyKeys = producer->proxyKeys( *it );
      DataKeys::const_iterator lastKey = proxyKeys.end();
      for( DataKeys::const_iterator itKey = proxyKeys.begin();
	   itKey != lastKey;
	   ++itKey ) {
	 resultString += (*itKey).type().name()
	    + std::string( "\", \"" )
	    + (*itKey).usage().value()
	    + std::string(  "\", \"" )
	    + (*itKey).production().value() 
	    + std::string( "\"\n" );
      }
      resultString += std::string( "\n" );
   }
   setResult( resultString );

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
// $Log: ProxiesCommand.cc,v $
// Revision 1.5  2002/08/16 15:46:37  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.4  2000/06/01 17:48:10  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.3  1999/02/22 23:38:08  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.2  1998/11/06 21:23:13  mkl
// renamed 'proxies' command to 'proxy'
//
// Revision 1.1  1998/11/06 21:02:29  mkl
// add ProxiesCommand to Producers
//
//
