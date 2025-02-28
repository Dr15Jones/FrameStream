#if !defined(STLUTILITY_INSTANTIATE_MAP_H)
#define STLUTILITY_INSTANTIATE_MAP_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate STL map
//
// Implementation:
//     Note:  If you wish to compare two maps via the == or !=
//            operators, you must instantiate the "equal" algorithm.
//            This is **NOT** done by default.  To turn it on, define
//            the proprocessor variable DO_EQUAL_INSTANTIATION
//
// Author:      Simon Patton
// Created:     Sat May 25 14:32:44 EDT 1996
// $Id: instantiate_map.h,v 1.11 1999/10/30 12:33:58 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_map.h,v $
// Revision 1.11  1999/10/30 12:33:58  cleo3
// updated to work with cxx 6.2
//
// Revision 1.10  1999/06/24 21:52:08  lkg
// minor cleanup
//
// Revision 1.9  1999/06/24 16:58:44  lkg
// Only instantiate the equal algorithm if the CPP flag DO_EQUAL_INSTANTIATION
// is set (sorry folks)
//
// Revision 1.8  1999/06/23 20:52:00  lkg
// Instantiate the equal algorithm, which is used by the == operator
//
// Revision 1.7  1998/11/07 17:33:56  cdj
// now take into account (MULTI)MAP_ALLOCATOR_ONLY_USES_CONTENTS_BUG
//
// Revision 1.6  1998/09/10 15:13:03  mkl
// had to add another round of distance functions for cxx 6.0 021
//
// Revision 1.5  1998/09/07 20:17:03  mkl
// added cpp-macro to define __rwstd::(__)rb_tree for different subversions of cxx 6.0 compiler's map implementations
//
// Revision 1.4  1998/06/26 22:21:16  cdj
// new instantiations for cxx 6.0
//
// Revision 1.3  1998/02/03 22:13:23  mkl
// changed *_COMPARE macros to *_COMP
//
// Revision 1.2  1998/02/02 23:31:53  sjp
// Fixed include files for new package
//
// Revision 1.1.1.1  1998/02/02 23:25:35  sjp
// New package for files that help STL usage
//
// Revision 1.5  1997/09/03 20:05:52  sjp
// Uses CPP macros for STL containers
//
// Revision 1.4  1997/08/14 19:32:09  sjp
// Corrected file to cope with rbtree error in cxx
//
// Revision 1.3  1997/08/14 18:00:08  sjp
// Fixed erroneous allocator for cxx instantiation
//
// Revision 1.2  1997/08/14 11:42:21  sjp
// Mods to run under CW Pro 1
//
// Revision 1.1  1997/08/06 14:09:27  sjp
// New file to instantiate STL container
//

#include <map>

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )

#  pragma define_template map< _map_key_ ,  _map_contents_ , _map_compare_ >

#if defined(NO_DEFAULT_PARAMETERS_FOR_RBTREE_BUG)
#  pragma define_template rb_tree<_map_key_ , pair< const _map_key_ ,  _map_contents_ > , select1st< pair< const _map_key_ ,  _map_contents_ > , _map_key_ > , _map_compare_ , allocator< _map_contents_ > >
//
// Have to define the functions here as 'cxx' does not allow you to "pick"
//   which template to use when there are multiple ones on offer!
void __distance(rb_tree<_map_key_ , pair< const _map_key_ ,  _map_contents_ > , select1st< pair< const _map_key_ ,  _map_contents_ > , _map_key_ > , _map_compare_ , allocator< _map_contents_ > >::iterator first,
		rb_tree<_map_key_ , pair< const _map_key_ ,  _map_contents_ > , select1st< pair< const _map_key_ ,  _map_contents_ > , _map_key_ > , _map_compare_ , allocator< _map_contents_ > >::iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

void __distance(rb_tree<_map_key_ , pair< const _map_key_ ,  _map_contents_ > , select1st< pair< const _map_key_ ,  _map_contents_ > , _map_key_ > , _map_compare_ , allocator< _map_contents_ > >::const_iterator first,
		rb_tree<_map_key_ , pair< const _map_key_ ,  _map_contents_ > , select1st< pair< const _map_key_ ,  _map_contents_ > , _map_key_ > , _map_compare_ , allocator< _map_contents_ > >::const_iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

#else

#  pragma define_template rb_tree<_map_key_ , pair< const _map_key_ ,  _map_contents_ > , select1st< pair< const _map_key_ ,  _map_contents_ > , _map_key_ > , _map_compare_ >
//
// Have to define the functions here as 'cxx' does not allow you to "pick"
//   which template to use when there are multiple ones on offer!
void __distance(rb_tree<_map_key_ , pair< const _map_key_ ,  _map_contents_ > , select1st< pair< const _map_key_ ,  _map_contents_ > , _map_key_ > , _map_compare_ >::iterator first,
		rb_tree<_map_key_ , pair< const _map_key_ ,  _map_contents_ > , select1st< pair< const _map_key_ ,  _map_contents_ > , _map_key_ > , _map_compare_ >::iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

void __distance(rb_tree<_map_key_ , pair< const _map_key_ ,  _map_contents_ > , select1st< pair< const _map_key_ ,  _map_contents_ > , _map_key_ > , _map_compare_ >::const_iterator first,
		rb_tree<_map_key_ , pair< const _map_key_ ,  _map_contents_ > , select1st< pair< const _map_key_ ,  _map_contents_ > , _map_key_ > , _map_compare_ >::const_iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

#endif /* NO_ALLOCATOR_IN_STL_DECLARATION_BUG */


#else

#include "STLUtility/fwd_map.h"
template class STL_MAP_COMP( _map_key_ , _map_contents_ , _map_compare_ ) ;

#if ( defined(NO_IMPLICIT_INSTANTIATION) && defined(__DECCXX) )

#if defined(MAP_ALLOCATOR_ONLY_USES_CONTENTS_BUG)
#define CXX_MAP_ALLOCATOR std::allocator<_map_contents_>
#else
#define CXX_MAP_ALLOCATOR std::allocator< std::pair< const _map_key_,_map_contents_> >
#endif
template class STLUTILITY_RB_TREE<_map_key_, 
                                std::pair<const _map_key_, _map_contents_>, 
                                STLUTILITY_SELECT1ST<std::pair<const _map_key_, 
                                                             _map_contents_>, 
                                                   _map_key_>, 
                                _map_compare_, 
                                CXX_MAP_ALLOCATOR >;

template void std:: STLUTILITY_FUNC(distance) (
   STLUTILITY_RB_TREE<_map_key_, 
                    std::pair<const _map_key_, 
                              _map_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _map_key_, 
                                                 _map_contents_>, 
                                       _map_key_>, 
                    _map_compare_, 
                    CXX_MAP_ALLOCATOR >::iterator, 
   STLUTILITY_RB_TREE<_map_key_, 
                    std::pair<const _map_key_, 
                              _map_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _map_key_, 
                                                 _map_contents_>, 
                                       _map_key_>, 
                    _map_compare_, 
                    CXX_MAP_ALLOCATOR >::iterator, 
   long&, 
   std::bidirectional_iterator_tag);

template void std:: STLUTILITY_FUNC(distance) (
   STLUTILITY_RB_TREE<_map_key_, 
                    std::pair<const _map_key_, 
                              _map_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _map_key_, 
                                                 _map_contents_>, 
                                       _map_key_>, 
                    _map_compare_, 
                    CXX_MAP_ALLOCATOR >::iterator, 
   STLUTILITY_RB_TREE<_map_key_, 
                    std::pair<const _map_key_, 
                              _map_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _map_key_, 
                                                 _map_contents_>, 
                                       _map_key_>, 
                    _map_compare_, 
                    CXX_MAP_ALLOCATOR >::iterator, 
   unsigned long&, 
   std::bidirectional_iterator_tag);

template void std:: STLUTILITY_FUNC(distance) (
   STLUTILITY_RB_TREE<_map_key_, 
                    std::pair<const _map_key_, _map_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _map_key_, 
                                                 _map_contents_>, 
                                       _map_key_>, 
                    _map_compare_, 
                    CXX_MAP_ALLOCATOR >::const_iterator, 
   STLUTILITY_RB_TREE<_map_key_, 
                    std::pair<const _map_key_, _map_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _map_key_, 
                                                 _map_contents_>, 
                                       _map_key_>, 
                    _map_compare_, 
                    CXX_MAP_ALLOCATOR >::const_iterator, 
   long&, std::bidirectional_iterator_tag);

template void std:: STLUTILITY_FUNC(distance) (
   STLUTILITY_RB_TREE<_map_key_, 
                    std::pair<const _map_key_, _map_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _map_key_, 
                                                 _map_contents_>, 
                                       _map_key_>, 
                    _map_compare_, 
                    CXX_MAP_ALLOCATOR >::const_iterator, 
   STLUTILITY_RB_TREE<_map_key_, 
                    std::pair<const _map_key_, _map_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _map_key_, 
                                                 _map_contents_>, 
                                       _map_key_>, 
                    _map_compare_, 
                    CXX_MAP_ALLOCATOR >::const_iterator, 
   unsigned long&, std::bidirectional_iterator_tag);

#if defined(DO_EQUAL_INSTANTIATION)
typedef STL_MAP_COMP( _map_key_ , _map_contents_ , _map_compare_ )::const_iterator _equal_iterator1_type_;
typedef _equal_iterator1_type_ _equal_iterator2_type_;
#include "STLUtility/instantiate_equal.h"
#endif /* DO_EQUAL_INSTANTIATION */

#endif /* NO_IMPLICIT_INSTANTIATION && __DECCXX */

#endif /* PRAGMA_TEMPLATE_INSTANTIATION_BUG && __DECCXX */

#endif /* STLUTILITY_INSTANTIATE_MAP_H */
