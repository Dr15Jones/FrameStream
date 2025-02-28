// -*- C++ -*-
//
// Package:     <Utility>
// Module:      StringWrapper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Mon Nov 24 13:14:33 EST 1997
// $Id: StringWrapper.cc,v 1.2 1998/07/06 15:43:42 mkl Exp $
//
// Revision history
//
// $Log: StringWrapper.cc,v $
// Revision 1.2  1998/07/06 15:43:42  mkl
// needed to include string first
//
// Revision 1.1  1997/11/24 18:31:25  mkl
// new StringWrapper class to get around g++ proboem with map<string, string>
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "Utility/StringWrapper.h"

// STL classes
#include <string>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "Utility.StringWrapper" ;

//
// static data member definitions
//

//
// constructors and destructor
//
StringWrapper::StringWrapper()
{
}
StringWrapper::StringWrapper( string& iString )
   : m_string( iString ) 
{
}

// StringWrapper::StringWrapper( const StringWrapper& )
// {
// }

StringWrapper::~StringWrapper()
{
}

//
// assignment operators
//
// const StringWrapper& StringWrapper::operator=( const StringWrapper& )
// {
// }

//
// member functions
//
string& 
StringWrapper::operator()() 
{
   return m_string;
}

// const member functions
const string& 
StringWrapper::operator()() const 
{
   return m_string;
}

//
// static member functions
//
