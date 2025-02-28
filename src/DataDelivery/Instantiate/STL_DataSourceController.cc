// -*- C++ -*-
//
// Package:     Scaffold
// Module:      CombinatoricList
// 
// Description: Instantiate the vector< const DataSourceController* >
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Wed Sep 11 21:45:29 EDT 1996
// $Id: STL_DataSourceController.cc,v 1.12 2002/12/09 16:05:23 cleo3 Exp $
//
// Revision history
//
// $Log: STL_DataSourceController.cc,v $
// Revision 1.12  2002/12/09 16:05:23  cleo3
// work around g++ instantiation bug
//
// Revision 1.11  1998/11/06 20:12:13  cdj
// Uses STD_PREFIX (needed for cxx v6.1)
//
// Revision 1.10  1998/07/23 16:38:09  cdj
// modified to instantiate find() under cxx 6.0
//
// Revision 1.9  1998/07/18 20:03:11  mkl
// also handle solaris correctly
//
// Revision 1.8  1998/06/24 19:52:42  cdj
// added return type to instantiation of templated function
//
// Revision 1.7  1998/02/03 21:28:14  mkl
// switch over to STLUtility library
//
// Revision 1.6  1997/08/27 03:39:34  sjp
// Updated to new name for bug flags
//
// Revision 1.5  1997/08/06 16:03:31  sjp
// Converted to use instantiation include files
//
// Revision 1.4  1997/07/28 17:22:37  sjp
// Fixed to work under cxx 5.6
//
// Revision 1.3  1997/07/09 19:01:44  sjp
// Moved string into DataFieldLabel header
//
// Revision 1.2  1997/07/09 18:01:09  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1  1997/07/02 19:26:16  sjp
// New file to instanitate STL for class
//
// Revision 1.1  1997/07/01 20:00:29  sjp
// New file to instantiate STL classes
//

#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// forward declarations
class DataSourceController ;

typedef DataSourceController* _vector_contents_ ;

#include "STLUtility/instantiate_vector.h"

//

// user include files
#include "DataDelivery/FrameDeliverer.h"

// STL include files
#include <map>

typedef DataSourceController* _map_key_ ;
typedef FrameDeliverer::SourceStatus _map_contents_ ;
typedef less< _map_key_ > _map_compare_ ;

#include "STLUtility/instantiate_map.h"

//

// user include files
#include "DataHandler/StreamPriorityGreater.h"

// STL include files
#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#include <multimap.h>
#endif

typedef Stream::Type _multimap_key_ ;
typedef DataSourceController* _multimap_contents_ ;
typedef StreamPriorityGreater _multimap_compare_ ;

#include "STLUtility/instantiate_multimap.h"

//

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
template vector< DataSourceController* >::iterator 
STD_PREFIX find(vector< DataSourceController* >::iterator, 
     vector< DataSourceController* >::iterator,  
     DataSourceController*  const&) ;
template vector< DataSourceController* >::iterator 
STD_PREFIX find(vector< DataSourceController* >::iterator, 
     vector< DataSourceController* >::iterator, 
     const  DataSourceController*  const&) ;
#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
}
#endif
