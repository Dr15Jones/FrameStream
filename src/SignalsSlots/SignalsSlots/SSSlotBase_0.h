#if !defined(SIGNALSSLOTS_SSSLOTBASE_0_H)
#define SIGNALSSLOTS_SSSLOTBASE_0_H
// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSlotBase_0
// 
/**\class SSSlotBase_0 SSSlotBase_0.h SignalsSlots/SSSlotBase_0.h

 Description: A Slot that takes no arguments

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 15:10:57 EDT 2003
// $Id: SSSlotBase_0.h,v 1.1.1.1 2003/09/09 13:15:02 cdj Exp $
//
// Revision history
//
// $Log: SSSlotBase_0.h,v $
// Revision 1.1.1.1  2003/09/09 13:15:02  cdj
// imported SignalsSlots source
//

// system include files

// user include files
#include "SignalsSlots/SSSlotBase.h"

// forward declarations

class SSSlotBase_0 : public SSSlotBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SSSlotBase_0(SSSlotted* iObject) :
	 SSSlotBase(iObject) {}

      // ---------- member functions ---------------------------
      virtual void action() = 0;


      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SSSlotBase_0( const SSSlotBase_0& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SSSlotBase_0& operator=( const SSSlotBase_0& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "SignalsSlots/Template/SSSlotBase_0.cc"
//#endif

#endif /* SIGNALSSLOTS_SSSLOTBASE_0_H */
