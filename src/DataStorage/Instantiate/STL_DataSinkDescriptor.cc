// -*- C++ -*-
//
// Package:     DataStorage
// Module:      STL_DataSinkDescriptor
// 
// Description: Instantiate the vector< const DataSinkDescriptor >
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Fri Jul 11 12:45:29 EDT 1997
// $Id: STL_DataSinkDescriptor.cc,v 1.4 1998/02/03 21:28:50 mkl Exp $
//
// Revision history
//
// $Log: STL_DataSinkDescriptor.cc,v $
// Revision 1.4  1998/02/03 21:28:50  mkl
// switch over to STLUtility library
//
// Revision 1.3  1997/09/04 15:16:27  mkl
// moved to new bug flags
//
// Revision 1.2  1997/08/13 02:58:18  mkl
// switched over to simpler STLUtility/instantiate_*.h files
//
// Revision 1.1  1997/07/11 16:53:25  mkl
// added STL instantiation files
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataStorage/DataSinkDescriptor.h"

#include <vector>

// forward declarations

typedef DataSinkDescriptor _vector_contents_;

#include "STLUtility/instantiate_vector.h"

#include "DataStorage/FrameStorer.h"

#if defined(MULTIMAP_IS_SEPARATE_BUG)
#include <multimap.h>
#else
#include <map>
#endif

typedef FrameStorer::SinkStatus _multimap_key_;
typedef DataSinkDescriptor _multimap_contents_;
typedef less< _multimap_key_ > _multimap_compare_;

#include "STLUtility/instantiate_multimap.h"
