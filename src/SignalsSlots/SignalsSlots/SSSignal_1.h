#if !defined(SIGNALSSLOTS_SSSIGNAL_1_H)
#define SIGNALSSLOTS_SSSIGNAL_1_H
// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSignal_1
// 
/**\class SSSignal_1 SSSignal_1.h SignalsSlots/SSSignal_1.h

 Description: A Signal that emits one argument of type ArgT

 Usage:
    You add this class as a public member data to a class you want
   other classes to be able to see signals from.  When you want to
   send a signal you use the 'emit' method and pass in the value
   you want emitted with the signal.

*/
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 14:54:23 EDT 2003
// $Id: SSSignal_1.h,v 1.1.1.1 2003/09/09 13:15:02 cdj Exp $
//
// Revision history
//
// $Log: SSSignal_1.h,v $
// Revision 1.1.1.1  2003/09/09 13:15:02  cdj
// imported SignalsSlots source
//

// system include files

// user include files
#include "SignalsSlots/SSSignalBase.h"
#include "SignalsSlots/SSSlot_1.h"

// forward declarations

template <class ArgT>
class SSSignal_1 : public SSSignalBase
{
  // ---------- friend classes and functions ---------------
  
   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SSSignal_1() {}

      // ---------- member functions ---------------------------
  void  emit(ArgT iArg) const {
    for(const_iterator itSlot = begin();
	itSlot != end();
	++itSlot ) {
      const_cast<SSSlotBase_1<ArgT>*>(static_cast<const SSSlotBase_1<ArgT>*>(*itSlot))->action(iArg);
    }
  }

      template<class T, class MethodArgT>
      void attach(T* iObject, void (T::* iMethod)(MethodArgT) ) {
	 add(new SSSlot_1<T,ArgT,MethodArgT>(iObject, iMethod ) );
      }
 
      void attach(SSSlotBase_1<ArgT>* iSlot ) {
	 add( iSlot );
      }

   private:
      // ---------- Constructors and destructor ----------------
      //SSSignal_1( const SSSignal_1& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SSSignal_1& operator=( const SSSignal_1& ); // stop default

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "SignalsSlots/Template/SSSignal_1.cc"
//#endif

#endif /* SIGNALSSLOTS_SSSIGNAL_1_H */
