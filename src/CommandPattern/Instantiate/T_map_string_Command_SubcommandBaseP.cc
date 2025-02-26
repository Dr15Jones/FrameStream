// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      T_map_string_Command_SubcommandInfo.cc
// 
// Description: Instantiate map for Command::SubcommandInfo
//
//
// Author:      Martin Lohner
// Created:     Wed Sep 3 12:20:00 EDT 1999
// $Id: T_map_string_Command_SubcommandBaseP.cc,v 1.1 1999/09/06 21:28:59 mkl Exp $
//
// Revision history
//
// $Log: T_map_string_Command_SubcommandBaseP.cc,v $
// Revision 1.1  1999/09/06 21:28:59  mkl
// new subcommand handling
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

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

class SubcommandBase;

typedef string _map_key_ ;
typedef SubcommandBase* _map_contents_ ;
typedef less<_map_key_> _map_compare_ ;

#include "STLUtility/instantiate_map.h"
