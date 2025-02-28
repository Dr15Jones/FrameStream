// -*- C++ -*-
//
// Package:     DataStorage
// Module:      STL_ProxyStorer
// 
// Description: Instantiate STL classes for ProxyStorer*
//
//
// Author:      Martin Lohner
// Created:     Fri Jul 11 12:45:29 EDT 1997
// $Id: STL_ProxyStorer.cc,v 1.7 2002/12/09 16:03:02 cleo3 Exp $
//
// Revision history
//
// $Log: STL_ProxyStorer.cc,v $
// Revision 1.7  2002/12/09 16:03:02  cleo3
// work around g++ instantiation bug
//
// Revision 1.6  1998/11/06 20:24:49  cdj
// use STD_PREFIX (needed by cxx v6.1)
//
// Revision 1.5  1998/06/24 17:38:16  cdj
// added return type to template function instantiation (needed by cxx 6.0)
//
// Revision 1.4  1998/02/03 21:28:50  mkl
// switch over to STLUtility library
//
// Revision 1.3  1997/09/04 15:16:28  mkl
// moved to new bug flags
//
// Revision 1.2  1997/08/19 02:53:02  mkl
// changes for cxx5.6
//
// Revision 1.1  1997/08/16 17:47:21  cdj
// Changed name of class to use Proxy instead of DataField
//
// Revision 1.2  1997/08/13 02:58:15  mkl
// switched over to simpler STLUtility/instantiate_*.h files
//
// Revision 1.1  1997/07/11 20:39:05  mkl
// STL instantiation files added
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataHandler/Stream.h"

#include <vector>

class ProxyStorer ;

typedef ProxyStorer* _vector_contents_;

#include "STLUtility/instantiate_vector.h"


//------------------------------------
#include <algorithm>

// for g++ or MetroWerks
#if !defined(STD_PREFIX)
#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif
#endif

#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
#if defined(STD_PREFIX)
#undef STD_PREFIX
#define STD_PREFIX
#endif
namespace std {
#endif
template vector< ProxyStorer*>::iterator 
STD_PREFIX find(vector< ProxyStorer* >::iterator, 
     vector< ProxyStorer* >::iterator,  
     ProxyStorer*  const&) ;
template vector< ProxyStorer* >::iterator 
STD_PREFIX find(vector< ProxyStorer* >::iterator, 
     vector< ProxyStorer* >::iterator, 
     const  ProxyStorer*  const&) ;
#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
}
#endif



