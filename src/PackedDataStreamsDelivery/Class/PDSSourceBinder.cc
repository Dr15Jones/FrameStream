// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSSourceBinder
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Sep 25 15:42:09 EDT 2000
// $Id: PDSSourceBinder.cc,v 1.2 2001/05/31 16:57:14 cdj Exp $
//
// Revision history
//
// $Log: PDSSourceBinder.cc,v $
// Revision 1.2  2001/05/31 16:57:14  cdj
// modifications necessary to allow chaining
//
// Revision 1.1.1.1  2000/09/29 17:48:06  cdj
// imported
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
#include "PackedDataStreamsDelivery/PDSSourceBinder.h"
#include "PackedDataStreamsDelivery/PDSSourceController.h"

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

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSSourceBinder" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSSourceBinder.cc,v 1.2 2001/05/31 16:57:14 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
PDSSourceBinder::PDSSourceBinder(const string& iFileName,
				 const Stream::Set& iBindStreams ) :
   DataSourceBinder(iFileName, string(""), iBindStreams )
{
}

PDSSourceBinder::PDSSourceBinder( const PDSSourceBinder& iBinder ) :
   DataSourceBinder( iBinder.dataSourceID(),
                     iBinder.parameters(),
                     iBinder.boundStreams())
{
}

PDSSourceBinder::~PDSSourceBinder()
{
}

//
// assignment operators
//
const PDSSourceBinder& PDSSourceBinder::operator=( const PDSSourceBinder& iBinder )
{
   setDataSourceID( iBinder.dataSourceID() );
   setParameters( iBinder.parameters() );
   bindStreams( iBinder.boundStreams() );
   return *this;
}

//
// member functions
//

//
// const member functions
//
DataSourceController*
PDSSourceBinder::createDataSourceController() const
{
   return ( new PDSSourceController( fileName(),
				     boundStreams() ) ) ;
}

PDSSourceController*
PDSSourceBinder::createSourceController( PDSProxyDeliverer* iDeliverer ) const
{
   return ( new PDSSourceController( fileName(), boundStreams(), iDeliverer ) ) ;
}

const string&
PDSSourceBinder::fileName() const
{
   return dataSourceID();
}

//
// static member functions
//
