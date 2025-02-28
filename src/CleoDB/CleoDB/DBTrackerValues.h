#if !defined(CLEODB_DBTRACKERVALUES_H)
#define CLEODB_DBTRACKERVALUES_H
// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBTrackerValues
// 
// Description: Values used by tracker to fit tracks
//
// Usage:
//    <usage>
//
// Author:      Simon Patton
// Created:     Tue Sep 16 11:21:01 EDT 1997
// $Id: DBTrackerValues.h,v 1.3 2000/06/16 00:57:56 marsh Exp $
//
// Revision history
//
// $Log: DBTrackerValues.h,v $
// Revision 1.3  2000/06/16 00:57:56  marsh
// Purged tool box typedefs.
//
// Revision 1.2  2000/03/01 00:37:21  cdj
// modified to work better with StorageHelpers
//
// Revision 1.1  1997/09/17 16:07:21  sjp
// New class to hold values used by tracker
//

// system include files

// user include files
#include "CLHEP/Geometry/Vector3D.h" // dasat memeber
#include "DataHandler/Stream.h" // for Stream::Type
#include "CleoDB/DBCandidate.h" // for DBCandidate::kMaxHypo and
				// DBCandidate::Hypo

// forward declarations

class DBTrackerValues
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      static const Stream::Type& kStream ;

      // Constructors and destructor
      DBTrackerValues( const HepVector3D& aMagneticField ,
		       const GeV* aMasses ) ;
      //DBTrackerValues( const DBTrackerValues& ) ;
      virtual ~DBTrackerValues();

      // assignment operator(s)
      //const DBTrackerValues& operator=( const DBTrackerValues& ) ; 

      // member functions

      // const member functions
      const HepVector3D& magneticField() const ;
      GeV mass( const DBCandidate::Hypo& aHypo ) const ;

      DABoolean operator==( const DBTrackerValues& iRHS ) const;

      // static member functions

   private:
      // Constructors and destructor
      DBTrackerValues(); // stop default ;


      // data members
      HepVector3D m_magneticField ;
      GeV m_masses[ DBCandidate::kMaxHypo ] ;

};

// inline function definitions

#endif /* CLEODB_DBTRACKERVALUES_H */
