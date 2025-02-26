#if !defined(STLUTILITY_INSTANTIATE_MULTISET_H)
#define STLUTILITY_INSTANTIATE_MULTISET_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate STL multiset
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Sat May 25 14:32:44 EDT 1996
// $Id: instantiate_multiset.h,v 1.7 1999/10/30 12:33:59 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_multiset.h,v $
// Revision 1.7  1999/10/30 12:33:59  cleo3
// updated to work with cxx 6.2
//
// Revision 1.6  1998/09/10 15:13:04  mkl
// had to add another round of distance functions for cxx 6.0 021
//
// Revision 1.5  1998/09/09 16:35:29  mkl
// added cpp-macro to define __rwstd::(__)rb_tree for different subversions of cxx 6.0 compiler's map implementations
//
// Revision 1.4  1998/06/26 22:21:18  cdj
// new instantiations for cxx 6.0
//
// Revision 1.3  1998/02/03 22:13:26  mkl
// changed *_COMPARE macros to *_COMP
//
// Revision 1.2  1998/02/02 23:31:56  sjp
// Fixed include files for new package
//
// Revision 1.1.1.1  1998/02/02 23:25:35  sjp
// New package for files that help STL usage
//
// Revision 1.4  1997/09/03 20:05:57  sjp
// Uses CPP macros for STL containers
//
// Revision 1.3  1997/08/14 19:32:14  sjp
// Corrected file to cope with rbtree error in cxx
//
// Revision 1.2  1997/08/14 11:42:24  sjp
// Mods to run under CW Pro 1
//
// Revision 1.1  1997/08/06 14:09:30  sjp
// New file to instantiate STL container
//

#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )

#  pragma define_template multiset< _multiset_contents_ , _multiset_compare_ >

#if defined(NO_DEFAULT_PARAMETERS_FOR_RBTREE_BUG)
#  pragma define_template rb_tree< _multiset_contents_, _multiset_contents_ , ident< _multiset_contents_ , _multiset_contents_ >, _multiset_compare_ , allocator< _multiset_contents_ > >
//
// Have to define the functions here as 'cxx' does not allow you to "pick"
//   which template to use when there are multiple ones on offer!
void __distance(rb_tree< _multiset_contents_, _multiset_contents_ , ident< _multiset_contents_ , _multiset_contents_ >, _multiset_compare_ , allocator< _multiset_contents_ > >::iterator first,
		rb_tree< _multiset_contents_, _multiset_contents_ , ident< _multiset_contents_ , _multiset_contents_ >, _multiset_compare_ , allocator< _multiset_contents_ > >::iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

void __distance(rb_tree< _multiset_contents_, _multiset_contents_ , ident< _multiset_contents_ , _multiset_contents_ >, _multiset_compare_ , allocator< _multiset_contents_ > >::const_iterator first,
		rb_tree< _multiset_contents_, _multiset_contents_ , ident< _multiset_contents_ , _multiset_contents_ >, _multiset_compare_ , allocator< _multiset_contents_ > >::const_iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

#else

#  pragma define_template rb_tree< _multiset_contents_, _multiset_contents_ , ident< _multiset_contents_ , _multiset_contents_ >, _multiset_compare_ >
//
// Have to define the functions here as 'cxx' does not allow you to "pick"
//   which template to use when there are multiple ones on offer!
void __distance(rb_tree< _multiset_contents_, _multiset_contents_ , ident< _multiset_contents_ , _multiset_contents_ >, _multiset_compare_ >::iterator first,
		rb_tree< _multiset_contents_, _multiset_contents_ , ident< _multiset_contents_ , _multiset_contents_ >, _multiset_compare_ >::iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

void __distance(rb_tree< _multiset_contents_, _multiset_contents_ , ident< _multiset_contents_ , _multiset_contents_ >, _multiset_compare_ >::const_iterator first,
		rb_tree< _multiset_contents_, _multiset_contents_ , ident< _multiset_contents_ , _multiset_contents_ >, _multiset_compare_ >::const_iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

#endif /* NO_ALLOCATOR_IN_STL_DECLARATION_BUG */

#else

#include "STLUtility/fwd_set.h"
template class STL_MULTISET_COMP( _multiset_contents_ , _multiset_compare_ ) ;

#if ( defined(NO_IMPLICIT_INSTANTIATION) && defined(__DECCXX) )
template class STLUTILITY_RB_TREE<_multiset_contents_, 
                                _multiset_contents_, 
                                STLUTILITY_IDENT<_multiset_contents_, 
                                               _multiset_contents_>,
                                _multiset_compare_, 
                                std::allocator<_multiset_contents_> >;

template void std:: STLUTILITY_FUNC(distance) (
   STLUTILITY_RB_TREE<_multiset_contents_, 
                    _multiset_contents_, 
                    STLUTILITY_IDENT<_multiset_contents_, 
                                   _multiset_contents_>,
                    _multiset_compare_, 
                    std::allocator<_multiset_contents_> >::iterator,
   STLUTILITY_RB_TREE<_multiset_contents_, 
                    _multiset_contents_, 
                    STLUTILITY_IDENT<_multiset_contents_, 
                                   _multiset_contents_>,
                    _multiset_compare_, 
                    std::allocator<_multiset_contents_> >::iterator,
   long&,
   std::bidirectional_iterator_tag);

template void std:: STLUTILITY_FUNC(distance) (
   STLUTILITY_RB_TREE<_multiset_contents_, 
                    _multiset_contents_, 
                    STLUTILITY_IDENT<_multiset_contents_, 
                                   _multiset_contents_>,
                    _multiset_compare_, 
                    std::allocator<_multiset_contents_> >::iterator,
   STLUTILITY_RB_TREE<_multiset_contents_, 
                    _multiset_contents_, 
                    STLUTILITY_IDENT<_multiset_contents_, 
                                   _multiset_contents_>,
                    _multiset_compare_, 
                    std::allocator<_multiset_contents_> >::iterator,
   unsigned long&,
   std::bidirectional_iterator_tag);

template void std:: STLUTILITY_FUNC(distance) (
   STLUTILITY_RB_TREE<_multiset_contents_, 
                    _multiset_contents_, 
                    STLUTILITY_IDENT<_multiset_contents_, 
                                   _multiset_contents_>,
                    _multiset_compare_, 
                    std::allocator<_multiset_contents_> >::const_iterator,
   STLUTILITY_RB_TREE<_multiset_contents_, 
                    _multiset_contents_, 
                    STLUTILITY_IDENT<_multiset_contents_, 
                                   _multiset_contents_>,
                    _multiset_compare_, 
                    std::allocator<_multiset_contents_> >::const_iterator,
   long&,
   std::bidirectional_iterator_tag);
   
template void std:: STLUTILITY_FUNC(distance) (
   STLUTILITY_RB_TREE<_multiset_contents_, 
                    _multiset_contents_, 
                    STLUTILITY_IDENT<_multiset_contents_, 
                                   _multiset_contents_>,
                    _multiset_compare_, 
                    std::allocator<_multiset_contents_> >::const_iterator,
   STLUTILITY_RB_TREE<_multiset_contents_, 
                    _multiset_contents_, 
                    STLUTILITY_IDENT<_multiset_contents_, 
                                   _multiset_contents_>,
                    _multiset_compare_, 
                    std::allocator<_multiset_contents_> >::const_iterator,
   unsigned long&,
   std::bidirectional_iterator_tag);
   
#endif /* NO_IMPLICIT_INSTANTIATION && __DECCXX */

#endif /* PRAGMA_TEMPLATE_INSTANTIATION_BUG && __DECCXX */

#endif /* STLUTILITY_INSTANTIATE_MULTISET_H */
