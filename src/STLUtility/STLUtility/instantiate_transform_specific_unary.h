#if !defined(STLUTILITY_INSTANTIATE_TRANSFORM_SPECIFIC_UNARY_H)
#define STLUTILITY_INSTANTIATE_TRANSFORM_SPECIFIC_UNARY_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      instantiate_transform_specific_unary
// 
// Description: instantiate help file for the 4-arg transform
//
// Usage: The user must with typedefs define 3 classes:
//      _transform_in_iterator_  : iterator for the input container
//      _transform_out_iterator_ : iterator for the output container
//      _transform_unary_fcn_    : unary function that takes a ref.
//                                 to the class in the input container
//                                 and returns the class held by the
//                                 output container
//
//      This instantiation will be useful if you've designed your own
//      class that inherits from unary_fcn.  If your unary fcn is built
//      up from elements of <functional>, you will more likely need
//      instantiate_transform_generic_unary
//
//
// Author:      Lawrence K. Gibbons
// Created:     Mon Jun 10 14:55:00 EDT 1999
// $Id: instantiate_transform_specific_unary.h,v 1.1 1999/06/24 00:31:18 lkg Exp $
//
// Revision history
//
// $Log: instantiate_transform_specific_unary.h,v $
// Revision 1.1  1999/06/24 00:31:18  lkg
// Add instantiation helpers for the transform algorithm that takes a unary
// function.  Two varieties: generic for use with a unary function derived
// from the functional classes {of form T_return *( T_arg )}, and one for
// a specific user-defined class that inherits from unary_function
//
//
//

// system include files

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif


#if ( defined(__DECCXX) )

template _transform_out_iterator_ 
STD_PREFIX transform( _transform_in_iterator_,
		      _transform_in_iterator_,
		      _transform_out_iterator_,
		      _transform_unary_fcn_ ) ;
#endif

#endif /* STLUTILITY_INSTANTIATE_TRANSFORM_SPECIFIC_UNARY_H */
