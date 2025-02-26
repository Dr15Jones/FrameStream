// -*- C++ -*-
//
// Package:     JobControl
// Module:      STL_SourceManager
// 
// Description: Instantiate STL classes for SourceManager
//
//
// Author:      Martin Lohner
// Created:     Thu Jul 24 12:20:00 EDT 1997
// $Id: T_mmap_StreamType_DataSourceDescriptorP.cc,v 1.1 1999/04/24 16:22:51 mkl Exp $
//
// Revision history
//
// $Log: T_mmap_StreamType_DataSourceDescriptorP.cc,v $
// Revision 1.1  1999/04/24 16:22:51  mkl
// keep track of DataSourceDescriptors, not just names of files
//
// Revision 1.5  1998/02/03 21:29:38  mkl
// switch over to STLUtility library
//
// Revision 1.4  1997/08/29 04:22:10  mkl
// simplify JobControl: remove FileInput/Output files, bug flag changes, handling of suffix .gz etc.
//
// Revision 1.3  1997/08/13 21:03:03  mkl
// changes to make it work with cxx
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataHandler/Stream.h"

// STL include files
#if defined(OLD_CXX_STRING_CLASS_BUG)
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */
#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#  include <multimap.h>
#else
#  include <map>
#endif
#include <map>

class DataSourceDescriptor;

typedef Stream::Type _multimap_key_ ;
typedef const DataSourceDescriptor* _multimap_contents_ ;
typedef less<_multimap_key_> _multimap_compare_ ;

#include "STLUtility/instantiate_multimap.h"

