// -*- C++ -*-
//
// Package:     <Signal>
// Module:      SignalHandler
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Fri Apr 30 16:28:25 EDT 1999
// $Id: SignalHandler.cc,v 1.1.1.1 1999/05/02 02:39:56 mkl Exp $
//
// Revision history
//
// $Log: SignalHandler.cc,v $
// Revision 1.1.1.1  1999/05/02 02:39:56  mkl
// imported sources
//

#include "Experiment/Experiment.h"

// system include files
#include <signal.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "Signal/SignalHandler.h"
#include "Signal/EventHandler.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "Signal.SignalHandler" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SignalHandler.cc,v 1.1.1.1 1999/05/02 02:39:56 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//
SignalHandler* SignalHandler::m_instance=0;
EventHandler* SignalHandler::m_signalHandlers[ SignalHandler::kNumOfSignals ];

//
// constructors and destructor
//
SignalHandler::SignalHandler()
{
}

// SignalHandler::SignalHandler( const SignalHandler& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SignalHandler::~SignalHandler()
{
}

//
// assignment operators
//
// const SignalHandler& SignalHandler::operator=( const SignalHandler& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
EventHandler* 
SignalHandler::registerHandler( Signal iSigNum, 
				EventHandler* iEventHandler )
{
   // save old EventHandler
   EventHandler* oldEventHandler = m_signalHandlers[ iSigNum ];
   
   // store new one in same slot
   m_signalHandlers[ iSigNum ] = iEventHandler;

   // register the dispatcher to handle this signal
   if( ::signal( iSigNum, SIG_IGN ) != SIG_IGN )
   {
      ::signal( iSigNum, dispatcher );
   }
//   struct sigaction sa;
//   sa.sa_handler = dispatcher;
//   sigemptyset( &sa.sa_mask );
//   sa.sa_flags = 0;
//   sigaction( int( iSigNum ), &sa, 0 );


   return oldEventHandler;
}

DABoolean 
SignalHandler::removeHandler( Signal iSigNum )
{
   DABoolean returnValue = false;
   
   if( 0 != m_signalHandlers[ iSigNum ] )
   {
      m_signalHandlers[ iSigNum ]=0;

      // clear mask
      ::signal( iSigNum, SIG_DFL );

      returnValue = true;
   }

   return returnValue;
}

//
// const member functions
//

//
// static member functions
//
void 
SignalHandler::dispatcher( int iSignalNum )
{
   // turn into enum
   Signal theSignal = Signal( iSignalNum );

   // perform sanity check...
   EventHandler* handler = m_signalHandlers[ theSignal ];
   if( handler != 0 )
   {
      // reset itself
      ::signal( theSignal, dispatcher );
      
      // dispatch signal
      handler->handleSignal( theSignal );
   }
}

SignalHandler* 
SignalHandler::instance()
{
   if( 0 == m_instance )
   {
      m_instance = new SignalHandler();
   }
   return m_instance;
}
