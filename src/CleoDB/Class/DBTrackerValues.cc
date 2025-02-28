// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBTrackerValues
// 
// Description: Values used by tracker to fit tracks
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Fri Jun 27 11:21:01 EDT 1997
// $Id: DBTrackerValues.cc,v 1.3 2000/06/16 00:57:54 marsh Exp $
//
// Revision history
//
// $Log: DBTrackerValues.cc,v $
// Revision 1.3  2000/06/16 00:57:54  marsh
// Purged tool box typedefs.
//
// Revision 1.2  2000/03/01 00:39:15  cdj
// added operator==
//
// Revision 1.1  1997/09/17 16:07:23  sjp
// New class to hold values used by tracker
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "CleoDB/DBTrackerValues.h"

//
// static data member definitions
//

const Stream::Type& DBTrackerValues::kStream = Stream::kEvent ;

//
// constructors and destructor
//

DBTrackerValues::DBTrackerValues( const HepVector3D& aMagneticField ,
				  const GeV* aMasses ) :
   m_magneticField( aMagneticField )
{
   for ( SmallCount hypo = 0 ;
	 hypo != DBCandidate::kMaxHypo ;
	 ++hypo ) {
      m_masses[ hypo ] = aMasses[ hypo ] ;
   }
}

DBTrackerValues::~DBTrackerValues()
{
}

//
// member functions
//

//
// const member functions
//

const HepVector3D&
DBTrackerValues::magneticField() const
{
   return ( m_magneticField ) ;
}

GeV
DBTrackerValues::mass( const DBCandidate::Hypo& aHypo ) const
{
   return( m_masses[ aHypo ] ) ;
}


DABoolean
DBTrackerValues::operator==( const DBTrackerValues& iRHS ) const
{
   
   if ( magneticField() == iRHS.magneticField() ) {
      for( unsigned int index = 0;
	   index < DBCandidate::kMaxHypo;
	   ++index ) {
	 if( m_masses[index] != iRHS.m_masses[index] ) {
	    return false;
	 }
      }
      return true;
   } 
   return false;
}

//
// static member functions
//
