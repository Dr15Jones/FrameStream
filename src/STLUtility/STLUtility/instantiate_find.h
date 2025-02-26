#if !defined(STLUTILITY_INSTANTIATE_FIND_H)
#define STLUTILITY_INSTANTIATE_FIND_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      instantiate_find
// 
// Description: instantiate help file for find with predicate
//
// Usage: The user must with typedefs define 2 classes:
//      _find_iterator_  : an input iterator
//      _find_predicate_ : a unary predicate; i.e. a boolean function
//                            with an argument of the type to which
//                            the _find_iterator_ dereferences.
//
//
// Author:      Lawrence K. Gibbons
// Created:     Mon Apr 12 13:38:53 EDT 1999
// $Id: instantiate_find.h,v 1.1 2001/05/31 19:39:58 cdj Exp $
//
// Revision history
//
// $Log: instantiate_find.h,v $
// Revision 1.1  2001/05/31 19:39:58  cdj
// added instantiate_find
//
// Revision 1.1  1999/05/13 01:58:14  lkg
// helper file for STL find instantiation
//
//

// system include files

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif


#if ( defined(__DECCXX) )

template _find_iterator_ STD_PREFIX find( _find_iterator_,
						_find_iterator_,
						const _find_type_& ) ;

#endif

#endif /* STLUTILITY_INSTANTIATE_FIND_IF_H */
