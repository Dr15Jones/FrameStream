// -*- C++ -*-
//
// Package:     InteractiveDelivery
// Module:      InteractiveProxyDeliverer
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Sat Apr 19 14:32:07 EDT 1997
// $Id: InteractiveProxyDeliverer.cc,v 1.6 2003/11/22 20:22:25 cdj Exp $
//
// Revision history
//
// $Log: InteractiveProxyDeliverer.cc,v $
// Revision 1.6  2003/11/22 20:22:25  cdj
// can now specify what stream should be used
//
// Revision 1.5  1997/08/14 11:43:31  sjp
// Mods to run under CW Pro 1
//
// Revision 1.4  1997/08/06 16:30:25  sjp
// Modified to use ProxyDeliverer
//
// Revision 1.3  1997/07/09 19:21:59  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.2  1997/06/03 17:40:23  sjp
// Put name to DataFieldDeliverer constructor
//
// Revision 1.1.1.1  1997/04/21 19:30:11  cdj
// First submission
//

#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */

// user include files
#include "InteractiveDelivery/InteractiveProxyDeliverer.h"

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
InteractiveProxyDeliverer::InteractiveProxyDeliverer(const Stream::Type& iStream) :
   ProxyDeliverer( "Interactive" )
{
   registerStream( iStream );
}

// InteractiveProxyDeliverer::InteractiveProxyDeliverer( const InteractiveProxyDeliverer& )
// {
// }

InteractiveProxyDeliverer::~InteractiveProxyDeliverer()
{
}

//
// assignment operators
//
// const InteractiveProxyDeliverer& InteractiveProxyDeliverer::operator=( const InteractiveProxyDeliverer& )
// {
// }

//
// member functions
//
void
InteractiveProxyDeliverer::disable( const Stream::Type& )
{
//do nothing
}

void
InteractiveProxyDeliverer::enable( const Stream::Type& )
{
//do nothing
}

void
InteractiveProxyDeliverer::resetCache( const Stream::Type& )
{
//do nothing
}

void
InteractiveProxyDeliverer::registerProxies( const Stream::Type& ,
					    KeyedProxies& )
{
//Does nothing since this Source produces no data
}
//
// const member functions
//

//
// static member functions
//
