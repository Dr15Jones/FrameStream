#if !defined(STLUTILITY_INSTANTIATE_ADJACENT_FIND_PREDICATE_H)
#define STLUTILITY_INSTANTIATE_ADJACENT_FIND_PREDICATE_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      instantiate_adjacent_find_predicate
// 
// Description: instantiate help file for adjacent_find with predicate
//
// Usage: The user must with typedefs define 2 classes:
//      _adjacent_find_iterator_  : a forward iterator
//      _adjacent_find_predicate_ : a binary predicate; i.e. a boolean function
//                                  with two arguments of the type
//                                  that the _adjacent_find_iterator_
//                                  dereferences to.
//
//
// Author:      Adam L. Lyon
// Created:     02-Jan-2002
// $Id: instantiate_adjacent_find_predicate.h,v 1.3 2002/01/02 21:15:02 lyon Exp $
//
// Revision history
//
// $Log: instantiate_adjacent_find_predicate.h,v $
// Revision 1.3  2002/01/02 21:15:02  lyon
// Remove instantiation of reverse from instantiate_adjacent_find_predicate.h
//
// Revision 1.2  1999/10/30 12:33:57  cleo3
// updated to work with cxx 6.2
//
// Revision 1.1  1999/04/12 19:19:35  bkh
// add some generic algorithm instantiate headers
//

// system include files

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif


#if ( defined(__DECCXX) )

template _adjacent_find_iterator_ STD_PREFIX adjacent_find(
                                                 _adjacent_find_iterator_,
                                                 _adjacent_find_iterator_,
						 _adjacent_find_predicate_ ) ;

#endif

#endif /* STLUTILITY_INSTANTIATE_ADJACENT_FIND_PREDICATE_H */
