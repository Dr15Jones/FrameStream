// -*- C++ -*-
//
// Package:     Producer
// Module:      T_vector_DataKey
// 
// Description: 
//
//
// Author:      Martin Lohner, Chris Jones
// Created:     Thu Jan 15 12:20:00 EDT 1998
// $Id: T_vector_DataKey.cc,v 1.1 1998/11/01 20:14:46 mkl Exp $
//
// Revision history
//
// $Log: T_vector_DataKey.cc,v $
// Revision 1.1  1998/11/01 20:14:46  mkl
// switched to new proxy factory registration scheme
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataHandler/DataKey.h"

// STL includes
#include <vector>

typedef DataKey _vector_contents_;

#include "STLUtility/instantiate_vector.h"
