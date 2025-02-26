// -*- C++ -*-
//
// Package:     DataHandler
// Module:      STL_RecordDeliverer
// 
// Description: Instantiate STL classes for RecordDeliverer*
//
//
// Author:      Simon Patton
// Created:     Wed Sep 11 21:45:29 EDT 1996
// $Id: STL_RecordDeliverer.cc,v 1.6 1998/02/03 21:28:16 mkl Exp $
//
// Revision history
//
// $Log: STL_RecordDeliverer.cc,v $
// Revision 1.6  1998/02/03 21:28:16  mkl
// switch over to STLUtility library
//
// Revision 1.5  1997/08/27 03:39:38  sjp
// Updated to new name for bug flags
//
// Revision 1.4  1997/08/06 16:03:37  sjp
// Converted to use instantiation include files
//
// Revision 1.3  1997/07/28 17:22:43  sjp
// Fixed to work under cxx 5.6
//
// Revision 1.2  1997/07/09 18:01:14  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1  1997/07/02 19:26:22  sjp
// New file to instanitate STL for class
//
// Revision 1.1  1997/03/29 16:34:54  sjp
// New field to instantiated templated class
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataHandler/Stream.h"

// STL include files
#include <map>

// forward declarations
class RecordDeliverer ;

typedef Stream::Type _map_key_ ;
typedef RecordDeliverer* _map_contents_ ;
typedef less< _map_key_ > _map_compare_ ;

#include "STLUtility/instantiate_map.h"
