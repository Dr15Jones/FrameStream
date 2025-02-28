// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSlotted
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 15:52:53 EDT 2003
// $Id: SSSlotted.cc,v 1.1.1.1 2003/09/09 13:15:01 cdj Exp $
//
// Revision history
//
// $Log: SSSlotted.cc,v $
// Revision 1.1.1.1  2003/09/09 13:15:01  cdj
// imported SignalsSlots source
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
#include "SignalsSlots/SSSlotted.h"
#include "SignalsSlots/SSSignalBase.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "SignalsSlots.SSSlotted" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SSSlotted.cc,v 1.1.1.1 2003/09/09 13:15:01 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//SSSlotted::SSSlotted()
//{
//}

// SSSlotted::SSSlotted( const SSSlotted& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SSSlotted::~SSSlotted()
{
   for(list<SSSignalBase*>::iterator itSignal = m_signals.begin();
       itSignal != m_signals.end();
       ++itSignal) {
      (*itSignal)->detach(this);
   }
}

//
// assignment operators
//
// const SSSlotted& SSSlotted::operator=( const SSSlotted& rhs )
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
