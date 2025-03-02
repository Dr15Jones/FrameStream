// -*- C++ -*-
//
// Package:     JobControl
// Module:      StreamCommand
//
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Wed Aug 6 14:05:15 EST 1997
// $Id: StreamCommand.cc,v 1.17 2000/06/01 17:48:46 mkl Exp $
//
// Revision history
//
// $Log: StreamCommand.cc,v $
// Revision 1.17  2000/06/01 17:48:46  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.16  1999/03/11 22:02:42  mkl
// source out stream will activate stream; turn off superfluous warning for 'param' command
//
// Revision 1.15  1999/02/22 23:41:42  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.14  1998/11/24 22:07:17  mkl
// cleanup of old code
//
// Revision 1.13  1998/11/09 19:33:14  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.12  1998/07/28 15:53:18  mkl
// ripple effect: needed to include set
//
// Revision 1.11  1998/07/01 23:16:44  mkl
// finalize histogram file before dtor
//
// Revision 1.10  1997/10/07 19:25:25  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.9  1997/09/10 01:52:40  mkl
// replaced \n by end
//
// Revision 1.8  1997/09/05 22:35:28  mkl
// undid singleton patteron for MasterProcessor
//
// Revision 1.7  1997/09/05 02:36:06  mkl
// tried to unify error handling with tcl way
//
// Revision 1.6  1997/09/03 05:57:51  mkl
// moved from 'const string kFacilityString' to 'static const char* const'
//
// Revision 1.5  1997/09/03 02:38:54  mkl
// restructuring suez libraries
//
// Revision 1.4  1997/08/22 04:21:55  mkl
// standardize error messages from commands
//
// Revision 1.3  1997/08/15 08:11:29  mkl
// changed Stream::Type to StreamType as constructor for the sake of cxx5.6
//
// Revision 1.2  1997/08/13 07:10:51  mkl
// Chains of Sources, new activation of streams, and ProxyDict
//
// Revision 1.1  1997/08/08 05:21:09  mkl
// first attempt at chains-of-files
//
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "JobControl/StreamCommand.h"
#include "JobControl/SourceManager.h"
#include "JobControl/JobControl.h"
#include "DataHandler/StreamSet.h"
#include "Experiment/report.h"
#include "JobControl/JobControl.h"

// STL classes
#include <set>
#include <cstring>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.StreamCommand";
 
const string helpMessage = 
string( "// Description: StreamCommand                                      \n" )+
string( "//                                                                 \n" )+
string( "// Valid subcommands are: (strm=stream)                            \n" )+
string( "//                                                                 \n" )+
string( "//  stream help                            see this help page      \n" )+
string( "//  stream activate <strm1> [<strm2> ..]   set active strms        \n" )+
string( "//  stream act      <strm1> [<strm2> ..]   synonym: \"activate\"   \n" )+
string( "//  stream list                            list streams            \n" )+
string( "//  stream ls                              synonym for \"ls\"      \n" )+
string( "//  stream bind <token> <strm1> [<strm2..] bind streams to token   \n" )+
string( "//                                                                 \n" )+
string( "// Standard streams are:  beginrun endrun event                    \n" )+
string( "//                        geometry hardware user                   \n" )+
string( "//                                                                 \n" )+
string( "                                                                   \n" ); 

//
// static data member definitions
//

//
// constructors and destructor
//
StreamCommand::StreamCommand( const Command::Name& name,
				    Module* target )
   : Command( name, target, false )
{
}

// StreamCommand::StreamCommand( const StreamCommand& )
// {
// }

StreamCommand::~StreamCommand()
{
}

//
// assignment operators
//
// const StreamCommand& StreamCommand::operator=( const StreamCommand& )
// {
// }

//
// member functions
//
int
StreamCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_ERROR;

   setArgs( argc, argv );
   if ( 2 <= argc ) {
      if( 0 == strcmp( argv[1], "help" ) ) {
	 result = helpHandler();
      } else 
      if( 0 == strcmp( argv[1], "activate" ) ) {
	 result = activateHandler();
      } else
      if( 0 == strcmp( argv[1], "act" ) ) {
	 result = activateHandler();
      } else 
      if( 0 == strcmp( argv[1], "list" ) ) {
	 result = listHandler();
      } else 
      if( 0 == strcmp( argv[1], "ls" ) ) {
	 result = listHandler();
      } else 
      if( 0 == strcmp( argv[1], "bind" ) ) {
	 result = bindHandler();
      } else 
      if( 0 == strcmp( argv[1], "use" ) ) { // undocumented feature!
	 result = useHandler();            // for testing only!
      }
      else {
	 report( SYSTEM, kFacilityString ) << "invalid command arg" << endl;
	 helpHandler();
	 result = COMMAND_ERROR;
      }
   } 
   else {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      helpHandler();
      result = COMMAND_ERROR;
   }

   return result;
}

int
StreamCommand::helpHandler()
{
   // print help from ModuleCommand.h header
   report( SYSTEM, kFacilityString ) << "\n" << helpMessage << endl;

   return COMMAND_OK;
}

int
StreamCommand::activateHandler()
{
   int result = COMMAND_ERROR;

   SourceManager* source = (SourceManager*)target();

   // expect 3 or more arguments!
   // eg. "stream act <stream1> [<stream2> etc.]"
   if ( 3 > m_argc ) 
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   }
   else
   {
      const char* arg;
      int index = 2;
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

      // finally pass on to SourceManager
      //source->activateStreams( readStreams );
      source->setStreamsToBeActivated( streams );

      // everything's fine
      result = COMMAND_OK;
   } 

   return result;
}

int
StreamCommand::listHandler()
{
   int result = COMMAND_OK;

   SourceManager* SM = (SourceManager*)target();

   string resultString;

   // "stream list"       --> list active sources
   if( 2 == m_argc )
   {
      resultString += SM->listStreams();
      resultString += SM->listStreamsToBeActivated();
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
StreamCommand::bindHandler()
{
   int result = COMMAND_OK;

   SourceManager* SM = (SourceManager*)target();

   // "stream bind token str1 [str2...]"       --> list active sources
   if( 4 > m_argc )
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   }
   else
   {
      SourceManager::Token token = m_argv[2];
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

      // finally pass on to SourceManager
      //source->activateStreams( readStreams );
      SM->bindStreamsToSource( token, streams );

      // everything's fine
      result = COMMAND_OK;
   }

   return result;
}

// ----------------- undocumented feature; for testing only --------------
int
StreamCommand::useHandler() 
{
   int result = COMMAND_ERROR;

   SourceManager* source = (SourceManager*)target();

   // expect 2
   // eg. "stream use"
   if ( 2 > m_argc ) 
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   }
   else
   {
      // take short-cut through JobControl; 
      // ugly but this is for testing only anyways
      source->activateStreams( JobControl::instance()->masterProcessor(),
			       JobControl::instance()->sinkManager() );

      result = COMMAND_OK;
   } 

   return result;
}
// end -------------- undocumented feature; for testing only --------------

//
// const member functions
//

//
// static member functions
//
