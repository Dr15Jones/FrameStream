// -*- C++ -*-
//
// Package:     <ProxyBind>
// Module:      T_vector_ProxyBoundActionBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sat Feb 27 11:42:39 EST 1999
// $Id: T_vector_ProxyBoundActionBase.cc,v 1.1.1.1 1999/03/04 19:11:57 cdj Exp $
//
// Revision history
//
// $Log: T_vector_ProxyBoundActionBase.cc,v $
// Revision 1.1.1.1  1999/03/04 19:11:57  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

// STL classes
#include <vector>

//
// instantiate
//
class ProxyBoundActionBase;
typedef ProxyBoundActionBase* _vector_contents_;
#include "STLUtility/instantiate_vector.h"
