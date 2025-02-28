// -*- C++ -*-
//
// Package:     PackedDataStreamsDelivery
// Module:      T_ChainBinder_PDS
// 
// Description: Instantiate ChainSourceBinder<PDSSourceBinder>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris Jones
// Created:     Tue Aug 5 14:32:27 EST 1997
// $Id: T_ChainBinder_PDS.cc,v 1.1 2001/05/31 16:57:16 cdj Exp $
//
// Revision history
//
// $Log: T_ChainBinder_PDS.cc,v $
// Revision 1.1  2001/05/31 16:57:16  cdj
// modifications necessary to allow chaining
//
// Revision 1.3  1997/08/27 03:40:53  sjp
// Updated to new name for bug flags
//
// Revision 1.2  1997/08/08 17:12:11  cdj
// Updated to work with PDSProxyDeliverer
//
// Revision 1.1  1997/08/06 18:44:25  mkl
// added ChainController and ChainBinder files
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>  // For 'exit'
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

#include "PackedDataStreamsDelivery/PDSSourceController.h"
#include "PackedDataStreamsDelivery/PDSSourceBinder.h"
#include "PackedDataStreamsDelivery/PDSProxyDeliverer.h"

#include "ChainDelivery/Template/ChainSourceBinder.cc"

#include <vector>

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP
#  pragma define_template ChainSourceBinder< PDSSourceBinder >
#else
template class ChainSourceBinder< PDSSourceBinder > ;
#endif /* (defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX)) */
