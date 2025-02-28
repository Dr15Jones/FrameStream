// -*- C++ -*-
//
// Package:     OBSchema
// Module:      OBYourItemHere
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      John Doe
// Created:     day-mon-xx
// RCS(Id)
//
// Revision history at end of file
//
#include "Experiment/Experiment.h"

// system include files

// user include files
//#include "Experiment/report.h"
#include "OBSchema/Generated/OBYourItemHere.h"

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "OBSchema.OBYourItemHere" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: one.cc,v 1.1 1999/06/30 21:48:43 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
OBYourItemHere::OBYourItemHere() 
{
}

OBYourItemHere::OBYourItemHere( Type1 iType1, Type2 iType2 )
   : m_type1( iType1 ), m_type2( iType2 ) 
{
}

// OBYourItemHere::OBYourItemHere( const OBYourItemHere& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

OBYourItemHere::~OBYourItemHere()
{
}

//
// assignment operators
//
// const OBYourItemHere& OBYourItemHere::operator=( const OBYourItemHere& rhs )
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

// ----------------------------------------------------------
// Revision history
//
// RCS(Log)
//
