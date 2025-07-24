// -*- C++ -*-
//
// Package:     <Signal>
// Module:      SIGINT_Handler
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Fri Apr 30 17:03:28 EDT 1999
// $Id: SIGINT_Handler.cc,v 1.5 2002/12/10 19:24:43 cdj Exp $
//
// Revision history
//
// $Log: SIGINT_Handler.cc,v $
// Revision 1.5  2002/12/10 19:24:43  cdj
// if an interrupt signal is caught when no terminal is attached, exit the job
//
// Revision 1.4  2002/08/16 18:46:18  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.3  1999/12/21 20:34:58  mkl
// added SIGINTHandler::reset method
//
// Revision 1.2  1999/08/26 03:45:01  mkl
// ctrl-c signal: give option to completely exit out of suez (the fast way) or just stop the event loop
//
// Revision 1.1.1.1  1999/05/02 02:39:56  mkl
// imported sources
//

#include "Experiment/Experiment.h"

// system include files
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>


// user include files
//#include "Experiment/report.h"
#include "Signal/SIGINT_Handler.h"

using namespace std;
//
// constants, enums and typedefs
//

static const char* const kFacilityString = "Signal.SIGINT_Handler" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SIGINT_Handler.cc,v 1.5 2002/12/10 19:24:43 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
SIGINT_Handler::SIGINT_Handler( DABoolean iCallExit )
   : m_callExit( iCallExit ),
     m_stopRequested( false )
{
}

// SIGINT_Handler::SIGINT_Handler( const SIGINT_Handler& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SIGINT_Handler::~SIGINT_Handler()
{
}

//
// assignment operators
//
// const SIGINT_Handler& SIGINT_Handler::operator=( const SIGINT_Handler& rhs )
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
void
SIGINT_Handler::handleSignal( Signal iSignal )
{
   assert( iSignal == SignalHandler::kSigInt );

   // If we are not connected to a terminal, exit 
   if( !isatty(STDIN_FILENO) ) {
      ::exit( 1 );
   }

   // keep track if user wants really out!
   DABoolean exitRequested = false;
   if( false == m_callExit )
   {
      m_stopRequested = promptUser( "stop?" );
      
      // if the user wants to stop, maybe he wants to get out completely?
      if( true == m_stopRequested )
      {
	 exitRequested = promptUser( "completely exit suez?" );
      }
   }
   else
   {
      exitRequested = promptUser( "exit?" );
   }

   // if a real exit is the way to go, get out asap
   if( true == exitRequested )
   {
      ::exit( 1 );
   }
}

DABoolean
SIGINT_Handler::promptUser( const char* iPrompt )
{
   DABoolean returnValue = false;

   cout << iPrompt << " (y/n)" << std::endl;
   char reply;
   cin >> reply;
   if( 'y' == reply || 'Y' == reply ) returnValue = true;

   return returnValue;
}

void
SIGINT_Handler::reset()
{
   m_stopRequested = false;
}

//
// const member functions
//
DABoolean
SIGINT_Handler::isStopRequested() const
{
   return m_stopRequested;
}

//
// static member functions
//
