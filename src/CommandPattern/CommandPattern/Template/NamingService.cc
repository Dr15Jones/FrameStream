#if !defined(NAMINGSERVICE_NAMINGSERVICE_CC)
#define NAMINGSERVICE_NAMINGSERVICE_CC
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      NamingService
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Thu Feb 18 18:39:01 EST 1999
// $Id: NamingService.cc,v 1.3 2002/12/09 15:25:13 cleo3 Exp $
//
// Revision history
//
// $Log: NamingService.cc,v $
// Revision 1.3  2002/12/09 15:25:13  cleo3
// added typename
//
// Revision 1.2  1999/12/11 19:10:14  mkl
// added more history command help info; minor fix-ups for Linux
//
// Revision 1.1  1999/02/22 23:40:55  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
//#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/NamingService.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
//#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kNamingServiceFacilityString = "CommandPattern.NamingService" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kNamingServiceIdString  = "$Id: NamingService.cc,v 1.3 2002/12/09 15:25:13 cleo3 Exp $";
static const char* const kNamingServiceTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
template< class T >
NamingService< T >::NamingService()
   : m_name2Object( *new _naming_service_namemap_ )
{
}

// template< class T >
// NamingService< T >::NamingService( const NamingService& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

template< class T >
NamingService< T >::~NamingService()
{
   // we don't own objects!
   delete &m_name2Object;
}

//
// assignment operators
//
// template< class T >
// const NamingService< T >& NamingService< T >::operator=( const NamingService< T >& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
template< class T >
DABoolean 
NamingService< T >::registerObject( const std::string& iName,
				    T* iObject )
{
   DABoolean returnValue = true;

   typename _naming_service_namemap_::iterator itFind = m_name2Object.find( iName );
   if( m_name2Object.end() == itFind )
   {
      m_name2Object[ iName ] = iObject;
   }
   else
   {
      report( INFO, kNamingServiceFacilityString )
	 << "Object with name " << iName << " has already been entered" 
	 << std::endl;
      returnValue = true;
   }

   return returnValue;
}

template< class T >
DABoolean 
NamingService< T >::deregisterObject( const std::string& iName )
{
   DABoolean returnValue = true;

   typename _naming_service_namemap_::iterator itFind = m_name2Object.find( iName );
   if( m_name2Object.end() == itFind )
   {
      report( ERROR, kNamingServiceFacilityString )
	 << "No such Object with name " << iName
	 << std::endl;
      returnValue = false;
   }
   else
   {
      m_name2Object.erase( itFind );
   }

   return returnValue;
}

//
// const member functions
//
template< class T >
T*
NamingService< T >::resolve( const std::string& iName )
{
   T* returnValue = 0;

   typename _naming_service_namemap_::iterator itFind = m_name2Object.find( iName );
   if( m_name2Object.end() != itFind )
   {
      returnValue = (*itFind).second;
   }
   else
   {
      report( ERROR, kNamingServiceFacilityString )
	 << "Cannot find Object with name " << iName
	 << std::endl;
   }

   return returnValue;
}

//
// static member functions
//

#endif /* NAMINGSERVICE_NAMINGSERVICE_CC */
