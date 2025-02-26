// -*- C++ -*-
//
// Package:     Processor
// Module:      STL_MMStringString
// 
// Description: Instantiate map< string, string >
//
//
// Author:      Martin Lohner
// Created:     Fri Jul 11 12:20:00 EDT 1997
// $Id: T_multimap_string_string.cc,v 1.1.1.1 2000/11/30 20:51:31 cdj Exp $
//
// Revision history
//
// $Log: T_multimap_string_string.cc,v $
// Revision 1.1.1.1  2000/11/30 20:51:31  cdj
// imported DynamicLoader source
//
// Revision 1.4  1998/09/24 14:27:42  mkl
// had to add back in intantiation file for map< string, StringWrapper >
//
// Revision 1.3  1998/09/23 19:56:04  mkl
// undid mistakenly submitted C3String test changes
//
// Revision 1.2  1998/06/18 13:33:24  mkl
// fixed include
//
// Revision 1.1  1998/06/17 18:17:26  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.5  1998/04/01 17:57:53  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.4  1998/02/03 21:29:53  mkl
// switch over to STLUtility library
//
// Revision 1.3  1997/11/24 18:35:08  mkl
// new StringWrapper class to get around g++ proboem with map<string, string>
//
// Revision 1.2  1997/10/20 17:14:25  mkl
// attempt to fix g++ problems with map(string, string) --> not working yet, but better
//
// Revision 1.1  1997/10/05 16:15:54  mkl
// Instantiation file for map<string, string>
//
// Revision 1.1  1997/09/04 06:34:57  mkl
// moved JobControl/STL_SharedObject here
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#if defined(OLD_CXX_STRING_CLASS_BUG)
#include "C++Std/fwd_string.h"
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */
#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#  include <map>
#  include <multimap.h>
#else
#  include <map>
#endif                    
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

#if defined(OLD_CXX_STRING_CLASS_BUG)
#include "C++Std/fwd_string.h"
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */
#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#  include <map>
#  include <multimap.h>
#else
#  include <map>
#endif                    

typedef string _multimap_key_ ;
typedef string _multimap_contents_ ;
typedef less< _multimap_key_ > _multimap_compare_ ;

#include "STLUtility/instantiate_multimap.h"

