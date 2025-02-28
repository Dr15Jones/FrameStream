// -*- C++ -*-
//
// Package:     DataDelivery
// Module:      DataSourceBinder
// 
// Description: Binds one or more DataStreams to one DataSource
//
// Implimentation:
//     At the moment, m_boundStreamList can contain a Stream that the
//      Source is unable to proccess.  This inconsistency is not determined
//      until boundStreamsAreValid is called.
//     Instead, I could check to see if the Streams are valid when the user
//      initially gives them to the DataSourceBinder, but I have no good way
//      of returning an error if they give me a wrong Stream in the 
//      constructor.
//
// Author:      Chris D Jones
// Created:     Thu Mar 13 13:24:09 EST 1997
// $Id: DataSourceBinder.cc,v 1.6 1997/08/27 03:39:21 sjp Exp $
//
// Revision history
//
// $Log: DataSourceBinder.cc,v $
// Revision 1.6  1997/08/27 03:39:21  sjp
// Updated to new name for bug flags
//
// Revision 1.5  1997/07/09 18:00:37  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.4  1997/04/21 19:17:17  cdj
// Now inherits from DataSourceDescriptor
//
// Revision 1.3  1997/03/20 22:39:34  cdj
// Correctly instantiated the stl container reference data members
// Added operator==( const DataSourceController& ) needed by FrameDeliverer
//
// Revision 1.2  1997/03/18 20:43:25  cdj
// 1) Code will now compile
// 2) Modified to handle changes in Stream::Set
//
// Revision 1.1  1997/03/13 21:51:32  cdj
// First submission.
// NOTE: No compilation has been attempted on this file so syntax errors are
// possible/likely.
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataDelivery/DataSourceBinder.h"
#include "DataDelivery/DataSourceController.h"
#include "DataHandler/StreamSet.h"

// STL classes
#if defined(OLD_CXX_STRING_CLASS_BUG)
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DataSourceBinder::DataSourceBinder( const Stream::Set& iBindStreams ):
   DataSourceDescriptor( string(""), string(""), iBindStreams)
{
}

DataSourceBinder::DataSourceBinder( const Stream::Type& iBindStream ) :
   DataSourceDescriptor( string(""), string(""), iBindStream)
{
}

DataSourceBinder::DataSourceBinder( const string& iDataSourceID,
				    const string& iParameters,
				    const Stream::Set& iBindStreams ):
   DataSourceDescriptor(iDataSourceID, iParameters, iBindStreams)
{
}

DataSourceBinder::DataSourceBinder( const string& iDataSourceID,
				    const string& iParameters,
				    const Stream::Type& iBindStream ):
   DataSourceDescriptor(iDataSourceID, iParameters, iBindStream)
{
}

// DataSourceBinder::DataSourceBinder( const DataSourceBinder& )
// {
// }

DataSourceBinder::~DataSourceBinder()
{
}

//
// assignment operators
//
// const DataSourceBinder& DataSourceBinder::operator=( const DataSourceBinder& )
// {
// }

//
// member functions
//

//
// const member functions
//

//
// static member functions
//
