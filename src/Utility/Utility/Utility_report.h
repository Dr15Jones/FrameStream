#if !defined(UTILITY_UTILITY_REPORT_H)
#define UTILITY_UTILITY_REPORT_H
// -*- C++ -*-
//
// Package:     Utility
// Module:      Utility_report
// 
// Description: Declare report object as a function, returning an ostream
//
// Usage:
//    <usage>
//
// Author:      Simon Patton
// Created:     Mon Sep  1 10:34:57 EDT 1997
// $Id: Utility_report.h,v 1.3 2002/08/16 19:44:34 cleo3 Exp $
//
// Revision history
//
// $Log: Utility_report.h,v $
// Revision 1.3  2002/08/16 19:44:34  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.2  1998/04/01 15:56:37  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.1  1997/09/01 15:41:16  sjp
// Declare global report as a function
//

// system include files
#include <iostream>

// user include files
#include "Utility/Severity.h"

// forward declarations
#include <string>

std::ostream& report(Severity severity) ;
std::ostream& report(Severity severity,
		const char* facility) ;
std::ostream& report(Severity severity,
		const std::string& facility) ;

// inline function definitions

#endif /* UTILITY_UTILITY_REPORT_H */
