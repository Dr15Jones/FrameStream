// -*- C++ -*-
//
// Package:     <ToolBox>
// Module:      TBDerefItr
// 
// Description: A smart pointer that implements an iterator over a
//              container of T*, eliminating the need for users to
//              double dereference.
//
// Implementation:
//     This just holds an STL list iterator, with the dereferencing
//     operators performing the first level of iteration, returning
//     either a T* (->) or a T& (*).
//
// Author:      Lawrence Gibbons
// Created:     Sat Feb 13 17:09:44 EST 1999
// $Id: TBDerefItr.cc,v 1.2 2003/05/15 19:43:36 cdj Exp $
//
// Revision history
//
// $Log: TBDerefItr.cc,v $
// Revision 1.2  2003/05/15 19:43:36  cdj
// can now use TBDerefItr with iterators that hold smart pointers
//
// Revision 1.1  2000/10/06 18:12:42  lkg
// New dereferencing iterator for containers holding T*. Based on the
// MCListItr class in MCInfo
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <list>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "ToolBox/TBDerefItr.h"

// STL classes
#include <list>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "ToolBox.TBDerefItr" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: TBDerefItr.cc,v 1.2 2003/05/15 19:43:36 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
template<class T_iter, class T_return, class T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>::TBDerefItr()
{}

template<class T_iter, class T_return, class T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>::TBDerefItr( const T_iter& anIterator ) :
   m_iterator( anIterator )
{}

template<class T_iter, class T_return, class T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>::TBDerefItr( const TBDerefItr<T_iter, T_return, T_valueType>& rhs ) :
   m_iterator( rhs.m_iterator )
{}

template<class T_iter, class T_return, class T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>::~TBDerefItr()
{
}

//
// assignment operators
//
template<class T_iter, class T_return, class T_valueType>
const TBDerefItr<T_iter, T_return, T_valueType>& 
TBDerefItr<T_iter, T_return, T_valueType>::operator=(const TBDerefItr<T_iter, T_return, T_valueType>& rhs)
{
  if( this != &rhs ) 
  {
     
     m_iterator = rhs.m_iterator;
  }

  return *this;
}

//
// member functions
//
template<class T_iter, class T_return, class T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>&
TBDerefItr<T_iter, T_return, T_valueType>::operator++()        // prefix
{
   ++m_iterator;
   return *this;
}

template<class T_iter, class T_return, class T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>::operator++(int)     // postfix
{
   TBDerefItr<T_iter, T_return, T_valueType> before( *this );
   ++(*this); // use prefix operator
   return( before );
}


template<class T_iter, class T_return, class T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>&
TBDerefItr<T_iter, T_return, T_valueType>::operator--()        // prefix
{
   --m_iterator;
   return *this;
}


template<class T_iter, class T_return, class T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>::operator--(int)     // postfix
{
   TBDerefItr<T_iter, T_return, T_valueType> before( *this );
   --(*this); // use prefix operator
   return ( before );
}


template<class T_iter, class T_return, class T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>&
TBDerefItr<T_iter, T_return, T_valueType>::operator+=( relative_address n )
{
   for ( relative_address i = 0; i != n; ++i, ++*this ) {}
   return *this;
}


template<class T_iter, class T_return, class T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>&
TBDerefItr<T_iter, T_return, T_valueType>::operator-=( relative_address n )
{
   for ( relative_address i = 0; i != n; ++i, --*this ) {}
   return *this;
}


//
// const member functions
//

template<class T_iter, class T_return, class T_valueType>
T_return&
TBDerefItr<T_iter, T_return, T_valueType>::operator*()
{
   return( **m_iterator );
}


template<class T_iter, class T_return, class T_valueType>
T_return*
TBDerefItr<T_iter, T_return, T_valueType>::operator->()
{
   //This allows it to be used with an iterator holding a smart pointer 
   return( &(**m_iterator) );
}


template<class T_iter, class T_return, class T_valueType>
DABoolean
TBDerefItr<T_iter, T_return, T_valueType>::operator==( const self& anTBDerefItr ) const
{
   return ( m_iterator == anTBDerefItr.m_iterator );
}


template<class T_iter, class T_return, class T_valueType>
DABoolean
TBDerefItr<T_iter, T_return, T_valueType>::operator!=( const self& anItr ) const
{
   return !( *this == anItr.m_iterator ); // use ==
}


template<class T_iter, class T_return, class T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>::operator+( relative_address n ) const
{
   TBDerefItr<T_iter, T_return, T_valueType> tempItr( *this );
   for( relative_address i = 0; i != n; ++i, ++tempItr ) {}
   return tempItr;
}


template<class T_iter, class T_return, class T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>
TBDerefItr<T_iter, T_return, T_valueType>::operator-( relative_address n ) const
{
   TBDerefItr<T_iter, T_return, T_valueType> tempItr( *this );
   for( relative_address i = 0; i != n; ++i, --tempItr ) {}
   return tempItr;
}


//
// static member functions
//
