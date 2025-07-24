#if !defined(STLUTILITY_INSTANTIATE_EQUAL_RANGE_H)
#define STLUTILITY_INSTANTIATE_EQUAL_RANGE_H
// -*- C++ -*-
//
// Package:     <STLUtility>
// Module:      instantiate_equal_range
// 
/*
 Description: instantiate the template equal_range

 Usage:
    This header instantiates 
        std::pair<iter,iter> equal_range(iter_first, iter_last);

    The user must set this typedefs before including this header file:
       _equal_range_value_type_ = object type to compare 
       _equal_range_iterator_   = iterator type for the container to search
       

    e.g. If you had an stl vector of MyItem, then you would need...
              typedef MyItem _equal_range_value_type_;
              typedef std::vector<MyItem>::iterator   _equal_range_iterator_;


*/
//
// Author:      Chris D Jones
// Created:     Wed Jul 12 10:03:59 EDT 2000
// $Id: instantiate_equal_range.h,v 1.1 2000/07/12 20:44:33 cdj Exp $
//
// Revision history
//
// $Log: instantiate_equal_range.h,v $
// Revision 1.1  2000/07/12 20:44:33  cdj
// added instantiate_equal_range.h
//

// system include files
#include <algorithm>


#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

#if ( defined(__DECCXX) )

template std::pair<_equal_range_iterator_,_equal_range_iterator_>
STD_PREFIX equal_range( _equal_range_iterator_ ,
			_equal_range_iterator_,
			const _equal_range_value_type_ &);

typedef iterator_traits< _equal_range_iterator_ >::difference_type*
                                            _equal_range_distance_ ;
typedef iterator_traits< _equal_range_iterator_ >::iterator_category
                                            _equal_range_tag_ ;


template std::pair<_equal_range_iterator_,_equal_range_iterator_>
STD_PREFIX STLUTILITY_FUNC(equal_range)
                         (_equal_range_iterator_, 
			  _equal_range_iterator_, 
			  const _equal_range_value_type_&, 
			  _equal_range_distance_, 
			  _equal_range_tag_);

#if !defined(NO_UPPER_BOUND_INSTANTIATION)
template _equal_range_iterator_ 
STD_PREFIX STLUTILITY_FUNC(upper_bound)
                        ( _equal_range_iterator_ ,
			  _equal_range_iterator_ ,
			  const _equal_range_value_type_ & ,
			  _equal_range_distance_ ,
			  _equal_range_tag_ );
#endif

#if !defined(NO_LOWER_BOUND_INSTANTIATION)
template _equal_range_iterator_ 
STD_PREFIX STLUTILITY_FUNC(lower_bound)
                        ( _equal_range_iterator_ ,
			  _equal_range_iterator_ ,
			  const _equal_range_value_type_ & ,
			  _equal_range_distance_ ,
			  _equal_range_tag_ );
#endif
#endif

#endif /* STLUTILITY_INSTANTIATE_EQUAL_RANGE_H */
