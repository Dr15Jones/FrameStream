#if !defined(STLUTILITY_INSTANTIATE_EQUAL_RANGE_COMP_H)
#define STLUTILITY_INSTANTIATE_EQUAL_RANGE_COMP_H
// -*- C++ -*-
//
// Package:     <STLUtility>
// Module:      instantiate_equal_range_comp
// 
/*
 Description: instantiate the template equal_range with a comparator 
              function object

 Usage:
    This header instantiates 
        pair<iter,iter> equal_range(iter_first, iter_last, compare_value,
	                            comparator);
 
    The user must set these typedefs before including this header file:
       _equal_range_value_type_ = object type to compare 
       _equal_range_iterator_   = iterator type for the container to search
       _equal_range_comp_       = the comparator function object type
       

    e.g. If you had an stl multiset of MyItem*. Say MyItem* has some member 
         function that returns an int. You want to find the entries in the
         multiset for which that member function returns a certain value 
         (say cellId [an int]). You have a helper function object called
         less_MyItem_cellId that does the comparisons necessary for 
	 equal_range.

	 You do...

	 typedef int _equal_range_value_type_;
         typedef STL_MULTISET(MyItem*)::iterator _equal_range_iterator_;
	 typedef less_MyItem_cellId _equal_range_comp_;

	 The equal_range call you have must look something like:
	 pair<_equal_range_iterator_, _equal_range_iterator_> result = 
            equal_range(myMultiSet.begin(), myMultiSet.end(), theCellIdIWant,
	                _equal_range_comp_() );
*/
//
// Author:      Adam L Lyon
// Created:     Tue May 1 16:16:16 EDT 2001
// $Id: instantiate_equal_range_comp.h,v 1.1 2001/05/01 21:06:08 lyon Exp $
//
// Revision history
//
// $Log: instantiate_equal_range_comp.h,v $
// Revision 1.1  2001/05/01 21:06:08  lyon
// Added
//
//

// system include files
#include <algorithm>


#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

#if ( defined(__DECCXX) )

// Define distance and tag
typedef iterator_traits< _equal_range_iterator_ >::difference_type*
                                            _equal_range_distance_ ;

typedef iterator_traits< _equal_range_iterator_ >::difference_type
                                            _equal_range_distance_val_ ;

typedef iterator_traits< _equal_range_iterator_ >::iterator_category
                                            _equal_range_tag_ ;

// We don't need to instantiate equal_range itself -- it's inlined.

// Instantiate STLUTILITY_FUNC(equal_range) for the forward_iterator_tag
//   (equal_range for the other iterator tags are inlined to 
//    call this one)

template pair< _equal_range_iterator_, _equal_range_iterator_ >
     STD_PREFIX STLUTILITY_FUNC(equal_range)(
			  _equal_range_iterator_,
			  _equal_range_iterator_,
			  const _equal_range_value_type_&,
			  _equal_range_comp_,
			  _equal_range_distance_,
			  forward_iterator_tag);

// Now do the same with upper_limit and lower_limit if necessary
#if !defined(NO_UPPER_BOUND_INSTANTIATION)
 template _equal_range_iterator_ 
    STD_PREFIX STLUTILITY_FUNC(upper_bound)(
			  _equal_range_iterator_,
			  _equal_range_iterator_,
			  const _equal_range_value_type_&,
			  _equal_range_comp_,
			  _equal_range_distance_,
			  forward_iterator_tag);
#endif

#if !defined(NO_LOWER_BOUND_INSTANTIATION)
 template _equal_range_iterator_ 
    STD_PREFIX STLUTILITY_FUNC(lower_bound)(
			  _equal_range_iterator_,
			  _equal_range_iterator_,
			  const _equal_range_value_type_&,
			  _equal_range_comp_,
			  _equal_range_distance_,
			  forward_iterator_tag);
#endif

// Now we instantiate STL_UTILITYFUNC(advance) for the appropriate 
// iterator tag
template void STD_PREFIX STLUTILITY_FUNC(advance)(_equal_range_iterator_&, 
						  _equal_range_distance_val_,
						  _equal_range_tag_);


#endif /* if defined __DECCXX */

#endif /* STLUTILITY_INSTANTIATE_EQUAL_RANGE_COMP_H */
