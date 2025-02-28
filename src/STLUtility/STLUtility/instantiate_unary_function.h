#if !defined(STLUTILITY_INSTANTIATE_UNARY_FUNCTION_H)
#define STLUTILITY_INSTANTIATE_UNARY_FUNCTION_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      instantiate_unary_function
// 
// Description: instantiate help file for find with predicate
//
// Usage: The user must with typedefs define 2 classes:
//      _unary_function_arg_    : the argument type of the unary function
//      _unary_function_result_ : the result type of the unary function
//
//
// Author:      Lawrence K. Gibbons
// Created:     Mon Jun 10 16:31:53 EDT 1999
// $Id: instantiate_unary_function.h,v 1.1 1999/06/24 00:33:20 lkg Exp $
//
// Revision history
//
// $Log: instantiate_unary_function.h,v $
// Revision 1.1  1999/06/24 00:33:20  lkg
// Helper function for instantiation of a unary function
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

template class unary_function< _unary_function_arg_ , _unary_function_result_ >;

#endif

#endif /* STLUTILITY_INSTANTIATE_UNARY_FUNCTION_H */
