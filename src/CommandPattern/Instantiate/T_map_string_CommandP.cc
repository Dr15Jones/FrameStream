// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      T_map_string_CommandP.cc
// 
// Description: Instantiate STL classes for Command
//
//
// Author:      Martin Lohner
// Created:     Fri July 11 12:00:00 EDT 1997
// $Id: T_map_string_CommandP.cc,v 1.3 1998/11/13 14:25:27 cdj Exp $
//
// Revision history
//
// $Log: T_map_string_CommandP.cc,v $
// Revision 1.3  1998/11/13 14:25:27  cdj
// forgot #include <string>
//
// Revision 1.2  1998/11/12 23:34:39  mkl
// change include vector to map
//
// Revision 1.1  1998/11/12 22:23:54  mkl
// finish new module loading and unloading
//
//

#include "Experiment/Experiment.h"
// system include files
#include <string>
#include <map>

// user include files

class Command;
typedef string _map_key_;
typedef Command* _map_contents_;
typedef less< _map_key_ > _map_compare_;
#include "STLUtility/instantiate_map.h"
