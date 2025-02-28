// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMStorageHelperBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon May 17 13:32:31 EDT 1999
// $Id: SMStorageHelperBase.cc,v 1.1.1.1 1999/09/13 21:21:43 cdj Exp $
//
// Revision history
//
// $Log: SMStorageHelperBase.cc,v $
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
#include "StorageManagement/SMStorageHelperBase.h"

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

static const char* const kFacilityString = "StorageManagement.SMStorageHelperBase" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SMStorageHelperBase.cc,v 1.1.1.1 1999/09/13 21:21:43 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
SMStorageHelperBase::SMStorageHelperBase( const TypeTag& iTypeTag) :
   m_typeTag( iTypeTag )
{
}

// SMStorageHelperBase::SMStorageHelperBase( const SMStorageHelperBase& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SMStorageHelperBase::~SMStorageHelperBase()
{
}

//
// assignment operators
//
// const SMStorageHelperBase& SMStorageHelperBase::operator=( const SMStorageHelperBase& rhs )
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

//
// const member functions
//

//
// static member functions
//
