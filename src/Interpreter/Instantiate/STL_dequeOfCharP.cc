// -*- C++ -*-
//
// Package:     Interpreter
// Module:      STL_dequeOfCharP
// 
// Description: Instantiate STL classes for deque of char*
//
//
// Author:      Martin Lohner
// Created:     Wed Mar 25 12:00:00 EDT 1998
// $Id: STL_dequeOfCharP.cc,v 1.2 1998/05/09 20:33:48 mkl Exp $
//
// Revision history
//
// $Log: STL_dequeOfCharP.cc,v $
// Revision 1.2  1998/05/09 20:33:48  mkl
// make g++ happy: ambiguous string operator
//
// Revision 1.1  1998/05/07 15:34:09  mkl
// implement history mechanism; implement proper tcl_source command
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <deque>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Interpreter/Readline.h"

// STL include files
#include <string>
#include <deque>

typedef char* _deque_contents_;
typedef less< _deque_contents_ > _deque_compare_;
#include "STLUtility/instantiate_deque.h"
