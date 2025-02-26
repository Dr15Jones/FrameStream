// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      T_map_string_ModuleP.cc
// 
// Description:
//
//
// Author:      Martin Lohner
// Created:     Sun Nov 1 12:00:00 EDT 1998
// $Id: T_map_string_ModuleP.cc,v 1.2 1998/11/12 23:34:40 mkl Exp $
//
// Revision history
//
// $Log: T_map_string_ModuleP.cc,v $
// Revision 1.2  1998/11/12 23:34:40  mkl
// change include vector to map
//
// Revision 1.1  1998/11/09 19:32:11  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
//

#include "Experiment/Experiment.h"
// system include files
#include <string>
#include <map>

// user include files

class Module;
typedef string _map_key_;
typedef Module* _map_contents_;
typedef less< _map_key_ > _map_compare_;

#include "STLUtility/instantiate_map.h"
