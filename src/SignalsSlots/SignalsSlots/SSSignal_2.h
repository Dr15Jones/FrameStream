#if !defined(SIGNALSSLOTS_SSSIGNAL_2_H)
#define SIGNALSSLOTS_SSSIGNAL_2_H
// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSignal_2
// 
/**\class SSSignal_2 SSSignal_2.h SignalsSlots/SSSignal_2.h

 Description: A Signal that emits two arguments of type ArgT1 and ArgT2

 Usage:
    You add this class as a public member data to a class you want
   other classes to be able to see signals from.  When you want to
   send a signal you use the 'emit' method and pass in the value
   you want emitted with the signal.

*/
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 14:54:23 EDT 2003
// $Id: SSSignal_2.h,v 1.1.1.1 2003/09/09 13:15:02 cdj Exp $
//
// Revision history
//
// $Log: SSSignal_2.h,v $
// Revision 1.1.1.1  2003/09/09 13:15:02  cdj
// imported SignalsSlots source
//

// system include files

// user include files
#include "SignalsSlots/SSSignalBase.h"
#include "SignalsSlots/SSSlot_2.h"

// forward declarations

template <class ArgT1, class ArgT2>
class SSSignal_2 : public SSSignalBase
{
  // ---------- friend classes and functions ---------------
  
   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SSSignal_2() {}

      // ---------- member functions ---------------------------
      void  emit(ArgT1 iArg1, ArgT2 iArg2) const {
	for(const_iterator itSlot = begin();
	    itSlot != end();
	    ++itSlot ) {
	  const_cast<SSSlotBase_2<ArgT1,ArgT2>*>(static_cast<const SSSlotBase_2<ArgT1,ArgT2>*>(*itSlot))->action(iArg1,iArg2);
    }
  }

      template<class T, class MethodArgT1, class MethodArgT2>
      void attach(T* iObject, void (T::* iMethod)(MethodArgT1,MethodArgT2) ) {
    add(new SSSlot_2<T,ArgT1,ArgT2,MethodArgT1,MethodArgT2>(iObject, iMethod ) );
      }
 
      void attach(SSSlotBase_2<ArgT1,ArgT2>* iSlot ) {
	 add( iSlot );
      }

   private:
      // ---------- Constructors and destructor ----------------
      //SSSignal_2( const SSSignal_2& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SSSignal_2& operator=( const SSSignal_2& ); // stop default

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "SignalsSlots/Template/SSSignal_2.cc"
//#endif

#endif /* SIGNALSSLOTS_SSSIGNAL_2_H */
