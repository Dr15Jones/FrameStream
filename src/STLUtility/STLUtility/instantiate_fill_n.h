// -*- C++ -*-
//
// Package:     STLUtility
// Module:      instantiate_fill_n_
// 
// Description: instantiate fill_n
//
// Implementation:
//                  The user must define 3 typedefs :
//         _fill_n_iterator_       :  the output iterator type
//         _fill_n_size_type_      :  the number-of-items type
//         _fill_n_value_type_     :  the class type of the value
//                                    (with no const or reference in it)
//
// Author:      Brian K. Heltsley
// Created:     Thu Apr 22 15:07:04 EDT 1999
// $Id: instantiate_fill_n.h,v 1.1 1999/04/22 19:46:07 bkh Exp $
//
// Revision history
//
// $Log: instantiate_fill_n.h,v $
// Revision 1.1  1999/04/22 19:46:07  bkh
// helper file for stl fill_n algorithm
//

#if !defined(STD_PREFIX)
#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif
#endif

#if ( defined(__DECCXX) )

template void STD_PREFIX fill_n( _fill_n_iterator_    ,
				 _fill_n_size_type_   ,
				 const _fill_n_value_type_&   ) ; 
#endif
