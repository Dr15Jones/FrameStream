// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      JobContext
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Thu Feb 18 18:34:57 EST 1999
// $Id: JobContext.cc,v 1.2 2000/12/01 20:00:59 cdj Exp $
//
// Revision history
//
// $Log: JobContext.cc,v $
// Revision 1.2  2000/12/01 20:00:59  cdj
// now includes map
//
// Revision 1.1  1999/02/22 23:40:40  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "CommandPattern/JobContext.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "CommandPattern.JobContext" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: JobContext.cc,v 1.2 2000/12/01 20:00:59 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//
JobContext* JobContext::m_instance = 0;

//
// constructors and destructor
//
JobContext::JobContext()
{
}

// JobContext::JobContext( const JobContext& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

JobContext::~JobContext()
{
}

//
// assignment operators
//
// const JobContext& JobContext::operator=( const JobContext& rhs )
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

//
// const member functions
//

//
// static member functions
//
JobContext*
JobContext::instance()
{
   if( 0 == m_instance )
   {
      m_instance = new JobContext;
   }

   return m_instance;
}
