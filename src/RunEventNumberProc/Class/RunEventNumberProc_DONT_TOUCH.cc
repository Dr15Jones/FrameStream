// -*- C++ -*-
//
// Package:     Processor
// Module:      RunEventNumberProc_DONT_TOUCH
// 
// Description: Miscellaneous methods which the user 
//              is not supposed to touch, 
//              but which need to be present 
//              in the shared processor library.
//
//              1.) Factory method to create processor RunEventNumberProc:
//                  creates a new RunEventNumberProc instance each time 
//                  it is called; it is used by Suez 
//                  to create a Processor after loading in 
//                  the code from a shared library.
//
//              2.) Definition of bind action
//
// Implimentation:
//
// Author:      Martin Lohner
// Created:     Wed Sep 10 01:42:59 EDT 1997
// $Id: RunEventNumberProc_DONT_TOUCH.cc,v 1.3 1998/01/26 23:53:57 mkl Exp $
//
// Revision history
//
// $Log: RunEventNumberProc_DONT_TOUCH.cc,v $
// Revision 1.3  1998/01/26 23:53:57  mkl
// got rid of -DSHARED_MODULE directive -- not needed
//
// Revision 1.2  1998/01/23 05:05:31  mkl
// moved over to new-style factory method
//
// Revision 1.1.1.1  1998/01/13 18:18:10  mkl
// imported RunEventNumberProc sources
//
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "RunEventNumberProc/RunEventNumberProc.h"
#include "Processor/Action.h"                

// STL classes

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.RunEventNumberProc: " ;

//
// function definitions
//

// ---------------------------factory method -------------------
extern "C" {
   Processor* makeProcessor( void );
}

Processor*
makeProcessor( void )
{
   return new RunEventNumberProc;
}

//
// static data member definitions
//

//
// member functions
//
// ---------------- binding method to stream -------------------
void
RunEventNumberProc::bind(
   ActionBase::ActionResult (RunEventNumberProc::*iMethod)( Frame& ),
   const Stream::Type& iStream )
{
   bindAction( iStream, new Action<RunEventNumberProc>( iMethod, this ) );
}

//
// const member functions
//

//
// static member functions
//
