#if !defined(STLUTILITY_ITERATOR_TRAITS_FIX_H)
#define STLUTILITY_ITERATOR_TRAITS_FIX_H
// -*- C++ -*-
//
// Package:     <STLUtility>
// Module:      iterator_traits_fix
// 
/**\class iterator_traits_fix iterator_traits_fix.h STLUtility/iterator_traits_fix.h

 Description: Define iterator_traits if the STL version is not C++ standards compliant

 Usage:
    If you need an iterator_traits for a pointer type, you can use the macros
    ITERATOR_TRAITS_PTR or ITERATOR_TRAITS_CONST_PTR depending on whether
    it is a pointer or a const pointer.
    
*/
//
// Author:      Chris D Jones
// Created:     Sun Oct  1 09:59:03 EDT 2000
// $Id: iterator_traits_fix.h,v 1.2 2003/07/29 15:40:28 cdj Exp $
//
// Revision history
//
// $Log: iterator_traits_fix.h,v $
// Revision 1.2  2003/07/29 15:40:28  cdj
// Improve handling of iterator_traits when the compiler doesn't have iterator traits but does do partial template specialization
//
// Revision 1.1  2000/10/01 14:51:45  cdj
// added iterator_traits_fix.h
//

// system include files
#include <iterator>

// user include files

// forward declarations

#if defined(NO_ITERATOR_TRAITS_BUG)
#if !defined( ITERATOR_TRAITS )
#define ITERATOR_TRAITS
//need an iterator traits
template< class T>
struct iterator_traits {
      typedef typename T::value_type value_type;
};
#endif
#if defined(NO_PARTIAL_TEMPLATE_SPECIALIZATION_BUG)
#define ITERATOR_TRAITS_PTR( _type_ ) \
template<> struct iterator_traits<_type_*> { typedef _type_ value_type; };

#define ITERATOR_TRAITS_CONST_PTR( _type_ ) \
template<> struct iterator_traits<const _type_*> { typedef _type_ value_type;};

ITERATOR_TRAITS_PTR(char)
ITERATOR_TRAITS_CONST_PTR(char)

ITERATOR_TRAITS_PTR(short)
ITERATOR_TRAITS_CONST_PTR(short)

ITERATOR_TRAITS_PTR(int)
ITERATOR_TRAITS_CONST_PTR(int)

ITERATOR_TRAITS_PTR(long)
ITERATOR_TRAITS_CONST_PTR(long)

ITERATOR_TRAITS_PTR(unsigned char)
ITERATOR_TRAITS_CONST_PTR(unsigned char)

ITERATOR_TRAITS_PTR(unsigned short)
ITERATOR_TRAITS_CONST_PTR(unsigned short)

ITERATOR_TRAITS_PTR(unsigned int)
ITERATOR_TRAITS_CONST_PTR(unsigned int)

ITERATOR_TRAITS_PTR(unsigned long)
ITERATOR_TRAITS_CONST_PTR(unsigned long)

ITERATOR_TRAITS_PTR(float)
ITERATOR_TRAITS_CONST_PTR(float)

ITERATOR_TRAITS_PTR(double)
ITERATOR_TRAITS_CONST_PTR(double)
#else

template<class T>
struct iterator_traits<T*> {
      typedef T value_type;
};
template<class T>
struct iterator_traits<const T*> {
      typedef T value_type;
};

//partial specialization takes care of these
#define ITERATOR_TRAITS_PTR( _type_ )
#define ITERATOR_TRAITS_CONST_PTR( _type_ )
#endif
#else
//don't need to do anything 
#define ITERATOR_TRAITS_PTR( _type_ )
#define ITERATOR_TRAITS_CONST_PTR( _type_ )
#endif

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "STLUtility/Template/iterator_traits_fix.cc"
//#endif

#endif /* STLUTILITY_ITERATOR_TRAITS_FIX_H */
