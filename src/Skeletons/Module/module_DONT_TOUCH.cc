// -*- C++ -*-
//
// Package:     <Modname>
// Module:      Modname_DONT_TOUCH.cc
// 
// Description: factory function to create Modname
//
// Implementation:
//     <Notes on implementation>
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
#include "Modname/Modname.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: module_DONT_TOUCH.cc,v 1.3 1998/12/01 21:11:54 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// function definitions
//

extern "C" { 
   Module* makeModule( void ); 
   const char* versionString( void );
}

Module*
makeModule( void )
{
   return new Modname;
}

const char*
versionString( void )
{
   return kTagString;
}
