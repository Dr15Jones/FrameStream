// -*- C++ -*-
//
// Package:     DataStorage
// Module:      STL_DataSinkController
// 
// Description: Instantiate the vector< const DataSinkController* >
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Fri July 11 12:31:00 EDT 1997
// $Id: STL_DataSinkController.cc,v 1.9 2002/12/09 16:03:02 cleo3 Exp $
//
// Revision history
//
// $Log: STL_DataSinkController.cc,v $
// Revision 1.9  2002/12/09 16:03:02  cleo3
// work around g++ instantiation bug
//
// Revision 1.8  1998/11/06 20:24:47  cdj
// use STD_PREFIX (needed by cxx v6.1)
//
// Revision 1.7  1998/06/24 17:38:15  cdj
// added return type to template function instantiation (needed by cxx 6.0)
//
// Revision 1.6  1998/02/03 21:28:49  mkl
// switch over to STLUtility library
//
// Revision 1.5  1997/09/04 15:16:26  mkl
// moved to new bug flags
//
// Revision 1.4  1997/08/19 02:53:01  mkl
// changes for cxx5.6
//
// Revision 1.3  1997/08/13 02:58:16  mkl
// switched over to simpler STLUtility/instantiate_*.h files
//
// Revision 1.2  1997/07/11 20:39:06  mkl
// STL instantiation files added
//
// Revision 1.1  1997/07/11 16:53:24  mkl
// added STL instantiation files
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */
#include <vector>

// forward declarations

class DataSinkController ;

typedef DataSinkController* _vector_contents_;

#include "STLUtility/instantiate_vector.h"

// ------------------------------------------------
// user include files
#include "DataStorage/DataSinkDescriptor.h"
#include "DataStorage/FrameStorer.h"

#include <map>

typedef DataSinkController* _map_key_;
typedef FrameStorer::SinkStatus _map_contents_;
typedef less< _map_key_ > _map_compare_;

// ------------------------------------------------
// user include files
#include "DataHandler/StreamPriorityGreater.h"

#if defined(MULTIMAP_IS_SEPARATE_BUG)
#include <multimap.h>
#endif

typedef Stream::Type _multimap_key_;
typedef DataSinkController* _multimap_contents_;
typedef less< _multimap_key_ > _multimap_compare_;


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
template vector<DataSinkController*>::iterator 
STD_PREFIX find( vector< DataSinkController* >::iterator, 
      vector< DataSinkController* >::iterator,  
      DataSinkController* const&) ;
template vector<DataSinkController* >::iterator
STD_PREFIX find( vector< DataSinkController* >::iterator, 
      vector< DataSinkController* >::iterator, 
      const  DataSinkController*  const&) ;
#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
}
#endif




