//- C++ -*-
//
// Package:     JobControl
// Module:      FileModule
// 
// Description: FileModule creates the proper Binders for 
//              file sources and sinks
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Wed Aug 20 00:50:01 EST 1997
// $Id: FileModule.cc,v 1.25 2001/06/15 21:06:21 cdj Exp $
//
// Revision history
//
// $Log: FileModule.cc,v $
// Revision 1.25  2001/06/15 21:06:21  cdj
// can now specify data (not) to store in a sink
//
// Revision 1.24  2000/05/15 15:34:30  mkl
// switch non-EMERGENCY suez messages to SYSTEM severity level
//
// Revision 1.23  2000/03/22 23:35:16  mkl
// turned cin-related couts into report(EMERGENCY) so that can check for errors in logfiles AND avoid too-high report level
//
// Revision 1.22  2000/03/16 21:39:26  mkl
// use cout when using cin
//
// Revision 1.21  1999/06/14 15:55:43  mkl
// return token name as tcl resultString
//
// Revision 1.20  1999/06/12 15:42:18  mkl
// print out what streams are the default
//
// Revision 1.19  1999/06/12 00:03:58  mkl
// allow to specify default streams per source format
//
// Revision 1.18  1999/05/28 20:37:31  mkl
// bug: 'ends' on Solaris does not flush buffer
//
// Revision 1.17  1999/05/12 20:35:24  mkl
// clean out old dependencies
//
// Revision 1.16  1999/03/11 22:02:38  mkl
// source out stream will activate stream; turn off superfluous warning for 'param' command
//
// Revision 1.15  1998/11/09 19:33:07  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.14  1998/07/28 15:53:15  mkl
// ripple effect: needed to include set
//
// Revision 1.13  1998/06/17 20:20:54  mkl
// clean-out
//
// Revision 1.12  1998/06/17 18:18:07  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.11  1998/03/15 01:14:20  mkl
// simplified handling of non-existent files: give error and return
//
// Revision 1.10  1997/12/03 04:33:12  mkl
// needed stdio include file requested by AIX
//
// Revision 1.9  1997/10/20 17:11:05  mkl
// fix for sink with unspecified streams
//
// Revision 1.8  1997/10/07 19:25:15  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.7  1997/10/07 04:19:01  mkl
// report --> cout for INFO messages
//
// Revision 1.6  1997/10/05 15:13:55  mkl
// New StringUtil methods
//
// Revision 1.5  1997/09/18 21:26:49  cdj
// changed Boolean to DABoolean
//
// Revision 1.4  1997/09/04 06:38:51  mkl
// moved StringUtilities, STL_AlgoString, and STL_SharedObject to better places
//
// Revision 1.3  1997/09/03 02:38:40  mkl
// restructuring suez libraries
//
// Revision 1.2  1997/08/29 04:21:52  mkl
// simplify JobControl: remove FileInput/Output files, bug flag changes, handling of suffix .gz etc.
//
// Revision 1.1  1997/08/20 06:23:32  mkl
// symmetrized sinks with sources in terms of user interface
//
//

#include "Experiment/Experiment.h"
// system include files
#include <stdio.h> // for FILE* pointer
#include <assert.h>
#include <stdlib.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "JobControl/FileModule.h"
#include "JobControl/JobControl.h"

#include "JobControl/SourceFormatMap.h"
#include "JobControl/SinkFormatMap.h"
#include "JobControl/SourceManager.h"
#include "DataDelivery/DataSourceBinder.h"
#include "DataStorage/DataSinkBinder.h"
#include "DataDelivery/FrameDeliverer.h"
#include "JobControl/Binder.h"

#include "JobControl/SinkManager.h"
#include "DataStorage/DataSinkBinder.h"
#include "DataStorage/FrameStorer.h"

#include "CommandPattern/StringUtilities.h"

// STL classes
#include <vector>
#include <set>
#include <cstring>

//
// constants, enums and typedefs
//
// BEWARE: g++ won't compile, if I replace "char* const" by "string"
static const char* const kFacilityString = "JobControl.FileModule";

//
// static data member definitions
//
//
// constructors and destructor
//
FileModule::FileModule( SourceFormatMap& iSourceFormatM, 
			SinkFormatMap& iSinkFormatM,
			SourceManager& iSourceM, SinkManager& iSinkM )
   : Module( "FileModule", "FileModule" ), 
     m_command( "file", this ),
     m_sourceFormatMap( iSourceFormatM ),
     m_sinkFormatMap  ( iSinkFormatM ),
     m_sourceManager  ( iSourceM ),
     m_sinkManager    ( iSinkM )
{
}

// FileModule::FileModule( const FileModule& )
// {
// }

FileModule::~FileModule()
{
}

//
// assignment operators
//
// const FileModule& FileModule::operator=( const FileModule& )
// {
// }

//
// member functions
//
// ---------------- input module --------------------
DABoolean
FileModule::addSource( const string& iSourceName, 
		       const StreamSet& iReadStreams,
		       string& ioToken )
{
   DABoolean success = false;

   // make local copy
   Stream::Set streams( iReadStreams );

   // if no streams specified, use proper default streams (based on extension)
   if( true == streams.empty() )
   {
      streams = m_sourceFormatMap.defaultStreams( iSourceName );
      string message( "using default streams:" );
      Stream::Set::const_iterator itEnd = streams.end();
      for( Stream::Set::const_iterator it = streams.begin();
	   it != itEnd;
	   ++it )
      {
	 message += string(" ")+(*it).value();
      }
      report( INFO, kFacilityString ) << message << endl;
   }

   BinderBase* binder = m_sourceFormatMap.createBinder( iSourceName, 
							streams );
   if( 0 != binder )
   {
      success = m_sourceManager.addSource( binder, ioToken );
   }

   return success;
}

DABoolean
FileModule::checkIfSourceExists( string& iSourceName )
{
   DABoolean sourceExists = false;
   
   string command = string( "ls " ) + iSourceName 
                  + string( " 2>/dev/null >/dev/null" );
   sourceExists = ( 0 != system( command.c_str() ) ) ? false : true;

   return sourceExists;
}

// ---------------- output module --------------------
DABoolean
FileModule::addSink( const string& iSinkName, 
           const StreamSet& iWriteStreams,
		     const StreamToDataStringTagsToStoreMap& iStreamsDataMap )
{
   DABoolean success = false;

   DataSinkBinder* binder = m_sinkFormatMap.createBinder( iSinkName, 
                        iWriteStreams, 
							   iStreamsDataMap );
   if( 0 != binder )
   {
      success = m_sinkManager.addSink( binder );
   }

   return success;
}

DABoolean
FileModule::addSink( const string& iSinkName, 
		     const StreamSet& iWriteStreams )
{
   DABoolean success = false;

   DataSinkBinder* binder = m_sinkFormatMap.createBinder( iSinkName, 
							  iWriteStreams );
   if( 0 != binder )
   {
      success = m_sinkManager.addSink( binder );
   }

   return success;
}

DABoolean
FileModule::checkSinkName( string& iSinkName )
{
   // Two things to check:
   // 1.) is the pathname valid
   // 2.) is the sinkName already in existence 
   //     --> does the user want to overwrite?

   DABoolean goodSinkName = true;

   string command;

   // 1.) check pathname
   command = string( "dirname " ) + iSinkName;
   FILE* FILEOutput = popen( command.c_str(), "r" );

   const Count BUFSIZE = 1024;
   char buf[BUFSIZE];
   fgets( buf, sizeof( buf ), FILEOutput );
   buf[strlen(buf)-1] = '\0';    // suppress \n
   pclose( FILEOutput );
   command = string( "ls " ) + string( buf ) + string( ">/dev/null 2>&1" );


   if( 0 != system( command.c_str() ) )
   {
      report( ERROR, kFacilityString )
	 << "No such directory exists. Try again.\n";
      goodSinkName = false;
   }
   else // directory exists, but is the file ok? 
   {
   // 2.) check file
      command = string( "ls " ) + iSinkName + string( ">/dev/null 2>&1" );;

      if( 0 == system( command.c_str() ) )
      {
         report( SYSTEM, kFacilityString )
	    << iSinkName 
	    << " exists; are you sure you want to overwrite? (y/n*)" 
	    << endl;
	 string answer;
	 cin >> answer;
	 if( "n" == answer || "N" == answer )
	 {
	    goodSinkName = false;
	 }
	 else
	 {
	    goodSinkName = true;
	 }
      }
      else // fresh file name
      {
	 goodSinkName = true;
      }
   }

   return goodSinkName;
}

//
// const member functions
//

//
// static member functions
//

