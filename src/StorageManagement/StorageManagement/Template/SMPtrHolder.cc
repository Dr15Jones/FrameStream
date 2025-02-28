// -*- C++ -*-
//
// Package:     <package>
// Module:      SMPtrHolder
// 
// Implementation:
//     <Notes on implementation>
//
// Author:      Konstantin Bukin
// Created:     Mon Oct 23 19:00:11 EDT 2000
// $Id: SMPtrHolder.cc,v 1.2 2000/11/03 21:39:28 cdj Exp $
//
// Revision history
//
// $Log: SMPtrHolder.cc,v $
// Revision 1.2  2000/11/03 21:39:28  cdj
// simplified design of SMPtrHolder
//
// Revision 1.1  2000/11/01 02:21:09  kbukin
// added T_vector_UInt8_helper.cc and added SMPtrHolder with it's storage helper
//

#define DO_EQUAL_INSTANTIATION

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
//#include <map>
#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "StorageManagement/SMPtrHolder.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
//static const char* const kFacilityString = "package.SMPtrHolder" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
//static const char* const kIdString  = "$Id: SMPtrHolder.cc,v 1.2 2000/11/03 21:39:28 cdj Exp $";
//static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
/*
template<class T_Ptr, class T_valueType>
SMPtrHolder<T_Ptr, T_valueType>::SMPtrHolder(const T_Ptr ptr)
{
     if (ptr){
          m_val.push_back(ptr);
     }
}

template<class T_Ptr, class T_valueType>
SMPtrHolder<T_Ptr, T_valueType>::SMPtrHolder()
{
}

template<class T_Ptr, class T_valueType>
SMPtrHolder<T_Ptr, T_valueType>::SMPtrHolder(const SMPtrHolder<T_Ptr, T_valueType>& h)
{

     back_insert_iterator<STL_VECTOR(T_Ptr)>  inserter(m_val);
     copy(h.m_val.begin(), h.m_val.end(), inserter);
}

template<class T_Ptr, class T_valueType>
SMPtrHolder<T_Ptr, T_valueType>::~SMPtrHolder()
{
}
*/

//
// assignment operators
//
/*
template<class T_Ptr, class T_valueType>
const SMPtrHolder<T_Ptr, T_valueType>&
SMPtrHolder<T_Ptr, T_valueType>::operator=( const SMPtrHolder<T_Ptr, T_valueType>& rhs )
{
     if( this != &rhs ) {
          m_val=rhs.m_val;
     }
     return *this;
}
*/
//
// member functions
//

//
// const member functions
//
/*
template<class T_Ptr, class T_valueType>
DABoolean SMPtrHolder<T_Ptr, T_valueType>::operator==(const SMPtrHolder<T_Ptr, T_valueType>& h) const
{
     return (m_val == h.m_val);
}

template<class T_Ptr, class T_valueType>
DABoolean SMPtrHolder<T_Ptr, T_valueType>::operator!=(const SMPtrHolder<T_Ptr, T_valueType>& h) const
{
     return !((*this) == h);
}

template<class T_Ptr, class T_valueType>
SMPtrHolder<T_Ptr, T_valueType>::const_iterator
SMPtrHolder<T_Ptr, T_valueType>::begin() const
{
     SMPtrHolder<T_Ptr, T_valueType>::const_iterator temp(m_val.begin());
     return temp;
}

template<class T_Ptr, class T_valueType>
SMPtrHolder<T_Ptr, T_valueType>::const_iterator
SMPtrHolder<T_Ptr, T_valueType>::end() const
{
     SMPtrHolder<T_Ptr, T_valueType>::const_iterator temp(m_val.end());
     return temp;
}
*/

//
// static member functions
//





