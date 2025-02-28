#if !defined(SIGNALSSLOTS_SSSLOTBASE_H)
#define SIGNALSSLOTS_SSSLOTBASE_H
// -*- C++ -*-
//
// Package:     <SignalsSlots>
// Module:      SSSlotBase
// 
/**\class SSSlotBase SSSlotBase.h SignalsSlots/SSSlotBase.h

 Description: Base class for callback slots used by signals

 Usage:

   object refers to the observer who wants to know about the signal that
    this slot has been attached.  The value is used to detach all
    slots associated with that object.

*/
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 14:48:04 EDT 2003
// $Id: SSSlotBase.h,v 1.1.1.1 2003/09/09 13:15:02 cdj Exp $
//
// Revision history
//
// $Log: SSSlotBase.h,v $
// Revision 1.1.1.1  2003/09/09 13:15:02  cdj
// imported SignalsSlots source
//

// system include files

// user include files

// forward declarations
class SSSlotted;

class SSSlotBase
{
   public:
      // ---------- Constructors and destructor ----------------
      virtual ~SSSlotBase() {}

      // ---------- member functions ---------------------------
      SSSlotted* object() {return m_object;}

      // ---------- const member functions ---------------------
      const SSSlotted* object() const {return m_object;}

   protected:
      SSSlotBase(SSSlotted* iObject) : m_object(iObject) {}

   private:
      // ---------- Constructors and destructor ----------------
      SSSlotBase( const SSSlotBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SSSlotBase& operator=( const SSSlotBase& ); // stop default


      // ---------- data members -------------------------------
      SSSlotted* m_object;

};

#endif /* SIGNALSSLOTS_SSSLOTBASE_H */
