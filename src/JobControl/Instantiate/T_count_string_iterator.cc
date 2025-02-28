// -*- C++ -*-
//
// Package:     <package>
// Module:      T_count_string_iterator
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Jun 15 15:59:25 EDT 2001
// $Id: T_count_string_iterator.cc,v 1.2 2002/12/06 16:33:18 cleo3 Exp $
//
// Revision history
//
// $Log: T_count_string_iterator.cc,v $
// Revision 1.2  2002/12/06 16:33:18  cleo3
// deal with g++ namespace instantiation bug
//
// Revision 1.1  2001/06/15 21:06:26  cdj
// can now specify data (not) to store in a sink
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
//#include <vector>
//#include <set>
//#include <map>
#include <algorithm>
//#include <utility>

// user include files
//#include "Experiment/report.h"


//
// constants, enums and typedefs
//
#if defined (NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
#undef STD_PREFIX
#define STD_PREFIX
namespace std {
#endif

#if !defined(NO_ITERATOR_TRAITS_BUG)
template 
iterator_traits<string::iterator>::difference_type
STD_PREFIX count(string::iterator, string::iterator, const char&);
#endif

#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
}
#endif
