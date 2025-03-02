// -*- C++ -*-
//
// Package:     JobControl
// Module:      SinkCommand
//
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue Aug 19 16:05:15 EST 1997
// $Id: SinkCommand.cc,v 1.11 2003/09/19 21:20:32 cdj Exp $
//
// Revision history
//
// $Log: SinkCommand.cc,v $
// Revision 1.11  2003/09/19 21:20:32  cdj
// changes needed for Path implementation
//
// Revision 1.10  2000/06/01 17:48:45  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.9  1999/02/22 23:41:38  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.8  1998/11/09 19:33:10  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.7  1998/07/28 15:53:16  mkl
// ripple effect: needed to include set
//
// Revision 1.6  1997/10/07 19:25:20  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.5  1997/09/10 01:52:34  mkl
// replaced \n by end
//
// Revision 1.4  1997/09/05 02:36:03  mkl
// tried to unify error handling with tcl way
//
// Revision 1.3  1997/09/03 05:57:48  mkl
// moved from 'const string kFacilityString' to 'static const char* const'
//
// Revision 1.2  1997/09/03 02:38:49  mkl
// restructuring suez libraries
//
// Revision 1.1  1997/08/20 06:23:36  mkl
// symmetrized sinks with sources in terms of user interface
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "JobControl/SinkCommand.h"
#include "JobControl/SinkManager.h"
#include "DataHandler/StreamSet.h"
#include "Experiment/report.h"

// STL classes
#include <set>
#include <cstring>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.SinkCommand";
 
const string helpMessage = 
string( "// Description: SinkCommand                                       \n" )+
string( "//                                                                \n" )+
string( "// Valid subcommands are: (strm=stream)                           \n" )+
string( "//                                                                \n" )+
string( "//  sink help                            see this help page       \n" )+
//string( "//  sink status sinkName                 print status            \n" )+
//string( "//  sink statusAll                       print status for all    \n" )+
string( "//  sink list                            list all sink            \n" )+
string( "//  sink list <sink>                     list sink properties     \n" )+
string( "//  sink ls [<sink>]                     synonym for \"ls\"       \n" )+
string( "//  sink remove <sink>                   remove <sink>            \n" )+
string( "//  sink rm     <sink>                   synonym: \"remove\"      \n" )+
string( "//  sink del    <sink>                   synonym: \"remove\"      \n" )+
string( "//  sink clear                           clear the sink list      \n" )+
string( "//  sink bind <sink> <strm1> [<strm2..]  bind streams to sink     \n" )+
string( "//                                                                \n" )+
string( "// Standard streams are:  beginrun endrun event                   \n" )+
string( "//                        geometry hardware user                  \n" )+
string( "//                                                                \n" )+
string( "// Warning: you can only write out ACTIVE streams!                \n" )+
string( "                                                                  \n" ); 

//
// static data member definitions
//

//
// constructors and destructor
//
SinkCommand::SinkCommand( const Command::Name& name,
			      Module* target )
   : Command( name, target, false )
{
}

// SinkCommand::SinkCommand( const SinkCommand& )
// {
// }

SinkCommand::~SinkCommand()
{
}

//
// assignment operators
//
// const SinkCommand& SinkCommand::operator=( const SinkCommand& )
// {
// }

//
// member functions
//
int
SinkCommand::execute( int argc, char* argv[] )
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
      } else 
      if( 0 == strcmp( argv[1], "remove" ) ) {
	 result = removeHandler();
      } else 
      if( 0 == strcmp( argv[1], "rm" ) ) {
	 result = removeHandler();
      } else 
      if( 0 == strcmp( argv[1], "del" ) ) {
	 result = removeHandler();
      } else 
      if( 0 == strcmp( argv[1], "clear" ) ) {
	 result = clearHandler();
      } else 
      if( 0 == strcmp( argv[1], "bind" ) ) {
	 result = bindHandler();
      } else 
      if( 0 == strcmp( argv[1], "use" ) ) { // undocumented feature
	 result = useHandler();             // for testing only
      } 
      else
      {
	 report( SYSTEM, kFacilityString ) << "invalid command arg" << endl;
	 helpHandler();
	 result = COMMAND_ERROR;
      }
   } 
   else 
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      helpHandler();
      result = COMMAND_ERROR;
   }

   return result;
}

int
SinkCommand::helpHandler()
{
   // print help from ModuleCommand.h header
   report( INFO, kFacilityString ) << "\n" << helpMessage << endl;

   return COMMAND_OK;
}

int
SinkCommand::listHandler()
{
   int result = COMMAND_OK;

   SinkManager* SM = (SinkManager*)target();

   string resultString;

   // different options:
   // "sink list"       --> list all sinks
   // "sink list name" --> list all sinks w/ name
   if( 2 == m_argc )
   {
      resultString += SM->listAllSinks();

      result = COMMAND_OK;
   } else
   if( 3 == m_argc )
   {
      SinkManager::SinkName sinkName( m_argv[2] );
      resultString += SM->list( sinkName );

      result = COMMAND_OK;
   }
   else
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   }
   setResult( resultString );

   return result;
}

int
SinkCommand::removeHandler()
{
   int result = COMMAND_OK;

   SinkManager* SM = (SinkManager*)target();

   // "sink remove name"  --> remove chain with name
   // correct number of args
   if( 3 == m_argc )
   {
      SinkManager::SinkName sinkName( m_argv[2] );
      if( ! SM->removeSink( sinkName ) ) {

         result = COMMAND_ERROR;
      }
   }
   else
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   }

   return result;
}

int
SinkCommand::clearHandler()
{
   int result = COMMAND_OK;

   SinkManager* sink = (SinkManager*)target( );

   sink->removeAllSinks();

   return result;
}

int
SinkCommand::bindHandler()
{
   int result = COMMAND_OK;

   SinkManager* SM = (SinkManager*)target();

   // "sink bind sinkname str1 [str2...]"   --> bind streams to sink
   if( 4 > m_argc )
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   }
   else
   {
      SinkManager::SinkName sinkName = m_argv[2];
      const char* arg;
      //int index = 2;
      int index = 3;
      StreamSet streams;
      while ( 0 != ( arg = getArgument( index++ ) ) ) 
      {
	 // check if stream string is non-standard --> issue warning
	 // (this is a good idea, because the user might have 
	 // mistyped the stream name
	 Stream::Type newStreamType = StreamType( arg );
	 if( true != newStreamType.isStandard() ) 
	 {
	    report( WARNING, kFacilityString )
	       << "Using non-standard Stream type!" << arg << "." << endl;
	 }
	 streams.add( newStreamType );
      }

      // finally pass on to SinkManager
      SM->bindStreamsToSink( sinkName, streams );

      result = COMMAND_OK;
   }

   return result;
}

int
SinkCommand::useHandler( ) // undocumented feature! For testing only
{
   int result = COMMAND_OK;

   SinkManager* SM = (SinkManager*)target();

   // expect 3 arguments
   // eg. "sink use
   if ( m_argc != 2 ) // wrong number of arguments
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   } 
   else
   {
      SM->useSinks();

      result = COMMAND_OK;
   }

   return result;
}

//
// const member functions
//

//
// static member functions
//
