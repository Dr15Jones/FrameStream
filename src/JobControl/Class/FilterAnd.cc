// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FilterAnd
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Jul 28 14:27:57 EDT 2003
// $Id: FilterAnd.cc,v 1.1 2003/09/19 21:26:41 cdj Exp $
//
// Revision history
//
// $Log: FilterAnd.cc,v $
// Revision 1.1  2003/09/19 21:26:41  cdj
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
#include "Experiment/report.h"
#include "JobControl/FilterAnd.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.FilterAnd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: FilterAnd.cc,v 1.1 2003/09/19 21:26:41 cdj Exp $";
static const char* const kTagString = "$Name:  $";

namespace JobControlNS {
//
// static data member definitions
//

//
// constructors and destructor
//
//FilterAnd::FilterAnd()
//{
//}

// FilterAnd::FilterAnd( const FilterAnd& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//FilterAnd::~FilterAnd()
//{
//}

//
// assignment operators
//
// const FilterAnd& FilterAnd::operator=( const FilterAnd& rhs )
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
FilterAnd::implementFilter(Frame& iFrame, 
			   const StreamType& iStream)
{
   ActionBase::ActionResult returnValue = ActionBase::kPassed;

   // check for ANY ACTION
   DABoolean anyAction = false;


   for( STL_VECTOR(Holder<FilterBase> )::iterator itFilter = filters().begin();
        itFilter != filters().end();
        ++itFilter )
   {
      FilterBase* filter = (*itFilter).get();

      ActionBase::ActionResult status = filter->filter( iFrame, iStream);

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
	    << "ActionBase::kFailed" << endl;
	 break;
      }
      else if( ActionBase::kError == returnValue )
      {
	 report( DEBUG, kFacilityString ) 
	    << "ActionBase::kError" << endl;
	 break;
      }
      else if( ActionBase::kStopProcessLoop == returnValue )
      {
	 report( DEBUG, kFacilityString ) 
	    << "ActionBase::kStopProcessLoop" << endl;
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


//
// const member functions
//
string 
FilterAnd::description() const
{
   string returnValue;
   if(filters().size() > 0 ) {
      returnValue = ( filters().front()->name() );
      for( STL_VECTOR(Holder<FilterBase> )::const_iterator itFilter = filters().begin() + 1;
           itFilter != filters().end();
           ++itFilter )
      {
         returnValue += " and "+(*itFilter)->name();
      }
   }
   return returnValue;
}

//
// static member functions
//
} //namespace JobControlNS
