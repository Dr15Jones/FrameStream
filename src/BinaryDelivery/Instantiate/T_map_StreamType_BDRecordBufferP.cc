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
// $Id: T_map_StreamType_BDRecordBufferP.cc,v 1.1 1998/11/04 16:09:52 mkl Exp $
//
// Revision history
//
// $Log: T_map_StreamType_BDRecordBufferP.cc,v $
// Revision 1.1  1998/11/04 16:09:52  mkl
// added template instantiations
//
//

#include "Experiment/Experiment.h"
// system include files
#include <string>
#include <map>

// user include files
#include "DataHandler/Stream.h"
class BDRecordBuffer;

typedef Stream::Type _map_key_;
typedef BDRecordBuffer* _map_contents_;
typedef less< Stream::Type > _map_compare_;

#include "STLUtility/instantiate_map.h"
