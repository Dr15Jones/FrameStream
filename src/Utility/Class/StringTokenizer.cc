// -*- C++ -*-
//
// Package:     Utility
// Module:      StringTokenizer
// 
// Description: please see header file for detailed description
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Sat Aug 22 16:25:35 EDT 1998
// $Id: StringTokenizer.cc,v 1.6 2000/03/02 16:59:32 mkl Exp $
//
// Revision history (at end of file)
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
#include "Utility/StringTokenizer.h"

// STL classes
#include <string>
#include <deque>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "Utility.StringTokenizer" ;

//
// static data member definitions
//

//
// constructors and destructor
//
StringTokenizer::StringTokenizer( const string& aString, 
				  char aDelimiter,
				  ParsingFunction iParsingFunction )
{
   m_tokens = (*iParsingFunction)( aString, aDelimiter );
}

// StringTokenizer::StringTokenizer( const StringTokenizer& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

StringTokenizer::~StringTokenizer()
{
}

//
// assignment operators
//
// const StringTokenizer& StringTokenizer::operator=( const StringTokenizer& rhs )
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
DABoolean
StringTokenizer::hasMoreElements() const
{
   return ! m_tokens.empty();
}

string
StringTokenizer::nextElement()
{
   string nextElement( m_tokens.front() );
   m_tokens.pop_front();

   return nextElement;
}

//
// static member functions
//
StringTokenizer::Tokens
StringTokenizer::parseString( const string& aString, char aDelimiter )
{
   Tokens returnValue;

   string::size_type i=0;
   do {
      i = aString.find_first_not_of( aDelimiter, i );
      string::size_type j = aString.find( aDelimiter, i+1 );
      if( i >= j ) break;
      string token( aString.substr( i, j-i ) );
      i=j+1;
      returnValue.push_back( token );
   } while( i>0 && i<aString.size());

   return returnValue;
}

// -----------------------------------------------------------------
// Revision history
//
// $Log: StringTokenizer.cc,v $
// Revision 1.6  2000/03/02 16:59:32  mkl
// new StringTokenizer parse handling
//
// Revision 1.5  1999/11/18 20:02:02  mkl
// go back to previous implementation of StringTokenizer; new NoSkipStringTokenizer uses new implementation
//
// Revision 1.4  1999/11/16 14:20:47  mkl
// StringTokenizer: allow specifying if multiple separators should be counted or skipped
//
// Revision 1.3  1998/08/24 21:16:07  mkl
// sigh: handle null strings correctly
//
// Revision 1.2  1998/08/24 15:51:08  mkl
// handle null string properly
//
// Revision 1.1  1998/08/22 21:58:26  mkl
// new StringTokenizer to parse strings into substrings based on a delimiter
//

