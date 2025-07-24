// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FilterProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Jul 28 13:31:51 EDT 2003
// $Id: FilterProc.cc,v 1.1 2003/09/19 21:26:43 cdj Exp $
//
// Revision history
//
// $Log: FilterProc.cc,v $
// Revision 1.1  2003/09/19 21:26:43  cdj
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
#include "JobControl/FilterProc.h"
#include "Processor/Processor.h"

#include "DAException/DAExceptionStackNameEntry.h"
//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.FilterProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: FilterProc.cc,v 1.1 2003/09/19 21:26:43 cdj Exp $";
static const char* const kTagString = "$Name:  $";

namespace JobControlNS
{
//
// static data member definitions
//

//
// constructors and destructor
//
FilterProc::FilterProc(Processor* iProc) :
   FilterBase(iProc->name()),
   m_proc(iProc)
{
}

// FilterProc::FilterProc( const FilterProc& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//FilterProc::~FilterProc()
//{
//}

//
// assignment operators
//
// const FilterProc& FilterProc::operator=( const FilterProc& rhs )
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
StreamSet
FilterProc::streams() const
{
   StreamSet returnValue;
   typedef _processor_stream2actions_ StreamActs;

   const StreamActs& streamActs = m_proc->actions();

   for(StreamActs::const_iterator iter = streamActs.begin();
       iter != streamActs.end();
       ++iter ) {
      //only if the action has been marked as 'should use' 
      //  should we include its stream
      if((*iter).second.shouldUse() ) {
	 returnValue.insert(returnValue.end(),
			    (*iter).first );
      }
   }

   return returnValue;
}

ActionBase::ActionResult
FilterProc::implementFilter(Frame& iFrame,
			    const StreamType& iStream )
{
   // add processor name into the stack
   DAExceptionStackNameEntry stackNameEntry(m_proc->identifier());

   return m_proc->execute(iStream, iFrame);
}
//
// const member functions
//
std::string 
FilterProc::description() const
{
   return name();
}

//
// static member functions
//
}
