// -*- C++ -*-
//
// Package:     PackedDataStreamsDelivery
// Module:      STL_PDSSourceBinder
// 
// Description: Instantiate STL classes for PDSSourceBinder
//
//
// Author:      Chris D Jones
// Created:     Wed May 30 09:45:00 EDT 2001
// $Id: T_PDSSourceBinder.cc,v 1.1 2001/05/31 16:57:17 cdj Exp $
//
// Revision history
//
// $Log: T_PDSSourceBinder.cc,v $
// Revision 1.1  2001/05/31 16:57:17  cdj
// modifications necessary to allow chaining
//
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <deque>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "PackedDataStreamsDelivery/PDSSourceBinder.h"

#include <vector>
typedef PDSSourceBinder _vector_contents_ ;
#include "STLUtility/instantiate_vector.h"

#include <deque>
typedef PDSSourceBinder _deque_contents_ ;
#include "STLUtility/instantiate_deque.h"

