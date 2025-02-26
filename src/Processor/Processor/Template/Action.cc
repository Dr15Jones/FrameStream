// -*- C++ -*-
//
// Package:     <package>
// Module:      Action
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Thu Apr 17 17:31:36 EDT 1997
// $Id: Action.cc,v 1.4 1998/03/27 15:27:03 mkl Exp $
//
// Revision history
//
// $Log: Action.cc,v $
// Revision 1.4  1998/03/27 15:27:03  mkl
// more naming fixups
//
// Revision 1.3  1997/10/07 19:24:49  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.2  1997/07/11 05:59:28  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.1.1.1  1997/05/23 20:18:01  mkl
// imported processor sources
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "Processor/Action.h"


// STL classes

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.Action";

//
// static data member definitions
//

//
// constructors and destructor
//
/*
template< class T>
Action<T>::Action( void (*iMethod)(T&, Frame& ), 
		   T* iProcessor ) :
   m_processor( iProcessor ),
   m_method( iMethod )
{
}
*/
// Action::Action( const Action& )
// {
// }
/*
template< class T>
Action<T>::~Action()
{
}
*/
//
// assignment operators
//
// const Action& Action::operator=( const Action& )
// {
// }

//
// member functions
//
/*
template< class T >
ActionBase::ActionResult
Action<T>::operator()( Frame& iFrame )
{
  return (*m_method)( *m_processor, iFrame );
}
*/
//
// const member functions
//

//
// static member functions
//

