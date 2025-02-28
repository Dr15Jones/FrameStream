// -*- C++ -*-
//
// Package:	NileFT - Nile FastTrack
//
// Module:	LogStream.cc
//
// Description:
//	Implementation of Isis ostream logger
//
// Author:	Dan Riley
// Created:	Mon Feb  5 12:50:11 EST 1996
// $Id: LogStream.cc,v 1.4 2000/05/12 20:59:05 dsr Exp $
//
// Revision history:
//
// $Log: LogStream.cc,v $
// Revision 1.4  2000/05/12 20:59:05  dsr
// Changed reportstream into a function so we can manage the initialization
// order problems.
// Added a SYSTEM severity for system non-error messages that should always
// be printed.
// Miscellaneous cleanups and robustness fixes for MessageLog.
//
// Revision 1.3  1997/08/27 03:38:58  sjp
// Updated to new name for bug flags
//
// Revision 1.2  1997/07/07 16:15:00  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1  1997/03/31 14:46:59  sjp
// File required for stand-alone output for MessageLog
//
// Revision 1.3  1996/07/26 19:02:33  dsr
// First cut at a standard administrative interface
// More tweeks to locks and scheduling
//
// Revision 1.2  1996/05/28 15:52:22  dsr
// Overhaul of makefiles and library structure, timestamp logstream
//
// Revision 1.1  1996/02/05 17:56:56  dsr
// Split off from MessageLog.cc
//

#include "Experiment/Experiment.h"

// Include files
#include <time.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
// Messenger not currently used (sjp)
//#include "Messenger.h"
#include "ToolBox/MessageLog.h"



//
// LogStream -- by default, DEBUG streams always dump, also dump for
// ALERT or worse.
//
bool
LogStream::Dumpit(Severity severity)
{
   // IF this is a debug stream OR this is a very serious message,
   // then log a dump (if we can).
   return Logit(DEBUG) || severity <= ALERT;
}

//
// Log method for the LogStream class.
//
void
LogStream::Log(Severity severity,
	       const string& facility,
	       const string& logmsg,
	       Messenger* messenger)
{
   if (Logit(severity)) {
      time_t now = ::time(0);
      
      m_out << ::ctime(&now)
	    << "%" << facility << "-" << SeverityString(severity) << ": "
	    << logmsg;
// Messenger not currently used (sjp)
//      if (messenger != 0 && Dumpit(severity)) {
//	 messenger->Dump(m_out);
//      }
//
      m_out << flush;
   }
}
