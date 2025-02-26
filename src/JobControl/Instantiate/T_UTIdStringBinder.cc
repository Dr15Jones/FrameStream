// -*- C++ -*-
//
// Package:     JobControl
// Module:      Binder
// 
// Description: Instantiate UTIdentifer< string , Binder >
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
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */


// user include files
#include "JobControl/BinderBase.h"
#if defined(OLD_CXX_STRING_CLASS_BUG)
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */

#include "Utility/Template/UTIdentifier.cc"


#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP

#  pragma define_template UTIdentifier< string, BinderBase >
#  pragma define_template operator<<< string, BinderBase >
#  pragma define_template operator>>< string, BinderBase >

#else

template class UTIdentifier< string , BinderBase > ;

#if defined(NEED_NAMESPACE_TO_INSTANTIATE_OVERLOADED_FUNCTION_BUG)
template ostream& ::operator<<( ostream& iOStream , const UTIdentifier< string , BinderBase >& iIdentifier ) ;
template istream& ::operator>>( istream& iIstream , UTIdentifier< string , BinderBase >& iIdentifier ) ;
#else
template ostream& operator<<( ostream& iOStream , const UTIdentifier< string , BinderBase >& iIdentifier ) ;
template istream& operator>>( istream& iIstream , UTIdentifier< string , BinderBase >& iIdentifier ) ;
#endif /* NEED_NAMESPACE_TO_INSTANTIATE_OVERLOADED_FUNCTION_BUG */

#endif /* (defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX)) */
