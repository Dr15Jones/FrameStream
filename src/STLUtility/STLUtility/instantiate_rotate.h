// -*- C++ -*-
//
// Package:     STLUtility
// Module:      instantiate_rotate
// 
// Description: instantiate rotate
//
// Implementation:
//                  The user must define 2 typedefs :
//         _rotate_iterator_         :  the output iterator type
//         _rotate_difference_type_  :  the iterator difference_type
//
// Author:      Brian K. Heltsley
// Created:     Tue Jun 08 15:07:04 EDT 1999
// $Id: instantiate_rotate.h,v 1.2 1999/10/30 12:34:00 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_rotate.h,v $
// Revision 1.2  1999/10/30 12:34:00  cleo3
// updated to work with cxx 6.2
//
// Revision 1.1  1999/06/08 21:19:00  bkh
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

template void STD_PREFIX STLUTILITY_FUNC(rotate) 
                                 ( _rotate_iterator_         ,
				   _rotate_iterator_         ,
				   _rotate_iterator_         ,
				   _rotate_difference_type_* ,
				   STD_PREFIX random_access_iterator_tag ) ;

template void STD_PREFIX STLUTILITY_FUNC(rotate_cycle) 
                                       ( _rotate_iterator_         ,
					 _rotate_iterator_         ,
					 _rotate_iterator_         ,
					 _rotate_difference_type_  ,
				         _rotate_iterator_           ) ;

template _rotate_difference_type_ 
              STD_PREFIX STLUTILITY_FUNC(gcd) 
                              ( _rotate_difference_type_  ,
				_rotate_difference_type_    ) ;

#endif
