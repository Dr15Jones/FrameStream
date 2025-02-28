// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSignal_0
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 15:02:03 EDT 2003
// $Id: SSSignal_0.cc,v 1.1.1.1 2003/09/09 13:15:01 cdj Exp $
//
// Revision history
//
// $Log: SSSignal_0.cc,v $
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
#include "SignalsSlots/SSSignal_0.h"
#include "SignalsSlots/SSSlotBase_0.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "SignalsSlots.SSSignal_0" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SSSignal_0.cc,v 1.1.1.1 2003/09/09 13:15:01 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//SSSignal_0::SSSignal_0()
//{
//}

// SSSignal_0::SSSignal_0( const SSSignal_0& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//SSSignal_0::~SSSignal_0()
//{
//}

//
// assignment operators
//
// const SSSignal_0& SSSignal_0::operator=( const SSSignal_0& rhs )
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
SSSignal_0::emit() const {
   for(const_iterator itSlot = begin();
       itSlot != end();
       ++itSlot ) {
      const_cast<SSSlotBase_0*>(static_cast<const SSSlotBase_0*>(*itSlot))->action();
   }
}

//
// static member functions
//


