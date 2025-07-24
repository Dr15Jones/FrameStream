// -*- C++ -*-
//
// Package:     Processor
// Module:      MasterProducer
// 
// Description: Main Producer in the system.
//
// Implementation: 
//
// Author:      Martin  Lohner
// Created:     Thu Jan 15 15:53:40 EST 1998
// $Id: MasterProducer.cc,v 1.27 2003/03/14 20:10:37 vk Exp $
//
// Revision history (at end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h> // for exit
#include <cassert>
#include <string>

// user include files
#include "Experiment/report.h"
#include "Processor/MasterProducer.h"
#include "Processor/ProducerCommand.h"
#include "CommandPattern/StringUtilities.h"
#include "DataDelivery/FrameDeliverer.h"
#include "Processor/GloballyVisibleSymbols.h"

// STL classes
#include <vector>
#include <map>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.MasterProducer";

//
// static data member definitions
//

//
// constructors and destructor
//
MasterProducer::MasterProducer( FrameDeliverer& iFrameDeliverer )
   : MultiLoader< Producer >( "C3_SHLIB" ), 
     Producer( "MasterProducer" ),
     m_command( *new ProducerCommand( "prod", this ) ),
     m_frameDeliverer( iFrameDeliverer )
{
}

// MasterProducer::MasterProducer( const MasterProducer& )
// {
// }

MasterProducer::~MasterProducer()
{
   // need to unload here because of virtual finalize()
   MultiLoader< Producer >::unloadAll();

   delete &m_command;
}

//
// assignment operators
//
// const MasterProducer& MasterProducer::operator=( const MasterProducer& )
// {
// }

//
// member functions
//
void
MasterProducer::init( void )
{
   // call init for all selected producers
   _loader_loaded_::const_iterator end( loaded().end() );
   for( _loader_loaded_::const_iterator iter = loaded().begin();
        iter != end;
        ++iter )
   {
      Producer* producer = fetch( *iter );

      // only call init if needed
      if( true == producer->callInit() )       // only after parameter change
      {
	 producer->init();
	 producer->setCallInit( false );
	 producer->setCallTerminate( true );
      }
   }
}

void
MasterProducer::terminate( void )
{
   // call terminate for all selected producers
   _loader_loaded_::const_iterator end( loaded().end() );
   for( _loader_loaded_::const_iterator iter = loaded().begin();
        iter != end;
        ++iter )
   {
      Producer* producer = fetch( *iter );

      // only call terminate if needed (after init)
      if(    true == producer->callInit()      // only after parameter change
          && true == producer->callTerminate() // only after init was run
	 )
      {
	 producer->terminate();
	 producer->setCallTerminate( false );
      }
   }
}

void
MasterProducer::hist_book( HIHistoManager& histMng )
{
   // call hist_book method for all selected producers
   _loader_loaded_::const_iterator end( loaded().end() );
   for( _loader_loaded_::const_iterator iter = loaded().begin();
        iter != end;
        ++iter )
   {
      Producer* producer = fetch( *iter );

      // only call hist_book if needed (e.g. first time!)
      if( true == producer->callHistBook() )
      {
	 producer->setCallHistBook( false );

	 // set proper subdirectory for given Processor
	 histMng.setDefaultDir( producer->name() );
	 
	 producer->hist_book( histMng );
      }
   }
}

void
MasterProducer::registerProviders( DABoolean iForceReload )
{
   // register all providers
   _loader_loaded_::const_iterator end( loaded().end() );
   for( _loader_loaded_::const_iterator iter = loaded().begin();
        iter != end;
        ++iter )
   {
      Producer* producer = fetch( *iter );

      // only call registerProxies if needed (e.g. first time!)
      if( 0 != producer 
	  && true == producer->callRegisterProxies( iForceReload )
	  && true != producer->supplies().empty() 
	 )
      {
	 // in case of force reload, have to wipe them out first
	 if( true == iForceReload ) 
	 {
	    FrameDeliverer::RemoveProviderStatus removeProviderStatus;
	    removeProviderStatus = m_frameDeliverer.removeProvider( *producer );
	    // since can't call "FrameDeliverer::contains", just ignore error
	    //if( FrameDeliverer::kRemoveProviderNoError != removeProviderStatus )
	    //{
	    //  report( ERROR, kFacilityString )
	    //  << "Force-reload: Error removing Producer " 
	    //  << producer->name() 
	    //  << " from FrameDeliverer" 
	    //  << std::endl;
	    //}
	 }

	 // register with FrameDeliverer, so that Producer can use "official"
	 // method of adding data
	 FrameDeliverer::AddProviderStatus addProviderStatus;
	 if( FrameDeliverer::kAddProviderNoError != 
	     ( addProviderStatus = m_frameDeliverer.addProvider( *producer ) ) )
	 {
	    report( ERROR, kFacilityString )
	       << "Error adding Producer " 
	       << producer->name() 
	       << " to FrameDeliverer" 
	       << std::endl;
	 }
      }
   }
}

// ------------- overridden MultiLoader< Producer > method
void
MasterProducer::initialize( const std::string& iName, Producer& iProducer )
{
   // call globally visible symbol to make debugging easier
   prodsel();

   // set name (important in case of shared Object module)
   iProducer.setName( iName );
}

// ------------- overridden MultiLoader< Producer > method
void
MasterProducer::initializeTag( const std::string& iTag, Producer& iProducer )
{
   // call globally visible symbol to make debugging easier
   prodsel();

   // set name (important in case of shared Object module)
   iProducer.setProductionTag( iTag );
}

// ------------- overridden MultiLoader< Producer > method
void
MasterProducer::finalize( const std::string& iName,  Producer& iProducer )
{
   // unregister Producer with FrameDeliverer
   FrameDeliverer::RemoveProviderStatus removeProviderStatus;
   if( true != iProducer.supplies().empty() 
       && FrameDeliverer::kRemoveProviderNoError != 
       ( removeProviderStatus 
	 = m_frameDeliverer.removeProvider( iProducer )))
   {
      report( DEBUG, kFacilityString )
	 << "Removing Processor/Provider " << iName
	 << " from FrameDeliverer failed; it had not been registered yet" << std::endl;
   }
   
   // call terminate before lifetime ends
   // only call terminate if needed (after init was run)
   if( false == iProducer.callInit() )
   {
      iProducer.terminate();
   }
   
}

//
// const member functions
//
// ------------- overridden MultiLoader< Producer > method
std::string
MasterProducer::makeErrorMesg( const std::string& iName ) const
{
   std::string returnValue = std::string( "Cannot make producer; are you sure " )
      + iName + std::string( " is a producer?" );
   return returnValue;
}

std::string
MasterProducer::loadingAsSuperClassMesg( const std::string& iName ) const
{
   std::string returnValue = std::string( "You're loading " ) 
      + iName + std::string( " as a Producer; make sure this is what you want!" );
   return returnValue;
}

//
// static member functions
//


// ------------------------------------------------------------------
// Revision history
//
// $Log: MasterProducer.cc,v $
// Revision 1.27  2003/03/14 20:10:37  vk
// Adjust Processor classes wrt to Loader/MultiLoader
//
// Revision 1.26  2000/02/29 17:44:22  mkl
// change EMERGENCY to DEBUG report level for unloading provider error messages
//
// Revision 1.25  2000/01/24 19:24:04  mkl
// MasterProc/ducer: only register provider if it has supplies
//
// Revision 1.24  2000/01/24 17:02:28  mkl
// MasterProcessor/Producer: ignore FrameDeliverer error when trying force-reload (and therefore remove) a non-existing provider, since have no 'FrameDeliverer::contains' method
//
// Revision 1.23  2000/01/19 16:52:46  mkl
// force reload of proxies after new source is added
//
// Revision 1.22  1999/10/07 17:45:30  mkl
// setDefaultDir per processor/producer based on name
//
// Revision 1.21  1999/09/14 18:37:29  mkl
// print better message when loading processor as producer
//
// Revision 1.20  1999/09/06 22:21:31  mkl
// move to new histogramming interface
//
// Revision 1.19  1998/11/19 21:42:13  mkl
// reshuffled dtors to see if it helps Brian
//
// Revision 1.18  1998/11/12 02:25:18  mkl
// minor cleanup
//
// Revision 1.17  1998/11/10 03:52:31  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.16  1998/11/09 21:25:16  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.15  1998/11/09 19:34:41  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.13  1998/09/08 19:37:56  mkl
// rename overloaded virtual function (renaming was in order anyways)
//
// Revision 1.12  1998/07/21 16:23:23  mkl
// register producer proxies AFTER source proxies; new ActionResult::kStopProcessLoop
//
// Revision 1.11  1998/06/29 14:53:58  mkl
// moved global symbols procsel/prodsel to just after creating proc/ducer
//
// Revision 1.10  1998/06/23 23:00:59  mkl
// cleanup of LoadableInterface
//
// Revision 1.9  1998/06/17 18:16:45  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.8  1998/04/20 19:25:26  mkl
// fix static linking of producers
//
// Revision 1.7  1998/04/07 17:23:39  mkl
// fix for memory corruption at deactivation of proc/ducers
//
// Revision 1.6  1998/03/27 15:26:56  mkl
// more naming fixups
//
// Revision 1.5  1998/03/11 19:04:40  mkl
// proper calling of init/terminate (e.g. for Parameter changes)
//
// Revision 1.4  1998/01/26 21:07:14  mkl
// because cxx/g++ dont allow yet base/derived-return types for virtual functions, had to kludge make factories
//
// Revision 1.3  1998/01/23 05:11:01  mkl
// beautification of printout in activation/selection process
//
// Revision 1.2  1998/01/20 04:55:04  mkl
// had to updated procSel to procsel; simiarly for prodSel
//
// Revision 1.1  1998/01/16 23:33:15  mkl
// added MasterProducer for selecting Producers at run time
//

