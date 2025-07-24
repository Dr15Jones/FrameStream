#if !defined(STLUTILITY_INSTANTIATE_SORT_H)
#define STLUTILITY_INSTANTIATE_SORT_H
// -*- C++ -*-
//
// Package:     STLUTILITY
// Module:      instantiate_sort
// 
// Description: Instantiate the STL sort algorithm that take two iterators
//              as arguments.
//
// Usage:
//    This header instantiates 
//        void sort(iter_first, iter_last);
//
//    The user must set these typedefs before including this header file:
//        _sort_value_type_  = the object in your container to sort
//        _sort_iterator_    = the iterator type for the container to sort
//
//    e.g. If you had an stl vector of MyItem, then you would need...
//              typedef std::vector<MyItem>             _sort_value_type_;
//              typedef std::vector<MyItem>::iterator   _sort_iterator_;
//
//   NOTE: If you use and ancillary class for the comparison, then you 
//         cannot use this header. You must use instantiate_sort_compare.h
//         instead. See that file for instructions.
//
//
// Author:      Adam Lyon
// Created:     Mon Apr 12 13:38:23 EDT 1999
// $Id: instantiate_sort.h,v 1.2 1999/10/30 12:34:01 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_sort.h,v $
// Revision 1.2  1999/10/30 12:34:01  cleo3
// updated to work with cxx 6.2
//
// Revision 1.1  1999/04/16 21:22:26  lyon
// Instantiations for sorts
//

// system include files
#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

#if ( defined(__DECCXX) )

template void STD_PREFIX sort( _sort_iterator_, _sort_iterator_ );

template void STD_PREFIX STLUTILITY_FUNC(final_insertion_sort)
                                               (_sort_iterator_,
						_sort_iterator_);

template void STD_PREFIX STLUTILITY_FUNC(insertion_sort)
                                         (_sort_iterator_,
					  _sort_iterator_);

template void STD_PREFIX STLUTILITY_FUNC(unguarded_insertion_sort_aux)
                                                       (_sort_iterator_,
							_sort_iterator_,
							_sort_value_type_*);

template void STD_PREFIX STLUTILITY_FUNC(quick_sort_loop_aux)
                                              (_sort_iterator_,
					       _sort_iterator_,
					       _sort_value_type_*);

template _sort_iterator_ STD_PREFIX STLUTILITY_FUNC(unguarded_partition)
                                              (_sort_iterator_,
					       _sort_iterator_,
					       _sort_value_type_);


template void STD_PREFIX STLUTILITY_FUNC(unguarded_linear_insert)
                                                  (_sort_iterator_,
						   _sort_value_type_);


#endif

#endif /* STLUTILITY_INSTANTIATE_SORT_H */
