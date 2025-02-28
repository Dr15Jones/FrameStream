// -*- C++ -*-
//
// Package:	NileFT - Nile FastTrack
//
// Module:	MessageLog.cc
//
// Description:
//	Implementation of the Nile MessageLogger.
//
// Author:	Dan Riley
// Created:	Thu Feb  1 16:56:57 EST 1996
// $Id: MessageLog.cc,v 1.13 2002/12/05 21:38:50 cleo3 Exp $
//
// Revision history:
//
// $Log: MessageLog.cc,v $
// Revision 1.13  2002/12/05 21:38:50  cleo3
// Now user stringstream if it is available
//
// Revision 1.12  2000/05/12 20:59:06  dsr
// Changed reportstream into a function so we can manage the initialization
// order problems.
// Added a SYSTEM severity for system non-error messages that should always
// be printed.
// Miscellaneous cleanups and robustness fixes for MessageLog.
//
// Revision 1.11  2000/02/25 14:59:18  dsr
// New interface MessageLog::leastSeverity() finds the the lowest severity
// of any of the currently tied Loggers.
//
// Renamed MessageLog report to reporstream; report is now a CPP macro that
// uses leastSeverity to suppress the evaluation of the ostream formatting
// operations for messages that would not be loggged by any Logger.
//
// Revision 1.10  1999/02/18 19:00:27  mkl
// added VERIFY SeverityString -- so stupid to keep enums in a separate 
// place in another library
//
// Revision 1.9  1998/07/27 23:56:02  mkl
// switch to new STL macros
//
// Revision 1.8  1998/07/18 20:28:25  mkl
// seekoff prototype without default 3rd arg bug
//
// Revision 1.7  1997/09/01 15:39:32  sjp
// Removed option flag that was not longer required
//
// Revision 1.6  1997/08/27 03:39:00  sjp
// Updated to new name for bug flags
//
// Revision 1.5  1997/08/06 14:44:32  sjp
// Updated the bug flags
//
// Revision 1.4  1997/07/07 16:15:03  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.3  1997/04/11 14:40:19  sjp
// Added fix for MWERKS
//
// Revision 1.2  1997/03/31 14:55:07  sjp
// Added `filename-only' includes
//
// Revision 1.1  1997/01/31 18:53:15  sjp
// Real class to handle messaging
//
// Revision 1.6  1996/02/12 23:50:29  dsr
// Moved nullfac into MessageLog class
//
// Revision 1.5  1996/02/06 20:20:08  dsr
// Move multimap stuff out of the class declaration, into the implementation.
//
// Revision 1.4  1996/02/06 15:56:52  dsr
// Added a Tie(facility) member to Logger.
// Added UnTie(logger) static member to MessageLog.
// ~Logger calls UnTie to correctly deal with Logger deletion.
//
// Revision 1.3  1996/02/05 17:59:10  dsr
// Split off LogStream class implimentation into a separate file.
//
// Revision 1.2  1996/02/04 19:10:14  dsr
// LogStream now automatically does a Dump() if this is a DEBUG stream or
// the Severity is ALERT or worse.  Use of 'dump' in a stream is discouraged,
// and may be removed later.
//
// Revision 1.1  1996/02/02 23:25:52  dsr
// New MessageLog class supports flexible routing and reporting of messages
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>

// Include files
#include "ToolBox/MessageLog.h"

#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#  include <multimap.h>
#else
#  include <map>
#endif
#include "STLUtility/fwd_multimap.h"

//
// character translations of severity levels; must match the enum
// in Utility/Utility/Severity.h!!! (not my fault -dsr)
//
static const char *SeverityLevels[] = {
   "SYSTEM",		// non-error events that should always be logged
   "EMERGENCY",		// fatal
   "ALERT",		// requires immediate action
   "CRITICAL",		// serious
   "ERROR",
   "WARNING",
   "NOTICE",		// "normal but significant"
   "INFO",		// informational
   "VERIFY",		// verify
   "DEBUG"		// debug
};

//
// Static member definitions
//

// should not be Logger* -- FIXME
typedef STL_MULTIMAP( string, MessageLog::Logger* ) LogMap;

// Map to match a facility to a set of loggers
//MessageLog::LogMap MessageLog::_loggers;
static LogMap* l_loggers;

// flag whether default log streams have been initialized
//bool MessageLog::_init = false;
static bool l_init = false;

inline static void
initML()
{
   if (!l_init) {
      l_init = true;
      l_loggers = new LogMap ;
   }
}

//
// Constructors and destructor
//
MessageLog::MessageLog()
   : nullfac(".")
{
   initML();
}

// MessageLog::MessageLog(const MessageLog &t)
// {
// }

MessageLog::~MessageLog()
{
}

//
// Assignment operator
//
// const MessageLog &
// MessageLog::operator=(const MessageLog &t)
// {
// }

//
// stuff some basic info into the msgstreambuf for later recovery
//
void
MessageLog::msgstreambuf::setLog(const string &f,
				 Severity s,
				 MessageLog *m)
{
   m_facility = f;
   m_severity = s;
   m_meslog = m;
}

//
// called when the msgstream is flushed; null terminate our message,
// dispatch it, and reset the stream.
//
int
MessageLog::msgstreambuf::sync()
{
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
   sputc(0);
#endif
   m_meslog->Log(m_severity, m_facility, str(), 0);
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
   freeze(0);
#if defined(SEEKOFF_PROTOTYPE_WITHOUT_DEFAULT_3RDARG_BUG)
   seekoff(0, ios::beg, ios::in | ios::out );
#else
   seekoff(0, ios::beg );
#endif
#else
   static string kNull;
   str(kNull);
#endif
   return 0;
}

//
// Return our msgstream set for the given severity and facility
//
ostream&
MessageLog::operator()(Severity severity)
{
   m_os.setLog(nullfac, severity, this);
   return m_os;
}

ostream&
MessageLog::operator()(Severity severity, const char* facility)
{
   return ( operator()( severity , string(facility) ) ) ;
}

ostream&
MessageLog::operator()(Severity severity, const string& facility)
{
   m_os.setLog(facility, severity, this);
   return m_os;
}

//
// dispatch a message to the loggers for a given facility -- would
// this be better done in the individual loggers??
//
void
MessageLog::Log(Severity severity,
		const string& facility,
		const string& logmsg,
		Messenger *messenger)
{
   string fac = facility;

   // dispatch is hierarchical, so work our way down the dots, trying
   // each shortening.
   while (fac.length() > 0) {
      if ((*l_loggers).find(fac) != (*l_loggers).end()) {
	 LogMap::iterator i = (*l_loggers).lower_bound(fac);
	 while (i != (*l_loggers).end() && (*i).first == fac) {
	    (*i++).second->Log(severity, facility, logmsg, messenger);
	 }
      }
#if defined(OLD_CXX_STRING_CLASS_BUG)
      size_t npos = -1 ;
      size_t nullfacLength = nullfac.length() ;
      size_t dot ;
      if ( fac.length() < nullfacLength ) {
	 dot = npos ;
      }
      else {
	 dot = fac.length() - nullfacLength ;
      }
      while ( ( dot != npos ) &&
	      ( fac( dot , nullfacLength ) != nullfac ) ) {
	 --dot ;
      }
      if ( dot != npos ) {
	 fac = fac( 0 , dot ) ;
      }
#else
      size_t dot = fac.rfind(nullfac);
#if defined(NPOS_IS_GLOBAL_CONSTANT_BUG)
      if (dot != NPOS)
#else
      if (dot != string::npos)
#endif
      {
	 fac.resize(dot);
      }
#endif
      else {
	 // last chance match  -- will be shortened to 0 on the next
	 // iteration (probably too clever for its own good)
	 fac = nullfac;
      }
   }
}

//
// Tie a facility to a logger
//
void
MessageLog::Tie(const string& facility, MessageLog::Logger& logger)
{
   initML(); // could be called before any instance constructed
   (*l_loggers).insert(LogMap::value_type(facility, &logger));
}

//
// UnTie a Logger
//
void
MessageLog::UnTie(MessageLog::Logger& logger)
{
   initML(); // could be called before any instance constructed
   LogMap::iterator i = (*l_loggers).begin();
   while (i != (*l_loggers).end()) {
      LogMap::iterator j = i++;
      if ((*j).second == &logger) {
	 (*l_loggers).erase(j);
      }
   }
}

//
// find the least serious severity of any of our Loggers
//
Severity
MessageLog::leastSeverity() const
{
   assert(l_loggers != 0);
   Severity least = EMERGENCY;

   LogMap::iterator i = (*l_loggers).begin();
   while (i != (*l_loggers).end()) {
      Severity s = (*i).second->getSeverity();
      if (s > least) {
	 least = s;
      }
      ++i;
   }
   return least;
}

//
// Destructor for Logger embedded class
//
MessageLog::Logger::~Logger()
{
   MessageLog::UnTie(*this);
}

//
// Translate a severity into a string
//
const char*
MessageLog::Logger::SeverityString(Severity severity)
{
   //bounds check -- FIXME!!
   return SeverityLevels[severity];
}

//
// Tie this logger to a facility
//
void
MessageLog::Logger::Tie(const string& facility)
{
   MessageLog::Tie(facility, *this);
}

//
// virtual fn. to decide if we should add a Dump().
//
bool
MessageLog::Logger::Dumpit(Severity)
{
   return true;
}

#if defined(Darwin)
typedef string _multimap_key_ ;
typedef MessageLog::Logger* _multimap_contents_ ;
typedef less< _multimap_key_ > _multimap_compare_ ;

#include "STLUtility/instantiate_multimap.h"
typedef pair<const string, MessageLog::Logger*> _pair_type_;
template std::_Rb_tree<string,_pair_type_, std::_Select1st<_pair_type_>, std::less<string>,std::allocator<_pair_type_> >;
#endif
