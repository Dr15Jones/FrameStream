// -*- C++ -*-
//
// Package:     JobControl
// Module:      STL_SinkFormat
// 
// Description: Instantiate STL classes for SinkFormat*
//
//
// Author:      Martin Lohner
// Created:     Fri June 12 17:20:00 EDT 1998
// $Id: STL_SinkFormat.cc,v 1.4 2003/02/20 18:45:01 cdj Exp $
//
// Revision history
//
// $Log: STL_SinkFormat.cc,v $
// Revision 1.4  2003/02/20 18:45:01  cdj
// fixed improper casting of Source(Sink)Format to Source(Sink)FormatModule
//
// Revision 1.3  1998/12/02 05:55:12  mkl
// towards interacting with Source- and SinkFormats
//
// Revision 1.2  1998/06/17 22:53:37  mkl
// fix up changes for g++
//
// Revision 1.1  1998/06/17 18:18:14  mkl
// allow dynamic loading of source and sink formats
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

// stl files
#include <string>
#include <map>

class SinkFormat;

typedef string _map_key_ ;
typedef SinkFormat* _map_contents_ ;
typedef less< _map_key_ > _map_compare_;

#include "STLUtility/instantiate_map.h"
