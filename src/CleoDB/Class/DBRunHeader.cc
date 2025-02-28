// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBRunHeader
// 
// Description: Container for run header information
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Your name here
// Created:     Mon Jan  1 00:00:00 EDT 1970
// $Id: DBRunHeader.cc,v 1.2 1998/11/06 19:56:51 marsh Exp $
//
// Revision history
//
// $Log: DBRunHeader.cc,v $
// Revision 1.2  1998/11/06 19:56:51  marsh
// Removed unneeded 'const's.
//
// Revision 1.1  1997/09/10 13:57:26  sjp
// File to handle DBRunHeader
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "CleoDB/DBRunHeader.h"

//
// static data member definitions
//

const Stream::Type& DBRunHeader::kStream = Stream::kBeginRun ;

//
// constructors and destructor
//

DBRunHeader::DBRunHeader( const Count aValue ) :
   m_value( aValue )
{
}

DBRunHeader::~DBRunHeader()
{
}

//
// member functions
//

//
// const member functions
//

Count
DBRunHeader::number() const
{
   return ( m_value ) ;
}

//
// static member functions
//
