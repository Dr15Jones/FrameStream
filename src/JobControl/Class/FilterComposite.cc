// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FilterComposite
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Jul 28 13:56:36 EDT 2003
// $Id: FilterComposite.cc,v 1.1 2003/09/19 21:26:42 cdj Exp $
//
// Revision history
//
// $Log: FilterComposite.cc,v $
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
#include "JobControl/FilterComposite.h"

#include "DataHandler/StreamSet.h"
//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.FilterComposite" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: FilterComposite.cc,v 1.1 2003/09/19 21:26:42 cdj Exp $";
static const char* const kTagString = "$Name:  $";

namespace JobControlNS {

//
// static data member definitions
//

//
// constructors and destructor
//
FilterComposite::FilterComposite(const string& iName):
   FilterBase(iName)
{
   //start by making the vector smaller than its default
   m_filters.reserve(5);
}

// FilterComposite::FilterComposite( const FilterComposite& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//FilterComposite::~FilterComposite()
//{
//}

//
// assignment operators
//
// const FilterComposite& FilterComposite::operator=( const FilterComposite& rhs )
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
void
FilterComposite::add(FilterBase* iFilter )
{
   m_filters.push_back(iFilter);
}

void
FilterComposite::reset() {
   FilterBase::reset();
   for( STL_VECTOR(Holder<FilterBase> )::iterator itFilter = m_filters.begin();
	itFilter != m_filters.end();
	++itFilter ) {
      (*itFilter)->reset();
   }
}
//
// const member functions
//
StreamSet
FilterComposite::streams() const 
{
   StreamSet returnValue;
   for( STL_VECTOR(Holder<FilterBase> )::const_iterator itFilter = m_filters.begin();
	itFilter != m_filters.end();
	++itFilter ) {
      returnValue.add( (*itFilter)->streams() );
   }
   return returnValue;
}

DABoolean
FilterComposite::contains(const FilterBase* iFilter) const 
{

   if (this == iFilter) {
      return true;
   }
   for( STL_VECTOR(Holder<FilterBase> )::const_iterator itFilter = m_filters.begin();
        itFilter != m_filters.end();
        ++itFilter ) {
      if( (*itFilter)->contains(iFilter) ) {
         return true;
      }
   }
   return false;
}

//
// static member functions
//
} //namespace JobControlNS
