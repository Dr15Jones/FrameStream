#if !defined(STLUTILITY_INSTANTIATE_EQUAL_H)
#define STLUTILITY_INSTANTIATE_EQUAL_H
// -*- C++ -*-
//
// Package:     STLUTILITY
// Module:      instantiate_equal
// 
// Description: Instantiate the STL equal algorithm that take two iterators
//              as arguments, returning a bool
//
// Usage:
//    This header instantiates 
//        bool equal(iter1_first, iter1_last, iter2_first);
//
//    The user must set these typedefs before including this header file:
//        _equal_iterator1_type_ = iterator type for the first container
//        _equal_iterator2_type_ = iterator type for container to compare
//
//    e.g. If you had an stl vector of MyItem, and an stl deque of
//    MyItem, then you would need...
//            typedef STL_VECTOR(MyItem)::iterator _equal_iterator1_type;
//            typedef STL_DEQUE(MyItem)::iterator  _equal_iterator2_type;
//
// Author:      Lawrence Gibbons
// Created:     Sun Apr 25 22:29:00 EDT 1999
// $Id: instantiate_equal.h,v 1.1 1999/05/13 01:58:58 lkg Exp $
//
// Revision history
//
//

// system include files
#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

#if ( defined(__DECCXX) )

template bool STD_PREFIX equal( _equal_iterator1_type_, 
				_equal_iterator1_type_,
				_equal_iterator2_type_ );

#define _mismatch_iterator1_type_ _equal_iterator1_type_
#define _mismatch_iterator2_type_ _equal_iterator2_type_
#include "STLUtility/instantiate_mismatch.h"
#endif

#endif /* STLUTILITY_INSTANTIATE_EQUAL_H */
