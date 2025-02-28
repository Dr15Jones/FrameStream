// -*- C++ -*-
//
// Package:     Utility
// Module:      NoSkipStringTokenizer
// 
// Description: please see header file for detailed description
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Thu Nov 18 16:25:35 EDT 1999
// $Id: NoSkipStringTokenizer.cc,v 1.2 2000/03/02 16:59:32 mkl Exp $
//
// Revision history
//
// $Log: NoSkipStringTokenizer.cc,v $
// Revision 1.2  2000/03/02 16:59:32  mkl
// new StringTokenizer parse handling
//
// Revision 1.1  1999/11/18 20:02:01  mkl
// go back to previous implementation of StringTokenizer; new NoSkipStringTokenizer uses new implementation
//
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#include <stdlib.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <deque>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "Utility/NoSkipStringTokenizer.h"

// STL classes
#include <string>
#include <deque>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "Utility.NoSkipStringTokenizer" ;

//
// static data member definitions
//

//
// constructors and destructor
//
NoSkipStringTokenizer::NoSkipStringTokenizer( const string& aString, 
					      char aDelimiter )
   : StringTokenizer( aString, aDelimiter, &NoSkipStringTokenizer::parseString )
{
}

// NoSkipStringTokenizer::NoSkipStringTokenizer( const NoSkipStringTokenizer& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

NoSkipStringTokenizer::~NoSkipStringTokenizer()
{
}

//
// assignment operators
//
// const NoSkipStringTokenizer& NoSkipStringTokenizer::operator=( const NoSkipStringTokenizer& rhs )
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
NoSkipStringTokenizer::Tokens
NoSkipStringTokenizer::parseString( const string& aString, char aDelimiter )
{
   Tokens returnValue;

   string::size_type i=0;
   do {
      string::size_type j = aString.find( aDelimiter, i );
      string token = (j>i) ? aString.substr( i, j-i ) : string("");
      i=j+1;
      //cout << "Token=" << token << endl;
      returnValue.push_back( token );
   } while( i>0 && i<aString.size());

   return returnValue;
}

