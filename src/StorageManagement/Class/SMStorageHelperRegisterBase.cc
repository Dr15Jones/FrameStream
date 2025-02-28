// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMStorageHelperRegisterBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 28 16:42:59 EDT 1999
// $Id: SMStorageHelperRegisterBase.cc,v 1.1.1.1 1999/09/13 21:21:43 cdj Exp $
//
// Revision history
//
// $Log: SMStorageHelperRegisterBase.cc,v $
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
#include "StorageManagement/SMStorageHelperRegisterBase.h"
#include "StorageManagement/SMStorageHelperManager.h"

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

static const char* const kFacilityString = "StorageManagement.SMStorageHelperRegisterBase" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SMStorageHelperRegisterBase.cc,v 1.1.1.1 1999/09/13 21:21:43 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
SMStorageHelperRegisterBase::SMStorageHelperRegisterBase( const TypeTag& iType)
  : SMStorageHelperBase( iType )
{
   SMStorageHelperManager::instance().registerHelper( this );
}

// SMStorageHelperRegisterBase::SMStorageHelperRegisterBase( const SMStorageHelperRegisterBase& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SMStorageHelperRegisterBase::~SMStorageHelperRegisterBase()
{
  SMStorageHelperManager::instance().unregisterHelper( this ); 
}

//
// assignment operators
//
// const SMStorageHelperRegisterBase& SMStorageHelperRegisterBase::operator=( const SMStorageHelperRegisterBase& rhs )
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
