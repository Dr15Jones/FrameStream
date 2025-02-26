// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      SourceFormatModule
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Tue Dec  1 22:45:30 EST 1998
// $Id: SourceFormatModule.cc,v 1.2 2000/12/01 20:26:04 cdj Exp $
//
// Revision history
//
// $Log: SourceFormatModule.cc,v $
// Revision 1.2  2000/12/01 20:26:04  cdj
// now includes map
//
// Revision 1.1  1998/12/02 05:55:07  mkl
// towards interacting with Source- and SinkFormats
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <set>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "JobControl/SourceFormatModule.h"

// STL classes
#include <set>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.SourceFormatModule" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SourceFormatModule.cc,v 1.2 2000/12/01 20:26:04 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
SourceFormatModule::SourceFormatModule( BinderType iType )
   : SourceFormat( iType ), Module( "SourceFormatModule", "SourceFormat" )
{
}

// SourceFormatModule::SourceFormatModule( const SourceFormatModule& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SourceFormatModule::~SourceFormatModule()
{
}

//
// assignment operators
//
// const SourceFormatModule& SourceFormatModule::operator=( const SourceFormatModule& rhs )
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

//
// const member functions
//

//
// static member functions
//
string
SourceFormatModule::factorySymbol()
{
   return SourceFormat::factorySymbol();
}
