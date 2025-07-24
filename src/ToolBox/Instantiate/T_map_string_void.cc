// -*- C++ -*-
//
// Package:     <ToolBox>
// Module:      T_map_UInt8_void
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sat Apr  8 13:02:14 EDT 2000
// $Id: T_map_string_void.cc,v 1.2 2000/12/27 21:34:23 cdj Exp $
//
// Revision history
//
// $Log: T_map_string_void.cc,v $
// Revision 1.2  2000/12/27 21:34:23  cdj
// added instantiation of advance needed by FATable with string identifiers
//
// Revision 1.1  2000/04/21 17:53:09  cdj
// added instantion of map files needed for new FAPtrTable implementation
//

#include "Experiment/Experiment.h"
#include <string>

//
// instantiate
//

#include <map>

typedef std::string _map_key_ ;
typedef void * _map_contents_ ;
typedef less< _map_key_ > _map_compare_ ;

#include "STLUtility/instantiate_map.h"

#if defined(__DECCXX)

//FATableItr uses advance
template void std:: STLUTILITY_FUNC(advance) (
     STL_MAP_COMP(_map_key_,_map_contents_,_map_compare_) ::const_iterator&
   , long
   , bidirectional_iterator_tag );
#endif
