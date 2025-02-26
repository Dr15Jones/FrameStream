#if !defined(STLUTILITY_INSTANTIATE_VECTOR_OF_VECTOR_H)
#define STLUTILITY_INSTANTIATE_VECTOR_OF_VECTOR_H
// -*- C++ -*-
//
// Package:     <Utility>
// Module:      instantiate_vector_of_vector
// 
// Description: Code required to explicilty instantiate STL vector-of-vector
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon Nov 24 19:52:35 EST 1997
// $Id: instantiate_vector_of_vector.h,v 1.4 1998/11/06 20:48:09 cdj Exp $
//
// Revision history
//
// $Log: instantiate_vector_of_vector.h,v $
// Revision 1.4  1998/11/06 20:48:09  cdj
// Uses STD_PREFIX (needed for cxx v6.1)
//
// Revision 1.3  1998/07/03 22:08:57  cdj
// instantiate functions needed for cxx 6.0
//
// Revision 1.2  1998/02/02 23:31:58  sjp
// Fixed include files for new package
//
// Revision 1.1.1.1  1998/02/02 23:25:35  sjp
// New package for files that help STL usage
//
// Revision 1.1  1997/11/25 01:27:36  mkl
// now instantiation of vector< vector< something >>
//

#include <vector>

// format:
// vector< vector < _vector_content_s > >

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP
//

// ---------------- normal vector stuff --------------------------
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


// ---------------- now vector< vector > stuff --------------------
#  pragma define_template vector< vector< _vector_contents_ > >
#  pragma define_template copy< vector< _vector_contents_ >*, vector< _vector_contents_ >* >
#  pragma define_template copy< const vector< _vector_contents_ >*, vector< _vector_contents_ >* >
#  pragma define_template copy_backward< vector< _vector_contents_ >* ,  vector< _vector_contents_ > *>
#  pragma define_template fill< vector< _vector_contents_ >* ,  vector< _vector_contents_ > >

//#  pragma define_template vector<vector<int, allocator<int> >, allocator<vector<int, allocator<int> > > >::insert_aux(vector<int, allocator<int> >*, const vector<int, allocator<int> >&)

#else

#include "STLUtility/fwd_vector.h"
template class STL_VECTOR( STL_VECTOR( _vector_contents_ ) ) ;

#if ( defined(NO_IMPLICIT_INSTANTIATION) && defined(__DECCXX) )
#include "STLUtility/instantiate_vector.h"

template STL_VECTOR( _vector_contents_ )* 
std::copy( STL_VECTOR( _vector_contents_ ) *, 
      STL_VECTOR( _vector_contents_ ) *, 
      STL_VECTOR( _vector_contents_ ) * );

template STL_VECTOR( _vector_contents_ )* 
std::copy( STL_VECTOR( _vector_contents_ ) const*, 
      STL_VECTOR( _vector_contents_ ) const*, 
      STL_VECTOR( _vector_contents_ ) * );
template STL_VECTOR( _vector_contents_ )* 
std::copy_backward( STL_VECTOR( _vector_contents_ )* ,  
	       STL_VECTOR( _vector_contents_ )* ,
	       STL_VECTOR( _vector_contents_ )* );
template void std::fill( STL_VECTOR( _vector_contents_ )* ,  
		    STL_VECTOR( _vector_contents_ )* ,
		    STL_VECTOR( _vector_contents_ ) const& );
#endif
#endif /* defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) */

#endif /* STLUTILITY_INSTANTIATE_VECTOR_OF_VECTOR_H */


