// -*- C++ -*-
//
// Package:     Utility
// Module:      Utility_report
// 
// Description: Declare report object as a function, returning an ostream
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Mon Sep  1 10:34:57 EDT 1997
// $Id: Utility_report.cc,v 1.4 1998/04/01 15:56:32 mkl Exp $
//
// Revision history
//
// $Log: Utility_report.cc,v $
// Revision 1.4  1998/04/01 15:56:32  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.3  1997/09/03 20:05:26  sjp
// Uses CPP macros for STL containers
//
// Revision 1.2  1997/09/01 15:47:48  sjp
// Added flags to avoid symbol confusion
//
// Revision 1.1  1997/09/01 15:40:15  sjp
// Basic implmentation of global report function
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Utility/Utility_report.h"

// STL include files
#include <string>
#include <iostream>

using namespace std;
//
// globals
//

#if !defined(USE_MESSAGELOG_FOR_REPORT)
ostream& report(Severity severity)
{
   if ( ERROR < severity ) {
      return ( cout ) ;
   }
   return ( cerr ) ;
}

ostream& report(Severity severity,
		const char* facility)
{
   report( severity , std::string( facility ) ) ;
}

ostream& report(Severity severity,
		const std::string& facility)
{
   static std::string oldFacility( "" ) ;
   
   if ( facility != oldFacility ) {
      report( severity ) << facility
			 << ": " ;
      oldFacility = facility ;
   }
   return ( report( severity ) ) ;
}
#endif /* USE_MESSAGELOG_FOR_REPORT */

//
// constants, enums and typedefs
//
