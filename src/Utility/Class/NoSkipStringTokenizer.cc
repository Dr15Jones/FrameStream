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

// user include files
#include "Utility/NoSkipStringTokenizer.h"

// STL classes
#include <string>
#include <deque>

using namespace std;
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
NoSkipStringTokenizer::NoSkipStringTokenizer( const std::string& aString, 
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
NoSkipStringTokenizer::parseString( const std::string& aString, char aDelimiter )
{
   Tokens returnValue;

   std::string::size_type i=0;
   do {
      std::string::size_type j = aString.find( aDelimiter, i );
      std::string token = (j>i) ? aString.substr( i, j-i ) : std::string("");
      i=j+1;
      //cout << "Token=" << token << std::endl;
      returnValue.push_back( token );
   } while( i>0 && i<aString.size());

   return returnValue;
}

