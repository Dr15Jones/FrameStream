// -*- C++ -*-
//
// Package:     <DefaultModule>
// Module:      DefaultModule
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Thu Feb 18 23:00:13 EST 1999
// $Id: DefaultModule.cc,v 1.1.1.1 1999/02/22 22:44:38 mkl Exp $
//
// Revision history
//
// $Log: DefaultModule.cc,v $
// Revision 1.1.1.1  1999/02/22 22:44:38  mkl
// imported sources
//
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
#include "Experiment/report.h"
#include "CommandPattern/DefaultModule.h"

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
static const char* const kFacilityString = "DefaultModule.DefaultModule" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DefaultModule.cc,v 1.1.1.1 1999/02/22 22:44:38 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//
static DefaultModule *gDefault = nullptr;
DefaultModule const* DefaultModule::instance() {

}

//
// constructors and destructor
//
DefaultModule::DefaultModule()
   : Module( "DefaultModule", "This is my module" ),
     m_command( "default", this )
//     m_internalCommand( "DefaultModule", this )
{
   gDefault = this;
}

// DefaultModule::DefaultModule( const DefaultModule& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

DefaultModule::~DefaultModule()
{
   if (gDefault == this) {
      gDefault = nullptr;
   }
}

//
// assignment operators
//
// const DefaultModule& DefaultModule::operator=( const DefaultModule& rhs )
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
Switch::OnOff
DefaultModule::setPrompting( Switch::OnOff iSetting )
{
   return m_prompting.turn( iSetting );
}

//
// const member functions
//
Switch::OnOff
DefaultModule::usePrompting() const
{
   return m_prompting.setting();
}

//
// static member functions
//
