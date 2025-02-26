// -*- C++ -*-
//
// Package:     Processor
// Module:      STL_AlgoString
// 
// Description: Instantiate algorithms dealing with vector< string >
//
// Implementation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Sat Jul 13 21:45:29 EDT 1997
// $Id: STL_AlgoString.cc,v 1.6 1998/11/06 20:37:02 cdj Exp $
//
// Revision history
//
// $Log: STL_AlgoString.cc,v $
// Revision 1.6  1998/11/06 20:37:02  cdj
// Uses STD_PREFIX (needed for cxx v6.1)
//
// Revision 1.5  1998/06/24 17:28:59  cdj
// added return type to templated function instantiation (needed by cxx 6.0)
//
// Revision 1.4  1998/04/01 17:57:52  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.3  1998/03/27 15:27:00  mkl
// more naming fixups
//
// Revision 1.2  1997/09/04 06:36:12  mkl
// moved JobControl/STL_AlgoString here
//
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(OLD_CXX_STRING_CLASS_BUG)
#include "C++Std/fwd_string.h"
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

#include <vector>
#include <algorithm>

// forward declarations

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP
//
// required for find
#  pragma define_template find< vector<string>::iterator, const string >

#elif defined(__GNUG__)  /* g++ */
// replacement for default find in function.h, because of trouble with 
// vector<string> and operator !=
template <class InputIterator>     
InputIterator find(InputIterator first, InputIterator last, const string& value)
{
    while (first != last && !(*first == value)) ++first;
    return first;
}
#else

// for MetroWerks
#if !defined(STD_PREFIX)
#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif
#endif

template vector<string>::iterator 
STD_PREFIX find ( vector<string>::iterator, 
		  vector<string>::iterator, 
		  const string& );
#endif /* (defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX)) */
