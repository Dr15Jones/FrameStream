// -*- C++ -*-
//
// Package:     JobControl
// Module:      Binder
// 
// Description: Instantiate UTIdentifer< std::string , Binder >
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Mon May 25 14:32:44 EDT 1998
// $Id: T_UTIdStringBinder.cc,v 1.2 1998/07/02 14:23:05 cdj Exp $
//
// Revision history
//
// $Log: T_UTIdStringBinder.cc,v $
// Revision 1.2  1998/07/02 14:23:05  cdj
// modified to compile under cxx 6.0
//
// Revision 1.1  1998/06/17 18:18:15  mkl
// allow dynamic loading of source and sink formats
//
//

#include "Experiment/Experiment.h"

// system include files


// user include files
#include "DataDelivery/BinderBase.h"
#include <string>
#include "Utility/Template/UTIdentifier.cc"



template class UTIdentifier< std::string , BinderBase > ;

template std::ostream& operator<<(std::ostream& iOStream , const UTIdentifier< std::string , BinderBase >& iIdentifier ) ;
template std::istream& operator>>( std::istream& iIstream , UTIdentifier< std::string , BinderBase >& iIdentifier ) ;
