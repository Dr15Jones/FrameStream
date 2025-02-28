#if !defined(STLUTILITY_INSTANTIATE_VECTOR_H)
#define STLUTILITY_INSTANTIATE_VECTOR_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate STL vector
//
// Implementation:
//     Note:  If you wish to compare two vectors via the == or !=
//            operators, you must instantiate the "equal" algorithm.
//            This is **NOT** done by default.  To turn it on, define
//            the proprocessor variable DO_EQUAL_INSTANTIATION
//
// Author:      Simon Patton
// Created:     Sat May 25 14:32:44 EDT 1996
// $Id: instantiate_vector.h,v 1.7 1999/06/24 21:52:10 lkg Exp $
//
// Revision history
//
// $Log: instantiate_vector.h,v $
// Revision 1.7  1999/06/24 21:52:10  lkg
// minor cleanup
//
// Revision 1.6  1999/06/24 16:58:45  lkg
// Only instantiate the equal algorithm if the CPP flag DO_EQUAL_INSTANTIATION
// is set (sorry folks)
//
// Revision 1.5  1999/06/23 20:53:29  lkg
// Instantiate the equal algorithm, which is used by the == operator
//
// Revision 1.4  1998/11/06 19:03:08  cdj
// added std:: to names of templated functions instantiated for cxx (for v6.1)
//
// Revision 1.3  1998/06/26 22:21:21  cdj
// new instantiations for cxx 6.0
//
// Revision 1.2  1998/02/02 23:31:57  sjp
// Fixed include files for new package
//
// Revision 1.1.1.1  1998/02/02 23:25:35  sjp
// New package for files that help STL usage
//
// Revision 1.3  1997/09/03 20:06:00  sjp
// Uses CPP macros for STL containers
//
// Revision 1.2  1997/08/14 11:42:27  sjp
// Mods to run under CW Pro 1
//
// Revision 1.1  1997/08/06 14:09:34  sjp
// New file to instantiate STL container
//

#include <vector>

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
#  pragma define_template vector< _vector_contents_ >

#  pragma define_template destroy< _vector_contents_* >
#  pragma define_template copy< _vector_contents_* ,  _vector_contents_*>
#  pragma define_template uninitialized_copy< _vector_contents_  const* ,  _vector_contents_*>
#  pragma define_template copy< _vector_contents_  const* ,  _vector_contents_*>
#  pragma define_template copy_backward< _vector_contents_* ,  _vector_contents_*>
#  pragma define_template uninitialized_copy< _vector_contents_* ,  _vector_contents_*>
#  pragma define_template fill< _vector_contents_* ,  _vector_contents_ >
#  pragma define_template uninitialized_fill_n< _vector_contents_* , unsigned long ,  _vector_contents_ >
#  pragma define_template __distance< _vector_contents_  const* , unsigned long>
#else

#include "STLUtility/fwd_vector.h"
template class STL_VECTOR( _vector_contents_ ) ;


#if ( defined(NO_IMPLICIT_INSTANTIATION) && defined(__DECCXX) )
template _vector_contents_* std::copy( _vector_contents_ *, 
				  _vector_contents_ *, 
				  _vector_contents_ * );

template _vector_contents_* std::copy( _vector_contents_ const*, 
				  _vector_contents_ const*, 
				  _vector_contents_ * );
template _vector_contents_* std::copy_backward( _vector_contents_* ,  
					   _vector_contents_* ,
					   _vector_contents_* );
template void std::fill( _vector_contents_* ,  
		    _vector_contents_* ,
		    _vector_contents_ const& );

#if defined(DO_EQUAL_INSTANTIATION)
// the comparison operator (==) is implemented in terms of the STL
// equal algorithm, which in turn uses mismatch.  Instantiate equal and 
// mismatch by default
typedef STL_VECTOR( _vector_contents_ )::const_iterator _equal_iterator1_type_;
typedef _equal_iterator1_type_ _equal_iterator2_type_;
#include "STLUtility/instantiate_equal.h"
#endif /* DO_EQUAL_INSTANTIATION */

#endif

#endif /* PRAGMA_TEMPLATE_INSTANTIATION_BUG && __DECCXX */

#endif /* STLUTILITY_INSTANTIATE_VECTOR_H */
