// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMProxyWriterBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon May 24 17:26:51 EDT 1999
// $Id: SMProxyWriterBase.cc,v 1.2 2000/07/19 18:52:07 mkl Exp $
//
// Revision history
//
// $Log: SMProxyWriterBase.cc,v $
// Revision 1.2  2000/07/19 18:52:07  mkl
// add a success return from SMProxyWriter::store
//
// Revision 1.1.1.1  1999/09/13 21:21:43  cdj
// imported package
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
#include "StorageManagement/SMProxyWriterBase.h"
#include "StorageManagement/SMSinkStream.h"

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

static const char* const kFacilityString = "StorageManagement.SMProxyWriterBase" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SMProxyWriterBase.cc,v 1.2 2000/07/19 18:52:07 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
SMProxyWriterBase::SMProxyWriterBase()
{
}

// SMProxyWriterBase::SMProxyWriterBase( const SMProxyWriterBase& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SMProxyWriterBase::~SMProxyWriterBase()
{
}

//
// assignment operators
//
// const SMProxyWriterBase& SMProxyWriterBase::operator=( const SMProxyWriterBase& rhs )
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
DABoolean
SMProxyWriterBase::store( const DataKey& iKey   ,
			  const Record& iRecord ,
			  SMSinkStream& iOStream  )
{
   DABoolean returnValue;

   if( returnValue = extractData( iKey, iRecord , iOStream ) )
   {
      writeData( iOStream );
   }

   return returnValue;
}

//
// const member functions
//

//
// static member functions
//
