// -*- C++ -*-
//
// Package:     JobControl
// Module:      SourceCommand
//
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue Jul 22 17:05:15 EST 1997
// $Id: SourceCommand.cc,v 1.25 2000/06/01 17:48:45 mkl Exp $
//
// Revision history
//
// $Log: SourceCommand.cc,v $
// Revision 1.25  2000/06/01 17:48:45  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.24  2000/03/09 19:13:11  mkl
// SourceCommand: dont need to force provider reload; GotoCommand: fix up help page
//
// Revision 1.23  2000/01/19 16:53:12  mkl
// force reload of proxies after new source is added
//
// Revision 1.22  1999/12/11 19:07:31  mkl
// added 'source status' command; use bug flag for linux string compare function problem
//
// Revision 1.21  1999/06/14 15:55:44  mkl
// return token name as tcl resultString
//
// Revision 1.20  1999/05/28 20:24:59  mkl
// Solaris stringstream does not exist, and strstream does not terminate; use snprintf instead
//
// Revision 1.19  1999/04/30 18:15:18  mkl
// first version of source act command handling
//
// Revision 1.18  1999/04/24 17:06:23  mkl
// make cxx happy
//
// Revision 1.17  1999/04/24 16:22:40  mkl
// keep track of DataSourceDescriptors, not just names of files
//
// Revision 1.16  1999/02/22 23:41:40  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.15  1998/11/09 19:33:11  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.14  1998/11/02 17:01:34  mkl
// source clear has to force reload of Proxies
//
// Revision 1.13  1998/07/28 15:53:17  mkl
// ripple effect: needed to include set
//
// Revision 1.12  1998/06/17 18:18:10  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.11  1997/10/07 19:25:23  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.10  1997/10/07 04:19:04  mkl
// report --> cout for INFO messages
//
// Revision 1.9  1997/09/10 01:52:36  mkl
// replaced \n by end
//
// Revision 1.8  1997/09/05 02:36:04  mkl
// tried to unify error handling with tcl way
//
// Revision 1.7  1997/09/03 05:57:50  mkl
// moved from 'const string kFacilityString' to 'static const char* const'
//
// Revision 1.6  1997/09/03 02:38:51  mkl
// restructuring suez libraries
//
// Revision 1.5  1997/08/20 06:23:38  mkl
// symmetrized sinks with sources in terms of user interface
//
// Revision 1.4  1997/08/15 08:11:27  mkl
// changed Stream::Type to StreamType as constructor for the sake of cxx5.6
//
// Revision 1.3  1997/08/13 07:10:49  mkl
// Chains of Sources, new activation of streams, and ProxyDict
//
// Revision 1.2  1997/08/08 05:21:03  mkl
// first attempt at chains-of-files
//
// Revision 1.1  1997/07/24 04:59:50  mkl
// adding chains of sources
//
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#include <stdlib.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "JobControl/SourceCommand.h"
#include "JobControl/SourceManager.h"
#include "JobControl/JobControl.h"
#include "Processor/MasterProcessor.h"
#include "Processor/MasterProducer.h"
#include "DataHandler/StreamSet.h"
#include "JobControl/Binder.h"

// STL classes
#include <map>
#include <set>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.SourceCommand";
 
const string helpMessage = 
string( "// Description: SourceCommand                                      \n" )+
string( "//                                                                 \n" )+
string( "// Valid subcommands are: (nm=name, src=source, strm=stream)       \n" )+
string( "//                                                                 \n" )+
string( "//  source help                            see this help page      \n" )+
string( "//  source create <nm>                     create name             \n" )+
string( "//  source list                            list all sources        \n" )+
string( "//  source list <nm>                       list sources in name    \n" )+
string( "//  source ls [<nm>]                       Synonym for \"ls\"      \n" )+
string( "//  source status                          print status            \n" )+
string( "//                                           (Sync problems etc.)  \n" )+
//string( "//  source stream nm ...                                        \n" )+
//string( "//  source stream nm stream1 ...                                \n" )+
string( "//  source edit <nm>                       edit name               \n" )+
string( "//  source remove <nm>                     remove name             \n" )+
string( "//  source remove <nm> <src1> [<src2>.]    del source(s) from nm\n" )+
string( "//  source rm     <nm> [<src1>...]         Synonym: \"remove\"     \n" )+
string( "//  source del    <nm> [<src1>...          Synonym: \"remove\"     \n" )+
string( "//  source clear                           clear the name list     \n" )+
string( "//  source names                           list names              \n" )+
string( "//  source rename <oldnm> <newnm>          rename name             \n" )+
string( "//  source bind <nm> <strm1> [<strm2..]    bind streams to name    \n" )+
string( "//  source activate <nm> <strm1> [<strm2> ..]                      \n" )+
string( "//                  use potentially active strms from this source  \n" )+
string( "//  source act <nm> <strm1> [<strm2>..]    Synonym: \"activate\"   \n" )+
string( "//  source clearactive [<nm> [<nm2> ...]   clear out active setting\n" )+
string( "//  source clearact    [<nm> [<nm2> ...]   Synonym: \"clearactive\"\n" )+
string( "//                                                                 \n" )+
string( "// Standard streams are:  beginrun endrun event                    \n" )+
string( "//                        geometry hardware user                   \n" )+
string( "//                                                                 \n" )+
//string( "// If no streams are specified, \"event beginrun\" are the       \n" )+
//string( "// default streams, and \"event\" is the default active stream.  \n" )+
string( "                                                                   \n" ); 

//
// static data member definitions
//

//
// constructors and destructor
//
SourceCommand::SourceCommand( const Command::Name& name,
			      SourceManager* target )
   : Command( name, target, false )
{
}

// SourceCommand::SourceCommand( const SourceCommand& )
// {
// }

SourceCommand::~SourceCommand()
{
}

//
// assignment operators
//
// const SourceCommand& SourceCommand::operator=( const SourceCommand& )
// {
// }

//
// member functions
//
int
SourceCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   setArgs( argc, argv );
   if ( 2 <= argc ) {
      if( 0 == strcmp( argv[1], "help" ) ) {
	 result = helpHandler();
      } else 
      if( 0 == strcmp( argv[1], "create" ) ) {
	 result = createTokenHandler();
      } else 
      if( 0 == strcmp( argv[1], "status" ) ) {
	 result = statusHandler();
      } else 
      if( 0 == strcmp( argv[1], "list" ) ) {
	 result = listHandler();
      } else 
      if( 0 == strcmp( argv[1], "ls" ) ) {
	 result = listHandler();
      } else 
      if( 0 == strcmp( argv[1], "edit" ) ) {
	 result = editHandler();
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
      if( 0 == strcmp( argv[1], "rename" ) ) {
	 result = renameTokenHandler();
      } else
      if( 0 == strcmp( argv[1], "names" ) ) {
	 result = listTokensHandler();
      } else 
      if( 0 == strcmp( argv[1], "bind" ) ) {
	 result = bindHandler();
      } else 
      if( 0 == strcmp( argv[1], "use" ) ) { // undocumented feature
	 result = useHandler();             // for testing only
      } else 
      if( 0 == strcmp( argv[1], "activate" ) ) {
	 result = activeHandler();
      } else
      if( 0 == strcmp( argv[1], "act" ) ) {
	 result = activeHandler();
      } else
      if( 0 == strcmp( argv[1], "clearactive" ) ) {
	 result = clearActiveHandler();
      } else
      if( 0 == strcmp( argv[1], "clearact" ) ) {
	 result = clearActiveHandler();
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
SourceCommand::helpHandler()
{
   // print help from ModuleCommand.h header
   report( SYSTEM, kFacilityString ) << "\n" << helpMessage << endl;

   return COMMAND_OK;
}

int
SourceCommand::useHandler( ) // undocumented feature! For testing only
{
   int result = COMMAND_OK;

   // expect 3 arguments
   // eg. "source use
   if ( m_argc != 2 ) // wrong number of arguments
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   } 
   else
   {
      DABoolean ignore;
      sourceManager().useSources( ignore );

      result = COMMAND_OK;
   }

   return result;
}

int
SourceCommand::createTokenHandler( )
{
   int result = COMMAND_OK;
   string resultString;

   // expect 3 arguments
   // eg. "source create token
   if ( m_argc != 3 ) // wrong number of arguments
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   } 
   else
   {
      // last argument is token name
      SourceManager::Token token( getArgument( 2 ) );

      // add a dummy binder; that's the signel
      BinderBase* binder = 
	 new Binder< DummySourceBinder >( (DummySourceBinder*)0,
					  BinderBase::kNone );
      if( 0 == binder ) {
	 report( EMERGENCY, kFacilityString )
	    << "out of memory" << endl;
	 assert( false );
	 ::exit( 1 );
      }
      sourceManager().addSource( binder, token );

      resultString += token;

      result = COMMAND_OK;
   }

   setResult( resultString );
   return result;
}

int
SourceCommand::statusHandler()
{
   int result = COMMAND_OK;

   string resultString = sourceManager().statusOfAllSources();
   setResult( resultString );

   return result;
}

int
SourceCommand::listHandler()
{
   int result = COMMAND_OK;

   string resultString;

   // different options:
   // "source list"       --> list all sources
   // "source list token" --> list all sources in token
   if( 2 == m_argc )
   {
      resultString += sourceManager().listAllSources();

      result = COMMAND_OK;
   } else
   if( 3 == m_argc )
   {
      SourceManager::Token token( m_argv[2] );
      resultString += sourceManager().list( token );

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
SourceCommand::listTokensHandler()
{
   int result = COMMAND_OK;

   string resultString = sourceManager().listTokens();
   setResult( resultString );

   return result;
}

int
SourceCommand::renameTokenHandler()
{
   int result = COMMAND_OK;

   // "source rename oldtoken newtoken"
   if( 4 == m_argc )
   {
      SourceManager::Token oldToken( m_argv[2] );
      SourceManager::Token newToken( m_argv[3] );
      sourceManager().renameToken( oldToken, newToken );

      result = COMMAND_OK;
   }
   else
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   }

   return result;
}

int
SourceCommand::editHandler()
{
   int result = COMMAND_OK;

   // different options:
   // "source edit token" --> edit source with "token"
   // correct number of args
   if( 3 == m_argc )
   {
      SourceManager::Token token( m_argv[2] );
      sourceManager().editSource( token );

      result = COMMAND_OK;
   }
   else
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;

      return result = COMMAND_ERROR;
   }

   return result;
}

int
SourceCommand::removeHandler()
{
   int result = COMMAND_OK;

   // different options:
   // "source remove token"               --> remove chain with "token"
   // "source remove token src [src2...]" --> remove certain srcs in token
   // correct number of args
   if( 3 == m_argc )
   {
      SourceManager::Token token( m_argv[2] );
      sourceManager().removeSource( token );

      result = COMMAND_OK;

   } else
   if( m_argc > 3 )
   {
      SourceManager::Token token( m_argv[2] );
      const char* arg;
      int index  = 3;
      while ( 0 != ( arg = getArgument( index++ ) ) )
      {
	 sourceManager().removeSourceFromChain( token, arg );
      }

      result = COMMAND_OK;
   }
   else
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   }

   return result;
}

int
SourceCommand::clearHandler()
{
   int result = COMMAND_OK;

   // remove all sources
   sourceManager().removeAllSources();
   
   return result;
}

int
SourceCommand::bindHandler()
{
   int result = COMMAND_OK;

   // "stream bind token str1 [str2...]" --> bind streams to sinks
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
	       << "Using non-standard Stream type!" << arg << endl;
	 }
	 streams.add( newStreamType );
      }

      // finally pass on to SourceManager
      sourceManager().bindStreamsToSource( token, streams );

      result = COMMAND_OK;
   }

   return result;
}

int
SourceCommand::activeHandler()
{
   int result = COMMAND_OK;

   // "stream act token str1 [str2...]" --> set potentially active 
   //                                       streams to come from this source
   if( 4 > m_argc )
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      return result = COMMAND_ERROR;
   }

   SourceManager::Token token = m_argv[2];
   const char* arg;
   //int index = 2;
   int index = 3;
   StreamSet toBeActiveStreams;
   while ( 0 != ( arg = getArgument( index++ ) ) ) 
   {
      // check if stream string is non-standard --> issue warning
      // (this is a good idea, because the user might have 
      // mistyped the stream name
      Stream::Type newStreamType = StreamType( arg );
      if( true != newStreamType.isStandard() ) 
      {
	 report( WARNING, kFacilityString )
	    << "Using non-standard Stream type!" << arg << endl;
      }
      toBeActiveStreams.add( newStreamType );
   }
   
   // finally pass on to SourceManager
   sourceManager().setToBeActiveStreamsInSource( token, toBeActiveStreams );
   
   result = COMMAND_OK;

   return result;
}

int
SourceCommand::clearActiveHandler()
{
   int result = COMMAND_OK;

   // "stream clearactive [token [token2]...]" --> clear out active settings
   if( 2 > m_argc )
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      return result = COMMAND_ERROR;
   }

   if( 2 == m_argc )
   {
      sourceManager().clearToBeActiveStreamsInAllSources();
   }
   else 
   {
      for( unsigned int i=2; i<m_argc; ++i ) 
      {
	 SourceManager::Token token = m_argv[i];
	 sourceManager().clearToBeActiveStreamsInSource( token );
      }
   }

   result = COMMAND_OK;

   return result;
}

//
// const member functions
//

//
// static member functions
//
