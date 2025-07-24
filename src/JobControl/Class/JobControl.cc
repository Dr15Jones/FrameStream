// -*- C++ -*-
//
// Package:     JobControl
// Module:      JobControl
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:       Martin  Lohner
// Created:     Tue Mar 18 15:48:55 EST 1997
// $Id: JobControl.cc,v 1.109 2003/11/21 20:09:15 cdj Exp $
//
// Revision history (end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <iostream>
#include <assert.h>
#include <stddef.h>

// user include files
#include "Experiment/report.h"

#include "JobControl/JobControl.h"

// DataDelivery 
#include "DataDelivery/DataSourceDescriptor.h"
#include "DataDelivery/FrameDeliverer.h"
#include "DataStorage/DataSinkDescriptor.h"
#include "DataStorage/FrameStorer.h"
#include "DataHandler/Frame.h"

#include "InteractiveDelivery/InteractiveSource.h"
#include "InteractiveDelivery/InteractiveSourceBinder.h"

// modules
#include "JobControl/SourceManager.h"
#include "JobControl/SinkManager.h"
#include "JobControl/SourceFormatMap.h"
#include "JobControl/SinkFormatMap.h"
#include "JobControl/FileModule.h"
#include "JobControl/SummaryModule.h"
#include "JobControl/BlankRecordModule.h"
#include "Processor/MasterProcessor.h"
#include "Processor/MasterProducer.h"
#include "ToolBox/HistogramPackage.h"
#include "DummyHistogram/DummyHistoManager.h"
#include "CommandPattern/DefaultModule.h"

#include "JobControl/PathModule.h"

// Utility
//#include "JobControl/AsyncInterrupt.h"
#include "CommandPattern/StringUtilities.h"
#include "DataHandler/FrameLogger.h"
#include "Signal/SIGINT_Handler.h"
#include "DAException/DAException.h"

// STL classes
#include <vector>
#include <map>
#include <set>
#include <map> // to define CPP macros

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.JobControl";

//
// static data member definitions
//
JobControl* JobControl::m_instance = 0;

//
// constructors and destructor
//
//JobControl::JobControl()
//{
//}
JobControl::JobControl()
   : LoaderModule( "JobControl", "JobControl" ),

     // ---------- datadelivery ----------------------
     m_frameDeliverer   ( *new FrameDeliverer   ),
     
     // -------------- "static" modules -------------------------------
     m_summaryM         ( *new SummaryModule ),
     m_sourceFM         ( *new SourceFormatMap ),
     m_sinkFM           ( *new SinkFormatMap ),
     m_sourceM          ( *new SourceManager( m_frameDeliverer ) ),
     m_sinkM            ( *new SinkManager  () ),
     m_producerM        ( *new MasterProducer ( m_frameDeliverer ) ),
     m_processorM       ( *new MasterProcessor( m_frameDeliverer ) ),

     m_pathM            ( *new PathModule(m_sinkM, m_processorM) ),

     m_defaultM         ( *new DefaultModule ),

     // ------------- Commands ----------------------------------------
     m_startCommand           ( "go", this ),
     m_nextStopsCommand       ( "nextstop", this ),
     m_skipCommand            ( "skip", this ),
     m_gotoCommand            ( "goto", this ),
     m_reprocessCommand       ( "reprocess", this ),
     m_parameterCommand       ( "param", this ),
     m_interactCommand        ( "inter", this ),
     m_exceptionControlCommand( "exception", this ),

     m_histoM( 0 ),
     m_defaultHistoM( 0 ),
     m_histoLockedIn( false ),

     // -------------- certain internal low-level parameters ------------
     m_alreadyAtStop( false ),
     m_continueEventLoopAfterException( false ),
     m_doDeleteSourceAtEnd( true )
{
   // --------- check for out-of-memory errors -----------------

   // ------ add modules ----------------
   // (Note: this gives up ownership of memory!)
   // "static" modules
   // ------ WARNING ---------
   // The order here IS IMPORTANT:
   // There is a build-in dependency, if it comes to who links
   // to whom. 
   // Processors are dependent on producers and source (format) libraries,
   // Producers are dependent on source (format) libraries.
   // Sink (format) libraries are dependent on source (format) libraries.
   // Make sure that the order added here is opposite from how they 
   // should be released!
   addModule( &m_summaryM );
   addModule( &m_sourceFM );
   addModule( &m_sinkFM );
   addModule( &m_sourceM );
   addModule( &m_sinkM   );
   addModule( &m_defaultM );

   // "other" modules: soon to be dloadable
   addModule( new FileModule( m_sourceFM, m_sinkFM,
			      m_sourceM,  m_sinkM ) );
   addModule( new BlankRecordModule( m_sourceM ) );

   addModule( &m_producerM, false ); // not owned 
   addModule( &m_processorM, false ); // not owned

   addModule( &m_pathM);
}

// JobControl::JobControl( const JobControl& )
// {
// }

JobControl::~JobControl()
{
   //get rid of the paths before we get rid of the processors
   removeModule(m_pathM.name());
   
   // ------- delete in reverse order ----------
   // delete processors and producers first to make sure that histograms
   // get written properly (e.g. in dtors)
   removeModule( m_processorM.name() );
   delete &m_processorM;
   removeModule( m_producerM.name() );
   delete &m_producerM;

   // only delete the default HistogramManager (if ever created); 
   // the *HistogramModules are responsible for their own.
   if ( 0 != m_defaultHistoM ) {
      delete m_defaultHistoM;
   }

   // delete modules
   clearModules();

   //delete &m_frameStorer;
   delete &m_frameDeliverer;
}

//
// assignment operators
//
// const JobControl& JobControl::operator=( const JobControl& )
// {
// }

//
// member functions
//

DABoolean
JobControl::eventLoop( StopCounter& iStopCounter ) 
{
   DABoolean returnValue = true;
   
   // setup signals and interrupt handler
   DABoolean callExit;
   static SIGINT_Handler handler( callExit=false );
   EventHandler* oldHandler = 
      SignalHandler::instance()->registerHandler( SignalHandler::kSigInt, 
						  &handler );

   // do all setup necessary
   if( false == ( returnValue=eventLoopSetup() ) ) return returnValue;

   // make sure that stopcounter's specially requested stops are all active
   returnValue = iStopCounter.checkAllStreamsToBeActive( 
      m_frameDeliverer.activeStreams() );
   if( false == returnValue ) return returnValue;

   // ------------ "event" loop
   // Now we can loop through all the events
   DABoolean isDone = false;
   while( !isDone ) 
   {
//      // check for user input
//      DABoolean stop = AsyncInterrupt::checkForUserInput();
//      if( true == stop ) break;
      // check flag set by interrupt handler
      if( true == handler.isStopRequested() ) {
	 handler.reset();
	 break;
      }

      // if we were given max number of events >0, count down!
      // but if the number is negative, process entire file
      if( 0 == iStopCounter() ) 
      {
	 isDone = true;
	 report( INFO, kFacilityString )
	    << "Reached end of requested number of stops." << std::endl;
	 break;
      }
	 
      // process next stop (we're either already there or need to go to next)
      Stream::Type stopType;
      if( true == m_alreadyAtStop ) {
	 // resynchronize Frame as a short cut for the real solution:
	 //   have FrameDeliverer check if Frame is up-to-date 
	 //   after producers were added
	 if( FrameDeliverer::kNextStopNoError!=m_frameDeliverer.resynchronize() ) {
	    report( ERROR, kFacilityString )
	       << "can't resynchronize properly after goto" << std::endl;
	    returnValue = false;
	    break;
	 }
	 stopType = m_frameDeliverer.currentStop();
	 m_alreadyAtStop = false;
      }
      else {
	 isDone = gotoNextStop( stopType,returnValue );
      }

      // -----------------------------------------------------------
	 // now do something at this stop
	 if( !isDone ) 
	 {
	    // count down requested number of stops
	    --iStopCounter( stopType ); 

	    // skip if requested
	    if( true == iStopCounter.skipThisStop( stopType ) ) continue;

	    // update counter
	    ++m_summaryM[ stopType ];
	 
	    // do process
	    DABoolean oShallSink=true;
	    DABoolean shallContinue = processStop();
	 
	    // problem?
	    if( false == shallContinue ) { break; }
	 
	 }
      // -----------------------------------------------------------

   }

   // revert interrupt handler back to default
   SignalHandler::instance()->registerHandler( SignalHandler::kSigInt, 
					       oldHandler );

   return returnValue;
}

DABoolean
JobControl::eventLoopSetup() 
{
   DABoolean returnValue = true;

   // The order of these steps is important!

   // ------------ sources and ...
   // feed DataSourceBinders to FrameDeliverer
   // (when there were new sources, all producers need to be forced to 
   //  register their proxies again!!!)
   DABoolean forceProxyReloadSinceNewSources;
   returnValue = m_sourceM.useSources( forceProxyReloadSinceNewSources );
   if( false == returnValue ) return returnValue;

   // ------------- processors/producers
   // hist_book of all newly selected producers/processors
   m_histoLockedIn = true;
   if( 0 == m_histoM ) {
      report( WARNING, kFacilityString )
	 << "no histogram manager selected! using default." << std::endl;

      if( 0 == m_defaultHistoM ) {
	 m_defaultHistoM = new DummyHistoManager();
      }
      
      m_histoM = m_defaultHistoM;
   }
   m_producerM.hist_book( *m_histoM );
   m_processorM.hist_book( *m_histoM );
   //NOTE: people's code depends on hist_book being called before init


   // MasterProcessor::terminate is now called:
   // 1.) at the end of a job
   //       --> done in MasterProcessor/ducer::deselect
   // 2.) before parameter changes to processors --> need to be here before 
   //      call to MasterProcessor/ducer::init
   m_processorM.terminate();
   m_producerM.terminate();

   // call init of all those producers/processors which
   // 1.) have been just selected (first time)
   // 2.) just had a parameter change
   m_processorM.init();
   m_producerM.init();

   // register proxies for all newly selected producers/processors
   m_producerM.registerProviders( forceProxyReloadSinceNewSources );
   m_processorM.registerProviders( forceProxyReloadSinceNewSources );

   // -------------- ... and sinks and active streams
   // feed DataSinkBinders to FrameStorer
   returnValue = m_pathM.processingPaths().initialize(m_frameDeliverer);
   if( false == returnValue ) return returnValue;

   // activate streams
   returnValue = m_sourceM.activateStreams( m_processorM, m_sinkM );
   if( false == returnValue ) return returnValue;
   
   return returnValue;
}

DABoolean
JobControl::goTo( int iRunNumber, int iEventNumber, const StreamType& iStream ) 
{
// this goTo function will goto a user-given run and event number
// AND PROCESS THAT STOP

   DABoolean returnValue = true;

   // get ahold of FrameDeliverer
   FrameDeliverer& FD = m_frameDeliverer;

   DABoolean isDone;

   // feed DataSourceBinders to FrameDeliverer 
   //    (in case that hasn't happened yet)
   DABoolean forceProxyReloadSinceNewSources;
   returnValue = m_sourceM.useSources( forceProxyReloadSinceNewSources );
   if( false == returnValue ) return returnValue;

   // Set up for interactive control:

   // already have user-requested run and event number as input parms

   // Save the list of presently active sources
   std::vector<DataSourceDescriptor> savedActiveSources = FD.activeSources();
   FD.removeAllActiveSources();

   // need to add InteractiveSource as only active source
   // It is important to set the right initial SyncValue
   // either from the currentFrame or reset to zero, if we just
   // opened a new active stream
   InteractiveSource intSource;
   
//   if( true = m_justOpenedNewActiveStream ) 
//   {
//      intSource.resetSyncValue( SyncValue( 0, 0, 0 ) );
//   } 
//   else
//   {
      intSource.resetSyncValue( FD.currentSyncValue() );
      intSource.setStream( iStream );
//   }
   InteractiveSourceBinder intBinder( &intSource );

   FrameDeliverer::AddSourceStatus iAddError;
   if( FrameDeliverer::kAddSourceNoError != 
       ( iAddError = FD.addSource( intBinder )))
   {
      report( EMERGENCY, kFacilityString )
	 << "Error adding InteractiveSource." << std::endl;
      returnValue=false;
   }
   else // successful addition of InteractiveSource
   {
      FrameDeliverer::AddActiveSourceStatus iActiveError;
      if( FrameDeliverer::kAddActiveSourceNoError != 
	  (iActiveError = FD.addActiveSource( intBinder)))
      {
	 report( EMERGENCY, kFacilityString )
	    << "Error making InteractiveSource an active source." << std::endl;
	 returnValue=false;
      }
      else // successfull activation of InteractiveSource
      {
	 
	 // give user-requested run and event number to InteractiveSource
	 if( false == 
	     intSource.setSyncValue( SyncValue( iRunNumber, iEventNumber ) ) )
	 {
	    report( EMERGENCY, kFacilityString )
	       << "Can't goto these run/event numbers!" << std::endl;
	    returnValue=false;
	 }
	 else // successful setting of run and event number
	 {
	    // do a "gotoNextStop"
	    Stream::Type streamType;
	    isDone = gotoNextStop( streamType,returnValue );

	    if( true == isDone )
	    {
	       report( EMERGENCY, kFacilityString )
		  << "Can't goto these run/event numbers!" << std::endl;
	       returnValue=false;
	    }	       
	 }
	 
	 // remove InteractiveSourceController as the Active Source
	 FD.removeAllActiveSources();
      }
      
      // remove InteractiveSourceController as Source
      FD.removeSource( intBinder );
   }
   
   // restore all the old active sources saved in step 1.)
   std::vector<DataSourceDescriptor>::const_iterator lastSavedActiveSource 
      = savedActiveSources.end();
   for( std::vector<DataSourceDescriptor>::const_iterator savedActiveSource
	   = savedActiveSources.begin();
	savedActiveSource != lastSavedActiveSource;
	++savedActiveSource )
   {
      FD.addActiveSource( *savedActiveSource );
   }
   
   if( true == returnValue && !isDone )
   {
      // need to prepare the event loop
      m_alreadyAtStop = true;
   }

   return returnValue;
}

DABoolean
JobControl::gotoNextStop( Stream::Type& oCurrentStop, DABoolean& oNoError )
{
   oNoError = true;
   //report( INFO, kFacilityString ) << "gotoNextStop()" << std::endl;

   // break condition
   DABoolean isDone = false;

   // get ahold of FrameDeliverer
   FrameDeliverer& FD = m_frameDeliverer;

   // Tell FrameDeliverer to goto the next stop, which in our case
   // is a new event.
   FrameDeliverer::NextStopStatus nextStopStatus;
   nextStopStatus = FD.gotoNextStop();

   oCurrentStop = FD.currentStop();
//   if( Stream::kNone == currentStop ) 
//   {  // No more events, should stop looping
//      isDone = true;

   // Now check nextStopStatus to determine exactly what happened
   switch( nextStopStatus )
   {
      // reached end of a passive source; need to replenish from SourceManager
      case FrameDeliverer::kNextStopReachedEndOfAPassiveSource:
      {
	 //report( ERROR, kFacilityString )
	 //   << "FrameDeliverer::kNextStopReachedEndOfAPassiveSource" << std::endl;
	 report( WARNING, kFacilityString )
	    << "Reached end of a passive source" << std::endl;
	 
	 // warn user that the last record might be OLD!
	 report( WARNING, kFacilityString ) 
	    << "Record in passive source might be old!" << std::endl;

	 // don't delete source-at-end; give warning but continue!
	 isDone = false;

	 break;
      }
	 
      case FrameDeliverer::kNextStopReachedEndOfAnActiveSource:
      {
	 //report( ERROR, kFacilityString )
	 //   << "FrameDeliverer::kNextStopReachedEndOfAnActiveSource" << std::endl;
	 report( INFO, kFacilityString )
	    << "Reached end of an active source" << std::endl;
	 
	 deleteSourceAtEnd();

	 // need to supply next DataSourceBinder in active chain
	 
	 // stop just in case
	 isDone = true;

	 break;
      }
      
      case FrameDeliverer::kNextStopNoActiveStreams:
      {
	 report( ERROR, kFacilityString )
	    //   << "FrameDeliverer::kNextStopNoActiveStreams" << std::endl;
	    << "No active stream defined!" << std::endl;

	 // stop just in case
	 isDone = true;
	 oNoError = false;

	 break;
      }

      case FrameDeliverer::kNextStopFailedToSyncAllSources:
      {
	 report( ERROR, kFacilityString )
	    << "FrameDeliverer::kNextStopFailedToSyncAllSources" << std::endl;

	 // stop just in case
	 isDone = true;
	 oNoError = false;

	 break;
      }

      case FrameDeliverer::kNextStopProblemWithASource:
      {
	 report( ERROR, kFacilityString )
	    << "FrameDeliverer::kNextStopProblemWithASource" << std::endl;

	 // stop just in case
	 isDone = true;
	 oNoError = false;

	 break;
      }
      
      case FrameDeliverer::kNextStopUnknownError:
      {
	 report( ERROR, kFacilityString )
	    << "FrameDeliverer::kNextStopUnknownError" << std::endl;

	 // stop just in case
	 isDone = true;
	 oNoError = false;

	 break;
      }

      default: // FrameDeliverer::kNextStopNoError
      {
	 isDone = false;

	 break;
      }
   } // switch over NextStopStatus

   return isDone;
}

DABoolean
JobControl::processStop()
{
   return m_pathM.processingPaths().processStop( m_frameDeliverer.currentFrame(),m_continueEventLoopAfterException );

}


DABoolean
JobControl::deleteSourceAtEnd( void )
{
   DABoolean returnValue = false;

   if( doDeleteSourceAtEnd() ) {
      FrameDeliverer& FD = m_frameDeliverer;
      
      //make sure to get rid of all sources that have ended
      DABoolean moreToCheck = true;
      while( moreToCheck ) {
	 // find source-at-end and delete
	 FrameDeliverer::StatusOfSources statusOfSources = 
	    FD.statusOfSources();
	 FrameDeliverer::StatusOfSources::iterator which 
	    = statusOfSources.find( FrameDeliverer::kSourceReachedEnd ); 
	 if( statusOfSources.end() != which )
	 {
	    DataSourceDescriptor DSD = (*which).second;
	    SourceManager::Token token = m_sourceM.findTokenFor( DSD );
	 //report( INFO ) 
	 //    << "Will remove source-at-end \"" << token << "\"" << std::endl;
	    m_sourceM.list( token ); // more verbose output
	    m_sourceM.removeSourceInUse( token );
	    
	    returnValue = true;
	 } else {
	    //no more sources are at end
	    moreToCheck = false;
	 }
      }
      if( !returnValue ) 
      {
	 report( ERROR, kFacilityString ) 
	    << "Can't find Source-at-end to be deleted!" << std::endl;
      }
   }
   return returnValue;
}

// --------------- frame-related ---------------------------------
FrameDeliverer&
JobControl::frameDeliverer()
{
   return m_frameDeliverer;
}

void 
JobControl::initLogger( FrameLogger& iLogger )
{
   // notify FrameLogger that Frame is available
   iLogger.setFrame( &(m_frameDeliverer.currentFrame()) );
}

void
JobControl::finalizeLogger( FrameLogger& iLogger )
{
   // notify FrameLogger that Frame is unavailable
   iLogger.unSetFrame( &(m_frameDeliverer.currentFrame()) );
}

// --------------------- modules ---------------------------------
MasterProcessor&
JobControl::masterProcessor()
{
   return m_processorM;
}
 
MasterProducer&
JobControl::masterProducer()
{
   return m_producerM;
}

SourceManager&
JobControl::sourceManager()
{
   return m_sourceM;
}
 
SinkManager&
JobControl::sinkManager()
{
   return m_sinkM;
}
 
SourceFormatMap&
JobControl::sourceFormats()
{
   return m_sourceFM;
}
 
SinkFormatMap&
JobControl::sinkFormats()
{
   return m_sinkFM;
}

DefaultModule&
JobControl::defaultModule()
{
   return m_defaultM;
}

void
JobControl::setHistogramManager( HIHistoManager* iHistoM )
{
   if( true == m_histoLockedIn && iHistoM != 0 ) {
      report( ERROR, kFacilityString )
	 << "histogram manager has already been locked in!" << std::endl;
   } else {
      m_histoM = iHistoM;
   }
}

void
JobControl::setContinueEventLoopAfterException( DABoolean iFlag )
{
   m_continueEventLoopAfterException = iFlag;
}

void
JobControl::setDoDeleteSourceAtEnd( DABoolean iFlag )
{
   m_doDeleteSourceAtEnd = iFlag;
}

HIHistoManager*
JobControl::histogramManagerP()
{
   return m_histoM;
}

//
// const member functions
//
const FrameDeliverer&
JobControl::frameDeliverer() const
{
   return m_frameDeliverer;
}
 
// --------------------- modules ---------------------------------
const MasterProcessor&
JobControl::masterProcessor() const
{
   return m_processorM;
}
 
const MasterProducer&
JobControl::masterProducer() const
{
   return m_producerM;
}
 
const SourceManager&
JobControl::sourceManager() const
{
   return m_sourceM;
}
 
const SinkManager&
JobControl::sinkManager() const
{
   return m_sinkM;
}
 
const SourceFormatMap&
JobControl::sourceFormats() const
{
   return m_sourceFM;
}
 
const SinkFormatMap&
JobControl::sinkFormats() const
{
   return m_sinkFM;
}
 
const DefaultModule&
JobControl::defaultModule() const
{
   return m_defaultM;
}

const HIHistoManager*
JobControl::histogramManagerP() const
{
   return m_histoM;
}

DABoolean
JobControl::isHistogramManagerLocked() const
{
   return m_histoLockedIn;
}

DABoolean
JobControl::continueEventLoopAfterException() const
{
   return m_continueEventLoopAfterException;
}

//
// static member functions
//
JobControl*
JobControl::instance()
{
   if( 0 == m_instance ) 
   {
      m_instance = new JobControl();
   }

   return m_instance;
}

void
JobControl::destroy()
{
   if( 0 != m_instance )
   {
      delete m_instance;
      m_instance = 0;
   }
   else
   {
      report( EMERGENCY, kFacilityString )
	 << "JobControl::m_instance == 0" << std::endl;
      assert( false );
      ::exit( 1 );
   }
}

// -------------------------------------------------------
// History:
//
// $Log: JobControl.cc,v $
// Revision 1.109  2003/11/21 20:09:15  cdj
// goto command now takes an optional argument that sets the Record type (default is event if event#> 0 else beginrun)
//
// Revision 1.108  2003/09/19 21:20:32  cdj
// changes needed for Path implementation
//
// Revision 1.107  2003/05/14 16:07:33  vk
// Add flush to have output when exception caught
//
// Revision 1.106  2003/04/25 15:40:00  vk
// When exception thrown printout DAExceptionStack
//
// Revision 1.105  2002/08/16 15:07:02  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.104  2001/12/18 21:51:45  cdj
// go command now returns a TCL ERROR if something went wrong
//
// Revision 1.103  2000/12/02 19:30:01  cdj
// Bug Fixes
// -ask SourceManager to find Token corresponding to a DataSourceDescriptor
//  (previously could remove the wrong source-at-end if multiple sources
//   shared the same base Token name)
// -now removes all sources that have reached their end
//
// Revision 1.102  2000/08/08 22:15:48  mkl
// resynchronize Frame explicitly after goto (if new producers were added); real solution: have FrameDeliverer check for change in setup and resynchronize if necessary
//
// Revision 1.101  2000/07/21 21:57:45  cdj
// changed back to calling hist_book before init
//
// Revision 1.100  2000/07/20 22:46:46  mkl
// fix wrongly-placed curly bracket which only showed up in debug mode
//
// Revision 1.99  2000/07/18 18:39:30  mkl
// reorder init/terminate vs proxy registration and histogram setup
//
// Revision 1.98  2000/06/06 23:43:32  mkl
// only catch exceptions in non-debug mode
//
// Revision 1.97  2000/03/17 15:38:54  cdj
// Can now set whether sources are deleted when they reach their end.  Needed for FrameIterate
//
// Revision 1.96  2000/03/16 22:52:22  mkl
// when delete modules in JobControl::dtor, first remove from CompositeModule
//
// Revision 1.95  2000/03/01 00:08:52  mkl
// control if should continue event loop in case of DataAccess Exceptions: exception command
//
// Revision 1.94  2000/02/29 17:53:51  mkl
// change skip and goto commands to properly work as expected: skip won't write nor process; goto and subsequent go will properly process the run/event in question
//
// Revision 1.93  2000/01/19 16:53:12  mkl
// force reload of proxies after new source is added
//
// Revision 1.92  2000/01/17 21:30:17  mkl
// StopCounter: have to check for active streams as precaution AFTER streams are activated
//
// Revision 1.91  1999/12/21 20:35:28  mkl
// added SIGINTHandler::reset method
//
// Revision 1.90  1999/12/15 20:28:53  mkl
// delete processors/producers before histogram module
//
// Revision 1.89  1999/12/06 21:48:39  mkl
// allow writing streams to be a true subset of active streams
//
// Revision 1.88  1999/11/11 05:08:01  mkl
// report back about failing sinking (not a bug)
//
// Revision 1.87  1999/09/06 22:20:08  mkl
// move to new histogramming interface
//
// Revision 1.86  1999/08/26 03:45:58  mkl
// ctrl-c signal: give option to completely exit out of suez (the fast way) or just stop the event loop
//
// Revision 1.85  1999/08/25 21:23:19  mkl
// ReportModule allows setting of report level and logging to files
//
// Revision 1.84  1999/07/09 23:09:21  mkl
// turn on debug message only in debug mode
//
// Revision 1.83  1999/07/01 20:49:04  mkl
// stop 'stop' loop if experiencing write problems
//
// Revision 1.82  1999/06/04 18:05:46  mkl
// fix up processStop() function to allow skimming
//
// Revision 1.81.2.2  1999/05/28 21:44:32  billm
// Fixed a ptr bug and removed useless HistogramManager files.
//
// Revision 1.81.2.1  1999/05/21 04:18:26  billm
// Now compatible with new histo interface.
//
// Revision 1.81  1999/05/02 02:44:06  mkl
// use new Signal library
//
// Revision 1.80  1999/03/16 00:40:02  mkl
// only warn about 'no action for this stop' at debug report level
//
// Revision 1.79  1999/03/15 19:14:16  mkl
// InteractCommand
//
// Revision 1.78  1999/03/11 22:02:39  mkl
// source out stream will activate stream; turn off superfluous warning for 'param' command
//
// Revision 1.77  1999/02/22 23:41:37  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.76  1999/01/27 22:55:25  mkl
// rewrote StringUtil utility functions
//
// Revision 1.75  1998/11/21 05:09:05  mkl
// this is scary: order of library destruction matters on solaris: first delete all processors, then all producers, then source formats etc
//
// Revision 1.74  1998/11/20 07:11:28  mkl
// HistogramModule now dynamically loaded
//
// Revision 1.73  1998/11/10 19:55:04  mkl
// bug fix: delete source/sink-formats before source/sink-manager
//
// Revision 1.72  1998/11/09 19:33:09  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.71  1998/10/01 14:40:59  mkl
// delayed stream activation until after calling init on Proc/ducers
//
// Revision 1.70  1998/09/22 17:07:04  mkl
// moved FrameLogger to DataHandler library
//
// Revision 1.69  1998/09/22 15:48:40  mkl
// use bkh's new FrameLogger
//
// Revision 1.68  1998/09/08 19:37:48  mkl
// rename overloaded virtual function (renaming was in order anyways)
//
// Revision 1.67  1998/07/31 19:23:20  mkl
// handle nested interrupts
//
// Revision 1.66  1998/07/31 19:03:29  mkl
// installed ctrl-c interrupt handler in event loop
//
// Revision 1.65  1998/07/29 20:06:48  mkl
// new summary command implemented
//
// Revision 1.64  1998/07/28 22:13:45  mkl
// change StopCounter from pass-by-value to pass-by-ref in event loop
//
// Revision 1.63  1998/07/28 15:53:15  mkl
// ripple effect: needed to include set
//
// Revision 1.62  1998/07/27 23:31:33  mkl
// skip command: need to process streams with higher or equal priority (which are not included in skip set
//
// Revision 1.61  1998/07/25 16:10:26  mkl
// add static linking of sources/sinks
//
// Revision 1.60  1998/07/21 16:21:58  mkl
// added histogram closing; new ActionResult::kStopProcessLoop
//
// Revision 1.59  1998/07/13 22:22:17  mkl
// added skip command
//
// Revision 1.58  1998/07/01 23:16:44  mkl
// finalize histogram file before dtor
//
// Revision 1.57  1998/06/23 23:00:46  mkl
// cleanup of LoadableInterface
//
// Revision 1.56  1998/06/23 21:24:41  mkl
// reorder deletion of Modules in dtor
//
// Revision 1.55  1998/06/17 18:18:09  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.54  1998/05/12 20:00:14  mkl
// new histogram command: for now can only set filename
//
// Revision 1.53  1998/05/09 20:28:17  mkl
// get rid of NextStopsCommand
//
// Revision 1.52  1998/05/08 22:13:56  mkl
// deprecated nextstop in favor of fancier go command
//
// Revision 1.51  1998/04/14 17:46:39  mkl
// renamed emptySource command emptysource
//
// Revision 1.50  1998/04/13 20:16:56  mkl
// give reasonable error message when not able to goto run# event#
//
// Revision 1.49  1998/04/08 19:49:59  mkl
// renamed 'parm' to 'param'
//
// Revision 1.48  1998/04/01 19:44:51  mkl
// dont delete source-at-end; give warning, but continue
//
// Revision 1.47  1998/04/01 19:43:14  mkl
// added Chris' BlankRecordDelivery handling
//
// Revision 1.46  1998/03/28 20:16:02  mkl
// do implicit bind of Parameter/Command to Module
//
// Revision 1.45  1998/03/16 23:17:54  mkl
// use bind instead of commands().push_back()
//
// Revision 1.44  1998/03/15 01:45:54  mkl
// reordered commands (g++ complained about out-of-order)
//
// Revision 1.43  1998/03/13 03:55:45  mkl
// moved all commands from CommandLineInterface to JobControl where they belong
//
// Revision 1.42  1998/03/11 19:05:49  mkl
// proper calling of init/terminate (e.g. for Parameter changes)
//
// Revision 1.41  1998/02/03 21:29:32  mkl
// switch over to STLUtility library
//
// Revision 1.40  1998/01/23 05:09:33  mkl
// CompositeDelivery, RawData, and ProxyExample are now DL producers
//
// Revision 1.39  1998/01/22 05:02:35  mkl
// delete hardwired registration of RawData- and ProxyExample providers
//
// Revision 1.38  1998/01/16 23:34:30  mkl
// added MasterProducer for selecting Producers at run time
//
// Revision 1.37  1997/11/01 21:23:18  mkl
// added RawDataProvider
//
// Revision 1.36  1997/10/20 17:11:06  mkl
// fix for sink with unspecified streams
//
// Revision 1.35  1997/10/15 02:19:54  mkl
// FORWARD_DECLARATION_NOT_BOUND_TO_DEFINITION_BUG for g++
//
// Revision 1.34  1997/10/07 19:25:17  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.33  1997/10/07 04:19:02  mkl
// report --> cout for INFO messages
//
// Revision 1.32  1997/10/05 15:13:56  mkl
// New StringUtil methods
//
// Revision 1.31  1997/09/18 21:26:51  cdj
// changed Boolean to DABoolean
//
// Revision 1.30  1997/09/13 19:49:57  sjp
// Added CompositeProvider to system
//
// Revision 1.29  1997/09/10 01:52:05  mkl
// rearranged timing of init and terminate calls
//
// Revision 1.28  1997/09/05 22:35:25  mkl
// undid singleton patteron for MasterProcessor
//
// Revision 1.27  1997/09/05 02:37:19  mkl
// wrap asynchronous interrupt handling in wrapper class
//
// Revision 1.26  1997/09/03 05:57:44  mkl
// moved from 'const string kFacilityString' to 'static const char* const'
//
// Revision 1.25  1997/09/03 02:38:42  mkl
// restructuring suez libraries
//
// Revision 1.24  1997/08/29 23:30:49  mkl
// added in asynchronous interrupt
//
// Revision 1.23  1997/08/29 04:21:54  mkl
// simplify JobControl: remove FileInput/Output files, bug flag changes, handling of suffix .gz etc.
//
// Revision 1.22  1997/08/22 04:21:49  mkl
// standardize error messages from commands
//
// Revision 1.21  1997/08/20 06:23:35  mkl
// symmetrized sinks with sources in terms of user interface
//
// Revision 1.20  1997/08/19 04:24:15  mkl
// massage to get storage going
//
// Revision 1.19  1997/08/18 20:56:24  mkl
// restored storage code
//
// Revision 1.18  1997/08/14 21:08:45  mkl
// don't erase iterator and then use it!
//
// Revision 1.17  1997/08/13 07:10:45  mkl
// Chains of Sources, new activation of streams, and ProxyDict
//
// Revision 1.16  1997/08/08 05:21:02  mkl
// first attempt at chains-of-files
//
// Revision 1.15  1997/07/24 04:59:49  mkl
// adding chains of sources
//
// Revision 1.14  1997/07/22 05:19:31  mkl
// replaced data() back to c_str() for g++
//
// Revision 1.13  1997/07/11 06:55:35  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.12  1997/07/02 01:40:29  mkl
// fixes to allow CXX version 5.4
//
// Revision 1.11  1997/07/01 03:16:34  mkl
// moved typedef map statements to .cc files
//
// Revision 1.10  1997/06/23 19:50:29  mkl
// Checking for appropriate stop in ProcessStop
//
// Revision 1.9  1997/06/06 06:18:10  mkl
// handle --> execute and other minor stuff
//
// Revision 1.8  1997/06/04 05:23:42  mkl
// misc
//
// Revision 1.7  1997/06/03 18:40:52  mkl
// allow any stream to have actions
//
// Revision 1.6  1997/05/23 20:22:27  mkl
// separated Processor stuff from JobControl
//
// Revision 1.5  1997/05/06 20:26:58  mkl
// changes in goto due to changes in InteractiveSource
//
// Revision 1.4  1997/05/06 18:35:49  mkl
// added GotoCommand and ReprocessCommand
//
// Revision 1.3  1997/05/03 19:59:24  mkl
// NewDataDeliveryInterfaces
//
// Revision 1.2  1997/04/01 05:15:47  mkl
// better handling of missing active stream.
//
// Revision 1.1  1997/03/27 06:53:03  mkl
// imported sources.
//
