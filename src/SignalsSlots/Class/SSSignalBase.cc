// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSignalBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 14:40:55 EDT 2003
// $Id: SSSignalBase.cc,v 1.1.1.1 2003/09/09 13:15:01 cdj Exp $
//
// Revision history
//
// $Log: SSSignalBase.cc,v $
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
#include "SignalsSlots/SSSignalBase.h"
#include "SignalsSlots/SSSlotBase.h"
#include "SignalsSlots/SSSlotted.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "SignalsSlots.SSSignalBase" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SSSignalBase.cc,v 1.1.1.1 2003/09/09 13:15:01 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//SSSignalBase::SSSignalBase()
//{
//}

// SSSignalBase::SSSignalBase( const SSSignalBase& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SSSignalBase::~SSSignalBase()
{
   for(iterator itSlot = begin();
       itSlot != end();
       ++itSlot ) {
      (*itSlot)->object()->disconnect(this);
      delete *itSlot;
   }
}

//
// assignment operators
//
// const SSSignalBase& SSSignalBase::operator=( const SSSignalBase& rhs )
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
SSSignalBase::detach(SSSlotted* iObject) {

   iterator itSlot = begin();
   while(itSlot != end() ) {
      //hold onto this iterator since we may need to remove
      // it from the list
      iterator itTemp = itSlot;
      ++itSlot;
      if( (*itTemp)->object() == iObject ) {
	 delete *itTemp;
	 m_slots.erase(itTemp);
      }
   }
}

void
SSSignalBase::add(SSSlotBase* iSlot )
{
   m_slots.push_back(iSlot);
   iSlot->object()->connectedTo(this);
}

//
// const member functions
//

//
// static member functions
//
