// -*- C++ -*-
//
// Package:     <package>
// Module:      T_map_string_KeywordBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Sep  5 11:03:04 EDT 2003
// $Id: T_map_string_KeywordBase.cc,v 1.1 2003/09/19 20:45:47 cdj Exp $
//
// Revision history
//
// $Log: T_map_string_KeywordBase.cc,v $
// Revision 1.1  2003/09/19 20:45:47  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <map>

namespace CommandPattern
{
   namespace Keyword {
      class Base;
   }
}

typedef string _map_key_;
typedef CommandPattern::Keyword::Base* _map_contents_;
typedef less<_map_key_ > _map_compare_;

#include "STLUtility/instantiate_map.h"
