#if !defined(STLUTILITY_INSTANTIATE_LIST_H)
#define STLUTILITY_INSTANTIATE_LIST_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate STL list
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue Aug 12 14:32:44 EDT 1997
// $Id: instantiate_list.h,v 1.9 2000/01/07 14:14:12 marsh Exp $
//
// Revision history
//
// $Log: instantiate_list.h,v $
// Revision 1.9  2000/01/07 14:14:12  marsh
// Fixed list::iterator copy instantiations
//
// Revision 1.8  1999/10/30 12:33:58  cleo3
// updated to work with cxx 6.2
//
// Revision 1.7  1998/11/07 21:24:50  cdj
// added additional instantiations needed by cxx v6.1
//
// Revision 1.6  1998/11/06 19:37:15  cdj
// added std:: to template function names (needed for cxx v6.1)
//
// Revision 1.5  1998/07/03 22:08:56  cdj
// instantiate functions needed for cxx 6.0
//
// Revision 1.4  1998/06/26 22:21:14  cdj
// new instantiations for cxx 6.0
//
// Revision 1.3  1998/06/20 02:45:47  cdj
// cxx 5.x needs definition of __advance to instantiate correctly
//
// Revision 1.2  1998/02/02 23:31:53  sjp
// Fixed include files for new package
//
// Revision 1.1.1.1  1998/02/02 23:25:35  sjp
// New package for files that help STL usage
//
// Revision 1.2  1997/09/03 20:05:49  sjp
// Uses CPP macros for STL containers
//
// Revision 1.1  1997/08/13 02:59:48  mkl
// added an instantiation file for lists
//
//

#include <list>

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
#  pragma define_template list< _list_contents_ >

#  pragma define_template destroy< _list_contents_* >
#  pragma define_template copy< _list_contents_* ,  _list_contents_*>
#  pragma define_template uninitialized_copy< _list_contents_  const* ,  _list_contents_*>
#  pragma define_template copy< _list_contents_  const* ,  _list_contents_*>
#  pragma define_template copy_backward< _list_contents_* ,  _list_contents_*>
#  pragma define_template uninitialized_copy< _list_contents_* ,  _list_contents_*>
#  pragma define_template fill< _list_contents_* ,  _list_contents_ >
#  pragma define_template uninitialized_fill_n< _list_contents_* , unsigned long ,  _list_contents_ >
#  pragma define_template __distance< _list_contents_  const* , unsigned long>
// keeps trying to instantiate the wrong __advance function
//   this is taken from <cxx/iterator>
void __advance (list< _list_contents_ >::iterator& i, long n, bidirectional_iterator_tag)
{
    if (n >= 1)
        while (n--) ++i;
    else
        while (n++) --i;
}
#else

#include <list>
template class std::list< _list_contents_ > ;

#if ( defined(NO_IMPLICIT_INSTANTIATION) && defined(__DECCXX) )
template std::list< _list_contents_ >::iterator std::copy(
   std::list< _list_contents_ >::iterator,
   std::list< _list_contents_ >::iterator,
   std::list< _list_contents_ >::iterator );

template std::list< _list_contents_ >::iterator std::copy(
   std::list< _list_contents_ >::const_iterator,
   std::list< _list_contents_ >::const_iterator,
   std::list< _list_contents_ >::iterator );

template void std::list<_list_contents_>::insert(
   std::list<_list_contents_>::iterator, 
   std::list<_list_contents_>::const_iterator, 
   std::list<_list_contents_ >::const_iterator);

template void std::list<_list_contents_>::insert(
   std::list<_list_contents_>::iterator, 
   std::list<_list_contents_>::iterator, 
   std::list<_list_contents_ >::iterator);

#if __DECCXX_VER >= 60290024
// list implementation changed
#elif __DECCXX_VER >= 60190027
template void std::list<_list_contents_>::__insert(
   std::list<_list_contents_>::iterator, 
   std::list<_list_contents_>::const_iterator, 
   std::list<_list_contents_ >::const_iterator,
   __false_category );

template void std::list<_list_contents_>::__insert(
   std::list<_list_contents_>::iterator, 
   std::list<_list_contents_>::iterator, 
   std::list<_list_contents_ >::iterator,
   __false_category );
#endif

#if defined(NEED_NAMESPACE_TO_INSTANTIATE_OVERLOADED_FUNCTION_BUG)
template void std:: STLUTILITY_FUNC(advance) (std::list<_list_contents_>::iterator&, long, std::bidirectional_iterator_tag);
#else
template void STLUTILITY_FUNC(advance)(list<_list_contents_ >::iterator&, long, bidirectional_iterator_tag);
#endif
#endif

#endif /* PRAGMA_TEMPLATE_INSTANTIATION_BUG && __DECCXX */

#endif /* STLUTILITY_INSTANTIATE_LIST_H */
