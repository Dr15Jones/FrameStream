#if !defined(UTILITY_SEVERITY_H)
#define UTILITY_SEVERITY_H
// -*- C++ -*-
//
// Package:     Utility
// Module:      Severity
// 
// Description: Severity level for reporting messages
//
// Usage:
//    include in any file that declares the "report" global object.
//
// Author:      Simon Patton
// Created:     Mon Sep  1 10:36:20 EDT 1997
// $Id: Severity.h,v 1.5 2000/05/13 20:13:59 dsr Exp $
//
// Revision history
//
// $Log: Severity.h,v $
// Revision 1.5  2000/05/13 20:13:59  dsr
// document the five(!) other files that must be updated when the Severity
// enum is touched.
//
// Revision 1.4  2000/05/12 20:59:42  dsr
// Adding the SYSTEM severity level
//
// Revision 1.3  1999/02/12 00:12:09  mkl
// added Verify report level (e.g. for standard pass2 verify messages
//
// Revision 1.2  1999/02/12 00:11:41  mkl
// added Verify report level (e.g. for standard pass2 verify messages
//
// Revision 1.1  1997/09/01 15:40:49  sjp
// New file listing severity levels for messaging
//

//
// constants, enums and typedefs
//

// The severity levels were originally copied from BSD4.3 syslog,
// but additional levels have been added...
//
// !!! ANY changes made here must be reflected in:
//     ToolBox/Class/MessageLog.cc (SeverityLevels[])
//     ToolBox/Class/reportF.cc
//     ToolBox/ToolBox/report.inc
//     Scungili/Scungili/ScungiliSeverity.h
//     InnerTrackFinderProd/Class/scungili_report.cc
// !!! BLECH !!!
//
enum Severity { //READ THE COMMENTS ABOVE BEFORE TOUCHING
   SYSTEM,		// non-error events that should always be logged
   EMERGENCY,		// fatal
   ALERT,		// requires immediate action
   CRITICAL,		// serious
   ERROR,
   WARNING,
   NOTICE,		// "normal but significant"
   INFO,		// informational
   VERIFY,		// verify
   DEBUG		// debug
};

#endif /* UTILITY_SEVERITY_H */
