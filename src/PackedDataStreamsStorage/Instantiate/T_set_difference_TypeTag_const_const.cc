// -*- C++ -*-
//
// Package:     <package>
// Module:      T_set_difference_TypeTag_const_const
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sun Nov 24 09:38:56 EST 2002
// $Id: T_set_difference_TypeTag_const_const.cc,v 1.2 2003/01/27 20:36:23 cleo3 Exp $
//
// Revision history
//
// $Log: T_set_difference_TypeTag_const_const.cc,v $
// Revision 1.2  2003/01/27 20:36:23  cleo3
// make instantiation compile under g++
//
// Revision 1.1  2002/11/24 15:04:58  cdj
// fixed missing symbol on OSF by removing autoinstantiations from PDSProxyStorer.cc to own files
//

#include "Experiment/Experiment.h"

// system include files
#include <set>
#include <iterator>

// user include files
//#include "Experiment/report.h"
#include "DataHandler/DataKeyTags.h"
#include "STLUtility/fwd_set.h"

typedef insert_iterator< STL_SET(TypeTag) > _output_iterator_;
typedef STL_SET( TypeTag )::const_iterator _const_input_iterator_;
typedef STL_SET( TypeTag )::iterator _input_iterator_;

#if defined(NO_IMPLICIT_INSTANTIATION)
template 
_output_iterator_ STD_PREFIX set_difference (_const_input_iterator_ , 
					     _const_input_iterator_ ,
					     _const_input_iterator_ , 
					     _const_input_iterator_ ,
					     _output_iterator_ );
#endif
