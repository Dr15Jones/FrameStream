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

// user include files
#include "DataDelivery/Template/Binder.cc"

// stl includes
#include <string>
#include <map>



template<> class Binder< _binder_ >;

template<> DataSourceBinder* makeChain( 
   Chainable< _binder_ >,
   const std::string&,
   const Stream::Set& );

template<> void addSourceToChain( 
   Chainable< _binder_ >,
   DataSourceBinder&,
   DataSourceBinder& );


#endif /* FRAMEACCESS_INSTANTIATECHAINABLEBINDER_H */
