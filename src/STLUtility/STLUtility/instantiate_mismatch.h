#if !defined(STLUTILITY_INSTANTIATE_MISMATCH_H)
#define STLUTILITY_INSTANTIATE_MISMATCH_H
// -*- C++ -*-
//
// Package:     STLUTILITY
// Module:      instantiate_mismatch
// 
// Description: Instantiate the STL mismatch algorithm that take two iterators
//              as arguments, returning the iterators into each container
//              as a pair
//
// Usage:
//    This header instantiates 
//        pair<iter1,iter2> mismatch(iter1_first, iter1_last, iter2_first);
//
//    The user must set these typedefs before including this header file:
//        _mismatch_iterator1_type_ = iterator type for the first container
//        _mismatch_iterator2_type_ = iterator type for container to compare
//
//    e.g. If you had an stl vector of MyItem, and an stl deque of
//    MyItem, then you would need...
//            typedef STL_VECTOR(MyItem)::iterator _mismatch_iterator1_type;
//            typedef STL_DEQUE(MyItem)::iterator  _mismatch_iterator2_type;
//
// Author:      Lawrence Gibbons
// Created:     Sun Apr 25 22:29:00 EDT 1999
// $Id: instantiate_mismatch.h,v 1.2 2003/02/05 21:00:52 cleo3 Exp $
//
// Revision history
//
//
// system include files
#include <algorithm>
#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

#if ( defined(__DECCXX) )

template pair< _mismatch_iterator1_type_, _mismatch_iterator2_type_ > 
STD_PREFIX mismatch( _mismatch_iterator1_type_, 
		     _mismatch_iterator1_type_,
		     _mismatch_iterator2_type_ );

#endif

#endif /* STLUTILITY_INSTANTIATE_EQUAL_H */
