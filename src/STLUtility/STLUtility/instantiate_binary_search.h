#if !defined(STLUTILITY_INSTANTIATE_BINARY_SEARCH_H)
#define STLUTILITY_INSTANTIATE_BINARY_SEARCH_H
// -*- C++ -*-
//
// Package:     STLUTILITY
// Module:      instantiate_binary_search
// 
// Description: Instantiate the STL binary search algorithm
//
// Usage:
//    This header instantiates 
//        bool binary_search(iter_first, iter_last, value);
//
//    The user must set these typedefs before including this header file:
//       _binary_search_value_type_ = object type to compare 
//       _binary_search_iterator_   = iterator type for the container to search
//
//    e.g. If you had an stl vector of MyItem, then you would need...
//              typedef STL_VECTOR(MyItem)             _sort_value_type_;
//              typedef STL_VECTOR(MyItem)::iterator   _sort_iterator_;
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Jun 12 13:15:23 EDT 1999
// $Id: instantiate_binary_search.h,v 1.2 1999/10/30 12:33:57 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_binary_search.h,v $
// Revision 1.2  1999/10/30 12:33:57  cleo3
// updated to work with cxx 6.2
//
// Revision 1.1  1999/06/24 00:32:48  lkg
// Helper file for instantiation of the binary search algorithm
//
//

// system include files
#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

#if ( defined(__DECCXX) )

template bool STD_PREFIX binary_search( _binary_search_iterator_ ,
					_binary_search_iterator_ ,
					const _binary_search_value_type_ & );

template _binary_search_iterator_ 
STD_PREFIX lower_bound( _binary_search_iterator_ ,
			_binary_search_iterator_ ,
			const _binary_search_value_type_ & );

typedef iterator_traits< _binary_search_iterator_ >::difference_type*
                                            _binary_search_distance_ ;
typedef iterator_traits< _binary_search_iterator_ >::iterator_category
                                            _binary_search_tag_ ;

template _binary_search_iterator_ 
STD_PREFIX STLUTILITY_FUNC(lower_bound)
                        ( _binary_search_iterator_ ,
			  _binary_search_iterator_ ,
			  const _binary_search_value_type_ & ,
			  _binary_search_distance_ ,
			  _binary_search_tag_ );


#endif

#endif /* STLUTILITY_INSTANTIATE_BINARY_SEARCH_H */
