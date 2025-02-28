// -*- C++ -*-
//
// Package:     JobControl
// Module:      T_count_vector_char
// 
// Description: Instantiate algorithms dealing with vector< char >
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Sat Jul 13 21:45:29 EDT 1997
// $Id: T_count_vector_char.cc,v 1.1 2002/12/12 14:32:38 cdj Exp $
//
// Revision history
//
// $Log: T_count_vector_char.cc,v $
// Revision 1.1  2002/12/12 14:32:38  cdj
// moved instantiation of count to own file to avoid multiple symbols on OSF
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

#include <vector>
#include <algorithm>

// forward declarations

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif
// for g++ or MetroWerks
#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
#if defined(STD_PREFIX)
#undef STD_PREFIX
#define STD_PREFIX
#endif
namespace std {
#endif
#if defined(NO_ITERATOR_TRAITS_BUG)
template void STD_PREFIX count ( vector< char>::iterator, 
			   vector< char>::iterator, 
			   const char&, int& );
#else
   template iterator_traits<vector<char>::iterator>::difference_type
   STD_PREFIX count( vector<char>::iterator,
		     vector<char>::iterator,
		     const char&);
#endif

#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
}
#endif
