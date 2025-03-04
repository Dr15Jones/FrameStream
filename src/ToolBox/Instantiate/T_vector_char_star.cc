// -*- C++ -*-
//
// Package:     ToolBox
// Module:      T_vector_char_star
// 
// Description: Instantiate vector< char* >
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D. Jones
// Created:     Fri Jul  3 13:58:08 EDT 1998
// $Id: T_vector_char_star.cc,v 1.1 1998/07/03 18:27:26 cdj Exp $
//
// Revision history
//
// $Log: T_vector_char_star.cc,v $
// Revision 1.1  1998/07/03 18:27:26  cdj
// now uses the "proper" vector instantiation
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

// STL classes

typedef char* _vector_contents_ ;
#include "STLUtility/instantiate_vector.h"
