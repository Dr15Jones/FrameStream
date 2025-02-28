// -*- C++ -*-
//
// Package:     Processor
// Module:      procname_DONT_TOUCH
// 
// Description: Miscellaneous methods which the user 
//              is not supposed to touch, 
//              but which need to be present 
//              in the shared processor library.
//
//              1.) Factory method to create processor procname:
//                  creates a new procname instance each time 
//                  it is called; it is used by Suez 
//                  to create a Processor after loading in 
//                  the code from a shared library.
//
// Implementation:
//
// Author:      John Doe
// Created:     day-mon-xx
// RCS(Id)
//
// Revision history
//
// RCS(Log)
// 
#include "Experiment/Experiment.h"

// system include files

// user include files
#include "procname/procname.h"

// STL classes

//
// constants, enums and typedefs
//

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
   return new procname;
}
//
// static data member definitions
//

//
// member functions
//

//
// const member functions
//

//
// static member functions
//
