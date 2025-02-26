// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      SubcommandBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Fri Sep  3 18:01:28 EDT 1999
// $Id: SubcommandBase.cc,v 1.1 1999/09/06 21:28:51 mkl Exp $
//
// Revision history
//
// $Log: SubcommandBase.cc,v $
// Revision 1.1  1999/09/06 21:28:51  mkl
// new subcommand handling
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "CommandPattern/SubcommandBase.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "CommandPattern.SubcommandBase" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SubcommandBase.cc,v 1.1 1999/09/06 21:28:51 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
SubcommandBase::SubcommandBase( const string& iName,
				Count iMinArgs,
				Count iMaxArgs )
   : m_name( iName ),
     m_minArgs( iMinArgs ),
     m_maxArgs( iMaxArgs )
{
}

// SubcommandBase::SubcommandBase( const SubcommandBase& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SubcommandBase::~SubcommandBase()
{
}

//
// assignment operators
//
// const SubcommandBase& SubcommandBase::operator=( const SubcommandBase& rhs )
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
