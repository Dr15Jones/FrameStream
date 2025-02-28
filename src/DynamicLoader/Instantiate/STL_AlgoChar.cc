// -*- C++ -*-
//
// Package:     JobControl
// Module:      STL_AlgoChar
// 
// Description: Instantiate algorithms dealing with vector< char >
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Sat Jul 13 21:45:29 EDT 1997
// $Id: STL_AlgoChar.cc,v 1.3 2002/12/12 14:32:38 cdj Exp $
//
// Revision history
//
// $Log: STL_AlgoChar.cc,v $
// Revision 1.3  2002/12/12 14:32:38  cdj
// moved instantiation of count to own file to avoid multiple symbols on OSF
//
// Revision 1.2  2002/12/09 15:41:20  cleo3
// work around g++ instantiation bug
//
// Revision 1.3  1998/11/06 19:47:35  cdj
// Use STD_PREFIX (needed by cxx 6.1)
//
// Revision 1.2  1998/06/23 19:38:21  cdj
// added bug flag needed for cxx 6.0
//
// Revision 1.1  1998/06/17 18:17:25  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.2  1997/08/29 04:22:00  mkl
// simplify JobControl: remove FileInput/Output files, bug flag changes, handling of suffix .gz etc.
//
// Revision 1.1  1997/08/13 07:10:53  mkl
// Chains of Sources, new activation of streams, and ProxyDict
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

#include <vector>
#include <algorithm>

// forward declarations

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif
// for g++ or MetroWerks
#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
#if defined(STD_PREFIX)
#undef STD_PREFIX
#define STD_PREFIX
#endif
namespace std {
#endif
template vector< char >::iterator STD_PREFIX find( vector< char>::iterator, 
					vector< char>::iterator, 
					const char& );


template class pair<const char *,const char *>;

template pair<const char*, const char* > STD_PREFIX mismatch ( const char*, 
							       const char*, 
							       const char* );

#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
}
#endif
