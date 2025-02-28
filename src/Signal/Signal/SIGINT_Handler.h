#if !defined(SIGNAL_SIGINT_HANDLER_H)
#define SIGNAL_SIGINT_HANDLER_H
// -*- C++ -*-
//
// Package:     <Signal>
// Module:      SIGINT_Handler
// 
// Description: Specific Handler for SIGINT
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Fri Apr 30 16:29:26 EDT 1999
// $Id: SIGINT_Handler.h,v 1.3 1999/12/21 20:35:02 mkl Exp $
//
// Revision history
//
// $Log: SIGINT_Handler.h,v $
// Revision 1.3  1999/12/21 20:35:02  mkl
// added SIGINTHandler::reset method
//
// Revision 1.2  1999/08/26 03:45:07  mkl
// ctrl-c signal: give option to completely exit out of suez (the fast way) or just stop the event loop
//
// Revision 1.1.1.1  1999/05/02 02:39:56  mkl
// imported sources
//

// system include files

// user include files
#include "Signal/EventHandler.h"

// forward declarations

class SIGINT_Handler : public EventHandler
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SIGINT_Handler( DABoolean iCallExit=true );
      virtual ~SIGINT_Handler();

      // ---------- member functions ---------------------------
      virtual void handleSignal( Signal iSignal );

      // local
      void reset();
      DABoolean isStopRequested() const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

   private:
      // ---------- Constructors and destructor ----------------
      SIGINT_Handler( const SIGINT_Handler& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SIGINT_Handler& operator=( const SIGINT_Handler& ); // stop default

      // ---------- private member functions -------------------
      DABoolean promptUser( const char* iPrompt );

      // ---------- data members -------------------------------
      DABoolean m_callExit;
      DABoolean m_stopRequested;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "Signal/Template/SIGINT_Handler.cc"
//#endif

#endif /* SIGNAL_SIGINT_HANDLER_H */
