// -*- C++ -*-
//
// Package:	NileFT - Nile FastTrack
//
// Module:	MessageLog.h
//
// Description:
//	Message logging class for NileFT.  Each MessageLog has an
// asssociated omsgstream and omsgstreambuf that accumulate the log
// message.  For multithreaded use, allocate a MessageLog per thread.
//
//	MessageLog maintains a list of Loggers, each entry associated
// with a facility (or facility hierarchy); the Loggers do the actual
// work of recording the message contents.
//
// The MesageLog constructor takes no arguments:
//	MessageLog mlog;
//
// operator() is overloaded; takes two arguments, a severity and an
// optional facility.  For severities, see below.  The facility will
// be used as the matching string to determine which Loggers the
// message is dispatched to.  The return value is an ostream& which
// the message should be streamed into.  The message is dispatched to
// the loggers when the flush() method of the omsgstreambuf is called,
// usually on std::endl.  Returns in the middle of the message should be
// represented with '\n', not std::endl, to avoid premature flushing:
//	mlog(severity, facility) << "My log message" << std::endl;
//
// Tie() is a static function which associates a Logger with a facility
// or facility hiearchy.  NB: there is only one association map, so
// facility/Logger associations are global.
//	Tie("Nile.sm", netlog);
// associates the facility Nile.sm with the Logger netlog such that all
// log messages under the facility hierachy Nile.sm are logged via the
// netlog logger.  netlog will still reject any messages which are below
// its severity level.
//	
// 	The Logger nested class is the parent class for all MessageLog
// Loggers.  The constructor takes a severity level -- only messages
// with that severity or greater will be logged.  Normally, the only
// use for a Logger is to Tie it to a facility hierarchy -- there are
// no other generally useful methods.
//
// Author:	Dan Riley
// Created:	Thu Feb  1 16:35:41 EST 1996
// $Id: MessageLog.h,v 1.12 2002/12/05 21:38:51 cleo3 Exp $
//
// Revision history:
//
// $Log: MessageLog.h,v $
// Revision 1.12  2002/12/05 21:38:51  cleo3
// Now user stringstream if it is available
//
// Revision 1.11  2002/08/16 19:34:00  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.10  2001/09/21 20:20:39  dsr
// fix error in omsgstream initialization of the parent ostream streambuf
//
// Revision 1.9  2000/05/12 20:59:18  dsr
// Changed reportstream into a function so we can manage the initialization
// order problems.
// Added a SYSTEM severity for system non-error messages that should always
// be printed.
// Miscellaneous cleanups and robustness fixes for MessageLog.
//
// Revision 1.8  2000/02/25 14:59:28  dsr
// New interface MessageLog::leastSeverity() finds the the lowest severity
// of any of the currently tied Loggers.
//
// Renamed MessageLog report to reporstream; report is now a CPP macro that
// uses leastSeverity to suppress the evaluation of the ostream formatting
// operations for messages that would not be loggged by any Logger.
//
// Revision 1.7  1999/08/23 20:03:15  mkl
// Logger method has to be 'const'
//
// Revision 1.6  1998/04/01 15:41:07  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.5  1997/09/01 15:38:54  sjp
// Severity definition moved to separate file
//
// Revision 1.4  1997/08/14 11:42:31  sjp
// Mods to run under CW Pro 1
//
// Revision 1.3  1997/07/07 16:15:47  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.2  1997/03/31 14:52:30  sjp
// Added `filename-only' includes
//
// Revision 1.1  1997/01/31 18:51:44  sjp
// Real class to handle messaging
//
// Revision 1.2  1996/07/26 19:02:21  dsr
// First cut at a standard administrative interface
// More tweeks to locks and scheduling
//
// Revision 1.1  1996/05/28 15:46:04  dsr
// Overhaul of scheduling, locks, makefile and library structure.
//
// Revision 1.5  1996/02/12 23:50:31  dsr
// Moved nullfac into MessageLog class
//
// Revision 1.4  1996/02/06 20:19:32  dsr
// Add setSeverity() and getSeverity() to Logger.
// Make Logger::SeverityString() static.
// Move multimap stuff entirely out of the class declaration.
//
// Revision 1.3  1996/02/06 15:56:54  dsr
// Added a Tie(facility) member to Logger.
// Added UnTie(logger) static member to MessageLog.
// ~Logger calls UnTie to correctly deal with Logger deletion.
//
// Revision 1.2  1996/02/05 17:59:59  dsr
// Added Dumpit() bool fn. to Logger
//
// Revision 1.1  1996/02/02 23:25:54  dsr
// New MessageLog class supports flexible routing and reporting of messages
//
#ifndef NILEFT_MESSAGELOG_H_
#define NILEFT_MESSAGELOG_H_

// Include files
#include <iostream>

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#define MESSAGELOG_BUFFER strstreambuf
#else
#include <sstream>
#define MESSAGELOG_BUFFER std::stringbuf
#endif
#include "Utility/Severity.h"

#if defined(OLD_CXX_STRING_CLASS_BUG)
#include <string>
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */

// Forward declarations

class Messenger;

// Class declaration

class MessageLog {
   public:
      // Base class for the objects that actually write log messages.
      // MessageLog keeps a list of these in the _loggers map.
      class Logger {
	 public:
	    Logger(Severity level) : m_level(level) {};
	    virtual ~Logger();
	    // messenger appears here so that the Isis News Logger
	    // can find the dump info.  This is pretty gross...
	    virtual void Log(Severity severity,
			     const std::string& facility,
			     const std::string& logmsg,
			     Messenger* messenger) = 0;
	    void Tie(const std::string& facility);
	    static const char* SeverityString(Severity severity);
	    void setSeverity(Severity severity) { m_level = severity; }
	    Severity getSeverity() const { return m_level; }
	 protected:
	    // fn. to check if the message meets the severity level
	    // of this logger.
	    bool Logit(Severity severity) { return severity <= m_level; }
	    virtual bool Dumpit(Severity severity);
	 private:
	    Severity m_level;
      };

      // Specialization of Logger for ostreams.
      class LogStream : public Logger {
	 public:
	    LogStream(Severity level,std::ostream& out)
	       : Logger(level), m_out(out) {}
	    ~LogStream() {}
	    void Log(Severity severity,
		     const std::string& facility,
		     const std::string& logmsg,
		     Messenger* messenger);
	 protected:
	    virtual bool Dumpit(Severity severity);
	 private:
	   std::ostream& m_out;
      };

   // Constants
      // Facility separator; also the last chance facility
      const std::string nullfac;
   // Constructors and destructor
      MessageLog();
      MessageLog(const MessageLog &);
      virtual ~MessageLog();
   // Assignment operator(s)
      const MessageLog & operator=(const MessageLog &);
   // Member functions
      // The interface to actually log a message.  Stuffs the severity
      // and facility into the msgstreambuf and then returns the assoc.
      // msgstream.
     std::ostream& operator()(Severity severity);
     std::ostream& operator()(Severity severity,
			  const char* facility) ;
     std::ostream& operator()(Severity severity,
			  const std::string& facility) ;
      // Called by the msgstreambuf
      virtual void Log(Severity severity,
		       const std::string& facility,
		       const std::string& logmsg,
		       Messenger *messenger);
   // Access functions
      Severity leastSeverity() const;
   // Static member functions
      // Associate a logger with a facility hierarchy.
      static void Tie(const std::string& facility, Logger& logger);
      static void UnTie(Logger& logger);
   // Friend classses and functions

      // Implementation details -- basically ostrstream.
      class msgstreambuf : public MESSAGELOG_BUFFER {
	 public:
	    virtual ~msgstreambuf() {}
	    msgstreambuf() : MESSAGELOG_BUFFER() {}
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
	    msgstreambuf(int initial_size) : MESSAGELOG_BUFFER(initial_size) {}
#endif
	    virtual int sync();
	    void setLog(const std::string &f, Severity s, MessageLog *m);
	 private:
	    std::string m_facility;
	    Severity m_severity;
	    MessageLog *m_meslog;
      };

      class omsgstream : public std::ostream {
	 public:
	    omsgstream() :std::ostream(&m_Sb), m_Sb() {
	       init(&m_Sb);
	    }
	    virtual ~omsgstream() {};
	    msgstreambuf* rdbuf() { return &m_Sb; }
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
	    void freeze(int n = 1) { m_Sb.freeze(n); }
	    char *str() { return m_Sb.str(); }
#else
	    std::string str() {return m_Sb.str(); }
#endif
//	    int frozen() { return m_Sb.frozen(); }
	    void setLog(const std::string &f, Severity s, MessageLog *m) {
	       m_Sb.setLog(f, s, m);
	    }
	 private:
	    msgstreambuf m_Sb;
      };

   protected:
   // Protected member functions
   // Protected data members
   private:
   // Private member functions
   // Private data members
      // Ourstd::ostream
      omsgstream m_os;
   // Static data members
};
// Inline functions

// syntactic sugar.
typedef MessageLog::LogStream LogStream;

#endif
