// -*- C++ -*-
//
// Package:     JobControl
// Module:      T_map_string_ReportModule_LogAndStreamStruct.cc
// 
// Description: Instantiate map for ReportModule::LogAndStreamStruct
//
//
// Author:      Martin Lohner
// Created:     Wed Sep 25 12:20:00 EDT 1999
// $Id: T_map_string_ReportModule_LogAndStreamStruct.cc,v 1.2 1999/09/06 22:20:12 mkl Exp $
//
// Revision history
//
// $Log: T_map_string_ReportModule_LogAndStreamStruct.cc,v $
// Revision 1.2  1999/09/06 22:20:12  mkl
// move to new histogramming interface
//
// Revision 1.1  1999/08/26 01:49:57  mkl
// make cxx happy (with respect to recent ReportModule submission)
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "JobControl/ReportModule.h"

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

typedef string _map_key_ ;
typedef ReportModule::LogAndStreamStruct _map_contents_ ;
typedef less<_map_key_> _map_compare_ ;

#include "STLUtility/instantiate_map.h"
