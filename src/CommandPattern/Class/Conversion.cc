// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Conversion
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Thu Sep  4 15:35:33 EDT 1997
// $Id: Conversion.cc,v 1.5 2003/01/27 19:12:38 cdj Exp $
//
// Revision history
//
// $Log: Conversion.cc,v $
// Revision 1.5  2003/01/27 19:12:38  cdj
// use stringstream if available
//
// Revision 1.4  2000/01/27 03:47:57  mkl
// simpler Conversion::stringToDigit implementation
//
// Revision 1.3  1999/10/25 18:50:02  mkl
// fixed wrong logic for Parameter< bool > instantiation
//
// Revision 1.2  1999/09/10 02:42:50  mkl
// location of Conversion class has moved
//
// Revision 1.1  1999/09/10 01:04:35  mkl
// 1) new smarter history command.
// 2) new "uppercase" function, since our compilers don't support it yet.
// 3) moved "Conversion" class to CommandPattern (needed by HistoryCommand).
//
// Revision 1.3  1998/02/10 03:32:45  mkl
// fixed nextstop -1 problem
//
// Revision 1.2  1997/09/18 21:26:46  cdj
// changed Boolean to DABoolean
//
// Revision 1.1  1997/09/05 02:37:18  mkl
// wrap asynchronous interrupt handling in wrapper class
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/Conversion.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.Conversion" ;

//
// static data member definitions
//

//
// constructors and destructor
//
Conversion::Conversion()
{
}

// Conversion::Conversion( const Conversion& )
// {
// }

Conversion::~Conversion()
{
}

//
// assignment operators
//
// const Conversion& Conversion::operator=( const Conversion& )
// {
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
long
Conversion::stringToDigit( const char* c, DABoolean& isNumber )
{
   return stringToLong( c, isNumber );
}

long
Conversion::stringToLong( const char* c, DABoolean& isNumber )
{
   long returnValue;
   isNumber = true;

   std::istringstream str( c );
   str >> returnValue;
   // error handling
   if(str.fail() ) {
      report( ERROR, kFacilityString )
         << "bad argument; can't interpret" << std::endl;
      isNumber = false;
   }

   return returnValue;
}

int
Conversion::stringToInt( const char* c, DABoolean& isNumber )
{
   return stringToLong( c, isNumber );
}

unsigned long
Conversion::stringToULong( const char* c, DABoolean& isNumber )
{
   unsigned long returnValue;
   isNumber = true;

   std::istringstream str( c );
   str >> returnValue;
   // error handling
   if( str.fail() ) {
      report( ERROR, kFacilityString )
         << "bad argument; can't interpret" << std::endl;
      isNumber = false;
   }

   return returnValue;
}

unsigned int
Conversion::stringToUInt( const char* c, DABoolean& isNumber )
{
   return stringToULong( c, isNumber );
}


