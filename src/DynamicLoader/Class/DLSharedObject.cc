// -*- C++ -*-
//
// Package:     <DynamicLoader>
// Module:      DLSharedObject
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Nov 20 13:36:47 EST 2000
// $Id: DLSharedObject.cc,v 1.2 2003/03/31 19:42:52 cdj Exp $
//
// Revision history
//
// $Log: DLSharedObject.cc,v $
// Revision 1.2  2003/03/31 19:42:52  cdj
// now works under OS X (Darwin)
//
// Revision 1.1.1.1  2000/11/30 20:51:31  cdj
// imported DynamicLoader source
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
#if !defined(D_AIX)
#if !defined(Darwin)
#include <dlfcn.h>
#else
#include <mach-o/dyld.h>
#endif
#else
#include <sys/ldr.h>
#include <sys/errno.h>
#endif                   

#include <assert.h>

// user include files
//#include "Experiment/report.h"
#include "DynamicLoader/DLSharedObject.h"
#include "DynamicLoader/DLSymbolNotFoundException.h"

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

static const char* const kFacilityString = "DynamicLoader.DLSharedObject" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DLSharedObject.cc,v 1.2 2003/03/31 19:42:52 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//DLSharedObject::DLSharedObject()
//{
//}

// DLSharedObject::DLSharedObject( const DLSharedObject& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//DLSharedObject::~DLSharedObject()
//{
//}

//
// assignment operators
//
// const DLSharedObject& DLSharedObject::operator=( const DLSharedObject& rhs )
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

void* 
DLSharedObject::getSymbol( const string& symbolName ) const
{
   void* returnValue = 0;

   assert( m_handle != 0 );

#if !defined(D_AIX) /* -------------------------------------------- */
#if defined(Darwin)
   string modifiedSymbolName = string("_")+symbolName;
   NSSymbol nsSymbol = NSLookupSymbolInModule(m_handle, modifiedSymbolName.c_str() );
   if( NULL !=nsSymbol) {
     returnValue = NSAddressOfSymbol(nsSymbol);
   } else {
     throw DLSymbolNotFoundException("");
   }
   //   if ( NULL != returnValue ) {

   //   }
#else
   returnValue = dlsym( m_handle, 
		   symbolName.c_str() );

   // error handling
   const char* error;
   if( NULL != (error = dlerror()) )  // symbol ok?
   {
      throw DLSymbolNotFoundException( error );
   }
#endif
#else /* --------------------- AIX -------------------------------- */
   //AIX only allows once symbol to be accessible per shared library

   string dummy( symbolName ); // to get rid of "unused variable" warning
   returnValue = m_handle;
   
#endif /* --------------------------------------------------------- */

   return returnValue;
}

//
// static member functions
//
