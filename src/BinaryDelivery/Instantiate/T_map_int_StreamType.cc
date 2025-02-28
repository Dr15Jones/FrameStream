// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      T_map_StreamType_BDRecordBufferP
// 
// Description:
//
//
// Author:      Martin Lohner
// Created:     Wed Nov 4 12:00:00 EDT 1998
// $Id: T_map_int_StreamType.cc,v 1.1 1998/11/04 16:10:02 mkl Exp $
//
// Revision history
//
// $Log: T_map_int_StreamType.cc,v $
// Revision 1.1  1998/11/04 16:10:02  mkl
// added template instantiations
//
//

#include "Experiment/Experiment.h"
// system include files
#include <string>
#include <map>

// user include files
#include "DataHandler/Stream.h"

typedef int _map_key_;
typedef Stream::Type _map_contents_;
typedef less< int > _map_compare_;

#include "STLUtility/instantiate_map.h"
