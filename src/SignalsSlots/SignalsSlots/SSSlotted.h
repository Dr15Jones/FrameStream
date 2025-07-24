#if !defined(SIGNALSSLOTS_SSSLOTTED_H)
#define SIGNALSSLOTS_SSSLOTTED_H
// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSlotted
// 
/**\class SSSlotted SSSlotted.h SignalsSlots/SSSlotted.h

 Description: Base class for a class that has 'slots'

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 15:40:25 EDT 2003
// $Id: SSSlotted.h,v 1.1.1.1 2003/09/09 13:15:02 cdj Exp $
//
// Revision history
//
// $Log: SSSlotted.h,v $
// Revision 1.1.1.1  2003/09/09 13:15:02  cdj
// imported SignalsSlots source
//

// system include files
#include <list>

// user include files

// forward declarations
class SSSignalBase;

class SSSlotted
{
      // ---------- friend classes and functions ---------------
      friend class SSSignalBase;

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SSSlotted() {}
      virtual ~SSSlotted();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SSSlotted( const SSSlotted& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SSSlotted& operator=( const SSSlotted& ); // stop default

      // ---------- private member functions -------------------

      //called by SSSignalBase
      void connectedTo(SSSignalBase* iSignal) {
	 m_signals.push_back(iSignal);
      }

      //called by SSSignalBase
      void disconnect(SSSignalBase* iSignal) {
	 std::list<SSSignalBase*>::iterator itSignal = m_signals.begin();
	 while(itSignal != m_signals.end() ) {
	    std::list<SSSignalBase*>::iterator itTemp = itSignal;
	    ++itSignal;
	    if( (*itTemp) == iSignal) {
	       m_signals.erase(itTemp);
	    }
	 }
      }

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      std::list<SSSignalBase*> m_signals;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "SignalsSlots/Template/SSSlotted.cc"
//#endif

#endif /* SIGNALSSLOTS_SSSLOTTED_H */
