// -*- C++ -*-
//
// Package:     <DBEventHeaderProd>
// Module:      DBEventHeaderProd_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Factory method to create processor DBEventHeaderProd:
//              creates a new DBEventHeaderProd instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Martin Lohner
// Created:     Tue Jun  1 14:15:24 EDT 1999
// $Id: DBEventHeaderProd_DONT_TOUCH.cc,v 1.1.1.1 1999/06/01 18:58:32 mkl Exp $
//
// Revision history
//
// $Log: DBEventHeaderProd_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  1999/06/01 18:58:32  mkl
// imported sources
//
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "DBEventHeaderProd/DBEventHeaderProd.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DBEventHeaderProd_DONT_TOUCH.cc,v 1.1.1.1 1999/06/01 18:58:32 mkl Exp $";
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
   return new DBEventHeaderProd;
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
