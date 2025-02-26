// -*- C++ -*-
//
// Package:     DataHandler
// Module:      STL_ProxyProvider
// 
// Description: Instantiate STL classes for ProxyProvider
//
//
// Author:      Simon Patton
// Created:     Wed Sep 11 21:45:29 EDT 1996
// $Id: STL_ProxyProvider.cc,v 1.5 1998/11/06 20:18:08 cdj Exp $
//
// Revision history
//
// $Log: STL_ProxyProvider.cc,v $
// Revision 1.5  1998/11/06 20:18:08  cdj
// Uses STD_PREFIX (needed for cxx v6.1)
//
// Revision 1.4  1998/06/24 17:15:22  cdj
// added new bug flag needed by cxx 6.0
//
// Revision 1.3  1998/02/03 21:28:37  mkl
// switch over to STLUtility library
//
// Revision 1.2  1997/08/27 03:39:12  sjp
// Updated to new name for bug flags
//
// Revision 1.1  1997/08/06 15:39:44  sjp
// New instnatiation file
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// forward declarations
class ProxyProvider ;

typedef ProxyProvider* _vector_contents_ ;

#include "STLUtility/instantiate_vector.h"

#include <algorithm>

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP
//
// required for find
#  pragma define_template find< vector<ProxyProvider*>::iterator , ProxyProvider* const >
#  pragma define_template find< vector<ProxyProvider*>::iterator , const ProxyProvider* const >
#else

#if !defined(STD_PREFIX)
#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif
#endif

template vector<ProxyProvider*>::iterator 
STD_PREFIX find(vector<ProxyProvider*>::iterator, 
     vector<ProxyProvider*>::iterator, 
     ProxyProvider* const&) ;
template vector<ProxyProvider*>::iterator 
STD_PREFIX find(vector<ProxyProvider*>::iterator, 
     vector<ProxyProvider*>::iterator, 
     const ProxyProvider* const&) ;
#endif /* (defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX)) */
