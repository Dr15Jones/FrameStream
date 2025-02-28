// -*- C++ -*-
//
// Package:     <Interpreter>
// Module:      PythonInterpreter
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Thu Mar  5 19:11:25 GMT 1998
// $Id: PythonInterpreter.cc,v 1.1.1.1 1998/03/11 18:52:18 mkl Exp $
//
// Revision history
//
// $Log: PythonInterpreter.cc,v $
// Revision 1.1.1.1  1998/03/11 18:52:18  mkl
// imported Interpreter sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "Interpreter/PythonInterpreter.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "Interpreter.PythonInterpreter" ;

//
// static data member definitions
//

//
// constructors and destructor
//
PythonInterpreter::PythonInterpreter()
{
}

// PythonInterpreter::PythonInterpreter( const PythonInterpreter& iPythonInterpreter )
// {
//    *this = iPythonInterpreter;
// }

PythonInterpreter::~PythonInterpreter()
{
}

//
// assignment operators
//
// const PythonInterpreter& PythonInterpreter::operator=( const PythonInterpreter& iPythonInterpreter )
// {
//   if( this != &iPythonInterpreter ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iPythonInterpreter );
//   }
//
//   return *this;
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
