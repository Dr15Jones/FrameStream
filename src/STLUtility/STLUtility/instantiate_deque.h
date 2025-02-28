#if !defined(STLUTILITY_INSTANTIATE_DEQUE_H)
#define STLUTILITY_INSTANTIATE_DEQUE_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate STL deque
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Wed Aug 13 14:32:44 EDT 1997
// $Id: instantiate_deque.h,v 1.5 1999/06/25 15:52:17 cdj Exp $
//
// Revision history
//
// $Log: instantiate_deque.h,v $
// Revision 1.5  1999/06/25 15:52:17  cdj
// put back the copy instantiation that uses pointers
//
// Revision 1.4  1999/06/23 19:15:48  lkg
// Rework the copy function instantiation to use const_iterators rather than
// simple pointers (which works only for things like Double, etc.)
//
// Revision 1.3  1998/06/26 22:21:13  cdj
// new instantiations for cxx 6.0
//
// Revision 1.2  1998/02/02 23:31:52  sjp
// Fixed include files for new package
//
// Revision 1.1.1.1  1998/02/02 23:25:35  sjp
// New package for files that help STL usage
//
// Revision 1.3  1997/09/03 20:05:47  sjp
// Uses CPP macros for STL containers
//
// Revision 1.2  1997/08/15 21:26:37  mkl
// added copy function prototype for cxx5.6
//
// Revision 1.1  1997/08/13 20:56:34  mkl
// added instantiation file for deque
//
//

#include <deque>

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
#  pragma define_template deque< _deque_contents_ >

#  pragma define_template copy< _deque_contents_** ,  _deque_contents_**>
#  pragma define_template copy< const _deque_contents_* ,  deque<_deque_contents_>::iterator >
#  pragma define_template copy< deque< _deque_contents_>::iterator , deque< _deque_contents_ >::iterator >
#  pragma define_template copy< deque< _deque_contents_>::const_iterator , deque< _deque_contents_ >::iterator >
#  pragma define_template copy< deque< _deque_contents_>::const_iterator, back_insert_iterator<deque < _deque_contents_ > > >
#  pragma define_template copy< const _deque_contents_*, back_insert_iterator<deque < _deque_contents_ > > >
#  pragma define_template copy_backward< deque< _deque_contents_>::iterator , deque< _deque_contents_ >::iterator >
#  pragma define_template back_inserter< deque< _deque_contents_ > >
#  pragma define_template fill< deque< _deque_contents_ >::iterator, _deque_contents_ >

#else

#include "STLUtility/fwd_deque.h"
template class STL_DEQUE( _deque_contents_ ) ;

#if ( defined(NO_IMPLICIT_INSTANTIATION) && defined(__DECCXX) )

template 
std::back_insert_iterator<std::deque<_deque_contents_, 
                                     std::allocator<_deque_contents_>
                                    > 
                         >
std::copy( 
   std::deque< _deque_contents_,
               std::allocator< _deque_contents_ > >::const_iterator,
   std::deque< _deque_contents_,
               std::allocator< _deque_contents_ > >::const_iterator,
   std::back_insert_iterator<std::deque<_deque_contents_, 
	                                std::allocator<_deque_contents_> > >);

template 
std::back_insert_iterator<std::deque<_deque_contents_, 
                                     std::allocator<_deque_contents_>
                                    > 
                         >
std::copy( _deque_contents_ const*, 
         _deque_contents_ const *, 
         std::back_insert_iterator<std::deque<_deque_contents_, 
                                              std::allocator<_deque_contents_> > >);

template 
std::insert_iterator<std::deque<_deque_contents_, 
                                std::allocator<_deque_contents_>
                               > 
                    >
std::copy( 
   std::deque< _deque_contents_,
               std::allocator< _deque_contents_ > >::const_iterator,
   std::deque< _deque_contents_,
               std::allocator< _deque_contents_ > >::const_iterator,
   std::insert_iterator<std::deque<_deque_contents_, 
                                   std::allocator<_deque_contents_> > >);

template
_deque_contents_**
std::copy(_deque_contents_**, _deque_contents_**, _deque_contents_**);

template 
std::deque<_deque_contents_, 
           std::allocator<_deque_contents_> >::iterator 
std::copy(std::deque<_deque_contents_, 
	             std::allocator<_deque_contents_> >::iterator, 
	  std::deque<_deque_contents_, 
	             std::allocator<_deque_contents_> >::iterator, 
	  std::deque<_deque_contents_, 
	             std::allocator<_deque_contents_> >::iterator );

template 
std::deque<_deque_contents_, 
           std::allocator<_deque_contents_> >::iterator 
std::copy(std::deque<_deque_contents_, 
	             std::allocator<_deque_contents_> >::const_iterator, 
	  std::deque<_deque_contents_, 
	             std::allocator<_deque_contents_> >::const_iterator, 
	  std::deque<_deque_contents_, 
	             std::allocator<_deque_contents_> >::iterator );

template
std::deque<_deque_contents_, std::allocator<_deque_contents_> >::iterator
std::copy_backward(std::deque<_deque_contents_, 
		              std::allocator<_deque_contents_> >::iterator, 
		   std::deque<_deque_contents_, 
		              std::allocator<_deque_contents_> >::iterator, 
		   std::deque<_deque_contents_, 
		              std::allocator<_deque_contents_> >::iterator);

template
void
std::fill(std::deque<_deque_contents_, 
	             std::allocator<_deque_contents_> >::iterator, 
	  std::deque<_deque_contents_, 
	             std::allocator<_deque_contents_> >::iterator, 
	  const _deque_contents_&);

#endif

#endif /* PRAGMA_TEMPLATE_INSTANTIATION_BUG && __DECCXX */

#endif /* STLUTILITY_INSTANTIATE_DEQUE_H */
