// -*- C++ -*-
//
// Package:     Bug
// Module:      no_iterator_traits_bug
// 
// Description: Test if compiler's STL uses iterator_traits
//
// Implementation:
//     If this file fails to compile, try recompiling with 
//      NO_ITERATOR_TRAITS_BUG flag set
//
// Author:      Chris D Jones
// Created:     Sat Oct 23 14:13:09 EDT 1999
// $Id: no_iterator_traits_bug.cc,v 1.2 2001/01/16 22:25:20 cdj Exp $
//
// Revision history
//
// $Log: no_iterator_traits_bug.cc,v $
// Revision 1.2  2001/01/16 22:25:20  cdj
// now closer to C++ standard
//
// Revision 1.1  1999/10/23 20:57:04  cdj
// first submission
//
#include "Experiment/Experiment.h"
#include <iostream.h>
#include <iterator>

#if !defined(NO_STD_NAMESPACE_BUG)
//using namespace std;
#endif

#if defined(NO_ITERATOR_TRAITS_BUG)
//create our own simplified iterator_traits
template< class Iterator >
class iterator_traits {
   public:
      typedef Iterator::value_type value_type;
};

//need to specialize use of pointers as iterators 
template<> class iterator_traits<int*> {
  public:
   typedef int value_type;
};

template<> class iterator_traits<unsigned int*> {
  public:
   typedef unsigned int value_type;
};
#endif 

//use iterator traits to pick which tester_iterator_type() to call
template< class Iterator >
void tester( Iterator  ) {
   typename iterator_traits<Iterator>::value_type* dummy = 0;
   tester_iterator_type( dummy );
}

void tester_iterator_type( int* ) {
   cout <<"int" << endl;
}

void tester_iterator_type( unsigned int* ) {
   cout <<"unsigned int" << endl;
}

int main()
{
   int* p1 = 0;
   tester(p1);

   unsigned int* p2 = 0;
   tester(p2);
}

