#if !defined(STLUTILITY_INSTANTIATE_SORT_COMPARE_H)
#define STLUTILITY_INSTANTIATE_SORT_COMPARE_H
// -*- C++ -*-
//
// Package:     STLUTILITY
// Module:      instantiate_sort_compare
// 
// Description: Instantiate the STL sort algorithm that take two iterators
//              and the compare object as arguments.
//
// Usage:
//    This header instantiates 
//        void sort( iter_first, iter_last, Compare() );
//
//    The user must set these typedefs before including this header file:
//        _sort_value_type_     = the object in your container to sort
//        _sort_iterator_       = the iterator type for the container to sort
//        _sort_compare_class_  = the comparison class 
//
//    e.g. If you had an stl vector of MyItem*, then you would need...
//              typedef MyItem*                         _sort_value_type_;
//              typedef STL_VECTOR(MyItem*)::iterator   _sort_iterator_;
//              typedef MyItemPtrCompare                _sort_compare_class_;
//              
//
//   NOTE: If you do not use the ancillary class for comparison, use
//         instantiate_sort.cc instead. See that file for instructions.
//
//
// Author:      Adam Lyon
// Created:     Mon Apr 13 13:38:23 EDT 1999
// $Id: instantiate_sort_compare.h,v 1.3 2001/12/18 23:01:54 lyon Exp $
//
// Revision history
//
// $Log: instantiate_sort_compare.h,v $
// Revision 1.3  2001/12/18 23:01:54  lyon
// Fix confusing typo in documentation
//
// Revision 1.2  1999/10/30 12:34:01  cleo3
// updated to work with cxx 6.2
//
// Revision 1.1  1999/04/16 21:22:30  lyon
// Instantiations for sorts
//

// system include files
#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

#if ( defined(__DECCXX) )

template void STD_PREFIX sort( _sort_iterator_, _sort_iterator_, 
			       _sort_compare_class_ );

template void STD_PREFIX STLUTILITY_FUNC(final_insertion_sort)
                                               (_sort_iterator_,
						_sort_iterator_,
						_sort_compare_class_);

template void STD_PREFIX STLUTILITY_FUNC(insertion_sort)
                                         (_sort_iterator_,
					  _sort_iterator_,
					  _sort_compare_class_);

template void STD_PREFIX STLUTILITY_FUNC(unguarded_insertion_sort_aux)
                                                       (_sort_iterator_,
							_sort_iterator_,
							_sort_value_type_*,
							_sort_compare_class_);

template void STD_PREFIX STLUTILITY_FUNC(quick_sort_loop_aux)
                                              (_sort_iterator_,
					       _sort_iterator_,
					       _sort_value_type_*,
					       _sort_compare_class_);

template _sort_iterator_ STD_PREFIX STLUTILITY_FUNC(unguarded_partition)
                                              (_sort_iterator_,
					       _sort_iterator_,
					       _sort_value_type_,
					       _sort_compare_class_);


template void STD_PREFIX STLUTILITY_FUNC(unguarded_linear_insert)
                                                  (_sort_iterator_,
						   _sort_value_type_,
						   _sort_compare_class_);


#endif

#endif /* STLUTILITY_INSTANTIATE_SORT_COMPARE_H */
