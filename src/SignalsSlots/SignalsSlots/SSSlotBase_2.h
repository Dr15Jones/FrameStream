#if !defined(SIGNALSSLOTS_SSSLOTBASE_2_H)
#define SIGNALSSLOTS_SSSLOTBASE_2_H
// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSlotBase_2
// 
/**\class SSSlotBase_2 SSSlotBase_2.h SignalsSlots/SSSlotBase_2.h

 Description: A Slot that takes 2 arguments

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 15:10:57 EDT 2003
// $Id: SSSlotBase_2.h,v 1.1.1.1 2003/09/09 13:15:02 cdj Exp $
//
// Revision history
//
// $Log: SSSlotBase_2.h,v $
// Revision 1.1.1.1  2003/09/09 13:15:02  cdj
// imported SignalsSlots source
//

// system include files

// user include files
#include "SignalsSlots/SSSlotBase.h"

// forward declarations

template <class ArgT1, class ArgT2>
class SSSlotBase_2 : public SSSlotBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SSSlotBase_2(SSSlotted* iObject) :
	 SSSlotBase(iObject) {}

      // ---------- member functions ---------------------------
      virtual void action(ArgT1,ArgT2) = 0;


      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SSSlotBase_2( const SSSlotBase_2& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SSSlotBase_2& operator=( const SSSlotBase_2& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "SignalsSlots/Template/SSSlotBase_2.cc"
//#endif

#endif /* SIGNALSSLOTS_SSSLOTBASE_2_H */
