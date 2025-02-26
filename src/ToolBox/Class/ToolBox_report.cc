// -*- C++ -*-
//
// Package:     TooBox
// Module:      ToolBox_report
// 
// Description: Declare report object to be an instance of MessageLog class
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Mon Jun  3 14:34:26 EDT 1996
// $Id: ToolBox_report.cc,v 1.7 2000/05/12 20:59:06 dsr Exp $
//
// Revision history
//
// $Log: ToolBox_report.cc,v $
// Revision 1.7  2000/05/12 20:59:06  dsr
// Changed reportstream into a function so we can manage the initialization
// order problems.
// Added a SYSTEM severity for system non-error messages that should always
// be printed.
// Miscellaneous cleanups and robustness fixes for MessageLog.
//
// Revision 1.6  2000/02/25 14:59:18  dsr
// New interface MessageLog::leastSeverity() finds the the lowest severity
// of any of the currently tied Loggers.
//
// Renamed MessageLog report to reporstream; report is now a CPP macro that
// uses leastSeverity to suppress the evaluation of the ostream formatting
// operations for messages that would not be loggged by any Logger.
//
// Revision 1.5  1997/09/01 15:47:45  sjp
// Added flags to avoid symbol confusion
//
// Revision 1.4  1997/09/01 15:38:12  sjp
// Modified to make exclusive use of MessageLog
//
// Revision 1.3  1997/08/14 16:31:54  sjp
// Added missing line storing oldFacility
//
// Revision 1.1  1997/07/08 14:33:10  sjp
// File replaces ToolBox_functions.cc
//
// Revision 1.5  1997/04/11 14:42:29  sjp
// added fielname-only option
//
// Revision 1.4  1997/02/17 20:03:59  sjp
// Installed MessgeLog messaging system
//
// Revision 1.3  1996/11/04 16:03:23  sjp
// Allowed for 'filename-only' include, for use with MWERKS
//
// Revision 1.2  1996/07/16 19:04:17  sjp
// Restructed Libraries
// Put relative pathnames into all includes
//
// Revision 1.1.1.1  1996/06/04 14:44:55  sjp
// New library files containing ToolBox Functions
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "ToolBox/ToolBox_report.h"

//
// globals
//

#if defined(USE_MESSAGELOG_FOR_REPORT)
MessageLog&
reportstream()
{
   static MessageLog* log = new MessageLog();
   return *log;
}
#endif /* USE_MESSAGELOG_FOR_REPORT */

//
// constants, enums and typedefs
//
