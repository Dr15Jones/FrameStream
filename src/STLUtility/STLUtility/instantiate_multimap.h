#if !defined(STLUTILITY_INSTANTIATE_MULTIMAP_H)
#define STLUTILITY_INSTANTIATE_MULTIMAP_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate STL multimap
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Sat May 25 14:32:44 EDT 1996
// $Id: instantiate_multimap.h,v 1.8 1999/10/30 12:33:59 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_multimap.h,v $
// Revision 1.8  1999/10/30 12:33:59  cleo3
// updated to work with cxx 6.2
//
// Revision 1.7  1998/11/07 17:33:58  cdj
// now take into account (MULTI)MAP_ALLOCATOR_ONLY_USES_CONTENTS_BUG
//
// Revision 1.6  1998/09/10 15:13:03  mkl
// had to add another round of distance functions for cxx 6.0 021
//
// Revision 1.5  1998/09/07 20:17:03  mkl
// added cpp-macro to define __rwstd::(__)rb_tree for different subversions of cxx 6.0 compiler's map implementations
//
// Revision 1.4  1998/06/26 22:21:17  cdj
// new instantiations for cxx 6.0
//
// Revision 1.3  1998/02/03 22:13:25  mkl
// changed *_COMPARE macros to *_COMP
//
// Revision 1.2  1998/02/02 23:31:55  sjp
// Fixed include files for new package
//
// Revision 1.1.1.1  1998/02/02 23:25:35  sjp
// New package for files that help STL usage
//
// Revision 1.5  1997/09/03 20:05:55  sjp
// Uses CPP macros for STL containers
//
// Revision 1.4  1997/08/14 19:32:12  sjp
// Corrected file to cope with rbtree error in cxx
//
// Revision 1.3  1997/08/14 18:00:10  sjp
// Fixed erroneous allocator for cxx instantiation
//
// Revision 1.2  1997/08/14 11:42:22  sjp
// Mods to run under CW Pro 1
//
// Revision 1.1  1997/08/06 14:09:29  sjp
// New file to instantiate STL container
//

#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multimap.h>
#else
#include <map>
#endif

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )

#  pragma define_template multimap< _multimap_key_ ,  _multimap_contents_ , _multimap_compare_ >

#if defined(NO_DEFAULT_PARAMETERS_FOR_RBTREE_BUG)
#  pragma define_template rb_tree<_multimap_key_ , std::pair< const _multimap_key_ ,  _multimap_contents_ > , select1st< std::pair< const _multimap_key_ ,  _multimap_contents_ > , _multimap_key_ > , _multimap_compare_ , allocator< _multimap_contents_ > >
//
// Have to define the functions here as 'cxx' does not allow you to "pick"
//   which template to use when there are multiple ones on offer!
void __distance(rb_tree<_multimap_key_ , std::pair< const _multimap_key_ ,  _multimap_contents_ > , select1st< std::pair< const _multimap_key_ ,  _multimap_contents_ > , _multimap_key_ > , _multimap_compare_ , allocator< _multimap_contents_ > >::iterator first,
		rb_tree<_multimap_key_ , std::pair< const _multimap_key_ ,  _multimap_contents_ > , select1st< std::pair< const _multimap_key_ ,  _multimap_contents_ > , _multimap_key_ > , _multimap_compare_ , allocator< _multimap_contents_ > >::iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

void __distance(rb_tree<_multimap_key_ , std::pair< const _multimap_key_ ,  _multimap_contents_ > , select1st< std::pair< const _multimap_key_ ,  _multimap_contents_ > , _multimap_key_ > , _multimap_compare_ , allocator< _multimap_contents_ > >::const_iterator first,
		rb_tree<_multimap_key_ , std::pair< const _multimap_key_ ,  _multimap_contents_ > , select1st< std::pair< const _multimap_key_ ,  _multimap_contents_ > , _multimap_key_ > , _multimap_compare_ , allocator< _multimap_contents_ > >::const_iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

#else

#  pragma define_template rb_tree<_multimap_key_ , std::pair< const _multimap_key_ ,  _multimap_contents_ > , select1st< std::pair< const _multimap_key_ ,  _multimap_contents_ > , _multimap_key_ > , _multimap_compare_ >
//
// Have to define the functions here as 'cxx' does not allow you to "pick"
//   which template to use when there are multiple ones on offer!
void __distance(rb_tree<_multimap_key_ , std::pair< const _multimap_key_ ,  _multimap_contents_ > , select1st< std::pair< const _multimap_key_ ,  _multimap_contents_ > , _multimap_key_ > , _multimap_compare_ >::iterator first,
		rb_tree<_multimap_key_ , std::pair< const _multimap_key_ ,  _multimap_contents_ > , select1st< std::pair< const _multimap_key_ ,  _multimap_contents_ > , _multimap_key_ > , _multimap_compare_ >::iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

void __distance(rb_tree<_multimap_key_ , std::pair< const _multimap_key_ ,  _multimap_contents_ > , select1st< std::pair< const _multimap_key_ ,  _multimap_contents_ > , _multimap_key_ > , _multimap_compare_ >::const_iterator first,
		rb_tree<_multimap_key_ , std::pair< const _multimap_key_ ,  _multimap_contents_ > , select1st< std::pair< const _multimap_key_ ,  _multimap_contents_ > , _multimap_key_ > , _multimap_compare_ >::const_iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

#endif /* NO_ALLOCATOR_IN_STL_DECLARATION_BUG */


#else

#include <map>
template class STL_MULTIMAP_COMP( _multimap_key_ , _multimap_contents_ , _multimap_compare_ ) ;

#if ( defined(NO_IMPLICIT_INSTANTIATION) && defined(__DECCXX) )
#if defined(MULTIMAP_ALLOCATOR_ONLY_USES_CONTENTS_BUG)
#define CXX_MULTIMAP_ALLOCATOR std::allocator<_multimap_contents_>
#else
#define CXX_MULTIMAP_ALLOCATOR std::allocator< std::pair< const _multimap_key_, _multimap_contents_> >
#endif

template class STLUTILITY_RB_TREE<_multimap_key_, 
                        std::pair<const _multimap_key_, _multimap_contents_>, 
                        STLUTILITY_SELECT1ST<std::pair<const _multimap_key_, 
                                                     _multimap_contents_>, 
                                            _multimap_key_>, 
                        _multimap_compare_, 
                        CXX_MULTIMAP_ALLOCATOR >;

template void std:: STLUTILITY_FUNC(distance) (
   STLUTILITY_RB_TREE<_multimap_key_, 
                    std::pair<const _multimap_key_, 
                              _multimap_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _multimap_key_, 
                                                 _multimap_contents_>, 
                                       _multimap_key_>, 
                    _multimap_compare_, 
                    CXX_MULTIMAP_ALLOCATOR >::iterator, 
   STLUTILITY_RB_TREE<_multimap_key_, 
                    std::pair<const _multimap_key_, 
                              _multimap_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _multimap_key_, 
                                                 _multimap_contents_>, 
                                       _multimap_key_>, 
                    _multimap_compare_, 
                    CXX_MULTIMAP_ALLOCATOR >::iterator, 
   long&, 
   std::bidirectional_iterator_tag);

template void std:: STLUTILITY_FUNC(distance) (
   STLUTILITY_RB_TREE<_multimap_key_, 
                    std::pair<const _multimap_key_, 
                              _multimap_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _multimap_key_, 
                                                 _multimap_contents_>, 
                                       _multimap_key_>, 
                    _multimap_compare_, 
                    CXX_MULTIMAP_ALLOCATOR >::iterator, 
   STLUTILITY_RB_TREE<_multimap_key_, 
                    std::pair<const _multimap_key_, 
                              _multimap_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _multimap_key_, 
                                                 _multimap_contents_>, 
                                       _multimap_key_>, 
                    _multimap_compare_, 
                    CXX_MULTIMAP_ALLOCATOR >::iterator, 
   unsigned long&, 
   std::bidirectional_iterator_tag);

template void std:: STLUTILITY_FUNC(distance) (
   STLUTILITY_RB_TREE<_multimap_key_, 
                    std::pair<const _multimap_key_, 
                              _multimap_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _multimap_key_, 
                                                 _multimap_contents_>, 
                                       _multimap_key_>, 
                    _multimap_compare_, 
                    CXX_MULTIMAP_ALLOCATOR >::const_iterator, 
   STLUTILITY_RB_TREE<_multimap_key_, 
                    std::pair<const _multimap_key_, 
                              _multimap_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _multimap_key_, 
                                                 _multimap_contents_>, 
                                       _multimap_key_>, 
                    _multimap_compare_, 
                    CXX_MULTIMAP_ALLOCATOR >::const_iterator, 
   long&, 
   std::bidirectional_iterator_tag);

template void std:: STLUTILITY_FUNC(distance) (
   STLUTILITY_RB_TREE<_multimap_key_, 
                    std::pair<const _multimap_key_, 
                              _multimap_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _multimap_key_, 
                                                 _multimap_contents_>, 
                                       _multimap_key_>, 
                    _multimap_compare_, 
                    CXX_MULTIMAP_ALLOCATOR >::const_iterator, 
   STLUTILITY_RB_TREE<_multimap_key_, 
                    std::pair<const _multimap_key_, 
                              _multimap_contents_>, 
                    STLUTILITY_SELECT1ST<std::pair<const _multimap_key_, 
                                                 _multimap_contents_>, 
                                       _multimap_key_>, 
                    _multimap_compare_, 
                    CXX_MULTIMAP_ALLOCATOR >::const_iterator, 
   unsigned long&, 
   std::bidirectional_iterator_tag);

#endif /* NO_IMPLICIT_INSTANTIATION && __DECCXX */

#endif /* PRAGMA_TEMPLATE_INSTANTIATION_BUG && __DECCXX */

#endif /* STLUTILITY_INSTANTIATE_MULTIMAP_H */
