#if !defined(COMMANDPATTERN_PARAMETER_SPECIAL_CC)
#define COMMANDPATTERN_PARAMETER_SPECIAL_CC
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Parameter_special
// 
// Description: Parameter template specializations 
//                 (for various standard types that can't use 
//                  default implementation)
//
// Implementation:
//
// Author:      Martin Lohner
// Created:     Tue Mar 10 10:19:10 EST 1998
// $Id: Parameter_special.cc,v 1.14 2000/07/28 17:03:47 mkl Exp $
//
// Revision history (at end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <ctype.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string.h>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/Parameter.h"

// STL classes
#include <string.h>

//
// constants, enums and typedefs
//

FILESCOPE_IN_TEMPLATE_CC_BUG const char* const 
kFacilityStringSpecial = "CommandPattern.Parameter_special" ;

//
// utility functions
//
static
DABoolean
stringContainsWhiteSpace( const string& iString )
{
   DABoolean returnValue = false;

   for( string::const_iterator it = iString.begin();
	it != iString.end();
	++it )
   {
      if( isspace( int( *it ) ) ) {
	 returnValue = true;
	 break;
      }
   }

   return returnValue;
}

//
// static data member definitions
//

//
// member functions
//

// --------------- string -----------------------
template <>
void 
Parameter< string >::setValue( string& value )
{
   assert( 2 <= m_argc );

   if( 2 < m_argc ) {
      report( SYSTEM, kFacilityStringSpecial )
	 << "will ignore extra arguments!" << endl;
   }

   value = getArgument( 1 );
}

// --------------- bool -------------------------
template <>
void 
Parameter< DABoolean >::setValue( DABoolean& value )
{
   assert( 2 <= m_argc );

   if( 2 < m_argc ) {
      report( SYSTEM, kFacilityStringSpecial )
	 << "will ignore extra arguments!" << endl;
   }

   if(    't' == getArgument(1)[0] 
       || 'T' == getArgument(1)[0] ) {
      value = true;
   } else 
   if(    'f' == getArgument(1)[0] 
       || 'F' == getArgument(1)[0] ) {
      value = false;
   }
   else {
      report( SYSTEM, "Suez" )
	 << "value must start with [TFtf]" << endl;
   }
}

template <>
int
Parameter<DABoolean>::listHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;

   if( true == value() ) {
      report( SYSTEM, "Suez" ) << "DABoolean: true" << endl;
   }
   else {
      report( SYSTEM, "Suez" ) << "DABoolean: false" << endl;
   }

   return returnValue;
}

// ------------------- vector ----------------------------
// since template specialization doesn't work with our compilers,
// use old-fashioned macros
//template< class T >
//int
//Parameter< vector< T > >::listHandler()
#define PARAMETER_VECTOR_LISTHANDLER( T ) \
template <> \
int \
Parameter< vector< T > >::listHandler() \
{ \
   Command::Result returnValue = Command::COMMAND_OK; \
\
   ostream& os = report( SYSTEM, kFacilityStringSpecial ); \
   os << className() << ": "; \
   os << "size=" << value().size() << ": "; \
   vector< T >::const_iterator itEnd = value().end(); \
   for( vector< T >::const_iterator it = value().begin(); \
	it != itEnd; \
	++it ) \
   { \
      if( it != value().begin() ) { os << " "; } \
      os << *it; \
   } \
   if( value().empty() ) { os << "empty"; } \
   os << endl; \
\
   return returnValue; \
}

// since template specialization doesn't work with our compilers,
// use old-fashioned macros
//template<>
//int
//Parameter< vector< string > >::listHandler()
#define PARAMETER_VECTOR_STRING_LISTHANDLER \
template <> \
int \
Parameter< vector< string > >::listHandler() \
{ \
   Command::Result returnValue = Command::COMMAND_OK; \
\
   ostream& os = report( SYSTEM, kFacilityStringSpecial ); \
   os << className() << ": "; \
   os << "size=" << value().size() << ": "; \
   vector< string >::const_iterator itEnd = value().end(); \
   for( vector< string >::const_iterator it = value().begin(); \
	it != itEnd; \
	++it ) \
   { \
      if( it != value().begin() ) { os << " "; } \
      DABoolean containsWhiteSpace = stringContainsWhiteSpace( *it ); \
      if( true == containsWhiteSpace ) { os << "{"; } \
      os << *it; \
      if( true == containsWhiteSpace ) { os << "}"; } \
   } \
   if( value().empty() ) { os << "empty"; } \
   os << endl; \
\
   return returnValue; \
}

//template< class T >
//void 
//Parameter< vector< T > >::setValue( vector< T >& value )
#define PARAMETER_VECTOR_SETVALUE( T ) \
template <> \
void \
Parameter< vector< T > >::setValue( vector< T >& value ) \
{ \
   assert( 2 <= m_argc ); \
\
   DABoolean statusOK = true; \
   vector< T > tempVector; \
   for( Count i=1; i<(Count)m_argc; ++i ) \
   { \
      T tempValue; \
      istrstream str( getArgument( i ) ); \
      str >> tempValue; \
      if( ios::failbit == str.fail() ) { \
	 report( SYSTEM, kFacilityStringSpecial ) \
	    << "bad argument; can't interpret" << endl; \
\
	 statusOK = false; \
	 break; \
      } \
\
      tempVector.push_back( tempValue ); \
   } \
\
   if( true == statusOK ) { \
      value = tempVector; \
   } \
}

//template<>
//void 
//Parameter< vector< string > >::setValue( vector< string >& value )
#define PARAMETER_VECTOR_STRING_SETVALUE \
template <> \
void \
Parameter< vector< string > >::setValue( vector< string >& value ) \
{ \
   assert( 2 <= m_argc ); \
\
   /* first clear out vector */ \
   value.erase( value.begin(), value.end() ); \
\
   for( Count i=1; i<(Count)m_argc; ++i ) \
   { \
      string tempValue( getArgument( i ) ); \
      value.push_back( tempValue ); \
   } \
}

// easy way to custom build the className method
#define PARAMETER_VECTOR_CLASSNAME( Tname ) \
template <> \
const char* \
Parameter< vector< Tname > >::className() \
{ return "vector<" #Tname ">" ; }

// define macro (since template instantiation doesn't work)
#define INSTANTIATE_PARAMETER_VECTOR( T ) \
PARAMETER_VECTOR_CLASSNAME( T ) \
PARAMETER_VECTOR_LISTHANDLER( T ) \
PARAMETER_VECTOR_SETVALUE( T ) \
template class Parameter< vector< T > >;

// define special string macro (since template instantiation doesn't work)
#define INSTANTIATE_PARAMETER_VECTOR_STRING \
PARAMETER_VECTOR_CLASSNAME( string ) \
PARAMETER_VECTOR_STRING_LISTHANDLER \
PARAMETER_VECTOR_STRING_SETVALUE \
template class Parameter< vector< string > >;

//
// const member functions
//

//
// static member functions
//


// ------------------------------------------------------------------
// Revision history
//
// $Log: Parameter_special.cc,v $
// Revision 1.14  2000/07/28 17:03:47  mkl
// preserve tcl grouping with curly brackets in vector parameters
//
// Revision 1.13  2000/06/01 18:02:25  mkl
// shorten some system-level kFacilityStrings to 'Suez' for better readability
//
// Revision 1.12  2000/06/01 17:49:29  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.11  2000/05/12 15:44:14  mkl
// reorder instantiation directives for Parameter of vector of T to have className directive first
//
// Revision 1.10  2000/01/04 20:53:34  mkl
// now print type with parameter value
//
// Revision 1.9  1998/11/09 19:31:58  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.8  1998/09/23 19:04:56  mkl
// typename; protect against multiple inclusion. All the make egcs happy
//
// Revision 1.7  1998/03/28 18:13:16  mkl
// eliminate g++ warnings (unused this, unsed that)
//
// Revision 1.6  1998/03/16 23:17:10  mkl
// print true/false for bool
//
// Revision 1.5  1998/03/15 00:08:16  mkl
// Parameter< vector< T > >
//
// Revision 1.4  1998/03/14 01:53:02  mkl
// added default value
//
// Revision 1.3  1998/03/12 15:38:38  mkl
// undid inline directive for template specializations because of g++
//
// Revision 1.2  1998/03/12 15:00:22  mkl
// Parameter.h comes from CommandPattern
//
// Revision 1.1  1998/03/11 19:10:42  mkl
// new Parameter sources
#endif /* COMMANDPATTERN_PARAMETER_SPECIAL_CC */
