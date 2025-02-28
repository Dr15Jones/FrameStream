#if !defined(SIGNALSSLOTS_SSSIGNALBASE_H)
#define SIGNALSSLOTS_SSSIGNALBASE_H
// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSignalBase
// 
/**\class SSSignalBase SSSignalBase.h SignalsSlots/SSSignalBase.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 14:33:15 EDT 2003
// $Id: SSSignalBase.h,v 1.1.1.1 2003/09/09 13:15:02 cdj Exp $
//
// Revision history
//
// $Log: SSSignalBase.h,v $
// Revision 1.1.1.1  2003/09/09 13:15:02  cdj
// imported SignalsSlots source
//

// system include files
#include <list>

// user include files

// forward declarations
class SSSlotBase;
class SSSlotted;

class SSSignalBase
{
      // ---------- friend classes and functions ---------------
      friend class SSSlotted;

   public:
      // ---------- constants, enums and typedefs --------------
      typedef list<SSSlotBase*>::iterator iterator;
      typedef list<SSSlotBase*>::const_iterator const_iterator;

      // ---------- Constructors and destructor ----------------
      SSSignalBase() {}
      virtual ~SSSignalBase();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:

      
      list<SSSlotBase*>::iterator begin() { return m_slots.begin(); }
      list<SSSlotBase*>::iterator end() {return m_slots.end(); }

      list<SSSlotBase*>::const_iterator begin() const { 
	 return m_slots.begin(); }
      list<SSSlotBase*>::const_iterator end() const {
	 return m_slots.end(); }

      ///The ownership is taken for iSlot
      void add(SSSlotBase* iSlot);
   private:
      // ---------- Constructors and destructor ----------------
      //SSSignalBase( const SSSignalBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SSSignalBase& operator=( const SSSignalBase& ); // stop default

      // ---------- private member functions -------------------

      //only called by SSSlotted
      ///removes all signals whose objects correspond to the pointer
      void detach(SSSlotted* iObject);

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      list<SSSlotBase*> m_slots;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "SignalsSlots/Template/SSSignalBase.cc"
//#endif

#endif /* SIGNALSSLOTS_SSSIGNALBASE_H */
