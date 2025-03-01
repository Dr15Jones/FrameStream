#if !defined(SIGNALSSLOTS_SSSLOT_1_H)
#define SIGNALSSLOTS_SSSLOT_1_H
// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSlot_1
// 
/**\class SSSlot_1 SSSlot_1.h SignalsSlots/SSSlot_1.h

 Description: A Slot that calls a member method that takes 1 argument

 Usage:
    This class gets automatically created when you attach a class to a
    SSSignal_1.

*/
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 15:10:57 EDT 2003
// $Id: SSSlot_1.h,v 1.2 2003/11/20 18:31:58 vk Exp $
//
// Revision history
//
// $Log: SSSlot_1.h,v $
// Revision 1.2  2003/11/20 18:31:58  vk
// On Linux with -g enabled flag compiler screws up and makes a wrong static_cast. Usage of dynamic_cast fix the problem.
//
// Revision 1.1.1.1  2003/09/09 13:15:02  cdj
// imported SignalsSlots source
//

// system include files

// user include files
#include "SignalsSlots/SSSlotBase_1.h"

// forward declarations

template<class T, class ArgT, class MethodArgT>
class SSSlot_1 : public SSSlotBase_1<ArgT>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SSSlot_1(T* iObject, void (T::* iMethod)(MethodArgT) ) :
	 SSSlotBase_1<ArgT>(iObject), m_method(iMethod) {}

      // ---------- member functions ---------------------------
      void action(ArgT iArg) {
#if defined(__linux__) && defined(CLEO_DEBUG)
	 (dynamic_cast<T*>(this->object())->*m_method)(iArg);
#else
	 (static_cast<T*>(this->object())->*m_method)(iArg);
#endif
      }

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SSSlot_1( const SSSlot_1& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SSSlot_1& operator=( const SSSlot_1& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      void (T::* m_method)(MethodArgT);

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "SignalsSlots/Template/SSSlot_1.cc"
//#endif

#endif /* SIGNALSSLOTS_SSSLOT_1_H */
