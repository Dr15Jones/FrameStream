#if !defined(EXPERIMENT_REPORT_H)
#define EXPERIMENT_REPORT_H
// -*- C++ -*-
//
// Package:     Experiment
// Module:      report
// 
// Description: declaration of global "report" object.
//
// Usage:
//  std::ostream& report( Severity severity ,
//		      const char* facility = 0 )
//		- global object to handle messages
//
// Author:      Simon Patton
// Created:     Mon Sep  1 10:31:51 EDT 1997
// $Id: report.h,v 1.2 1998/04/01 18:06:33 mkl Exp $
//
// Revision history
//
// $Log: report.h,v $
// Revision 1.2  1998/04/01 18:06:33  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.1  1997/09/01 15:42:54  sjp
// New file to handle global report declaration
//

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Utility/Severity.h"

// forward declarations
#include <iosfwd>

// STL include files
#include <string>

#if defined(USE_MESSAGELOG_FOR_REPORT)
#include "ToolBox/ToolBox_report.h"
#else
#include "Utility/Utility_report.h"
#endif /* USE_MESSAGELOG_FOR_REPORT */

// inline function definitions

#endif /* EXPERIMENT_REPORT_H */
