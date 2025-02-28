// -*- C++ -*-
//
// Package:     <Modname>
// Module:      Modname
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      John Doe
// Created:     day-mon-xx
// RCS(Id)
//
// Revision history
//
// RCS(Log)
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Experiment/report.h"
#include "Modname/Modname.h"

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
static const char* const kFacilityString = "Modname.Modname" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: module.cc,v 1.6 2000/12/04 19:11:09 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
Modname::Modname()
   : Module( "Modname", "This is my module" ),
     m_command( "modname", this ),
     m_internalCommand( "modname", this )
{
}

// Modname::Modname( const Modname& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

Modname::~Modname()
{
}

//
// assignment operators
//
// const Modname& Modname::operator=( const Modname& rhs )
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
void
Modname::printNumber( int iNumber ) const
{
   report( INFO, kFacilityString )
      << "and the number is: " << iNumber << endl;
}

//
// static member functions
//
