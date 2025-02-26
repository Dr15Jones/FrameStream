#if !defined(STLUTILITY_ITERATOR_MACROS_H)
#define STLUTILITY_ITERATOR_MACROS_H
// -*- C++ -*-
//
// Package:     <STLUtility>
// Module:      iterator_macros
// 
/**\file iterator_macros.h STLUtility/iterator_macros.h

 Description: CPP Macros to handle the change in STL iterators that occured
              between the ARM and the final standard

 Usage:
    When inheriting from an iterator, us the appropriate macro

*/
//
// Author:      Chris Jones
// Created:     Fri Oct 22 18:01:16 EDT 1999
// $Id: iterator_macros.h,v 1.1 1999/10/30 12:34:02 cleo3 Exp $
//
// Revision history
//
// $Log: iterator_macros.h,v $
// Revision 1.1  1999/10/30 12:34:02  cleo3
// updated to work with cxx 6.2
//

// system include files
#include <iterator>

// user include files

// forward declarations
#if defined(OLD_ITERATOR_CLASSES_BUG)
#define STL_FORWARD_ITERATOR( it_value_type_ ) forward_iterator< it_value_type_ , ptrdiff_t >
#else
#define STL_FORWARD_ITERATOR( it_value_type_ ) iterator< forward_iterator_tag, it_value_type_ >
#endif
#endif /* STLUTILITY_ITERATOR_MACROS_H */
