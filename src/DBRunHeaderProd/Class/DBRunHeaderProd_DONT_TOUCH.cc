// -*- C++ -*-
//
// Package:     <DBRunHeaderProd>
// Module:      DBRunHeaderProd_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Factory method to create processor DBRunHeaderProd:
//              creates a new DBRunHeaderProd instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Martin Lohner
// Created:     Thu Jul 22 12:18:25 EDT 1999
// $Id: DBRunHeaderProd_DONT_TOUCH.cc,v 1.1.1.1 1999/07/22 18:20:52 aw Exp $
//
// Revision history
//
// $Log: DBRunHeaderProd_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  1999/07/22 18:20:52  aw
// Imported initial DBRunHeaderProd sources
//
//
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "DBRunHeaderProd/DBRunHeaderProd.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DBRunHeaderProd_DONT_TOUCH.cc,v 1.1.1.1 1999/07/22 18:20:52 aw Exp $";
static const char* const kTagString = "$Name:  $";

//
// function definitions
//

extern "C" {
   Producer* makeProducer( void );
   const char* versionString( void );
}

Producer*
makeProducer( void )
{
   return new DBRunHeaderProd;
}

const char*
versionString( void )
{
   return kTagString;
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
