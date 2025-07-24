#if !defined(STLUTILITY_INSTANTIATE_PARTIAL_SORT_COMPARE_H)
#define STLUTILITY_INSTANTIATE_PARTIAL_SORT_COMPARE_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      instantiate_partial_sort_compare
// 
// Description: instantiate help file for partial_sort with compare class
//
// Usage: The user must with typedefs define 4 classes:
//
//        _partial_sort_iterator_       : the iterator type
//        _partial_sort_value_type_     : the type that the iterator points to
//        _partial_sort_distance_type_  : the iterator difference_type
//        _partial_sort_compare_class_  : the comparison class which must
//                                        have an boolean member function
//                          operator()( _partial_sort_value_type_ ,
//                                      _partial_sort_value_type_ ) 
//    
//        For example, if you had an stl vector of doubles to be sorted
//
// typedef double                               _partial_sort_value_type_    ;
// typedef std::vector< Value >::iterator        _partial_sort_iterator_      ;
// typedef std::vector< Value >::difference_type _partial_sort_distance_type_ ;
// typedef less<double>                         _partial_sort_compare_class_ ;
//
//
//  If _partial_sort_value_type_ is not a built-in class, then you must have
//  something like the following:
//
//        class CompareWidgetClass
//        {
//          public:
//             DABoolean operator()( const Widget p1 , const Widget p2 ) const
//             {
//                return someFunction( p1 ) < someFunction( p2 ) ;
//             }
//        } ;
//
// Author:      Brian K. Heltsley
// Created:     Fri Apr  9 13:38:53 EDT 1999
// $Id: instantiate_partial_sort_compare.h,v 1.2 1999/10/30 12:34:00 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_partial_sort_compare.h,v $
// Revision 1.2  1999/10/30 12:34:00  cleo3
// updated to work with cxx 6.2
//
// Revision 1.1  1999/04/12 19:19:36  bkh
// add some generic algorithm instantiate headers
//

// system include files

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif


#if ( defined(__DECCXX) )

template void STD_PREFIX STLUTILITY_FUNC(partial_sort)
                                       ( _partial_sort_iterator_      ,
					 _partial_sort_iterator_      ,
					 _partial_sort_iterator_      ,
					 _partial_sort_value_type_*   ,
					 _partial_sort_compare_class_   ) ;

template void STD_PREFIX STLUTILITY_FUNC(adjust_heap)
                                      (  _partial_sort_iterator_      ,
					 _partial_sort_distance_type_ ,
					 _partial_sort_distance_type_ , 
					 _partial_sort_value_type_    ,
					 _partial_sort_compare_class_   ) ;

template void STD_PREFIX STLUTILITY_FUNC(push_heap)
                                    (    _partial_sort_iterator_      ,
					 _partial_sort_distance_type_ , 
					 _partial_sort_distance_type_ ,
					 _partial_sort_value_type_    , 
					 _partial_sort_compare_class_   ) ;

template void STD_PREFIX sort_heap(      _partial_sort_iterator_      ,
					 _partial_sort_iterator_      ,
					 _partial_sort_compare_class_   ) ;

template void STD_PREFIX STLUTILITY_FUNC(make_heap)
                                    (    _partial_sort_iterator_      ,
					 _partial_sort_iterator_      ,
					 _partial_sort_compare_class_ ,
					 _partial_sort_value_type_*   ,
					 _partial_sort_distance_type_*  ) ;

#endif

#endif /* STLUTILITY_INSTANTIATE_PARTIAL_SORT_COMPARE_H */
