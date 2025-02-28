// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      T_vectorAndDeque_BinarySourceBinder
// 
// Description: Instantiate STL classes for BinarySourceBinder
//
//
// Author:      Martin Lohner
// Created:     Mon Nov 16 12:20:00 EDT 1998
// $Id: T_vectorAndDeque_BinarySourceBinder.cc,v 1.1 1998/11/16 16:51:46 mkl Exp $
//
// Revision history
//
// $Log: T_vectorAndDeque_BinarySourceBinder.cc,v $
// Revision 1.1  1998/11/16 16:51:46  mkl
// additions necessary to load BinarySourceFormat and chain binary files
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <deque>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "BinaryDelivery/BinarySourceBinder.h"

#include <vector>
typedef BinarySourceBinder _vector_contents_ ;
#include "STLUtility/instantiate_vector.h"

#include <deque>
typedef BinarySourceBinder _deque_contents_ ;
#include "STLUtility/instantiate_deque.h"

