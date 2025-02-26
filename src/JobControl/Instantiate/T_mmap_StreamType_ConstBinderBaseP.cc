// -*- C++ -*-
//
// Package:     JobControl
// Module:      T_mmap_StreamType_BinderBaseP
// 
// Description: Instantiate STL classes for SourceManager
//
//
// Author:      Martin Lohner
// Created:     Mon April 20 12:20:00 EDT 1999
// $Id: T_mmap_StreamType_ConstBinderBaseP.cc,v 1.1 1999/04/30 18:15:23 mkl Exp $
//
// Revision history
//
// $Log: T_mmap_StreamType_ConstBinderBaseP.cc,v $
// Revision 1.1  1999/04/30 18:15:23  mkl
// first version of source act command handling
//
// Revision 1.1  1999/04/24 16:22:49  mkl
// keep track of DataSourceDescriptors, not just names of files
//
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

class BinderBase;

typedef Stream::Type _multimap_key_ ;
typedef const BinderBase* _multimap_contents_ ;
typedef less<_multimap_key_> _multimap_compare_ ;

#include "STLUtility/instantiate_multimap.h"

