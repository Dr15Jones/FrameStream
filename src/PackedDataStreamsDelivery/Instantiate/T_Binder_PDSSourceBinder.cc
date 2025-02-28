// -*- C++ -*-
//
// Package:     PDSDelivery
// Module:      T_Binder_PDSSourceBinder.cc
// 
// Description: Instantiate Binder
//
//
// Author:      Martin Lohner
// Created:     Mon Nov 16 12:20:00 EDT 1998
// $Id: T_Binder_PDSSourceBinder.cc,v 1.2 2001/05/31 19:44:36 cdj Exp $
//
// Revision history
//
// $Log: T_Binder_PDSSourceBinder.cc,v $
// Revision 1.2  2001/05/31 19:44:36  cdj
// changes needed for chaining now work on OSF
//
// Revision 1.1.1.1  2000/09/29 17:48:06  cdj
// imported
//
// Revision 1.1  1998/11/16 16:51:35  mkl
// additions necessary to load PDSSourceFormat and chain binary files
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "PackedDataStreamsDelivery/PDSSourceBinder.h"

// stl includes
#include <string>
#include <map>

typedef PDSSourceBinder _binder_;
#include "DataDelivery/instantiateChainableBinder.h"

