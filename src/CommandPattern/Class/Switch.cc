// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Switch
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Sat Feb 20 14:14:52 EST 1999
// $Id: Switch.cc,v 1.2 1999/06/23 04:35:48 mkl Exp $
//
// Revision history
//
// $Log: Switch.cc,v $
// Revision 1.2  1999/06/23 04:35:48  mkl
// added 'toBoolean' method to Switch class
//
// Revision 1.1  1999/02/22 23:40:44  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/Switch.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "CommandPattern.Switch" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: Switch.cc,v 1.2 1999/06/23 04:35:48 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
Switch::Switch( OnOff iDefault )
   : m_switch( iDefault ) 
{
}

// Switch::Switch( const Switch& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

Switch::~Switch()
{
}

//
// assignment operators
//
// const Switch& Switch::operator=( const Switch& rhs )
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
Switch::turn( OnOff iOn ) 
{ 
   m_switch = iOn; 
   return m_switch; 
}

//
// const member functions
//
Switch::OnOff 
Switch::setting() const 
{ 
   return m_switch; 
}

//
// static member functions
//
string
Switch::toString( OnOff iSetting )
{
   string result = (kOn == iSetting )?"on":"off";
   return result;
}
   
DABoolean
Switch::toBoolean( OnOff iSetting )
{
   DABoolean result = (kOn == iSetting )?true:false;
   return result;
}
   
Switch::OnOff
Switch::toSwitch( const string& iSettingString )
{
   // default setting is ON
   Switch::OnOff returnValue( kOn );

   if(    iSettingString == string( "on" )
       || iSettingString == string( "ON" )
      ) 
   {
      returnValue = kOn;
   } else 
   if(    iSettingString == string( "off" )
       || iSettingString == string( "OFF" )
      )
   {
      returnValue = kOff;
   }
   else
   {
      report( ERROR, kFacilityString )
	 << "bad argument: 'on/off' only! Will set to ON" << endl;
   }
   
   return returnValue;
}
   
