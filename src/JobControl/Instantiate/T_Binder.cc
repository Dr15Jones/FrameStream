// -*- C++ -*-
//
// Package:     JobControl
// Module:      STL_Binder
// 
// Description: Instantiate STL classes for Binder
//
//
// Author:      Martin Lohner
// Created:     Wed June 16 12:20:00 EDT 1998
// $Id: T_Binder.cc,v 1.2 1998/09/23 19:01:17 mkl Exp $
//
// Revision history
//
// $Log: T_Binder.cc,v $
// Revision 1.2  1998/09/23 19:01:17  mkl
// typename; protect against multiple inclusion. All the make egcs happy
//
// Revision 1.1  1998/06/17 20:20:28  mkl
// fanned out instantiation files for Not/Chainable Binders
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "JobControl/SourceManager.h"
#include "JobControl/BinderBase.h"

// stl includes
#include <string>
#include <map>

typedef SourceManager::Token _map_key_ ;
typedef BinderBase* _map_contents_ ;
typedef std::less< _map_key_ > _map_compare_ ;

/*
#if !defined(__GNUG__) || ( __GNUC__ == 2 && __GNUC_MINOR__ >= 80 )
#include "STLUtility/instantiate_map.h"
#else
template class pair<const string, BinderBase*> ;
template class map<string, BinderBase*, less<string> > ;
template class rb_tree<string, pair<const string, BinderBase*>, select1st<pair<const string, BinderBase*>, string>, less<string> > ;
//template class less<string > ;
template operator!=(rb_tree<string, pair<string const, BinderBase*>, select1st<pair<string const, BinderBase*>, string >, less<string > >::iterator const &, rb_tree<string, pair<string const, BinderBase*>, select1st<pair<string const, BinderBase*>, string >, less<string > >::iterator const &) ;
#endif
*/
