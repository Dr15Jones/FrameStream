// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Subcommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Fri Sep  3 17:54:25 EDT 1999
// $Id: Subcommand.cc,v 1.1 1999/09/06 21:28:57 mkl Exp $
//
// Revision history
//
// $Log: Subcommand.cc,v $
// Revision 1.1  1999/09/06 21:28:57  mkl
// new subcommand handling
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "CommandPattern/Subcommand.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "CommandPattern.Subcommand" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: Subcommand.cc,v 1.1 1999/09/06 21:28:57 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
/*
template< class T >
Subcommand<T>::Subcommand( const string& iName,
			   Count iMinArgs,
			   Count iMaxArgs,
			   SubcommandFunction& iFunction )
   : SubcommandBase( iName, 
		     iMinArgs,
		     iMaxArgs ),
     m_subcomfunc( iFunction )
{
}
*/
// template< class T >
// Subcommand<T>::Subcommand( const Subcommand<T>& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }
/*
template< class T >
Subcommand<T>::~Subcommand()
{
}
*/
//
// assignment operators
//
// template< class T >
// const Subcommand<T>& Subcommand<T>::operator=( const Subcommand<T>& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
/* 
template< class T >
int
Subcommand<T>::execute()
{
   return (T::*m_subcomfun)();
}
*/
//
// const member functions
//

//
// static member functions
//
