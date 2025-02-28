// -*- C++ -*-
//
// Package:     JobControl
// Module:      T_LoaderBase
// 
// Description: Instantiate LoaderBase<>
//
//
// Author:      Valentine Kouznetsov
// Created:     Sun Mar 16 13:28:26 EST 2003
// $Id: T_LoaderBase.cc,v 1.1 2003/03/17 00:07:22 vk Exp $
//
// Revision history
//
// $Log: T_LoaderBase.cc,v $
// Revision 1.1  2003/03/17 00:07:22  vk
// Instantiate instance of LoaderBase<SourceFormat> & LoaderBase<SinkFormat>
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#include <map>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataDelivery/SourceFormat.h"
#include "DataStorage/SinkFormat.h"
#include "CommandPattern/Template/LoaderBase.cc"

// stl includes
#include <string>
#include <vector>
#include <map>
#include <set>

template class LoaderBase< SourceFormat >;
template class LoaderBase< SinkFormat >;

