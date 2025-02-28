#if !defined(STORAGEMANAGEMENT_SMSTORAGEPROXYHELPER_CC)
#define STORAGEMANAGEMENT_SMSTORAGEPROXYHELPER_CC
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMStorageProxyHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 15:34:34 EDT 1999
// $Id: SMStorageProxyHelper.cc,v 1.1 1999/10/18 18:29:26 cdj Exp $
//
// Revision history
//
// $Log: SMStorageProxyHelper.cc,v $
// Revision 1.1  1999/10/18 18:29:26  cdj
// first submission
//
// Revision 1.1.1.1  1999/09/13 21:21:42  cdj
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
#include "StorageManagement/SMStorageProxyHelper.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMProxyWriter.h"
#include "StorageManagement/SMProxy.h"
#include "DataHandler/RecordMethods.h"
#include "DataHandler/DataKey.h"

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

//static const char* const kFacilityString = "StorageManagement.SMStorageProxyHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
//static const char* const kIdString  = "$Id: SMStorageProxyHelper.cc,v 1.1 1999/10/18 18:29:26 cdj Exp $";
//static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//

// SMStorageProxyHelper::SMStorageProxyHelper( const SMStorageProxyHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//
// assignment operators
//
// const SMStorageProxyHelper& SMStorageProxyHelper::operator=( const SMStorageProxyHelper& rhs )
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
template< class T>
SMProxyBase* 
SMStorageProxyHelper<T>::makeProxy() const
{
   return new SMProxy<T>( const_cast< SMStorageProxyHelper<T>* >(this) );
}

template< class T>
SMProxyWriterBase* 
SMStorageProxyHelper<T>::makeProxyWriter() const
{
   return new SMProxyWriter<T>( const_cast< SMStorageProxyHelper<T>* >(this) );
}

//
// const member functions
//

//
// static member functions
//

#endif /* STORAGEMANAGEMENT_SMSTORAGEPROXYHELPER_CC */
