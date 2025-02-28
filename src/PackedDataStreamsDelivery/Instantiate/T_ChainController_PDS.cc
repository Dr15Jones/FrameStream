// -*- C++ -*-
//
// Package:     PackedDataStreamsDelivery
// Module:      T_ChainController_PDS
// 
// Description: Instantiate ChainSourceController<PDSSourceController>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris Jones
// Created:     Wed May 30 09:45:27 EST 2001
// $Id: T_ChainController_PDS.cc,v 1.1 2001/05/31 16:57:17 cdj Exp $
//
// Revision history
//
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>  // For 'exit'

#include "PackedDataStreamsDelivery/PDSSourceController.h"
#include "PackedDataStreamsDelivery/PDSSourceBinder.h"
#include "PackedDataStreamsDelivery/PDSProxyDeliverer.h"

#include "ChainDelivery/ChainSourceController.h"
#include "ChainDelivery/Template/ChainSourceController.cc"

template class ChainSourceController< PDSSourceBinder > ;



