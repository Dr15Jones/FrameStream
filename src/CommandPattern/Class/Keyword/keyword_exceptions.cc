// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      keyword_exceptions
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Jul 18 18:27:49 EDT 2003
// $Id: keyword_exceptions.cc,v 1.1 2003/09/19 20:45:35 cdj Exp $
//
// Revision history
//
// $Log: keyword_exceptions.cc,v $
// Revision 1.1  2003/09/19 20:45:35  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#define SSTREAM strstream
#else
#include <sstream>
#define SSTREAM stringstream
#endif

// user include files
//#include "Experiment/report.h"
#include "CommandPattern/Keyword/keyword_exceptions.h"


//
// constants, enums and typedefs
//

namespace CommandPattern
{
namespace Keyword
{
const char*
TooFewArgsException::what() const {
   if( m_result.size() == 0 ) {
      SSTREAM stream;
      stream <<m_keyword <<" requires at least "<<m_need<<" arguments but was only given "<<m_got<<ends;
      m_result = stream.str();
   }
   return m_result.c_str();
}

const char*
TooManyArgsException::what() const {
   if( m_result.size() == 0 ) {
      SSTREAM stream;
      stream <<m_keyword <<" requires no more than "<<m_need<<" arguments but was given "<<m_got<<ends;
      m_result = stream.str();
   }
   return m_result.c_str();
}

const char*
WrongNumberArgsException::what() const {
   if( m_result.size() == 0 ) {
      SSTREAM stream;
      stream <<m_keyword <<" needs a different number of arguments than "<<m_got<<ends;
      m_result = stream.str();
   }
   return m_result.c_str();
}

const char*
UnknownArgException::what() const {
   if( m_result.size() == 0 ) {
      m_result = m_keyword + " was passed the unknown argument \""
	 +m_arg+"\"";
   }
   return m_result.c_str();
}

} //namespace Keyword
} //namespace CommandPattern
