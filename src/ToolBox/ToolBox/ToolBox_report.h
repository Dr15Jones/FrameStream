#if !defined(TOOLBOX_TOOLBOX_REPORT_H)
#define TOOLBOX_TOOLBOX_REPORT_H
// -*- C++ -*-
//
// Package:     TooBox
// Module:      ToolBox_report
// 
// Description: Declare report object to be an instance of MessageLog class
//
// Usage:
//   ostream& report( Severity severity ,
//		      const char* facility = 0 )
//		- global object to handle messages
//
// Author:      Simon Patton
// Created:     Mon Jun  3 12:45:03 EDT 1996
// $Id: ToolBox_report.h,v 1.8 2002/08/16 19:34:01 cleo3 Exp $
//
// Revision history
//
// $Log: ToolBox_report.h,v $
// Revision 1.8  2002/08/16 19:34:01  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.7  2000/05/12 20:59:19  dsr
// Changed reportstream into a function so we can manage the initialization
// order problems.
// Added a SYSTEM severity for system non-error messages that should always
// be printed.
// Miscellaneous cleanups and robustness fixes for MessageLog.
//
// Revision 1.6  2000/02/25 14:59:29  dsr
// New interface MessageLog::leastSeverity() finds the the lowest severity
// of any of the currently tied Loggers.
//
// Renamed MessageLog report to reporstream; report is now a CPP macro that
// uses leastSeverity to suppress the evaluation of the ostream formatting
// operations for messages that would not be loggged by any Logger.
//
// Revision 1.5  1997/09/01 15:38:10  sjp
// Modified to make exclusive use of MessageLog
//
// Revision 1.4  1997/08/27 03:38:46  sjp
// Updated to new name for bug flags
//
// Revision 1.3  1997/08/20 18:15:07  sjp
// Added string header file
//
// Revision 1.2  1997/08/14 11:42:35  sjp
// Mods to run under CW Pro 1
//
// Revision 1.1  1997/07/08 14:32:56  sjp
// File replaces functions.h
//
// Revision 1.5  1997/04/11 14:43:29  sjp
// Added filename-only option
//
// Revision 1.4  1997/02/17 20:04:07  sjp
// Installed MessgeLog messaging system
//
// Revision 1.3  1996/11/04 16:04:30  sjp
// Allowed for 'filename-only' include, for use with MWERKS
//
// Revision 1.2  1996/07/16 19:04:48  sjp
// Restructed Libraries
// Put relative pathnames into all includes
//
// Revision 1.1.1.1  1996/06/04 14:44:53  sjp
// New library files containing ToolBox Functions
//

// system include files
#include <iostream>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Utility/Severity.h"
#include "ToolBox/MessageLog.h"

// forward declarations

// STL include files

//
// externs (i.e. globals)
//

MessageLog& reportstream();

//
// The define below works as follows:
//
// report(DEBUG, "Bart") << "Eat my shorts!" << std::endl;
//
// expands to
//
// DEBUG > reportstream.leastSeverity() ?
//        reportstream(DEBUG, "Bart") : reportstream(DEBUG, "Bart")
//        << "Eat my shorts!" << std::endl;
//
// Parenthesized to show operator precedence
//
// DEBUG > reportstream.leastSeverity() ?
//        reportstream(DEBUG, "Bart") : 
//        (reportstream(DEBUG, "Bart") << "Eat my shorts!" << std::endl);
//
// so the expression with the messages is only evaluated if
// leastSeverity() is DEBUG or greater.
//
// This mystical form was used rather than a more straightforward if
// expression because some user code saves references to report.
//
// This will fall over miserably if anyone has used the single
// argument form of operator(); fortunately, this form was never
// documented for CLEO3 use.
//
#define report(severity, facility) \
    severity > reportstream().leastSeverity() ? \
        (reportstream())(severity, facility) : \
        (reportstream())(severity, facility)

// inline function definitions

#endif /* TOOLBOX_TOOLBOX_REPORT_H */
