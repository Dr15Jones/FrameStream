// -*- C++ -*-
//
// Package:     Processor
// Module:      MasterProcessor
// 
// Description: Main Processor in the system.
//
// Implementation: MainProcessor is implemented as singleton.
//              At each action stage (beginRun, etc.) it calls all actions
//              of all "active" "plugged-in" Processors.
//
// Author:       Martin  Lohner
// Created:     Tue Mar 18 15:53:40 EST 1997
// $Id: MasterProcessor.cc,v 1.65 2003/09/19 19:35:39 cdj Exp $
//
// Revision history (at end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h> // for exit
#include <cassert>

// user include files
#include "Experiment/report.h"
#include "Processor/MasterProcessor.h"
#include "Processor/ProcessorCommand.h"
#include "DataHandler/Frame.h"
#include "DataHandler/StreamSet.h"

#include "CommandPattern/StringUtilities.h"

#include "DataDelivery/FrameDeliverer.h"

// globally visible symbol for debugging
#include "Processor/GloballyVisibleSymbols.h"

#include "DAException/DAExceptionStackNameEntry.h"

// STL classes
#include <vector>
#include <map>
//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.MasterProcessor";

typedef _processor_stream2actions_ ActionMap;

//
// static data member definitions
//

//
// constructors and destructor
//
MasterProcessor::MasterProcessor( FrameDeliverer& iFrameDeliverer )
   : MultiLoader< Processor >( "C3_SHLIB" ),
     Processor( "MasterProcessor" ),
     m_command( *new ProcessorCommand( "proc", this ) ),
     m_frameDeliverer( iFrameDeliverer )
{
}

// MasterProcessor::MasterProcessor( const MasterProcessor& )
// {
// }

MasterProcessor::~MasterProcessor()
{
   // need to unload here because of virtual finalize()
   MultiLoader< Processor >::unloadAll();

   delete &m_command;
}

//
// assignment operators
//
// const MasterProcessor& MasterProcessor::operator=( const MasterProcessor& )
// {
// }

//
// member functions
//
void
MasterProcessor::init( void )
{


   // call init for all selected producers
   _loader_loaded_::const_iterator end( loaded().end() );
   for( _loader_loaded_::const_iterator iter = loaded().begin();
        iter != end;
        ++iter )
   {
      Processor* processor = fetch( *iter );

      // only call init if needed
      if( true == processor->callInit() )       // only after parameter change
      {
	 processor->init();
	 processor->setCallInit( false );
	 processor->setCallTerminate( true );
      }
   }
}

void
MasterProcessor::terminate( void )
{
   // call terminate for all selected producers
   _loader_loaded_::const_iterator end( loaded().end() );
   for( _loader_loaded_::const_iterator iter = loaded().begin();
        iter != end;
        ++iter )
   {
      Processor* processor = fetch( *iter );

      // only call terminate if needed (after init)
      if(    true == processor->callInit()      // only after parameter change
          && true == processor->callTerminate() // only after init was run
	 )
      {
	 processor->terminate();
	 processor->setCallTerminate( false );
      }
   }
}

void
MasterProcessor::hist_book( HIHistoManager& histMng )
{
   // call hist_book method for all selected producers
   _loader_loaded_::const_iterator end( loaded().end() );
   for( _loader_loaded_::const_iterator iter = loaded().begin();
        iter != end;
        ++iter )
   {
      Processor* processor = fetch( *iter );

      // only call hist_book if needed (e.g. first time!)
      if( true == processor->callHistBook() )
      {
	 processor->setCallHistBook( false );
	 
	 // set proper subdirectory for given Processor
	 histMng.setDefaultDir( processor->name() );
	 
	 processor->hist_book( histMng );

// doesn't work; need better way via a HistogramManager wrapper
//	 // set back to default root directory
//	 histMng.setDefaultDir( histMng.rootDir()->name() );
      }
   }
}

void
MasterProcessor::registerProviders( DABoolean iForceReload )
{
   // call hist_book method for all selected producers
   _loader_loaded_::const_iterator end( loaded().end() );
   for( _loader_loaded_::const_iterator iter = loaded().begin();
        iter != end;
        ++iter )
   {
      Processor* processor = fetch( *iter );

      // only call registerProxies if needed (e.g. first time!)
      if( 0 != processor 
	  && true == processor->callRegisterProxies( iForceReload )
	  && true != processor->supplies().empty()
	 )
      {
	 // in case of force reload, have to wipe them out first
	 if( true == iForceReload ) 
	 {
	    FrameDeliverer::RemoveProviderStatus removeProviderStatus;
	    removeProviderStatus = m_frameDeliverer.removeProvider( *processor );
	    // since can't call "FrameDeliverer::contains", just ignore error
	    //if( FrameDeliverer::kRemoveProviderNoError != removeProviderStatus )
	    //{
	    //  report( ERROR, kFacilityString )
	    // << "Force-reload: Error removing Processor " 
	    // << processor->name() 
	    // << " from FrameDeliverer" 
	    // << std::endl;
	    //}
	 }

	 // register with FrameDeliverer, so that Processor can use "official"
	 // method of adding data
	 FrameDeliverer::AddProviderStatus addProviderStatus;
	 if( FrameDeliverer::kAddProviderNoError != 
	     ( addProviderStatus = m_frameDeliverer.addProvider( *processor ) ) )
	 {
	    report( ERROR, kFacilityString )
	       << "Error adding Processor " 
	       << processor->name() 
	       << " to FrameDeliverer" 
	       << std::endl;
	 }
      }
   }
}

ActionBase::ActionResult
MasterProcessor::executeActions( const Stream::Type& streamType, 
				 Frame& frame )
{
   ActionBase::ActionResult returnValue = ActionBase::kPassed;



   // check for ANY ACTION
   DABoolean anyAction = false;

   _loader_loaded_::const_iterator end( loaded().end() );
   for( _loader_loaded_::const_iterator iter = loaded().begin();
        iter != end;
        ++iter )
   {
      Processor* processor = fetch( *iter );

      // add processor name into the stack
      DAExceptionStackNameEntry stackNameEntry(processor->identifier());

      ActionBase::ActionResult status = processor->execute( streamType, frame );

      // check for ANY ACTION
      if( ActionBase::kNoAction != status )
      {
	 returnValue = status;
	 anyAction   = true;
      }

      // break execution path if any one action fails!
      if( ActionBase::kFailed == returnValue )
      {
	 report( DEBUG, kFacilityString ) 
	    << "ActionBase::kFailed" << std::endl;
	 break;
      }
      if( ActionBase::kError == returnValue )
      {
	 report( DEBUG, kFacilityString ) 
	    << "ActionBase::kError" << std::endl;
	 break;
      }
      if( ActionBase::kStopProcessLoop == returnValue )
      {
	 report( DEBUG, kFacilityString ) 
	    << "ActionBase::kStopProcessLoop" << std::endl;
	 break;
      }
   }

   // check for ANY ACTION
   if( false == anyAction )
   {
      returnValue = ActionBase::kNoAction;
   }
   
   return returnValue;
}

 
// ------------- overridden MultiLoader< Processor > method
void
MasterProcessor::initialize( const std::string& iName, Processor& iProcessor )
{
   // call globally visible symbol to make debugging easier
   procsel();
   
   // set name (important in case of shared Object module)
   iProcessor.setName( iName );
}

// ------------- overridden MultiLoader< Producer > method
void
MasterProcessor::initializeTag( const std::string& iTag, Processor& iProcessor )
{
   // call globally visible symbol to make debugging easier
   procsel();
      
   // set name (important in case of shared Object module)
   iProcessor.setProductionTag( iTag );

   addedProcessor.emit(iProcessor.name());
}
            
// ------------- overridden MultiLoader< Processor > method
void
MasterProcessor::finalize( const std::string& iName, Processor& iProcessor )
{
   // unregister Processor with FrameDeliverer
   FrameDeliverer::RemoveProviderStatus removeProviderStatus;
   if( true != iProcessor.supplies().empty()
       && FrameDeliverer::kRemoveProviderNoError != 
       ( removeProviderStatus 
	 = m_frameDeliverer.removeProvider( iProcessor )))
   {
      report( DEBUG, kFacilityString )
	 << "Removing Processor/Provider " << iName
	 << " from FrameDeliverer failed; it had not been registered yet" << std::endl;
   }
   
   // call terminate before lifetime ends
   // only call terminate if needed (after init was run)
   if( false == iProcessor.callInit() )
   {
      iProcessor.terminate();
   }

   removingProcessor.emit(iName);
}

DABoolean 
MasterProcessor::canUnload(const std::string& iName, Processor&)
{
   DABoolean returnValue = true;
   requestToRemoveProcessor.emit(iName,returnValue);
   if(!returnValue) {
      report(SYSTEM,kFacilityString) <<"Processor "<<iName<<" is being used so can not be removed at this time.\n  First remove any path or filter that contains "<<iName<<std::endl;
   }
   return returnValue;
}

//
// const member functions
//
const StreamSet
MasterProcessor::streamsToBeActivated() const
{
   StreamSet streams;

   // Algorithm
   // loop over all processors
   //    loop over all actions per processor
   //        add stream bound to action to StreamSet
   _loader_loaded_::const_iterator end( loaded().end() );
   for( _loader_loaded_::const_iterator iter = loaded().begin();
        iter != end;
        ++iter )
   {
      const Processor* processor = fetch( *iter );

      const ActionMap& actionMap = processor->actions();

      ActionMap::const_iterator endAct = actionMap.end();
      for( ActionMap::const_iterator actIt = actionMap.begin();
	   actIt != endAct;
	   ++actIt )
      {
	 Processor::ActionInfo actionInfo = (*actIt).second;
	 if( true == actionInfo.shouldUse() )
	 {
	    streams.insert( (*actIt).first );
	 }
      }
   }

   return streams;
}

std::vector<std::string>
MasterProcessor::loadedNames() const
{
   std::vector<std::string> returnValue;
   for(_loader_loaded_map_::const_iterator itLoaded = loadedMap().begin();
       itLoaded != loadedMap().end();
       ++itLoaded ) {
      returnValue.push_back( (*itLoaded).first );
   }
   return returnValue;
}

// ------------- overridden MultiLoader< Processor > method
std::string
MasterProcessor::makeErrorMesg( const std::string& iName ) const
{
   std::string returnValue = std::string( "Cannot make processor; are you sure " )
      + iName + std::string( " is a processor?" );
   return returnValue;
}

//
// static member functions
//

// -------------------------------------------------------------------
// Revision history
//
// $Log: MasterProcessor.cc,v $
// Revision 1.65  2003/09/19 19:35:39  cdj
// added signals to communicate what Processors are available
//
// Revision 1.64  2003/04/25 15:28:30  vk
// Add entry to DAExceptionStack while executeActions
//
// Revision 1.63  2003/03/14 20:10:37  vk
// Adjust Processor classes wrt to Loader/MultiLoader
//
// Revision 1.62  2000/12/04 04:46:56  cdj
// removed unused includes of SharedObjectHandler.h
//
// Revision 1.61  2000/09/27 20:40:31  mkl
// print out in debug mode what type of failure of process path (ActionBase::kFailed/kError/kStopProcessLoop
//
// Revision 1.60  2000/02/29 17:44:21  mkl
// change EMERGENCY to DEBUG report level for unloading provider error messages
//
// Revision 1.59  2000/01/24 19:24:04  mkl
// MasterProc/ducer: only register provider if it has supplies
//
// Revision 1.58  2000/01/24 17:02:27  mkl
// MasterProcessor/Producer: ignore FrameDeliverer error when trying force-reload (and therefore remove) a non-existing provider, since have no 'FrameDeliverer::contains' method
//
// Revision 1.57  2000/01/19 16:52:46  mkl
// force reload of proxies after new source is added
//
// Revision 1.56  1999/10/07 17:45:28  mkl
// setDefaultDir per processor/producer based on name
//
// Revision 1.55  1999/09/14 18:37:28  mkl
// print better message when loading processor as producer
//
// Revision 1.54  1999/09/06 22:21:30  mkl
// move to new histogramming interface
//
// Revision 1.53  1999/03/15 18:44:24  mkl
// ActionCommand allows to list and en/disable actions at runtime
//
// Revision 1.52  1999/03/14 22:23:40  mkl
// fixed bug in execution loop (anything but kPassed stopped event loop); get rid of void in function declaration/definion
//
// Revision 1.51  1998/11/19 21:42:12  mkl
// reshuffled dtors to see if it helps Brian
//
// Revision 1.50  1998/11/12 02:25:17  mkl
// minor cleanup
//
// Revision 1.49  1998/11/10 03:52:31  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.48  1998/11/09 21:25:16  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.47  1998/11/09 19:34:40  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.45  1998/09/08 19:37:56  mkl
// rename overloaded virtual function (renaming was in order anyways)
//
// Revision 1.44  1998/07/21 16:23:22  mkl
// register producer proxies AFTER source proxies; new ActionResult::kStopProcessLoop
//
// Revision 1.43  1998/06/29 14:53:59  mkl
// moved global symbols procsel/prodsel to just after creating proc/ducer
//
// Revision 1.42  1998/06/23 23:00:59  mkl
// cleanup of LoadableInterface
//
// Revision 1.41  1998/06/17 18:16:44  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.39  1998/05/19 20:27:05  mkl
// bug fix: dont terminate processing path for ActionBase::NoAction
//
// Revision 1.38  1998/04/20 19:25:25  mkl
// fix static linking of producers
//
// Revision 1.37  1998/04/07 17:23:38  mkl
// fix for memory corruption at deactivation of proc/ducers
//
// Revision 1.36  1998/03/27 15:26:55  mkl
// more naming fixups
//
// Revision 1.35  1998/03/11 19:04:39  mkl
// proper calling of init/terminate (e.g. for Parameter changes)
//
// Revision 1.34  1998/02/03 22:11:23  mkl
// moved over to new Processor::execute functions in executeActions()
//
// Revision 1.33  1998/02/03 02:16:38  mkl
// get rid of dependency code
//
// Revision 1.32  1998/01/26 21:07:13  mkl
// because cxx/g++ dont allow yet base/derived-return types for virtual functions, had to kludge make factories
//
// Revision 1.31  1998/01/23 05:11:00  mkl
// beautification of printout in activation/selection process
//
// Revision 1.30  1998/01/20 04:55:03  mkl
// had to updated procSel to procsel; simiarly for prodSel
//
// Revision 1.29  1998/01/16 23:33:15  mkl
// added MasterProducer for selecting Producers at run time
//
// Revision 1.28  1997/11/24 18:32:51  mkl
// minor change in printout
//
// Revision 1.27  1997/10/15 02:17:30  mkl
// handle factory name properly for debug mode
//
// Revision 1.26  1997/10/07 19:24:46  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.25  1997/10/07 04:15:32  mkl
// replaced HbookManager by HIHistoManager
//
// Revision 1.24  1997/10/02 22:37:52  mkl
// New StringUtil functions
//
// Revision 1.23  1997/09/18 21:29:01  cdj
// changed Boolean to DABoolean
//
// Revision 1.22  1997/09/10 07:20:35  mkl
// bug fix in executeActions: didn't supply default for anyActionForThisStop
//
// Revision 1.21  1997/09/10 01:45:55  mkl
// rearranged timing of init and terminate calls
//
// Revision 1.20  1997/09/05 22:33:52  mkl
// moved init/terminate to Producer; implemented hist_book routine
//
// Revision 1.19  1997/09/04 06:34:23  mkl
// bug fix in MasterProcessor::clearProcessors
//
// Revision 1.18  1997/09/03 05:58:10  mkl
// moved from 'const string kFacilityString' to 'static const char* const'
//
// Revision 1.17  1997/09/03 02:43:36  mkl
// restructuring suez libraries
//
// Revision 1.16  1997/08/29 04:19:32  mkl
// bug flag name change
//
// Revision 1.15  1997/08/20 06:24:29  mkl
// fixed deleting iterator problem
//
// Revision 1.14  1997/08/12 22:20:50  mkl
// added method to return streams bound to actions
//
// Revision 1.13  1997/07/22 05:21:01  mkl
// use factory method for statically linked processors
//
// Revision 1.12  1997/07/11 05:59:22  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.11  1997/07/02 01:42:21  mkl
// fixes to allow CXX version 5.4
//
// Revision 1.10  1997/07/01 03:16:54  mkl
// moved typedef map statements to .cc files
//
// Revision 1.9  1997/06/17 20:27:50  mkl
// allow multiple actions per stream
//
// Revision 1.8  1997/06/14 03:52:50  mkl
// replaced static function calls with pointers to member functions
//
// Revision 1.7  1997/06/06 06:19:29  mkl
// fix of leak
//
// Revision 1.6  1997/06/04 05:24:10  mkl
// misc
//
// Revision 1.5  1997/06/03 18:40:10  mkl
// allow any stream to have actions
//
// Revision 1.4  1997/05/28 21:49:56  mkl
// beautifications
//
// Revision 1.3  1997/05/26 20:06:09  mkl
// operator != problem
//
// Revision 1.2  1997/05/24 18:32:28  cdj
// Changed Stream::TypeLess to less< Stream::Type >
//
// Revision 1.1.1.1  1997/05/23 20:18:00  mkl
// imported processor sources
//
// Revision 1.4  1997/05/15 17:41:38  mkl
// MasterProcessor now contains a SharedObjectHandler. Added "processor
// reorder" command.
//
// Revision 1.3  1997/05/14 17:14:55  mkl
// added capability to load/unload shared objects.
//
// Revision 1.2  1997/05/03 19:59:25  mkl
// NewDataDeliveryInterfaces
//
// Revision 1.1  1997/03/27 06:53:04  mkl
// imported sources.
//
