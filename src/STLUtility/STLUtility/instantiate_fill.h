// -*- C++ -*-
//
// Package:     STLUtility
// Module:      instantiate_fill
// 
// Description: instantiate fill
//
// Implementation:
//                  The user must define 2 typedefs :
//         _fill_iterator_       :  the output iterator type
//         _fill_value_type_     :  the class type of the value
//                                    (with no const or reference in it)
//
// Author:      Brian K. Heltsley
// Created:     Tue Jun 08 15:07:04 EDT 1999
// $Id: instantiate_fill.h,v 1.1 1999/06/08 21:18:59 bkh Exp $
//
// Revision history
//
// $Log: instantiate_fill.h,v $
// Revision 1.1  1999/06/08 21:18:59  bkh
// add fill and rotate instantiation helper files
//
//

#if !defined(STD_PREFIX)
#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif
#endif

#if ( defined(__DECCXX) )

template void STD_PREFIX fill( _fill_iterator_    ,
			       _fill_iterator_    ,
			       const _fill_value_type_&   ) ; 
#endif
