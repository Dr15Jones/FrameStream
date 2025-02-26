// -*- C++ -*-
//
// Package:     ToolBox
// Module:      Triplet
// 
// Description: 
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Wed Aug 19 13:27:15 EDT 1998
// $Id: Triplet.cc,v 1.4 1999/07/01 15:00:08 bkh Exp $
//
// Revision history
//
// $Log: Triplet.cc,v $
// Revision 1.4  1999/07/01 15:00:08  bkh
// Install operator< so can be a key in sets & maps
//
// Revision 1.3  1998/11/06 17:14:58  bkh
// avoid warning messages by removing unesthetic 'const'
//
// Revision 1.2  1998/08/20 19:52:06  bkh
// Fix for g++
//
// Revision 1.1  1998/08/19 21:10:24  bkh
// new class
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "ToolBox/Triplet.h"

// STL classes

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

template < class T1, class T2, class T3 >
Triplet<T1,T2,T3>::Triplet()
{
}

template < class T1, class T2, class T3 >
Triplet<T1,T2,T3>::Triplet( const T1& aFirst  ,
			    const T2& aSecond ,
			    const T3& aThird  
   ) :
   m_first  ( aFirst  ) ,
   m_second ( aSecond ) ,
   m_third  ( aThird  )
{
}

template < class T1, class T2, class T3 >
Triplet<T1,T2,T3>::Triplet( const Triplet& rhs )
{
   *this = rhs ;
}

//
// assignment operators
//

template < class T1, class T2, class T3 >
const Triplet<T1,T2,T3>& 
Triplet<T1,T2,T3>::operator=( const Triplet& rhs )
{
   if( this != &rhs ) 
   {
      m_first  = rhs.m_first  ;
      m_second = rhs.m_second ;
      m_third  = rhs.m_third  ;
   }
   
   return *this ;
}

//
// member functions
//

//
// const member functions
//

template < class T1, class T2, class T3 >
const T1& 
Triplet<T1,T2,T3>::first()  const 
{
   return m_first  ; 
}

template < class T1, class T2, class T3 >
const T2& 
Triplet<T1,T2,T3>::second() const
{
   return m_second ;
}

template < class T1, class T2, class T3 >
const T3& 
Triplet<T1,T2,T3>::third()  const 
{
   return m_third  ;
}  

template < class T1, class T2, class T3 >
DABoolean 
Triplet<T1,T2,T3>::operator==( const Triplet& aRHS ) const
{
  return ( m_first  == aRHS.m_first  &&
	   m_second == aRHS.m_second &&
	   m_third  == aRHS.m_third       ) ; 
}

template < class T1, class T2, class T3 >
DABoolean 
Triplet<T1,T2,T3>::operator<( const Triplet& aRHS ) const
{
   return ( m_first  <  aRHS.m_first  ||
	    ( m_first  == aRHS.m_first && m_second <  aRHS.m_second ) ||
	    ( m_first  == aRHS.m_first && m_second == aRHS.m_second   &&
	      m_third  <  aRHS.m_third  )  ) ; 
}

//
// static member functions
//
