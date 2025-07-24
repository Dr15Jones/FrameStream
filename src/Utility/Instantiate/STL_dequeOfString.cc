// -*- C++ -*-
//
// Package:     Utility
// Module:      STL_dequeOfString
// 
// Description: Instantiate STL classes for simple types: string
//
//
// Author:      Martin Lohner
// Created:     Fri March 14 18:48:00 EDT 1998
// $Id: STL_dequeOfString.cc,v 1.2 1998/08/23 18:12:14 mkl Exp $
//
// Revision history
//
// $Log: STL_dequeOfString.cc,v $
// Revision 1.2  1998/08/23 18:12:14  mkl
// make g++ happy: proper inclusions of stl/string header files
//
// Revision 1.1  1998/08/22 21:58:27  mkl
// new StringTokenizer to parse strings into substrings based on a delimiter
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <deque>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

// STL files
#include <string>
#include <deque>

typedef std::string _deque_contents_;
#include "STLUtility/instantiate_deque.h"
