// -*- C++ -*-
//
// Package:     DataStorage
// Module:      DataSinkBinder
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Sun May 25 16:55:32 EDT 1997
// $Id: DataSinkBinder.cc,v 1.2 1997/07/11 06:20:08 mkl Exp $
//
// Revision history
//
// $Log: DataSinkBinder.cc,v $
// Revision 1.2  1997/07/11 06:20:08  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.1.1.1  1997/05/30 15:41:36  cdj
// First submission
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "DataStorage/DataSinkBinder.h"
#include "DataStorage/DataSinkController.h"
#include "DataHandler/StreamSet.h"


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
DataSinkBinder::DataSinkBinder( const Stream::Set& iBindStreams ):
   DataSinkDescriptor( string(""), string(""), iBindStreams)
{
}

DataSinkBinder::DataSinkBinder( const Stream::Type& iBindStream ) :
   DataSinkDescriptor( string(""), string(""), iBindStream)
{
}

DataSinkBinder::DataSinkBinder( const string& iDataSinkID,
				    const string& iParameters,
				    const Stream::Set& iBindStreams ):
   DataSinkDescriptor(iDataSinkID, iParameters, iBindStreams)
{
}

DataSinkBinder::DataSinkBinder( const string& iDataSinkID,
				    const string& iParameters,
				    const Stream::Type& iBindStream ):
   DataSinkDescriptor(iDataSinkID, iParameters, iBindStream)
{
}

// DataSinkBinder::DataSinkBinder( const DataSinkBinder& )
// {
// }

DataSinkBinder::~DataSinkBinder()
{
}

//
// assignment operators
//
// const DataSinkBinder& DataSinkBinder::operator=( const DataSinkBinder& )
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
