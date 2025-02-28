// -*- C++ -*-
//
// Package:     Scaffold
// Module:      CombinatoricList
// 
// Description: Instantiate the vector< const DataSourceDescriptor >
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Wed Sep 11 21:45:29 EDT 1996
// $Id: STL_DataSourceDescriptor.cc,v 1.6 1998/02/03 21:28:14 mkl Exp $
//
// Revision history
//
// $Log: STL_DataSourceDescriptor.cc,v $
// Revision 1.6  1998/02/03 21:28:14  mkl
// switch over to STLUtility library
//
// Revision 1.5  1997/08/27 03:39:35  sjp
// Updated to new name for bug flags
//
// Revision 1.4  1997/08/06 16:03:34  sjp
// Converted to use instantiation include files
//
// Revision 1.3  1997/07/28 17:22:39  sjp
// Fixed to work under cxx 5.6
//
// Revision 1.2  1997/07/09 18:01:11  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1  1997/07/02 19:26:18  sjp
// New file to instanitate STL for class
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataDelivery/DataSourceDescriptor.h"

typedef DataSourceDescriptor _vector_contents_ ;

#include "STLUtility/instantiate_vector.h"

//

#include "DataDelivery/FrameDeliverer.h"

#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#include <multimap.h>
#else
#include <map>
#endif

typedef FrameDeliverer::SourceStatus _multimap_key_ ;
typedef DataSourceDescriptor _multimap_contents_ ;
typedef less< _multimap_key_ > _multimap_compare_ ;

#include "STLUtility/instantiate_multimap.h"
