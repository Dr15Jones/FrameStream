// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      BlankRecordCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D. Jones
// Created:     Sun Mar 29 19:21:56 EST 1998
// $Id: BlankRecordCommand.cc,v 1.14 2003/10/20 20:43:56 vk Exp $
//
// Revision history
//
// $Log: BlankRecordCommand.cc,v $
// Revision 1.14  2003/10/20 20:43:56  vk
// Modify emptysource to accept optional time parameter. Example: emptysource one vk 113000 10 -time 22222 physics. Time value can  be any positive number (UInt64).
//
// Revision 1.13  2002/12/06 16:36:45  cleo3
// deal with strstream/stringstream
//
// Revision 1.12  2000/12/01 20:26:03  cdj
// now includes map
//
// Revision 1.11  2000/06/01 17:48:42  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.10  1999/06/14 15:55:42  mkl
// return token name as tcl resultString
//
// Revision 1.9  1999/02/22 23:41:36  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.8  1998/12/02 20:01:17  cdj
// added the 'manyTime' subcommand
//
// Revision 1.7  1998/11/09 19:33:06  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.6  1998/10/20 15:54:13  mkl
// fixed up documentation
//
// Revision 1.5  1998/09/08 16:03:07  mkl
// replaced emptySource with emptysource in help info
//
// Revision 1.4  1998/07/28 15:53:14  mkl
// ripple effect: needed to include set
//
// Revision 1.3  1998/06/17 18:18:05  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.2  1998/04/02 22:41:45  cdj
// corrected the example in 'emptySource help' command
//
// Revision 1.1  1998/04/01 19:43:13  mkl
// added Chris' BlankRecordDelivery handling
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <set>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif

// user include files
#include "Experiment/report.h"
#include "JobControl/BlankRecordCommand.h"
#include "JobControl/BlankRecordModule.h"
#include "JobControl/JobControl.h"
#include "DataHandler/StreamSet.h"

#include "BlankRecordDelivery/BlankRecordOneStop.h"
#include "BlankRecordDelivery/BlankRecordManyRunsStop.h"
#include "BlankRecordDelivery/BlankRecordManyEventsStop.h"

// STL classes
#include <set>
#include <cstring>

//
// constants, enums and typedefs
//
const string helpMessage = 
string( " Description: EmptySourceCommand                                \n" )+
string( "                                                                \n" )+
string( " Valid subcommands are:                                         \n" )+
string( "     (<src>=sourcename, <strm>=stream, <rn#>=run#, <ev#>=event#,\n" )+
string( "     [ -time # ] optional parameter to specify time, default 0).\n" )+
string( "                                                                \n" )+
string( "  emptysource help                    see this help page        \n" )+
string( "                                                                \n" )+
string( "  emptysource defaultTime <src> <strm1> [<strm2>..]             \n" )+
string( "  emptysource def         <src> <strm1> [<strm2>..]             \n" )+
string( "    define a source with name <src> with Records                \n" )+
string( "    that occur at (rn#, ev#) =(0,1).                            \n" )+
string( "    You need to specify source name and at least one stream.    \n" )+
string( "                                                                \n" )+
string( "  emptysource oneTime <src> <rn#> <ev#> [ -time # ] <strm1> [<strm2>..]\n" )+
string( "  emptysource one     <src> <rn#> <ev#> [ -time # ] <strm1> [<strm2>..]\n" )+
string( "    define a source with name <src> with Records                \n" )+
string( "    that occur at (rn#, ev#)                                    \n" )+
string( "    You need to specify source name, run- and event- numbers,   \n ")+
string( "    optional time value and at least one stream.                \n" )+
string( "                                                                \n" )+
string( "  emptysource manyTime <src> run <strt> <#stps> <strm1> [<strm2>..]\n")+
string( "  emptysource many     <src> run <strt> <#stps> <strm1> [<strm2>..]\n")+
string( "    define a source with name <src> with Records that occur     \n" )+
string( "    on beginruns starting with run number <strt> and then       \n" )+
string( "    stopping <#stps> number of times                            \n" )+
string( "    You need to specify source name, start run #, # stops and at\n" )+
string( "    least one stream.                                           \n" )+
string( "                                                                \n" )+
string( "  emptysource manyTime <src> event <strt> <#stps> <strm1> [<strm2>..]\n")+
string( "  emptysource many     <src> event <strt> <#stps> <strm1> [<strm2>..]\n")+
string( "    define a source with name <src> with Records that occur     \n" )+
string( "    on events with run number <strt> with the first record      \n" )+
string( "    occuring at run#=<strt> event#=1 and the last Record at     \n" )+
string( "    run#=<strt> event#=<#stps>.                                 \n" )+
string( "    You need to specify source name, start run #, # stops and at\n" )+
string( "    least one stream.                                           \n" )+
string( "                                                                \n" )+
string( "  ----------- Command Overview ----------------                 \n" )+
string( "  This command allows you to create a source that produces      \n" )+
string( "  empty Records at certain times given by (run, event).         \n" )+
string( "  The source created can produce any Records specified,         \n" )+
string( "  even non-standard Records. Different subcommands are          \n" )+
string( "  used to specify the 'time' associated with the Records.       \n" )+
string( "                                                                \n" )+
string( "  You can also change the name you give to your source          \n" )+
string( "  via the \"source\" command.  Please see the help page         \n" )+
string( "  for the \"source\" command for details.                       \n" )+
string( "                                                                \n" )+
string( "  Example:                                                      \n" )+
string( "  i.)  suez> emptysource def geom basegeometry dralignment      \n" )+
string( "    creates a source named 'geom' that produces a BaseGeom      \n" )+
string( "    and DRAlignment Record at the earliest possible time.       \n" )+
string( "                                                                \n" )+
string( "  ii.) suez> emptysource one DRAligned 12345 0 dralignment      \n" )+
string( "    creates a source named 'DRAligned' that produces a          \n" )+
string( "    DRAlignment Record at the time associated with the          \n" )+
string( "    BeginRun Record for run# 12345                              \n" );

static const char* const kFacilityString = "JobControl.BlankRecordCommand" ;

//
// static data member definitions
//

//
// constructors and destructor
//
BlankRecordCommand::BlankRecordCommand( const Command::Name& iName,
					BlankRecordModule* iTarget ) 
   : Command( iName, iTarget, false )
{
}

// BlankRecordCommand::BlankRecordCommand( const BlankRecordCommand& )
// {
// }

BlankRecordCommand::~BlankRecordCommand()
{
}

//
// assignment operators
//
// const BlankRecordCommand& BlankRecordCommand::operator=( const BlankRecordCommand& )
// {
// }

//
// member functions
//
int 
BlankRecordCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_ERROR;

   setArgs( argc, argv );
   if ( 2 <= argc ) {
      if( 0 == strcmp( argv[1], "help" ) ) {
	 result = helpHandler();
      } else if( 0 == strcmp( argv[1], "defaultTime" ) ) {
	 result = defaultTimeSourceHandler();
      } else if( 0 == strcmp( argv[1], "def" ) ) {
	 result = defaultTimeSourceHandler();
      } else if( 0 == strcmp( argv[1], "oneTime" ) ) {
	 result = oneTimeSourceHandler();
      } else if( 0 == strcmp( argv[1], "one" ) ) {
	 result = oneTimeSourceHandler();
      } else if( 0 == strcmp( argv[1], "manyTime" ) ) {
	 result = manyTimeSourceHandler();
      } else if( 0 == strcmp( argv[1], "many" ) ) {
	 result = manyTimeSourceHandler();
      } else {
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
BlankRecordCommand::helpHandler()
{
   // print help from ModuleCommand.h header
   report( SYSTEM, kFacilityString ) << "\n" << helpMessage << endl;

   return COMMAND_OK;

}

int 
BlankRecordCommand::defaultTimeSourceHandler()
{
   int result = COMMAND_ERROR;
   string resultString; // name of resulting source token

   BlankRecordModule* blankRecordModule = (BlankRecordModule*)target();

   // expect 4 or more arguments!
   // eg. "emptysource defaultTime <sourcename> <stream1> [<stream2> etc.]"
   if ( m_argc < 4 ) // wrong number of arguments
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   } 
   else
   {
      // first the sourceName
      string sourceName( getArgument( 2 ) );

      //get the read streams
      StreamSet readStreams;
      parseStreams( readStreams, 3 );

      //Make the algorithm that set the Stops
      BlankRecordStopsBase* pStops = new BlankRecordOneStop;

      if( 0 == pStops ){
	 report( EMERGENCY, kFacilityString) << "out of memory" << endl;
	 result = COMMAND_ERROR;
      } else {
	 // finally add source to system
	 string ioToken;
	 blankRecordModule->addSource( sourceName, 
				       readStreams,
				       pStops,
				       ioToken );

	 // everything's fine
	 result = COMMAND_OK;
      } 
   }

   setResult( resultString );
   return result;
}

int 
BlankRecordCommand::oneTimeSourceHandler()
{
   int result = COMMAND_ERROR;
   string resultString;

   BlankRecordModule* blankRecordModule = (BlankRecordModule*)target();

   // expect 6 or more arguments!
   // eg. "emptysource oneTime <sourcename> <rn#> <ev#> <optional -time #> <stream1> [<stream2> etc.]"
   if ( m_argc < 6 ) // wrong number of arguments
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   } else {
      // first the sourceName
      string sourceName( getArgument( 2 ) );
      
      // Determine optional time parameter
      string timeSet( getArgument(5) );
      short int numArgToReadStreams=5;
      DABoolean readTime=false;
      if(timeSet=="-time") {
        // with time set we expect 8 or more arguments
        if( m_argc < 8 ) {
          report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
          result = COMMAND_ERROR;
          setResult( resultString );
          return result;
        }
        numArgToReadStreams=7; // start reading streams from 7th parameter
        readTime=true;
      }
      
      //read the run and event number
      SyncValue syncValue;
      if( !parseSyncValue( syncValue, 3, readTime ) ){
	 //problem with sync value
	 report( SYSTEM, kFacilityString) << "not a value time "
					  << getArgument(3)<<" "
					  << getArgument(4)<<" ";
         if(readTime) {
           report( SYSTEM, kFacilityString) 
             << getArgument(5) <<" "<< getArgument(6) << endl;
         } else {
           report( SYSTEM, kFacilityString) << endl;
         }
	 result = COMMAND_ERROR;
      } else {
	 //get the read streams
	 StreamSet readStreams;
	 parseStreams( readStreams, numArgToReadStreams );
	 
	 //Make the algorithm that set the Stops
	 BlankRecordStopsBase* pStops = new BlankRecordOneStop( syncValue );
	 
	 if( 0 == pStops ){
	    report( EMERGENCY, kFacilityString) << "out of memory" << endl;
	    result = COMMAND_ERROR;
	 } else {
	    // finally add source to system
	    string ioToken;
	    blankRecordModule->addSource( sourceName, 
					  readStreams,
					  pStops,
					  ioToken );
	    resultString += ioToken;
	    
	    // everything's fine
	    result = COMMAND_OK;
	 } 
      }

   }

   setResult( resultString );
   return result;
}

int 
BlankRecordCommand::manyTimeSourceHandler()
{
   int result = COMMAND_ERROR;
   string resultString;

   BlankRecordModule* blankRecordModule = (BlankRecordModule*)target();

   // expect 7 or more arguments!
   // eg. "emptysource oneTime <sourcename> <rn#> <ev#> <stream1> [<stream2> etc.]"
   if ( m_argc < 7 ) // wrong number of arguments
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      result = COMMAND_ERROR;
   } else {
      // first the sourceName
      string sourceName( getArgument( 2 ) );
      
      DABoolean stopOnRuns = false;
      //Are we stopping on runs or events?
      if( 0 == strncmp( getArgument( 3 ), "run", 3 ) ) {
	 //stopping on runs
	 stopOnRuns = true;
      } else if( 0 != strncmp( getArgument(3 ), "ev", 2 ) ) {
	 //improper agrument
	 report( SYSTEM, kFacilityString ) 
	    << "second argument must be 'runs' or 'events' not "<< getArgument(3) << endl;
	 result = COMMAND_ERROR;
	 return result;
      }

      //read the start number
      long start;
      if( ! parseLong( start, 4 ) ) {
	 report( SYSTEM, kFacilityString) 
	    <<" start value not a number "<<
	    getArgument( 4 ) << endl;
	 return COMMAND_ERROR;
      }

      if( start < 0 ) {
	 report( SYSTEM, kFacilityString ) 
	    <<" start value less than 0: " << getArgument( 4 ) << endl;
	 return COMMAND_ERROR;
      }

      //read the number of stops
      long nStops;
      if( ! parseLong( nStops, 5 ) ) {
	 report( SYSTEM, kFacilityString) 
	    <<" number of stops value not a number "<<
	    getArgument( 5 ) << endl;
	 return COMMAND_ERROR;
      }

      if( start < 0 ) {
	 report( SYSTEM, kFacilityString ) 
	    <<" number of stops value <=0: " << getArgument( 5 ) << endl;
	 return COMMAND_ERROR;
      }

      //get the read streams
      StreamSet readStreams;
      parseStreams( readStreams, 6 );
      
      //Make the algorithm that set the Stops
      BlankRecordStopsBase* pStops(0);
      if( stopOnRuns ) {
	 pStops = new BlankRecordManyRunsStop( start, nStops );
      } else {
	 pStops = new BlankRecordManyEventsStop( start, nStops );
      }
	 
      if( 0 == pStops ){
	 report( EMERGENCY, kFacilityString) << "out of memory" << endl;
	 result = COMMAND_ERROR;
      } else {
	 // finally add source to system
	 string ioToken;
	 blankRecordModule->addSource( sourceName, 
				       readStreams,
				       pStops,
				       ioToken );
	 resultString += ioToken;
	    
	 // everything's fine
	 result = COMMAND_OK;
      } 
   }

   setResult( resultString );
   return result;
}

//
// const member functions
//
void 
BlankRecordCommand::parseStreams( StreamSet& readStreams, int index ) const
{
   const char* arg;
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
      readStreams.add( newStreamType );
   }
}

DABoolean
BlankRecordCommand::parseSyncValue( SyncValue& oSyncValue, 
                                    int iIndex,
                                    DABoolean readTime ) const
{
   const char* arg;

   //Need to convert a string to a number
   long runNumber;
   long eventNumber;
   UInt64 timeStamp=0; // default time stamp equal 0

   arg = getArgument( iIndex );

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
   istrstream ist( arg, strlen(arg));
#else
   istringstream ist( string(arg, strlen(arg)));
#endif
   if( ist >> runNumber ){
      //able to get a number
      if( 0 > runNumber ){
	 report( WARNING, kFacilityString )
	    << "negative run# " << runNumber << "." << endl;
	 return false;
      }
   } else {
      report( WARNING, kFacilityString )
	 << "run # is not a number:" << arg << "." << endl;
      return false;
   }

   arg = getArgument( iIndex+1 );
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
   istrstream ist2( arg, strlen(arg));
#else
   istringstream ist2( string(arg, strlen(arg)));
#endif
   if( ist2 >> eventNumber ){
      //able to get a number
      if( 0 > eventNumber ){
	 report( WARNING, kFacilityString )
	    << "negative event# " << eventNumber << "." << endl;
	 return false;
      }
   } else {
      report( WARNING, kFacilityString )
	 << "event# is not a number:" << arg << "." << endl;
      return false;
   }

   // we only read time when it requested.
   // Need to mentioned that when it happens we need to skip
   // requested parameter -time and read number behind it that's why
   // we increment iIndex by 3 not by 2 (one for -time).
   if(readTime) {
     arg = getArgument( iIndex+3 );
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
     istrstream ist3( arg, strlen(arg));
     string dummy=ist3.rdbuf()->str();
#else
     istringstream ist3( string(arg, strlen(arg)));
     string dummy=ist3.str();
#endif
     // On Linux _it is able_ to read -10 as UInt64 and result
     // will be converted to large number. On Solaris/OSF it's
     // impossible. So we need to make additional check for "-"
     // in incoming string.
     int iSearch = dummy.find("-"); // search for negative numbers
     if( ist3 >> timeStamp ){
        //able to get a number
        if( iSearch != string::npos || 0 > timeStamp ){
	   report( WARNING, kFacilityString )
	   << "time is not a number or you provided negative value: " 
	   << arg << endl;
	   return false;
        }
     } else {
        report( WARNING, kFacilityString )
	   << "time is not a number or you provided negative value: " 
	   << arg << endl;
	   return false;
     }
   
   }

   report( DEBUG, kFacilityString )
      << "syncValue(run,evt,time) = "
      << "( "<<runNumber<<", "<<eventNumber<<", "<<timeStamp<<" )"<<endl;
   oSyncValue = SyncValue( (unsigned long) runNumber,
			   (unsigned long) eventNumber, 
			   (UInt64) timeStamp );

   return true;
}

DABoolean
BlankRecordCommand::parseLong( long& oValue, int iIndex ) const
{
   //Need to convert a string to a number

   const char* arg = getArgument( iIndex );

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
   istrstream ist( arg, strlen(arg));
#else
   istringstream ist( string(arg, strlen(arg)));
#endif
   if( ! (ist >> oValue) ){
      return false;
   }
   return true;
}
//
// static member functions
//


