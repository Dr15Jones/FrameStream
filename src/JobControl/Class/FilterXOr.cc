// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FilterXOr
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Jul 28 14:27:57 EDT 2003
// $Id: FilterXOr.cc,v 1.1 2003/09/19 21:26:43 cdj Exp $
//
// Revision history
//
// $Log: FilterXOr.cc,v $
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
#include "Experiment/report.h"
#include "JobControl/FilterXOr.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.FilterXOr" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: FilterXOr.cc,v 1.1 2003/09/19 21:26:43 cdj Exp $";
static const char* const kTagString = "$Name:  $";

namespace JobControlNS {
//
// static data member definitions
//

//
// constructors and destructor
//
//FilterXOr::FilterXOr()
//{
//}

// FilterXOr::FilterXOr( const FilterXOr& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//FilterXOr::~FilterXOr()
//{
//}

//
// assignment operators
//
// const FilterXOr& FilterXOr::operator=( const FilterXOr& rhs )
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
FilterXOr::implementFilter(Frame& iFrame, 
			   const StreamType& iStream)
{
   ActionBase::ActionResult returnValue = ActionBase::kFailed;

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
	 anyAction   = true;
         
         if( ActionBase::kPassed == status )
         {
            report( DEBUG, kFacilityString ) 
            << "ActionBase::kPassed" << endl;
            if( returnValue == ActionBase::kPassed) {
               returnValue = ActionBase::kFailed;
            } else {
               returnValue = ActionBase::kPassed;
            }
         } 
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
FilterXOr::description() const
{
   string returnValue( filters().front()->name() );
   for( STL_VECTOR(Holder<FilterBase> )::const_iterator itFilter = filters().begin() + 1;
        itFilter != filters().end();
        ++itFilter )
   {
      returnValue += " xor "+(*itFilter)->name();
   }
   return returnValue;
}

//
// static member functions
//
} //namespace JobControlNS
