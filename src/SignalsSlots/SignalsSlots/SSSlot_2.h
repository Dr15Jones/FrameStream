#if !defined(SIGNALSSLOTS_SSSLOT_2_H)
#define SIGNALSSLOTS_SSSLOT_2_H
// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSlot_2
// 
/**\class SSSlot_2 SSSlot_2.h SignalsSlots/SSSlot_2.h

 Description: A Slot that calls a member method that takes 2 arguments

 Usage:
    This class gets automatically created when you attach a class to a
    SSSignal_2.

*/
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 15:10:57 EDT 2003
// $Id: SSSlot_2.h,v 1.2 2004/03/03 20:09:51 vk Exp $
//
// Revision history
//
// $Log: SSSlot_2.h,v $
// Revision 1.2  2004/03/03 20:09:51  vk
// Make gdb happy by using dynamic_cast
//
// Revision 1.1.1.1  2003/09/09 13:15:02  cdj
// imported SignalsSlots source
//

// system include files

// user include files
#include "SignalsSlots/SSSlotBase_2.h"

// forward declarations

template<class T, class ArgT1, class ArgT2, class MethodArgT1,  class MethodArgT2>
  class SSSlot_2 : public SSSlotBase_2<ArgT1,ArgT2>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SSSlot_2(T* iObject, void (T::* iMethod)(MethodArgT1,MethodArgT2) ) :
	 SSSlotBase_2<ArgT1,ArgT2>(iObject), m_method(iMethod) {}

      // ---------- member functions ---------------------------
	 void action(ArgT1 iArg1, ArgT2 iArg2) {
#if defined(__linux__) && defined(CLEO_DEBUG)
	   (dynamic_cast<T*>(object())->*m_method)(iArg1, iArg2);
#else
	   (static_cast<T*>(object())->*m_method)(iArg1, iArg2);
#endif
      }

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SSSlot_2( const SSSlot_2& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SSSlot_2& operator=( const SSSlot_2& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      void (T::* m_method)(MethodArgT1,MethodArgT2);

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "SignalsSlots/Template/SSSlot_2.cc"
//#endif

#endif /* SIGNALSSLOTS_SSSLOT_2_H */
