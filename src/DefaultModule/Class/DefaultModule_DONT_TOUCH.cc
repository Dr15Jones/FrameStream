// -*- C++ -*-
//
// Package:     <DefaultModule>
// Module:      DefaultModule_DONT_TOUCH.cc
// 
// Description: factory function to create DefaultModule
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Thu Feb 18 23:00:13 EST 1999
// $Id: DefaultModule_DONT_TOUCH.cc,v 1.1.1.1 1999/02/22 22:44:38 mkl Exp $
//
// Revision history
//
// $Log: DefaultModule_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  1999/02/22 22:44:38  mkl
// imported sources
//
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "CommandPattern/DefaultModule.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DefaultModule_DONT_TOUCH.cc,v 1.1.1.1 1999/02/22 22:44:38 mkl Exp $";
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
   return new DefaultModule;
}

const char*
versionString( void )
{
   return kTagString;
}
