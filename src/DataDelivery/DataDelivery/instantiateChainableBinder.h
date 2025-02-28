#if !defined(DATADELIVERY_INSTANTIATECHAINABLEBINDER_H)
#define DATADELIVERY_INSTANTIATECHAINABLEBINDER_H
// -*- C++ -*-
//
// Package:     DataDelivery
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate a Binder of some format
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Wed June 16 14:32:44 EDT 1998
// $Id: instantiateChainableBinder.h,v 1.2 1998/06/18 16:02:19 mkl Exp $
//
// Revision history
//
// $Log: instantiateChainableBinder.h,v $
// Revision 1.2  1998/06/18 16:02:19  mkl
// fix problem with g++ internal compiler error
//
// Revision 1.1  1998/06/17 20:17:54  mkl
// added instantiation files for Not/Chainable Binders
//
//

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "JobControl/Template/Binder.cc"

// stl includes
#include <string>
#include <map>


#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP

#pragma define_template Binder< _binder_ >

#pragma define_template makeChain< _binder_ >
#pragma define_template addSourceToChain< _binder_ >

#else

template class Binder< _binder_ >;

//template DataSourceBinder* makeChain< _binder_ >( 
template DataSourceBinder* makeChain( 
   Chainable< _binder_ >,
   const string&,
   const Stream::Set& );

//template void addSourceToChain< _binder_ >( 
template void addSourceToChain( 
   Chainable< _binder_ >,
   DataSourceBinder&,
   DataSourceBinder& );

#endif /* defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) */

#endif /* FRAMEACCESS_INSTANTIATECHAINABLEBINDER_H */
