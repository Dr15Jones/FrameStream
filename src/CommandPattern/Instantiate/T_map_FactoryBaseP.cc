// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      T_map_FactoryBaseP.cc
// 
// Description: Instantiate map< string, FactoryBase* >
//
// Author:      Martin Lohner
// Created:     Tue Nov 9 12:20:00 EDT 1998
// $Id: T_map_FactoryBaseP.cc,v 1.1 1998/11/10 23:22:52 mkl Exp $
//
// Revision history
//
// $Log: T_map_FactoryBaseP.cc,v $
// Revision 1.1  1998/11/10 23:22:52  mkl
// static linking of proc/ducers/source-/sink-formats/modules whatever; and cleanup
//
//


#include "Experiment/Experiment.h"

// system include files
#include <string>
#include <map>

// user include files

class FactoryBase;

typedef string _map_key_;
typedef FactoryBase* _map_contents_;
typedef less< _map_key_ > _map_compare_;

#include "STLUtility/instantiate_map.h"
