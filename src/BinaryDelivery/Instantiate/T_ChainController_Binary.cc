// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      T_ChainController_Binary
// 
// Description: Instantiate ChainSourceController<BinarySourceController>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Mon Nov 16 14:32:27 EST 1998
// $Id: T_ChainController_Binary.cc,v 1.1 1998/11/16 16:51:42 mkl Exp $
//
// Revision history
//
// $Log: T_ChainController_Binary.cc,v $
// Revision 1.1  1998/11/16 16:51:42  mkl
// additions necessary to load BinarySourceFormat and chain binary files
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>  // For 'exit'
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <deque>
#include <vector>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

#include "BinaryDelivery/BinarySourceController.h"
#include "BinaryDelivery/BinarySourceBinder.h"
#include "BinaryDelivery/BinaryProxyDeliverer.h"

#include "ChainDelivery/ChainSourceController.h"
#include "ChainDelivery/Template/ChainSourceController.cc"

#include <deque>
#include <vector>
#include <set>

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP
#  pragma define_template ChainSourceController< BinarySourceBinder >
#else
template class ChainSourceController< BinarySourceBinder > ;
#endif /* (defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX)) */



