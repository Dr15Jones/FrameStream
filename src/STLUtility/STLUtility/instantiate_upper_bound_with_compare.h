#if !defined(STLUTILITY_INSTANTIATE_UPPER_BOUND_WITH_COMPARE_H)
#define STLUTILITY_INSTANTIATE_UPPER_BOUND_WITH_COMPARE_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      instantiate_upper_bound_with_compare
// 
/**\class instantiate_upper_bound_with_compare instantiate_upper_bound_with_compare.h STLUtility/instantiate_upper_bound_with_compare.h

 Description: File is used to instantiate the symbols necessary to use the 
 generic function upper_bound

 Usage:
    The user must typedef the three classes
         _upper_bound_iterator_ : an input iterator
	 _upper_bound_compare_   : the comparison function used

*/
//
// Author:      Chris D Jones
// Created:     Thu Nov  2 10:44:34 EST 2000
// $Id: instantiate_upper_bound_with_compare.h,v 1.1 2002/05/06 10:29:10 bkh Exp $
//
// Revision history
//
// $Log: instantiate_upper_bound_with_compare.h,v $
// Revision 1.1  2002/05/06 10:29:10  bkh
// add upper bound just like lower
//
// Revision 1.1  2000/11/02 19:56:22  cdj
// added instantiate_upper_bound_with_compare.h
//

// system include files

// user include files


#if defined(__DECCXX)
typedef STD_PREFIX iterator_traits<_upper_bound_iterator_> _upper_bound_iterator_traits_;
template _upper_bound_iterator_ 
STD_PREFIX _RWupper_bound(_upper_bound_iterator_, 
		    _upper_bound_iterator_, 
		    const _upper_bound_iterator_traits_::value_type &, 
		    _upper_bound_compare_ , 
		    _upper_bound_iterator_traits_::difference_type*, 
		    _upper_bound_iterator_traits_::iterator_category ) ;
#endif

#endif /* STLUTILITY_INSTANTIATE_UPPER_BOUND_WITH_COMPARE_H */






