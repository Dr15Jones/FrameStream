// -*- C++ -*-
//
// Bug Name:   NEED_NAMESPACE_TO_INSTANTIATE_OVERLOADED_FUNCTION_BUG
// 
// Description: 
//      Demonstates the bug seen in cxx 6.0 which requires that the
//    namespace for an overloaded templated function be explicitly
//    included when doing explicit instantiation of the function.
//
// Existance:
//    cxx: 6.0
//
//
// Author:      Chris D. Jones
// Created:     Tue Jun 23 10:08:00 EDT 1998
// $Id: need_namespace_to_instantiate_overloaded_function_bug.cc,v 1.3 2001/01/16 22:25:18 cdj Exp $
//
// Revision history
//
// $Log: need_namespace_to_instantiate_overloaded_function_bug.cc,v $
// Revision 1.3  2001/01/16 22:25:18  cdj
// now closer to C++ standard
//
// Revision 1.2  2000/05/05 19:38:37  mkl
// get started on linux
//
// Revision 1.1  1998/06/23 19:35:54  cdj
// demonstate the bug
//

#include "Experiment/Experiment.h"

#if !defined(NO_NAMESPACE_BUG)
namespace mine {

template< class T >
int foo( const T& ) ;

template< class T, class U >
int foo( const T&, const U& ) ;

template< class T >
int foo( const T& ) {
   return sizeof(T);
}

template< class T, class U >
int foo( const T&, const U& ) {
   return sizeof(T)+sizeof(U);
}

}
using namespace mine;

#if defined( NEED_NAMESPACE_TO_INSTANTIATE_OVERLOADED_FUNCTION_BUG )
template int foo( const int& , const float& );
#else
#if defined(NEED_TYPESPEC_TO_INSTANTIATE_NAMESPACED_FUNCTION_BUG)
template int foo<int, float>( const int& , const float& );
#else
#if defined( NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_FUNCTION_BUG )
namespace mine {
template int foo( const int& , const float& );
}
#else
template int foo( const int& , const float& );
#endif
#endif
#endif
#endif // NO_NAMESPACE_BUG

