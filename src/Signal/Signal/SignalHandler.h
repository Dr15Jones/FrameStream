#if !defined(SIGNAL_SIGNALHANDLER_H)
#define SIGNAL_SIGNALHANDLER_H
// -*- C++ -*-
//
// Package:     <Signal>
// Module:      SignalHandler
// 
// Description: Signal Handler is the Manager object that
//              allows registration of specific event handlers 
//              to handle c signals in an OO way
//
//              Implemented as Singleton
// 
//              (Based on Douglas C. Schmidt's article
//               "Applying Design Patterns To Simplify Signal Handling"
//               in "The C++ Report", April 1998)
// Usage:
//
// It's easy to write a specialized handler for specific types of signals.
// You will have to register your handler with SignalHandler (a singleton)
// so that it can dispatch the signal properly to your handler.
//
// To use it in your code, you'll have to include the proper include files.
// It's usually best to hold onto the old handler and reinstall it after
// you're done with the special handling in your code.
//
//#include "Signal/SignalHandler.h"
//#include "Signal/SIGINT_Handler.h"
//   
//   // install an interrupt handler and save the old handler
//   SIGINT_Handler sigint_handler;
//   EventHandler* oldHandler = 
//      SignalHandler::instance()->registerHandler( SignalHandler::kSigInt, 
//                                                  &sigint_handler );
//
//   while( false == sigint_handler.isStopRequested() )
//   {
//      doSomething();
//   }
//
//   // reinstall the old handler
//   SignalHandler::instance()->registerHandler( SignalHandler::kSigInt,
//                                               oldHandler );
//
//
// Author:      Martin Lohner
// Created:     Fri Apr 30 16:28:22 EDT 1999
// $Id: SignalHandler.h,v 1.2 1999/05/02 15:02:14 mkl Exp $
//
// Revision history
//
// $Log: SignalHandler.h,v $
// Revision 1.2  1999/05/02 15:02:14  mkl
// more documentation
//
// Revision 1.1.1.1  1999/05/02 02:39:56  mkl
// imported sources
//

// system include files
#include <signal.h>

// user include files

// forward declarations
class EventHandler;

class SignalHandler
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      enum Signal { kSigAbrt=SIGABRT, 
		    kSigFpe =SIGFPE, 
		    kSigInt =SIGINT, 
		    kSigSegv=SIGSEGV,
		    kSigTerm=SIGTERM,
		    kNumOfSignals=NSIG
      };

      // ---------- Constructors and destructor ----------------
      virtual ~SignalHandler();

      // ---------- member functions ---------------------------
      EventHandler* registerHandler( Signal iSignal, 
				     EventHandler* iEventHandler );
      DABoolean removeHandler( Signal iSignal );

      // ---------- static member functions --------------------
      static SignalHandler* instance();

   protected:
      // ---------- protected member functions -----------------
      SignalHandler();

   private:
      // ---------- Constructors and destructor ----------------
      SignalHandler( const SignalHandler& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SignalHandler& operator=( const SignalHandler& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------
      // Entry point adapter installed into <sigaction>;
      // must be static method or static (global) function extern "C" function.
      static void dispatcher( int iSignalNum );

      // singleton instance
      static SignalHandler* m_instance;

      // signal slots
      static EventHandler* m_signalHandlers[ kNumOfSignals ];
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "Signal/Template/SignalHandler.cc"
//#endif

#endif /* SIGNAL_SIGNALHANDLER_H */
