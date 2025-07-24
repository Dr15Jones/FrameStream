// -*- C++ -*-
//
// Package:     InteractiveDelivery
// Module:      InteractiveSourceBinder
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Sat Apr 19 14:31:47 EDT 1997
// $Id: InteractiveSourceBinder.cc,v 1.3 2003/11/22 20:22:25 cdj Exp $
//
// Revision history
//
// $Log: InteractiveSourceBinder.cc,v $
// Revision 1.3  2003/11/22 20:22:25  cdj
// can now specify what stream should be used
//
// Revision 1.2  1997/07/09 19:22:03  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1.1.1  1997/04/21 19:30:11  cdj
// First submission
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "InteractiveDelivery/InteractiveSourceBinder.h"
#include "InteractiveDelivery/InteractiveSourceController.h"
#include "InteractiveDelivery/InteractiveSource.h"

// STL classes

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
InteractiveSourceBinder::InteractiveSourceBinder( InteractiveSource* iSource):
   DataSourceBinder( std::string(InteractiveSourceController::kID),
		     std::string(""),
		     iSource->stream() ),
   m_source(iSource)
{
}

// InteractiveSourceBinder::InteractiveSourceBinder( const InteractiveSourceBinder& )
// {
// }

InteractiveSourceBinder::~InteractiveSourceBinder()
{
}

//
// assignment operators
//
// const InteractiveSourceBinder& InteractiveSourceBinder::operator=( const InteractiveSourceBinder& )
// {
// }

//
// member functions
//

//
// const member functions
//
DataSourceController*
InteractiveSourceBinder::createDataSourceController( void ) const
{
   return new InteractiveSourceController(m_source );
}

//
// static member functions
//
