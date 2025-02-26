// -*- C++ -*-
//
// Bug Name:    typename keyword not defined
// 
// Description:
//     The C++ standard wants "typename" to be used in templates, whenever
//     the compiler can't be psychic.
//
// Existance:
//   cxx:
//
// Author:      Martin Lohner
// Created:     Thu Apr 9 11:50:21 EDT 1998
// $Id: typename.cc,v 1.2 1998/04/09 23:15:25 cleo3 Exp $
//
// Revision history
//
// $Log: typename.cc,v $
// Revision 1.2  1998/04/09 23:15:25  cleo3
// port to egcs
//
// Revision 1.1  1998/04/09 15:01:35  cleo3
// sample program testing typename bug
//
//

#include <iostream.h>

// one way around it is to define typename to nothing
//#if defined(__DECCXX)
//#define typename
//#endif


class MyClass
{
   public:
      typedef int MyType;
};

template< class T >
class MyTemplateClass
{
   public:
      typedef typename T::MyType MyType;
};


template class MyTemplateClass< MyClass >;
