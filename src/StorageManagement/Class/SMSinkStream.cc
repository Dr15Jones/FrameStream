// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMSinkStream
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sun Oct 31 14:55:45 EST 1999
// $Id: SMSinkStream.cc,v 1.1 1999/11/03 17:53:42 cdj Exp $
//
// Revision history
//
// $Log: SMSinkStream.cc,v $
// Revision 1.1  1999/11/03 17:53:42  cdj
// added compression hints code
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
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMPackInfo.h"

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

static const char* const kFacilityString = "StorageManagement.SMSinkStream" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SMSinkStream.cc,v 1.1 1999/11/03 17:53:42 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//
SMPackInfo* SMSinkStream::s_defaultPackInfo = new SMPackInfo;

//
// constructors and destructor
//
//SMSinkStream::SMSinkStream()
//{
//}

// SMSinkStream::SMSinkStream( const SMSinkStream& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//SMSinkStream::~SMSinkStream()
//{
//}

//
// assignment operators
//
// const SMSinkStream& SMSinkStream::operator=( const SMSinkStream& rhs )
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
