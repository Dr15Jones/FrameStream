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
// $Id: need_typespec_to_instantiate_namespaced_function_bug.cc,v 1.2 2001/01/16 22:25:18 cdj Exp $
//
// Revision history
//
// $Log: need_typespec_to_instantiate_namespaced_function_bug.cc,v $
// Revision 1.2  2001/01/16 22:25:18  cdj
// now closer to C++ standard
//
// Revision 1.1  2000/05/05 19:38:38  mkl
// get started on linux
//
// Revision 1.1  1998/06/23 19:35:54  cdj
// demonstate the bug
//

#include "Experiment/Experiment.h"

#if !defined(NO_NAMESPACE_BUG)
namespace mine {

template< class T >
int foo( const T& ){
    return 0;   
}

}
using namespace mine;

//#define NEED_TYPESPEC_TO_INSTANTIATE_NAMESPACED_FUNCTION_BUG
#if defined(NEED_TYPESPEC_TO_INSTANTIATE_NAMESPACED_FUNCTION_BUG)
#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_FUNCTION_BUG)
namespace mine {
template int mine::foo<int>( const int& );
}
#else
template int mine::foo<int>( const int& );
#endif
#else
#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_FUNCTION_BUG)
namespace mine {
template int mine::foo( const int& );
}
#else
template int mine::foo( const int& );
#endif
#endif
#endif // NO_NAMESPACE_BUG




