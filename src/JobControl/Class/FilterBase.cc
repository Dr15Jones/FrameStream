// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FilterBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Jul 28 10:57:45 EDT 2003
// $Id: FilterBase.cc,v 1.2 2003/09/28 20:16:17 cdj Exp $
//
// Revision history
//
// $Log: FilterBase.cc,v $
// Revision 1.2  2003/09/28 20:16:17  cdj
// initialize the reference count of FilterBase
//
// Revision 1.1  2003/09/19 21:26:42  cdj
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
#include "JobControl/FilterBase.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.FilterBase" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: FilterBase.cc,v 1.2 2003/09/28 20:16:17 cdj Exp $";
static const char* const kTagString = "$Name:  $";

namespace JobControlNS {
//
// static data member definitions
//

//
// constructors and destructor
//
FilterBase::FilterBase(const string& iName) :
   m_filtered(false),
   m_name(iName),
   m_refCount(0)
{
}

// FilterBase::FilterBase( const FilterBase& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

FilterBase::~FilterBase()
{
}

//
// assignment operators
//
// const FilterBase& FilterBase::operator=( const FilterBase& rhs )
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
ActionBase::ActionResult
FilterBase::filter(Frame& iFrame, const StreamType& iStream) {
   if(!m_filtered) {
      m_result = implementFilter(iFrame, iStream );
      //only set true after having run the implemenation
      // just incase of an exception
      m_filtered = true;
   }
   return m_result;
}

void
FilterBase::reset()
{
   m_filtered = false;
}

void
FilterBase::removeRef()
{
   if(0 == --m_refCount) {
      delete this;
   }
}

DABoolean
FilterBase::contains(const FilterBase* iFilter) const {
   return iFilter == this;
}

//
// const member functions
//

//
// static member functions
//
} //namespace JobControlNS
