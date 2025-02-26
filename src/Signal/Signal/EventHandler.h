#if !defined(SIGNAL_EVENTHANDLER_H)
#define SIGNAL_EVENTHANDLER_H
// -*- C++ -*-
//
// Package:     <Signal>
// Module:      EventHandler
// 
// Description: Abstract Class for all EventHandlers
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Fri Apr 30 16:28:49 EDT 1999
// $Id: EventHandler.h,v 1.1.1.1 1999/05/02 02:39:56 mkl Exp $
//
// Revision history
//
// $Log: EventHandler.h,v $
// Revision 1.1.1.1  1999/05/02 02:39:56  mkl
// imported sources
//

// system include files

// user include files
#include "Signal/SignalHandler.h"

// forward declarations

class EventHandler
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef SignalHandler::Signal Signal;

      // ---------- Constructors and destructor ----------------
      EventHandler() {}
      virtual ~EventHandler() {}

      // ---------- member functions ---------------------------
      virtual void handleSignal( Signal iSignal ) = 0;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

   private:
      // ---------- Constructors and destructor ----------------
      EventHandler( const EventHandler& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const EventHandler& operator=( const EventHandler& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "Signal/Template/EventHandler.cc"
//#endif

#endif /* SIGNAL_EVENTHANDLER_H */
