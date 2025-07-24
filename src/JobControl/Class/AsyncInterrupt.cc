// -*- C++ -*-
//
// Package:     JobControl
// Module:      AsyncInterrupt
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Thu Sep  4 17:22:05 EDT 1997
// $Id: AsyncInterrupt.cc,v 1.7 2000/05/15 15:34:30 mkl Exp $
//
// Revision history
//
// $Log: AsyncInterrupt.cc,v $
// Revision 1.7  2000/05/15 15:34:30  mkl
// switch non-EMERGENCY suez messages to SYSTEM severity level
//
// Revision 1.6  2000/03/22 23:35:16  mkl
// turned std::cin-related couts into report(EMERGENCY) so that can check for errors in logfiles AND avoid too-high report level
//
// Revision 1.5  1998/07/30 21:18:01  mkl
// slight freshen up of asynchronous interrupts
//
// Revision 1.4  1998/07/18 20:20:06  mkl
// solaris complains about non-standard include files
//
// Revision 1.3  1997/10/09 03:47:44  mkl
// added p/P for pause
//
// Revision 1.2  1997/09/18 21:26:45  cdj
// changed Boolean to DABoolean
//
// Revision 1.1  1997/09/05 02:37:17  mkl
// wrap asynchronous interrupt handling in wrapper class
//

#include "Experiment/Experiment.h"

// system include files
#if defined(SUNCC)
#include <unistd.h>
#include <sys/filio.h>
#else
#include <sgtty.h>
#endif

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "JobControl/AsyncInterrupt.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.AsyncInterrupt" ;

//
// static data member definitions
//

//
// constructors and destructor
//
AsyncInterrupt::AsyncInterrupt()
{
}

// AsyncInterrupt::AsyncInterrupt( const AsyncInterrupt& )
// {
// }

AsyncInterrupt::~AsyncInterrupt()
{
}

//
// assignment operators
//
// const AsyncInterrupt& AsyncInterrupt::operator=( const AsyncInterrupt& )
// {
// }

//
// member functions
//
//
// const member functions
//

//
// static member functions
//
DABoolean
AsyncInterrupt::checkForUserInput( void )
{
   DABoolean returnValue = false;

   char input;
   DABoolean status = readTerminal( input );
   //if( status != 0 ) cout << "-I-got string " << input << "\n";
   if( false == status ) return false;

   if(    input == 'q' 
       || input == 'Q' 
       || input == 'e' 
       || input == 'E'
      ) 
   {
      report( SYSTEM, kFacilityString )
	 << "Do you really want to quit (Y/N)? " << std::flush;
      char reply;
      std::cin >> reply;
      if( 'y' == reply || 'Y' == reply ) returnValue = true;
   }
   else if( input == 'p'
         || input == 'P' 
      )
   {
      report( SYSTEM, kFacilityString )
	 << "Pausing... Continue? (y/n)" << std::flush;
      char reply;
      std::cin >> reply;
      returnValue = ('y' == reply || 'Y' == reply) ? false : true;
   }
	    
   return returnValue;
}
	 
DABoolean
AsyncInterrupt::readTerminal( char& oInput )
// -------------------------------------------------------------------
// Checks to see if anything was typed at the terminal without stopping
//  the program, i.e. it performs an asynchronous read.
// -------------------------------------------------------------------
{
   DABoolean haveInput = false;
   int numberOfBytes;

   int res = checkAsynchronousInput( numberOfBytes );

   if( numberOfBytes > 0)
   {
      std::cin.get( oInput );
      haveInput = true;
   }
   else
   {
      oInput = ' ';
      haveInput = false;
   }

   return haveInput;
}



int
AsyncInterrupt::checkAsynchronousInput( int& numberOfBytes )
// -------------------------------------------------------------------
// Checks if there is a completed type-in entry in the standard input
// device. If something has been typed in (*bytes > 0) then a Fortran
// read can be done on unit 5.
// -------------------------------------------------------------------
{
  // check standard input device byte count
  int res = ioctl( 0, FIONREAD, &numberOfBytes );
  if( numberOfBytes <= 0) numberOfBytes = -1;

  return res;
}

