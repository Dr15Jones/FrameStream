// -*- C++ -*-
//
// Package:     Interpreter
// Module:      STL_setOfCommands
// 
// Description: Instantiate STL classes for Command
//
//
// Author:      Martin Lohner
// Created:     Wed Mar 25 12:00:00 EDT 1998
// $Id: STL_setOfCommands.cc,v 1.1 1998/03/26 20:01:13 mkl Exp $
//
// Revision history
//
// $Log: STL_setOfCommands.cc,v $
// Revision 1.1  1998/03/26 20:01:13  mkl
// added gnu readline support
//
//

#include "Experiment/Experiment.h"
// system include files
#include <string>
#include <set>

// user include files
#include "Interpreter/Readline.h"

typedef Readline::CommandName _set_contents_;
typedef less< _set_contents_ > _set_compare_;
#if 0
#include "STLUtility/instantiate_set.h"
#endif
