// -*- C++ -*-
//
// Package:     _package_
// Module:      _helper_
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: _helper_.cc,v 1.3 2001/01/31 22:16:06 cdj Exp $
//
// Revision history
//
// $Log: _helper_.cc,v $
// Revision 1.3  2001/01/31 22:16:06  cdj
// added reminder to users in storage routine to register new versions
//
// Revision 1.2  2000/01/21 21:07:37  cdj
// helper skeletons now include SMPackInfo.h
//
// Revision 1.1  1999/10/18 18:13:04  cdj
// first submission
//
// Revision 1.2  1999/09/30 22:38:33  cdj
// no longer need default constructor
//
// Revision 1.1.1.1  1999/09/13 21:21:45  cdj
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
#include "_package_/_helper_.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMPackInfo.h" //defines sm_pack*

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

static const char* const kFacilityString = "_package_._helper_" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: _helper_.cc,v 1.3 2001/01/31 22:16:06 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
_helper_::_helper_()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &_helper_::deliverV1 );
}

// _helper_::_helper_( const _helper_& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//_helper_::~_helper_()
//{
//}

//
// assignment operators
//
// const _helper_& _helper_::operator=( const _helper_& rhs )
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
void 
_helper_::implementStore( 
   SMSinkStream& iSink,
   const _class_& iData ) 
{
// NOTE: Any change (adding/removing variable OR packing info) to this routine
//    MUST be accompanied by registering a new version deliver routine in
//    this class's constructor.  
//    If only the packing info is changes, you can register the same deliver
//    routine a second time.

   iSink 
      << SM_VAR( iData, _var_name_ )  _var_loop_ 
      ;
}

_class_* 
_helper_::deliverV1( SMSourceStream& iSource )
{
   
   _var_type_ _var_name_; _var_loop_

   iSource 
      >> _var_name_ _var_loop_
	 ;
   
   return make( _class_( 
      _var_name_, _var_most_loop_ 
      _var_name_ ) ); _var_end_loop
}

//
// const member functions
//
const _class_& 
_helper_::getDefault() const
{
   //give constructor unique values to allow test of store and deliver 
   // functions
   static const _class_ temp(
      _var_type_ ( _var_index_ ), // _var_name_ _var_most_loop_
      _var_type_ ( _var_index_ ) ); // _var_name_ _var_end_loop
   return temp;
}

DABoolean 
_helper_::compare( 
   const _class_* iNewData, 
   const _class_& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for _class_
   return (*iNewData == iOldData ) ;
}

//
// static member functions
//

//_class_*
//SMStorageHelper<_class_>::make( const _class_& iTempData ) const
//{
   //change this line if _class_ does not have a copy constructor
//   return new _class_( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
SM_REGISTER_STORAGE( _helper_ );

#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( _helper_, _class_ )

//this is done to create a TypeTag and its name
#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE(_class_)
#include "StorageManagement/instantiate_one_typetag.h"

#include "StorageManagement/Template/SMStorageHelper.cc"
template class SMStorageHelper<_class_>;

//------------------------------------------------------
