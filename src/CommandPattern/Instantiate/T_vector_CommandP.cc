// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      T_vector_CommandP.cc
// 
// Description: Instantiate STL classes for Command
//
//
// Author:      Martin Lohner
// Created:     Fri July 11 12:00:00 EDT 1997
// $Id: T_vector_CommandP.cc,v 1.1 1998/11/12 22:23:58 mkl Exp $
//
// Revision history
//
// $Log: T_vector_CommandP.cc,v $
// Revision 1.1  1998/11/12 22:23:58  mkl
// finish new module loading and unloading
//
//

#include "Experiment/Experiment.h"
// system include files
#include <vector>

// user include files

class Command;
typedef Command* _vector_contents_;

#include "STLUtility/instantiate_vector.h"
