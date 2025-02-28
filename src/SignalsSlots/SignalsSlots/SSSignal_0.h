#if !defined(SIGNALSSLOTS_SSSIGNAL_0_H)
#define SIGNALSSLOTS_SSSIGNAL_0_H
// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSignal_0
// 
/**\class SSSignal_0 SSSignal_0.h SignalsSlots/SSSignal_0.h

 Description: A Signal that emits no arguments

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 14:54:23 EDT 2003
// $Id: SSSignal_0.h,v 1.1.1.1 2003/09/09 13:15:02 cdj Exp $
//
// Revision history
//
// $Log: SSSignal_0.h,v $
// Revision 1.1.1.1  2003/09/09 13:15:02  cdj
// imported SignalsSlots source
//

// system include files

// user include files
#include "SignalsSlots/SSSignalBase.h"
#include "SignalsSlots/SSSlot_0.h"

// forward declarations

class SSSignal_0 : public SSSignalBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SSSignal_0() {}

      // ---------- member functions ---------------------------
      void  emit() const;

      template<class T>
      void attach(T* iObject, void (T::* iMethod)() ) {
	 add(new SSSlot_0<T>(iObject, iMethod ) );
      }

      void attach( SSSlotBase_0* iSlot ) {
	 add( iSlot );
      }

   private:
      // ---------- Constructors and destructor ----------------
      //SSSignal_0( const SSSignal_0& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SSSignal_0& operator=( const SSSignal_0& ); // stop default

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "SignalsSlots/Template/SSSignal_0.cc"
//#endif

#endif /* SIGNALSSLOTS_SSSIGNAL_0_H */
