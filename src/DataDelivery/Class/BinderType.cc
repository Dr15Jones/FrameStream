// -*- C++ -*-
//
// Package:     JobControl
// Module:      BinderType
// 
// Description: Specialization of UTIdentifier for Binders
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Mar 30 11:56:15 EDT 1998
// $Id: BinderType.cc,v 1.2 1998/09/08 19:24:11 mkl Exp $
//
// Revision history
//
// $Log: BinderType.cc,v $
// Revision 1.2  1998/09/08 19:24:11  mkl
// clean up for warning messages from cxx 6.0
//
// Revision 1.1  1998/06/17 18:18:04  mkl
// allow dynamic loading of source and sink formats
//
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Experiment/report.h" // For error report
#include "DataDelivery/BinderType.h"


// STL classes
#include <string>
#include <map>
#include <vector>
#include <algorithm>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.BinderType";

typedef _bindertype_arestandard_ DABooleanList ;

//
// static data member definitions
//

//
// constructors and destructor
//
BinderType::BinderType( void )
{
   findIsStandard(); //Set isStandard to default
}

BinderType::BinderType( const std::string& iString, 
			DABoolean iIsStandard ) 
   : UTIdentifier< std::string, BinderBase >( iString )
{
   setIsStandard(iIsStandard );
}

// BinderType::BinderType( const BinderType& )
// {
// }

BinderType::~BinderType()
{
}

//
// assignment operators
//
// const BinderType& BinderType::operator=( const BinderType& )
// {
// }

//
// member functions
//

//
// const member functions
//
DABoolean
BinderType::isStandard( void ) const
{
   return findIsStandard();
}

//
// static member functions
//

//Simple utility function which checks to see if an index to a vector
// is contained within that vector.
// This function is used to make the code more readable and because it
// guarantees that the same algorithm is used in four places.
template <class T>
inline
DABoolean 
isNoIndex( const std::vector< T >& ipVector, const Count& iIndex ) 
{
   return ( ipVector.size() < iIndex+1 );
} 

DABooleanList&
BinderType::standards( void )
{
   static DABooleanList m_standards ;
   static DABoolean m_first = !false ;

   if ( m_first ) {
      //There probably won't be more than 40 binder types, but there will be
      // less than the 4000 that is normally reserved for vector.
      m_standards.reserve(40);
      m_first = false ;
   }
   return ( m_standards ) ;
}

DABoolean 
BinderType::findIsStandard( void ) const
{
   Count iIndex = index();
   DABoolean returnValue(false);
   if( isNoIndex(standards(), iIndex) ){
      //default is not standard
      standards().push_back(false);
   } else {
      returnValue = standards()[iIndex];
   }
   return returnValue;
}

void
BinderType::setIsStandard( const DABoolean iIsStandard )
{
   Count iIndex = index();
   if( isNoIndex( standards(), iIndex )){
      //add a new entry
      standards().push_back( iIsStandard );
   } else {
      //if new isStandard doesn't match old isStandard this is an error
      DABoolean trueIsStandard;
      if( (trueIsStandard = standards()[iIndex] )
	  != iIsStandard ){
	 report( EMERGENCY ,
		 kFacilityString )<< "isStandard for Binder "
				  << value()
				  <<" has already been set to "
				  << trueIsStandard
				  <<" and you tried to change this to "
				  <<iIsStandard
				  << std::endl ;
	 exit( 1 ) ;
      }
   }
   return;
}


//Utility functions
std::ostream&
operator<<(std::ostream& iOStream, const BinderType& iBinderType )
{
   return ( iOStream << iBinderType.value() );
}

std::istream&
operator>>( std::istream& iIStream, BinderType& iBinderType )
{
   std::string tmp ;
   iIStream >> tmp ;
   iBinderType = BinderType( tmp ) ;
   return ( iIStream );
}
