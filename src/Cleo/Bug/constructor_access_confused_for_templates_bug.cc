// -*- C++ -*-
//
// Bug Name:    CONSTRUCTOR_ACCESS_CONFUSED_FOR_TEMPLATES_BUG
// 
// Description:
//     It appears that when upcasting a reference to a templated class
// to its base class within a second templated class, the compiler
// complains that a constructor is not accessible.
//
//     The work around appears simple, you only need to add an used
// instance to thew class before the upcast!!
//
// Existance:
//   cxx: all versions
//
// Author:      Simon Patton
// Created:     Fri Aug  1 11:50:21 EDT 1997
// $Id: constructor_access_confused_for_templates_bug.cc,v 1.2 1999/10/23 20:50:29 cdj Exp $
//
// Revision history
//
// $Log: constructor_access_confused_for_templates_bug.cc,v $
// Revision 1.2  1999/10/23 20:50:29  cdj
// bug fix: One needs default constructor
//
// Revision 1.1  1998/03/16 22:59:51  mkl
// Simon's bug code snipplets for bug/feature flags
//
//

class One
{
   public:
      One() {}

   private:
      One( const One& a ) ;
} ;

template < class T >
class Two : public One
{
   public:
      Two() {} 

   private:
      Two( const Two& a ) ;
} ;


//const Two< int > tmp ;


template < class T >
class Three
{
   public:
      const One& getOne() ;
   private:
      static const Two< T >& getTwo() ;
} ;

template < class T >
const One&
Three< T >::getOne()
{
#if defined(CONSTRUCTOR_ACCESS_CONFUSED_FOR_TEMPLATES_BUG)
   const Two< T > a ;
#endif
   return ( getTwo() ) ;
}

template < class T >
const Two< T >&
Three< T >::getTwo()
{
   static Two< T > a ;
   return ( a ) ;
}

#if defined(__DECCXX)
#pragma define_template Three< int >
#else
template class Three< int > ;
#endif
