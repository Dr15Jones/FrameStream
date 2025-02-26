// -*- C++ -*-
//
// Package:     Processor
// Module:      STL_MMStringWrapperString
// 
// Description: Instantiate map< string, StringWrapper >
//
//
// Author:      Martin Lohner
// Created:     Fri Sep 25 12:20:00 EDT 1998
// $Id: STL_MMStringWrapperString.cc,v 1.1 1998/09/24 14:27:43 mkl Exp $
//
// Revision history
//
// $Log: STL_MMStringWrapperString.cc,v $
// Revision 1.1  1998/09/24 14:27:43  mkl
// had to add back in intantiation file for map< string, StringWrapper >
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#  include <map>
#  include <multimap.h>
#else
#  include <map>
#endif                    
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#if defined(OLD_CXX_STRING_CLASS_BUG)
#include "C++Std/fwd_string.h"
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */

// user include files
#include "Utility/StringWrapper.h"

#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#  include <map>
#  include <multimap.h>
#else
#  include <map>
#endif                    


typedef string _multimap_key_ ;
typedef StringWrapper _multimap_contents_ ;
typedef less< _multimap_key_ > _multimap_compare_ ;

#include "STLUtility/instantiate_multimap.h"

