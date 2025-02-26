// -*- C++ -*-
//
// Package:     DataDelivery
// Module:      
// 
// Description: 
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Wed Sep 11 21:45:29 EDT 1996
// $Id: STL_FindNextRecordInfo.cc,v 1.6 1998/02/03 21:28:15 mkl Exp $
//
// Revision history
//
// $Log: STL_FindNextRecordInfo.cc,v $
// Revision 1.6  1998/02/03 21:28:15  mkl
// switch over to STLUtility library
//
// Revision 1.5  1997/08/27 03:39:36  sjp
// Updated to new name for bug flags
//
// Revision 1.4  1997/08/06 16:03:36  sjp
// Converted to use instantiation include files
//
// Revision 1.3  1997/07/28 17:22:41  sjp
// Fixed to work under cxx 5.6
//
// Revision 1.2  1997/07/09 18:01:13  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1  1997/07/02 19:26:19  sjp
// New file to instanitate STL for class
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataHandler/SyncValue.h"
#include "DataDelivery/FindNextRecordInfo.h"
#include "DataDelivery/SortFindNextRecordInfo.h"

#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif

typedef FindNextRecordInfo _multiset_contents_ ;
typedef SortFindNextRecordInfo _multiset_compare_ ;

#include "STLUtility/instantiate_multiset.h"

//

#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#include <multimap.h>
#else
#include <map>
#endif

typedef SyncValue _multimap_key_ ;
typedef FindNextRecordInfo _multimap_contents_ ;
typedef less< _multimap_key_ > _multimap_compare_ ;

#include "STLUtility/instantiate_multimap.h"
