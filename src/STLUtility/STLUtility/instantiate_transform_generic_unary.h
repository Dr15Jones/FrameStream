#if !defined(STLUTILITY_INSTANTIATE_TRANSFORM_UNARY_H)
#define STLUTILITY_INSTANTIATE_TRANSFORM_UNARY_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      instantiate_transform_unary
// 
// Description: instantiate help file for the 4-arg transform that
//              takes
//
// Usage: The user must with typedefs define 4 classes:
//      _transform_in_iterator_      : iterator for the input container
//      _transform_in_element_type_  : type held by the input container
//      _transform_out_iterator_     : iterator for the output container
//      _transform_out_element_type_ : type held by the output container
//
//      This form of the instatiation should be useful if your unary 
//      function is built from elements of <functional>
//
// Author:      Lawrence K. Gibbons
// Created:     Mon Jun 10 14:55:00 EDT 1999
// $Id: instantiate_transform_generic_unary.h,v 1.1 1999/06/24 00:31:17 lkg Exp $
//
// Revision history
//
// $Log: instantiate_transform_generic_unary.h,v $
// Revision 1.1  1999/06/24 00:31:17  lkg
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

typedef _transform_out_element_type_ 
                (*_transform_function_ptr_)(_transform_in_element_type_);

template _transform_out_iterator_ 
STD_PREFIX transform( _transform_in_iterator_,
		      _transform_in_iterator_,
		      _transform_out_iterator_,
		      _transform_function_ptr_ ) ;
#endif

#endif /* STLUTILITY_INSTANTIATE_TRANSFORM_UNARY_H */
