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
// $Id: typename_bug.cc,v 1.1 2001/01/16 22:26:51 cdj Exp $
//
// Revision history
//
// $Log: typename_bug.cc,v $
// Revision 1.1  2001/01/16 22:26:51  cdj
// first submission
//
// Revision 1.2  1998/04/09 23:15:25  cleo3
// port to egcs
//
// Revision 1.1  1998/04/09 15:01:35  cleo3
// sample program testing typename bug
//
//
#include "Experiment/Experiment.h"
#if defined(typename)
#undef typename
#endif

#include <iostream.h>

// one way around it is to define typename to nothing
//#if defined(__DECCXX)
//#define typename
//#endif

#if !defined(TYPENAME_BUG)
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
#endif // TYPENAME_BUG
