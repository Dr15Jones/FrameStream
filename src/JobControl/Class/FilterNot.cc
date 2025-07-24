// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FilterNot
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Jul 28 13:31:51 EDT 2003
// $Id: FilterNot.cc,v 1.1 2003/09/19 21:26:42 cdj Exp $
//
// Revision history
//
// $Log: FilterNot.cc,v $
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
#include "JobControl/FilterNot.h"
#include "Processor/Processor.h"

#include "DAException/DAExceptionStackNameEntry.h"
//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.FilterNot" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: FilterNot.cc,v 1.1 2003/09/19 21:26:42 cdj Exp $";
static const char* const kTagString = "$Name:  $";

namespace JobControlNS
{
//
// static data member definitions
//

//
// constructors and destructor
//
FilterNot::FilterNot(const std::string& iName, FilterBase* iFilter) :
   FilterBase(iName),
   m_filter(iFilter)
{
}

// FilterNot::FilterNot( const FilterNot& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//FilterNot::~FilterNot()
//{
//}

//
// assignment operators
//
// const FilterNot& FilterNot::operator=( const FilterNot& rhs )
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
FilterNot::streams() const
{
   return m_filter->streams();
}

DABoolean 
FilterNot::contains(const FilterBase* iFilter) const
{
   return iFilter == m_filter.get();
}

ActionBase::ActionResult
FilterNot::implementFilter(Frame& iFrame,
			    const StreamType& iStream )
{
   ActionBase::ActionResult value = m_filter->filter(iFrame, iStream);
   
   if( value == ActionBase::kPassed ) {
      return ActionBase::kFailed;
   }
   if( value == ActionBase::kFailed ) {
      return ActionBase::kPassed;
   }
   
   return value;
}
//
// const member functions
//
std::string 
FilterNot::description() const
{
   return std::string("not ")+m_filter->name();
}

//
// static member functions
//
}
