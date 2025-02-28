#if !defined(SIGNALSSLOTS_SSSLOT_0_H)
#define SIGNALSSLOTS_SSSLOT_0_H
// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSlot_0
// 
/**\class SSSlot_0 SSSlot_0.h SignalsSlots/SSSlot_0.h

 Description: A Slot that takes no arguments

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 15:10:57 EDT 2003
// $Id: SSSlot_0.h,v 1.2 2004/03/03 20:09:51 vk Exp $
//
// Revision history
//
// $Log: SSSlot_0.h,v $
// Revision 1.2  2004/03/03 20:09:51  vk
// Make gdb happy by using dynamic_cast
//
// Revision 1.1.1.1  2003/09/09 13:15:02  cdj
// imported SignalsSlots source
//

// system include files

// user include files
#include "SignalsSlots/SSSlotBase_0.h"

// forward declarations

template<class T>
class SSSlot_0 : public SSSlotBase_0
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SSSlot_0(T* iObject, void (T::* iMethod)() ) :
	 SSSlotBase_0(iObject), m_method(iMethod) {}

      // ---------- member functions ---------------------------
      void action() {
#if defined(__linux__) && defined(CLEO_DEBUG)
	 (dynamic_cast<T*>(object())->*m_method)();
#else
	 (static_cast<T*>(object())->*m_method)();
#endif
      }

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SSSlot_0( const SSSlot_0& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SSSlot_0& operator=( const SSSlot_0& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      void (T::* m_method)();

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "SignalsSlots/Template/SSSlot_0.cc"
//#endif

#endif /* SIGNALSSLOTS_SSSLOT_0_H */
