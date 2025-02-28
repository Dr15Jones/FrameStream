#if !defined(STLUTILITY_INSTANTIATE_LOWER_BOUND_WITH_COMPARE_H)
#define STLUTILITY_INSTANTIATE_LOWER_BOUND_WITH_COMPARE_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      instantiate_lower_bound_with_compare
// 
/**\class instantiate_lower_bound_with_compare instantiate_lower_bound_with_compare.h STLUtility/instantiate_lower_bound_with_compare.h

 Description: File is used to instantiate the symbols necessary to use the 
 generic function lower_bound

 Usage:
    The user must typedef the three classes
         _lower_bound_iterator_ : an input iterator
	 _lower_bound_compare_   : the comparison function used

*/
//
// Author:      Chris D Jones
// Created:     Thu Nov  2 10:44:34 EST 2000
// $Id: instantiate_lower_bound_with_compare.h,v 1.1 2000/11/02 19:56:22 cdj Exp $
//
// Revision history
//
// $Log: instantiate_lower_bound_with_compare.h,v $
// Revision 1.1  2000/11/02 19:56:22  cdj
// added instantiate_lower_bound_with_compare.h
//

// system include files

// user include files


#if defined(__DECCXX)
typedef STD_PREFIX iterator_traits<_lower_bound_iterator_> _lower_bound_iterator_traits_;
template _lower_bound_iterator_ 
STD_PREFIX _RWlower_bound(_lower_bound_iterator_, 
		    _lower_bound_iterator_, 
		    const _lower_bound_iterator_traits_::value_type &, 
		    _lower_bound_compare_ , 
		    _lower_bound_iterator_traits_::difference_type*, 
		    _lower_bound_iterator_traits_::iterator_category ) ;
#endif

#endif /* STLUTILITY_INSTANTIATE_LOWER_BOUND_WITH_COMPARE_H */






