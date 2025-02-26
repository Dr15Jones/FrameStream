#if !defined(DATADELIVERY_INSTANTIATENOTCHAINABLEBINDER_H)
#define DATADELIVERY_INSTANTIATENOTCHAINABLEBINDER_H
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
// $Id: instantiateNotChainableBinder.h,v 1.1 1998/06/17 20:17:55 mkl Exp $
//
// Revision history
//
// $Log: instantiateNotChainableBinder.h,v $
// Revision 1.1  1998/06/17 20:17:55  mkl
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

#else

template class Binder< _binder_ >;

#endif /* defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) */

#endif /* FRAMEACCESS_INSTANTIATENOTCHAINABLEBINDER_H */
