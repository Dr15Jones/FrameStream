#if !defined(STLUTILITY_INSTANTIATE_COPY_H)
#define STLUTILITY_INSTANTIATE_COPY_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      instantiate_copy
// 
// Description: instantiate help file for find with predicate
//
// Usage: The user must with typedefs define 2 classes:
//      _copy_in_iterator_  : first and last iterator of a container
//                            to be coped
//      _copy_out_iterator_ : iterator of container where stuff should be coped
//
//
// Author:      Konstantin Bukin
// Created:     Mon Oct 30 13:27:33 EST 2000
// $Id: instantiate_copy.h,v 1.2 2003/02/05 21:00:51 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_copy.h,v $
// Revision 1.2  2003/02/05 21:00:51  cleo3
// minor changes needed for cxx 6.5
//
// Revision 1.1  2000/11/01 02:13:53  kbukin
// add copy instantiation helper files
//

// system include files
#include <algorithm>

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif


#if defined(NO_IMPLICIT_INSTANTIATION) 

template _copy_out_iterator_ STD_PREFIX copy( _copy_in_iterator_,
                                              _copy_in_iterator_,
                                              _copy_out_iterator_ ) ;

#endif

#endif /* STLUTILITY_INSTANTIATE_COPY_H */

