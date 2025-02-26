#if !defined(STLUTILITY_INSTANTIATE_FOR_EACH_H)
#define STLUTILITY_INSTANTIATE_FOR_EACH_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      Instantiation
// 
// Description: instantiate for_each
//
// Implementation:
//                 The user must define three typedef's:
//                 _for_each_element_type_  : element type to be operated on
//                 _for_each_iterator_      : iterator to the elements
//                 _for_each_function_type_ : the function type to be executed
//                                            on the elements (usually void)
//
//         Note: the function you specify must not be just a 
//               member function; it must be a static member function
//               or a stand-alone function.
//
// Author:      Brian Heltsley
// Created:     Mon Apr 12 14:32:44 EDT 1999
// $Id: instantiate_for_each.h,v 1.1 1999/04/12 19:19:36 bkh Exp $
//
// Revision history
//
// $Log: instantiate_for_each.h,v $
// Revision 1.1  1999/04/12 19:19:36  bkh
// add some generic algorithm instantiate headers
//
//
//

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif


#if ( defined(__DECCXX) )

// the following construct defines the function pointer to be
// a ptr to a function that takes a single argument of the specified type. 

typedef _for_each_function_type_ 
                (*_for_each_function_ptr_)(_for_each_element_type_) ;

template _for_each_function_ptr_ 
        STD_PREFIX for_each( _for_each_iterator_     , 
			     _for_each_iterator_     , 
			     _for_each_function_ptr_   ) ;

#endif

#endif /* STLUTILITY_INSTANTIATE_FOR_EACH_H */
