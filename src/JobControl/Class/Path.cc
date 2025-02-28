// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      Path
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Jul 28 16:39:35 EDT 2003
// $Id: Path.cc,v 1.2 2004/01/09 18:48:38 cdj Exp $
//
// Revision history
//
// $Log: Path.cc,v $
// Revision 1.2  2004/01/09 18:48:38  cdj
// fix to path: needed to delay initialization of sinks until all sources and producers have been registered
//
// Revision 1.1  2003/09/19 21:26:44  cdj
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

// user include files
//#include "Experiment/report.h"
#include "JobControl/Path.h"
#include "JobControl/FilterBase.h"

#include "DAException/DAExceptionStackNameEntry.h"
#include "Processor/Processor.h"
#include "DAException/DAExceptionBase.h"
#include "DAException/DAException.h"

#include "DataStorage/DataSinkBinder.h"

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.Path" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: Path.cc,v 1.2 2004/01/09 18:48:38 cdj Exp $";
static const char* const kTagString = "$Name:  $";

namespace JobControlNS {
//
// static data member definitions
//


//
// constructors and destructor
//
Path::Path(const string& iName,
           FilterBase* iFilter,
	   const STL_VECTOR(Processor*)& iOpProcs,
	   const STL_VECTOR(DataSinkBinder*)& iSinks ) :
   m_filter(iFilter),
   m_procOperations(iOpProcs),
   m_name(iName)
{
   DABoolean sinksOK = true;

   //is the list of processors unique
   if( ! iOpProcs.empty() ) {
      for(STL_VECTOR(Processor*)::const_iterator itProc = iOpProcs.begin();
          itProc != iOpProcs.end()-1;
          ++itProc ) {
         for(STL_VECTOR(Processor*)::const_iterator itProc2 = itProc+1;
             itProc2 != iOpProcs.end();
             ++itProc2) {
            if( *itProc == *itProc2 ) {
               throw DAException((string("The Processor ")+(*itProc)->name()+" appears multiple times in the operations of path "+iName).c_str());
            }
         }
      }
   }
   for(STL_VECTOR(DataSinkBinder*)::const_iterator itBinder = iSinks.begin();
       itBinder != iSinks.end();
       ++itBinder) {
      for(STL_VECTOR(DataSinkBinder*)::const_iterator itBinder2 = itBinder+1;
          itBinder2 != iSinks.end();
          ++itBinder2) {
         if( *itBinder2 == *itBinder ) {
            throw DAException((string("The sink ")+(*itBinder)->dataSinkID()+string(" appears multiple times in the path ")+iName).c_str());
         }
      }
      DataSinkBinder* dsb = (*itBinder);

      addSink( *dsb );
      /*
      // hand over to FrameStorer
      FrameStorer::AddSinkStatus status;
      
      if( FrameStorer::kAddSinkNoError != 
          ( status = m_storer.addSink( *dsb ) ) ) 
      {
         switch(status){
            case FrameStorer::kAddSinkBinderFailedToMakeController:
            {
               report( EMERGENCY, kFacilityString ) 
               << (*dsb).dataSinkID() <<" Failed to make Sink." << endl;
               break;
            }
            case FrameStorer::kAddSinkInvalidStopsForSink:
            {
               report( EMERGENCY, kFacilityString ) 
               << (*dsb).dataSinkID() << " can't goto those stops." << endl;
               break;
            }
            case FrameStorer::kAddSinkSinkInaccessible:
            {
               report( EMERGENCY, kFacilityString ) 
               << (*dsb).dataSinkID() <<" is inaccessible." << endl;
               break;
            }
            case FrameStorer::kAddSinkBadParameters:
            {
               report( EMERGENCY, kFacilityString )
               << (*dsb).dataSinkID() << " Bad parameters." << endl;
               break;
            }
            case FrameStorer::kAddSinkUnknownError:
            default:
            {
               report( EMERGENCY, kFacilityString )
               << (*dsb).dataSinkID() <<" an unknown AddSink error occurred." << endl;
               break;
            }
         }
         sinksOK = false;
      }
      else 
      {
         cout 
         << "Opened data sink \"" 
         << dsb->dataSinkID() << "\"." << endl;
      }
      */
   } // loop over sinks

   if( !sinksOK ) {
      //throw exception
      throw DAException("Path failed to initialize");
   }
}

// Path::Path( const Path& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

Path::~Path()
{
}

//
// assignment operators
//
// const Path& Path::operator=( const Path& rhs )
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
Path::execute( Frame& iFrame, DABoolean iContinueOnException )
{
   DABoolean returnValue = true;
   ActionBase::ActionResult result = m_filter->filter(iFrame,
                                                   iFrame.stopStream() );
   
   if( ActionBase::kPassed == result ||
       ActionBase::kNoAction == result ) {
      for(STL_VECTOR(Processor*)::iterator itProc = m_procOperations.begin();
	  itProc != m_procOperations.end();
	  ++itProc ) {
	 try {
	    // add processor name into the stack
	    DAExceptionStackNameEntry stackNameEntry((*itProc)->identifier());
	    
	    ActionBase::ActionResult result = (*itProc)->execute(iFrame.stopStream(), iFrame);
	    switch (result) {
	       case ActionBase::kPassed:
	       case ActionBase::kFailed:
	       case ActionBase::kNoAction:
		  break;
	       case ActionBase::kError:
		  report(ERROR,kFacilityString ) <<"In the path " <<name()
						 <<" the Processor "
						 << (*itProc)->name()
						 <<" reported an Error"
						 <<endl;
	          returnValue = false;
	          break;
	       case ActionBase::kStopProcessLoop:
		  returnValue = false;
	          break;
	       default:
	         report(ERROR,kFacilityString ) 
		    <<"In the path "<<name()
		    << " the Processor "
		    << (*itProc)->name()
		    << " returned an unknown ActionBase result"
		    << endl;
		 returnValue = false;
	    }
	 } catch (const DAExceptionBase& iException ) {
	    if(iContinueOnException) {
	       //print message
	       ostream& myReport = report(ERROR,kFacilityString ) ;
	       myReport << iException.exceptionStack()
			<< "-eventLoop: caught a DAException:\n\"" 
			<< iException.what() << "\""
			<< "\n; will continue with this record..."<<endl;
	    } else {
	       throw;
	    }
            //reset stack
	 }
      }

      FrameStorer::StoreFrameStatus storeStatus = m_storer.storeFrame(iFrame);
      if( FrameStorer::kStoreFrameNoError != storeStatus )
      {
	 switch(storeStatus)
	 {
	    case FrameStorer::kStoreFrameWarningNoSinkForRecord:
	    {
	       //report( INFO, kFacilityString ) 
	       //<< "no sink defined for this record type: " 
	       //<< iFrame.stopStream().value()<< endl;
	       //<< "FrameStorer::kStoreFrameWarningNoSinkForRecord" << endl;
	       break;
	    }
	    case FrameStorer::kStoreFrameProblemWithASink:
	    {
	       throw DAException("FrameStorer::kStoreFrameProblemWithASink");
	       break;
	    }
	    case FrameStorer::kStoreFrameUnknownSinkError:
	    {
	       throw DAException( "FrameStorer::kStoreFrameUnknownSinkError" );
	       break;
	    }
	    case FrameStorer::kStoreFrameUnknownRecordError:
	    {
	       throw DAException( "FrameStorer::kStoreFrameUnknownRecordError" );
	       break;
	    }
	    case FrameStorer::kStoreFrameUnknownError:
	    default:
	    {
	       throw DAException( "Unknown Store error from FrameStorer");
	       break;
	    }
	 }
      }
   } else {
      if(ActionBase::kFailed != result ) {
	 returnValue = false;
      }
   }
   return returnValue;
}

DABoolean 
Path::removeSink(const DataSinkDescriptor& iSink) {
   //is it in our uninitialized list?
   for(STL_VECTOR(DataSinkBinder*)::iterator itBinder = m_uninitializedSinks.begin();
       itBinder != m_uninitializedSinks.end();
       ++itBinder) {
      if( *(*itBinder) == iSink) {
	 m_uninitializedSinks.erase(itBinder);
	 return true;
      }
   }
   return removeSinkFromStorer(iSink);
}
void
Path::addSink( const DataSinkBinder& iSink ) {
   //I don't want to have to instantiate another vector type
   m_uninitializedSinks.push_back(const_cast<DataSinkBinder*>(&iSink));
}

DABoolean 
Path::removeSinkFromStorer(const DataSinkDescriptor& iSink) {
   return FrameStorer::kRemoveSinkNoError == m_storer.removeSink(iSink);
}

void
Path::addSinkToStorer( const DataSinkBinder& iSink ) {
  FrameStorer::AddSinkStatus status;

   if( FrameStorer::kAddSinkNoError != 
       ( status = m_storer.addSink( iSink ) ) ) 
   {
      switch(status){
         case FrameStorer::kAddSinkBinderFailedToMakeController:
         {
            report( EMERGENCY, kFacilityString ) 
            << (iSink).dataSinkID() <<" Failed to make Controller." << endl;
            break;
         }
         case FrameStorer::kAddSinkInvalidStopsForSink:
         {
            report( EMERGENCY, kFacilityString ) 
            << (iSink).dataSinkID() << " can't goto those stops." << endl;
            break;
         }
         case FrameStorer::kAddSinkSinkInaccessible:
         {
            report( EMERGENCY, kFacilityString ) 
            << (iSink).dataSinkID() <<" is inaccessible." << endl;
            break;
         }
         case FrameStorer::kAddSinkBadParameters:
         {
            report( EMERGENCY, kFacilityString )
            << (iSink).dataSinkID() << " Bad parameters." << endl;
            break;
         }
         case FrameStorer::kAddSinkUnknownError:
         default:
         {
            report( EMERGENCY, kFacilityString )
            << (iSink).dataSinkID() <<" an unknown AddSink error occurred." << endl;
            break;
         }
      }
      throw DAException("failed to add sink");
   }
   else 
   {
      cout 
      << "Opened data sink \"" 
      << iSink.dataSinkID() << "\"." << endl;
   }
}

void 
Path::initializeSinks()
{
   while(m_uninitializedSinks.size() != 0) {
      //add before removing from our list just incase we
      // have an exception
      addSinkToStorer( *(m_uninitializedSinks.back()) );
      m_uninitializedSinks.pop_back();
   }
}

void
Path::isNotInOperations(const string& iName, DABoolean& iFlag)
{
   if(iFlag) {
      for(STL_VECTOR(Processor*)::iterator itProc = m_procOperations.begin();
          itProc != m_procOperations.end();
          ++itProc ) {
         if((*itProc)->name() == iName ) {
            iFlag = false;
            break;
         }
      }
   }
}
void
Path::notUsingSink(const string& iName, DABoolean& iFlag)
{
   if(iFlag) {
      for(STL_VECTOR(DataSinkBinder*)::iterator itBinder = 
	     m_uninitializedSinks.begin();
	  itBinder != m_uninitializedSinks.end();
	  ++itBinder) {
	 if( (*itBinder)->dataSinkID() == iName) {
	    iFlag = false;
	    return;
	 }
      }

      const _framestorer_sinkdescriptors_& sinks = m_storer.sinks();
      for(_framestorer_sinkdescriptors_::const_iterator itSink = sinks.begin();
          itSink != sinks.end();
          ++itSink ) {
         if((*itSink).dataSinkID() == iName ) {
            iFlag = false;
            break;
         }
      }
   }
}

//
// const member functions
//
DABoolean
Path::mustBeSequential() const 
{
   return m_storer.mustSequentiallyStore();
}

_framestorer_sinkdescriptors_ 
Path::sinks() const
{
   _framestorer_sinkdescriptors_ returnValue = m_storer.sinks();

   for(STL_VECTOR(DataSinkBinder*)::const_iterator itBinder= m_uninitializedSinks.begin();
       itBinder != m_uninitializedSinks.end();
       ++itBinder ) {
      returnValue.push_back(*(*itBinder) );
   }
   return returnValue;
}
//
// static member functions
//
} //namespace JobControlNS
