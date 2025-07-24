// -*- C++ -*-
//
// Package:     Carin
// Module:      ChargedVisibleList
// 
// Description: Instantiate the ChargedVisibleList for 'ChargedKaon'
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Wed Sep 11 21:45:29 EDT 1996
// $Id: STL_Loggers.cc,v 1.11 2002/12/05 21:33:46 cleo3 Exp $
//
// Revision history
//
// $Log: STL_Loggers.cc,v $
// Revision 1.11  2002/12/05 21:33:46  cleo3
// removed old g++ CPP statements
//
// Revision 1.10  1998/10/01 19:21:31  mkl
// special extra instantiation of rb_tree required for egcs compiler
//
// Revision 1.9  1998/09/23 19:13:08  mkl
// typename; protect against multiple inclusion. All to make egcs happy
//
// Revision 1.8  1998/02/03 21:30:39  mkl
// switch over to STLUtility library
//
// Revision 1.7  1997/08/27 03:39:01  sjp
// Updated to new name for bug flags
//
// Revision 1.6  1997/08/06 14:42:53  sjp
// fixed a few typos
//
// Revision 1.5  1997/08/06 14:23:11  sjp
// Converted to use instantiation include files
//
// Revision 1.4  1997/07/30 05:49:04  sjp
// Fixed to work under cxx 5.6
//
// Revision 1.3  1997/07/10 20:59:46  sjp
// Revived code to make g++ work
//
// Revision 1.2  1997/07/07 16:15:05  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1  1997/01/31 18:53:17  sjp
// Real class to handle messaging
//
// Revision 1.2  1997/01/21 20:32:10  sjp
// Changed CPP flags and include because of library reorganization
//
// Revision 1.1  1996/11/04 17:17:40  sjp
// New file for new `List' module
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "ToolBox/MessageLog.h"

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

typedef std::string _multimap_key_ ;
typedef MessageLog::Logger* _multimap_contents_ ;
typedef less< _multimap_key_ > _multimap_compare_ ;

//#include "STLUtility/instantiate_multimap.h"
