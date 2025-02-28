// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      ProcessingPaths
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Thu Jul 10 15:34:38 EDT 2003
// $Id: ProcessingPaths.cc,v 1.5 2004/01/09 18:48:39 cdj Exp $
//
// Revision history
//
// $Log: ProcessingPaths.cc,v $
// Revision 1.5  2004/01/09 18:48:39  cdj
// fix to path: needed to delay initialization of sinks until all sources and producers have been registered
//
// Revision 1.4  2003/11/21 14:41:13  cdj
// fixed bug where could not start processing if Proc was used directly in a Path instead of a Filter
//
// Revision 1.3  2003/09/24 18:08:18  cdj
// now properly compiles under debug option
//
// Revision 1.2  2003/09/22 19:38:05  cdj
// fixed bug when using default path and user adds procs, does go, then removes all procs and then adds new procs
//
// Revision 1.1  2003/09/19 21:26:45  cdj
// first submission of Path code
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#include <memory>
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "JobControl/ProcessingPaths.h"

#include "JobControl/SinkManager.h"
#include "DataStorage/DataSinkBinder.h"
#include "DataDelivery/FrameDeliverer.h"
#include "Processor/MasterProcessor.h"

#include "JobControl/FilterAnd.h"
#include "JobControl/FilterProc.h"
#include "JobControl/Path.h"

#include "DAException/DAExceptionStackNameEntry.h"

#include "DAException/DAExceptionBase.h"

using JobControlNS::Path;
using JobControlNS::FilterAnd;
using JobControlNS::FilterBase;
using JobControlNS::FilterProc;

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.ProcessingPaths" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: ProcessingPaths.cc,v 1.5 2004/01/09 18:48:39 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
ProcessingPaths::ProcessingPaths(SinkManager& iSM,
                                 MasterProcessor& iMP) :
m_sinkManager(&iSM),
m_masterProcessor(&iMP),
m_defaultFilter(0),
m_usingDefault( true ),
m_procsChanged(false),
m_sinksChanged(false)
{
   //attach our slots
   m_sinkManager->addedSink.attach(this, &ProcessingPaths::addSink);
   m_sinkManager->removingSink.attach(this, &ProcessingPaths::removeSink );
   m_sinkManager->removingSinkInUse.attach(this, &ProcessingPaths::removeSink );
   
   m_masterProcessor->addedProcessor.attach(this, &ProcessingPaths::addProcessor);
   m_masterProcessor->removingProcessor.attach(this, &ProcessingPaths::removeProcessor);
   m_masterProcessor->requestToRemoveProcessor.attach(this, &ProcessingPaths::processorNotBeingUsed);
}

// ProcessingPaths::ProcessingPaths( const ProcessingPaths& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

ProcessingPaths::~ProcessingPaths()
{
   for( STL_VECTOR(Path*)::iterator itPath = m_paths.begin();
        itPath != m_paths.end();
        ++itPath ) {
      delete (*itPath);
   }      
}

//
// assignment operators
//
// const ProcessingPaths& ProcessingPaths::operator=( const ProcessingPaths& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
DABoolean
ProcessingPaths::initialize(FrameDeliverer& iFD)
{
   DABoolean returnValue = true;

   if(m_usingDefault) {
      try {
         //doing this for the first time?
         if(m_paths.empty() ) {
            //Create the Filter
            auto_ptr<FilterAnd> defaultFilter( new FilterAnd("default") );
            
            for( STL_VECTOR(JobControlNS::Holder<FilterProc> )::iterator itFilter = m_filterProcs.begin();
                 itFilter != m_filterProcs.end();
                 ++itFilter ) {
               defaultFilter->add( (*itFilter).get() );
               //cout <<"added "<<(*itFilter)->processor()->name()<<endl;
            }
            
            const STL_VECTOR(string) sinkNames = m_sinkManager->unusedSinks();
            
            STL_VECTOR(DataSinkBinder*) binders;
            binders.reserve(sinkNames.size() );
            
            for( STL_VECTOR(string)::const_iterator itName = sinkNames.begin();
                 itName != sinkNames.end();
                 ++itName ) {
               DataSinkBinder* dsb = m_sinkManager->binderFor(*itName);
               
               
               // if no streams have been bound yet, use the active streams
               if( true == dsb->boundStreams().empty() )
               {
                  const StreamSet& activeStreams = iFD.activeStreams();
                  
                  // rebind sink with active streams
                  dsb->bindStreams( activeStreams );
               }
               
               binders.push_back(dsb);
            }
      
            //Create the path
            STL_VECTOR(Processor*) noProcessors;

            m_defaultFilter = defaultFilter.get();
            m_definedFilters.push_back( defaultFilter.release() );
            
            m_paths.push_back( new Path( "default",
                                         m_definedFilters.back().get(),
                                         noProcessors,
                                         binders ) );
            
	    if( returnValue ) {
               m_sinkManager->useSinks();
            } else {
               //m_frameStorer.removeAllSinks();
            }
         } else {
            //need to update the default path if there were changes
            if(m_procsChanged) {
               if(0 == m_defaultFilter) {
                  //Create the Filter
                  auto_ptr<FilterAnd> defaultFilter( new FilterAnd("default") );
                  
                  for( STL_VECTOR(JobControlNS::Holder<FilterProc> )::iterator itFilter = m_filterProcs.begin();
                       itFilter != m_filterProcs.end();
                       ++itFilter ) {
                     defaultFilter->add( (*itFilter).get() );
                     //cout <<"added "<<(*itFilter)->processor()->name()<<endl;
                  }
                  m_defaultFilter = defaultFilter.get();
                  m_definedFilters.push_back( defaultFilter.release() );
                  m_paths.front()->setFilter(m_defaultFilter);
               }
            }
            if(m_sinksChanged){
               //Add new sinks to default path
               const STL_VECTOR(string) sinkNames = m_sinkManager->unusedSinks();
               
               for( STL_VECTOR(string)::const_iterator itName = sinkNames.begin();
                    itName != sinkNames.end();
                    ++itName ) {
                  DataSinkBinder* dsb = m_sinkManager->binderFor(*itName);
                  
                  
                  // if no streams have been bound yet, use the active streams
                  if( true == dsb->boundStreams().empty() )
                  {
                     const StreamSet& activeStreams = iFD.activeStreams();
                     
                     // rebind sink with active streams
                     dsb->bindStreams( activeStreams );
                  }
                  m_paths.front()->addSink(*dsb);
               }
               m_sinkManager->useSinks();
            }
         }
      } catch( const DAExceptionBase& ) {
         returnValue = false;
      }
      m_procsChanged=false;
      m_sinksChanged=false;
   } else {
      DABoolean properlyConfigured = true;
      //check to make sure all filters, processors, and sinks are being used
      for( STL_VECTOR(JobControlNS::Holder<JobControlNS::FilterBase> )::iterator itFilter = m_definedFilters.begin();
           itFilter != m_definedFilters.end();
           ++itFilter ) {
         DABoolean used = false;
         //is this used in a path?
         for(STL_VECTOR(JobControlNS::Path*)::iterator itPath = m_paths.begin();
             itPath != m_paths.end();
             ++itPath) {
            if( (*itPath)->filter() == (*itFilter).get() ) {
               used=true;
               break;
            }
	    if( (*itPath)->filter()->contains( (*itFilter).get() ) ) {
	       used = true;
	       break;
	    }
         }
         if(!used) {
            //is this used by another filter? (Since filters must be defined before they can be used by other
            // filters it means that only filters later in the list could use this filter)
	    //or it can be used by an unnamed filter created for a Path
            for(STL_VECTOR(JobControlNS::Holder<JobControlNS::FilterBase> )::iterator itFilter2 = itFilter+1;
                itFilter2 != m_definedFilters.end();
                ++itFilter2){
               if( (*itFilter2)->contains( (*itFilter).get() ) ) {
                  used = true;
                  break;
               }
            }
            if(!used) {
	       //is it used in a Path?
	       for(STL_VECTOR(JobControlNS::Path*)::iterator itPath = m_paths.begin();
		   itPath != m_paths.end();
		   ++itPath) {
		  if( (*itPath)->filter()->contains( (*itFilter).get() ) ) {
		     used=true;
		     break;
		  }
	       }
	    } 
	    if( !used) {
               report(SYSTEM,kFacilityString) <<"The filter "<<(*itFilter)->name()<<" is not being used"<<endl;
               properlyConfigured = false;
            }
         }
      }
      //Processors
      for(STL_VECTOR(JobControlNS::Holder<JobControlNS::FilterProc> )::iterator itFProc = m_filterProcs.begin();
          itFProc != m_filterProcs.end();
          ++itFProc ) {
         DABoolean used = false;
         for( STL_VECTOR(JobControlNS::Holder<JobControlNS::FilterBase> )::iterator itFilter = 
              m_definedFilters.begin();
              itFilter != m_definedFilters.end();
              ++itFilter ) {
            if( (*itFilter)->contains( (*itFProc).get()) ) {
               used = true;
               break;
            }
         }
         if( !used ) {
	    //see if it is in a Path
	    for(STL_VECTOR(JobControlNS::Path*)::iterator itPath = m_paths.begin();
		itPath != m_paths.end();
		++itPath) {
	       //is it in the filter?
	       if( (*itPath)->filter()->contains( (*itFProc).get() ) ) {
		  used=true;
		  break;
	       }
	       //is it in the operation?
	       for( STL_VECTOR(Processor*)::const_iterator itProc = (*itPath)->operations().begin();
		    itProc != (*itPath)->operations().end();
		    ++itProc) {
		  if( (*itProc) == (*itFProc).get()->processor() ) {
		     used=true;
		     break;
		  }
	       }
	       if(used) {break;}
	    }
	    if( !used ) {
	       report(SYSTEM,kFacilityString)<<"The processor "<<(*itFProc)->processor()->name() <<" is not begin used"<<endl;
	       properlyConfigured = false;
	    }
         }
      }
      //Sinks
      STL_VECTOR(string) unused = m_sinkManager->unusedSinks();
      for(STL_VECTOR(string)::iterator itSinkName = unused.begin();
          itSinkName != unused.end();
          ++itSinkName ) {
         report(SYSTEM,kFacilityString)<<"The sink "<<(*itSinkName) <<" is not being used"<<endl;
         properlyConfigured = false;
      }
      if(!properlyConfigured) {
         report(SYSTEM,kFacilityString)<<" Path configuration error: please remove all unused filters, processors and sinks"<<endl;
         returnValue = false;
      }
   }
   //sinks must be initialized AFTER all sources and producers/processors
   // because sinks may need to know what proxies will be available
   if(returnValue) {
      for(STL_VECTOR(JobControlNS::Path*)::iterator itPath = m_paths.begin();
	  itPath != m_paths.end();
	  ++itPath) {
	 (*itPath)->initializeSinks();
	 // make sure that data are READ sequentially, if one of the sinks needs
	 // to WRITTEN sequentially
	 if( true == (*itPath)->mustBeSequential() )
	 {
	    iFD.setForcedSequentialAccess( true );
	 }
	 
      }
   }
   return returnValue;
}


DABoolean
ProcessingPaths::processStop(Frame& iFrame, DABoolean iContinueOnException)
{
   DABoolean returnValue = true;
   //Need to reset all filters before processing the paths
   // since multiple paths may share the same filter
   for( STL_VECTOR(Path*)::iterator itPath = m_paths.begin();
       itPath != m_paths.end();
       ++itPath ) {
     (*itPath)->filter()->reset();
   }

   for( STL_VECTOR(Path*)::iterator itPath = m_paths.begin();
       itPath != m_paths.end();
       ++itPath ) {
#ifndef CLEO_DEBUG
      try { // protect against exceptions that would stop event loop
#endif        
         if( ! (*itPath)->execute( iFrame, iContinueOnException ) ) {
	    returnValue = false;
	    break;
	 }
	 
#ifndef CLEO_DEBUG
      } catch( DAExceptionBase& thisException ) {
         if( true == iContinueOnException ) {
            report(ERROR,kFacilityString) << thisException.exceptionStack() 
					  << "caught a DAException:\n\"" 
					  << thisException.what() << "\""
					  << "\n; will continue..."<<endl;
         } else {
            throw;
         }
      }
#endif
   }
   return returnValue;
}

DABoolean
ProcessingPaths::add(Path* iPath)
{
   if(m_usingDefault) {
      m_usingDefault = false;
      m_defaultFilter = 0;
   }
   
   m_paths.push_back(iPath);
   //stop removal of a Processor if the Path is using that Processor
   m_masterProcessor->requestToRemoveProcessor.attach(iPath, &Path::isNotInOperations);
   m_sinkManager->requestToRemoveSink.attach(iPath, &Path::notUsingSink);
   return true;
}

DABoolean
ProcessingPaths::add(FilterBase* iFilter)
{
   if(m_usingDefault) {
      m_usingDefault = false;
      m_defaultFilter = 0;
   }
   m_definedFilters.push_back(iFilter);
   return true;
}

void 
ProcessingPaths::addSink(const string&)
{
   m_sinksChanged=true;
}
void 
ProcessingPaths::removeSink(const string& iName)
{
   DataSinkBinder* binder = m_sinkManager->binderFor(iName);
   assert(0!= binder);
   
   DABoolean sinkInUse =false;
   //see if a path is using this sink
   STL_VECTOR(Path*)::iterator itPath = m_paths.begin();
   for( ;
        itPath != m_paths.end();
        ++itPath ) {
      if( (*itPath)->removeSink(*binder) ) {
         //since only one path can hold a sink, we can stop here
         sinkInUse = true;
         break;
      }
   }
   if( sinkInUse && !m_usingDefault) {
      report(WARNING,kFacilityString)<<"removed Sink from path "<<(*itPath)->name()<<endl;
   }
}

void 
ProcessingPaths::addProcessor(const string& iName)
{
   m_procsChanged=true;
   
   //cout <<iName<<endl;
   
   FilterProc* temp = new FilterProc(m_masterProcessor->fetch( iName ));
   m_filterProcs.push_back(temp);

   if(m_usingDefault) {
      if(!m_paths.empty() ) {
	 //NOTE: path can be non-empty but with empty defaultFilter if
	 // 1) did a 'go'
	 // 2) removed all Procs
	 //   We can't get rid of the default path because there
	 //   might be an open sink attached
	 if(0 != m_defaultFilter) {
	    m_defaultFilter->add(temp);
	 }
      }
   }
}

void 
ProcessingPaths::removeProcessor(const string& iName)
{
   m_procsChanged=true;

   Processor* proc = m_masterProcessor->fetch( iName );
   STL_VECTOR(JobControlNS::Holder<FilterProc> )::iterator itFilter = m_filterProcs.begin();
   for(;
       itFilter != m_filterProcs.end();
       ++itFilter) {
      if((*itFilter)->processor() == proc ) {
         break;
      }
   }
   assert(itFilter != m_filterProcs.end() );
   if(m_usingDefault) {
      if(!m_paths.empty()) {
	 // NOTE: can't do
         //   delete m_paths.front();
         //   m_paths.pop_back();
	 // because there might be an open sink attached
	 // to this path
         m_paths.front()->setFilter(0);
         m_defaultFilter=0;
      }
   } 
   m_filterProcs.erase(itFilter);
}

void
ProcessingPaths::reorder(const STL_VECTOR(JobControlNS::Path*)& iOrder )
{
   m_paths = iOrder;
}

void 
ProcessingPaths::processorNotBeingUsed(const string& iName, DABoolean& iFlag)
{
   if(!m_usingDefault) {
      //see if any filters use this
      FilterBase* procFilter = 0;
      for(STL_VECTOR(JobControlNS::Holder<FilterProc> )::iterator itFilter = m_filterProcs.begin();
          itFilter != m_filterProcs.end();
          ++itFilter ) {
         if( (*itFilter)->processor()->name() == iName ) {
            procFilter = (*itFilter).get();
            break;
         }
      }
      assert( 0 != procFilter);
      for(STL_VECTOR(JobControlNS::Holder<FilterBase> )::iterator itFilter = m_definedFilters.begin();
          itFilter != m_definedFilters.end();
          ++itFilter) {
         if( (*itFilter)->contains(procFilter) ) {
            iFlag = false;
            break;
         }
      }
   }
}


DABoolean
ProcessingPaths::remove(JobControlNS::Path* iPath )
{
   for(STL_VECTOR(Path*)::iterator itPath = m_paths.begin();
       itPath != m_paths.end();
       ++itPath) {
      if( *itPath == iPath ) {
         delete iPath;
         m_paths.erase( itPath );
         return true;
      }
   }
   return false;
}

DABoolean
ProcessingPaths::remove(JobControlNS::FilterBase* iFilter )
{
   STL_VECTOR(JobControlNS::Holder<FilterBase> )::iterator itFoundFilter = m_definedFilters.end();
   //being used by another filter?
   for(STL_VECTOR(JobControlNS::Holder<FilterBase> )::iterator itFilter = m_definedFilters.begin();
       itFilter != m_definedFilters.end();
       ++itFilter) {
      if((*itFilter).get() == iFilter) {
         itFoundFilter = itFilter;
      } else if( (*itFilter)->contains(iFilter) ) {
         return false;
      }
   }

   if(itFoundFilter == m_definedFilters.end() ) {
      return false;
   }
   
   //being used in a path?
   for(STL_VECTOR(Path*)::iterator itPath = m_paths.begin();
       itPath != m_paths.end();
       ++itPath) {
      if( (*itPath)->filter() == iFilter ) {
         return false;
      }
   }
   m_definedFilters.erase(itFoundFilter);
   return true;
}   
//
// const member functions
//

//
// static member functions
//
