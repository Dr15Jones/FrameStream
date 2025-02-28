// -*- C++ -*-
//
// Package:     Bug
// Module:      old_iterator_classes_bug
// 
// Description: Test to see if the compiler is using the old iterator classes
//
// Usage:
//     The final C++ standard changed what you were supposed to inherit from
//      when creating your own iterators.  
//
//     A work around for this problem is to use CPP macros
//
// #if defined(OLD_ITERATOR_CLASSES_BUG)
// #define STL_FORWARD_ITERATOR( it_value_type_ ) forward_iterator< it_value_type_ , ptrdiff_t >
// #else
// #define STL_FORWARD_ITERATOR( it_value_type_ ) iterator< forward_iterator_tag, it_value_type_ >
// #endif
//
// This solution is available by including STLUtility/iterator_macros.h
//
// Author:      Chris D Jones
// Created:     Sat Oct 23 15:24:29 EDT 1999
// $Id: old_iterator_classes_bug.cc,v 1.3 2001/01/16 22:25:21 cdj Exp $
//
// Revision history
//
// $Log: old_iterator_classes_bug.cc,v $
// Revision 1.3  2001/01/16 22:25:21  cdj
// now closer to C++ standard
//
// Revision 1.2  2000/05/05 19:38:38  mkl
// get started on linux
//
// Revision 1.1  1999/10/23 20:57:05  cdj
// first submission
//

#include "Experiment/Experiment.h"

#include <iterator>

#if !defined(NO_NAMESPACE_BUG)
using namespace std;
#endif

#if defined(OLD_ITERATOR_CLASSES_BUG)
#define STL_FORWARD_ITERATOR( it_value_type_ ) forward_iterator< it_value_type_ , ptrdiff_t >
#else
#define STL_FORWARD_ITERATOR( it_value_type_ ) iterator< forward_iterator_tag, it_value_type_ >
#endif


class MyIterator :
#if defined(OLD_ITERATOR_CLASSES_BUG)
      public forward_iterator< int, ptrdiff_t >
#else
      public iterator< forward_iterator_tag,  int >
#endif
{
};

