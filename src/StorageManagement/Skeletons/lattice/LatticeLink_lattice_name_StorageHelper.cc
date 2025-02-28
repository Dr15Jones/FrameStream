// -*- C++ -*-
//
// Package:     <package>
// Module:      _lattice_name_StorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed Oct  6 10:45:44 EDT 1999
// $Id: LatticeLink_lattice_name_StorageHelper.cc,v 1.5 2003/04/04 21:34:44 cdj Exp $
//
// Revision history
//
// $Log: LatticeLink_lattice_name_StorageHelper.cc,v $
// Revision 1.5  2003/04/04 21:34:44  cdj
// added compile time checking of data in deliver function matches type stored
//
// Revision 1.4  2001/01/31 22:16:03  cdj
// added reminder to users in storage routine to register new versions
//
// Revision 1.3  2000/01/21 21:07:34  cdj
// helper skeletons now include SMPackInfo.h
//
// Revision 1.2  2000/01/08 19:18:08  cdj
// updated Lattice code to work with new cxx compiler
//
// Revision 1.1  1999/10/18 21:30:18  cdj
// renamed files
//
// Revision 1.2  1999/10/18 18:16:45  cdj
// easier to use and maintain
//
// Revision 1.1  1999/10/11 22:00:36  cdj
// added Lattice storage code
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <iterator>

// user include files
#include "Experiment/report.h"
#include "_package_/LatticeLink_lattice_name_StorageHelper.h"

#include "StorageManagement/SMLatticeLinkInfoIn.h"
#include "StorageManagement/SMLatticeLinkInfoOut.h"
#include "StorageManagement/SMLatticeLinkInfoDefault.h"

#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMContents.h"
#include "StorageManagement/SMContentsBuiltIn.h"
#include "StorageManagement/SMFillContents.h"

#include "StorageManagement/SMPackInfo.h" //defines sm_pack*

#include "StorageManagement/SMDeliverer.h"

#include "StorageManagement/smTestReturnTypeMatchesVariable.h"

// STL classes
#include <vector>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "package.LatticeLink_lattice_name_StorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: LatticeLink_lattice_name_StorageHelper.cc,v 1.5 2003/04/04 21:34:44 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//Simplify some names
typedef _lattice_name_::VectorLeftID LeftIDs;
typedef _lattice_name_::VectorRightID RightIDs;

//
// static data member definitions
//

//
// constructors and destructor
//
LatticeLink_lattice_name_StorageHelper::LatticeLink_lattice_name_StorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &LatticeLink_lattice_name_StorageHelper::deliverV1 );
}

// LatticeLink_lattice_name_StorageHelper::LatticeLink_lattice_name_StorageHelper( const LatticeLink_lattice_name_StorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

LatticeLink_lattice_name_StorageHelper::~LatticeLink_lattice_name_StorageHelper()
{
}

//
// assignment operators
//
// const LatticeLink_lattice_name_StorageHelper& LatticeLink_lattice_name_StorageHelper::operator=( const LatticeLink_lattice_name_StorageHelper& rhs )
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
LatticeLink_lattice_name_StorageHelper::implementStore( 
   SMSinkStream& iSink,
   const SMLatticeLinkInfoBase< _lattice_name_ >& iData ) 
{
// NOTE: Any change (adding/removing variable OR packing info) to this routine
//    MUST be accompanied by registering a new version deliver routine in
//    this class's constructor.  
//    If only the packing info is changes, you can register the same deliver
//    routine a second time.

   const LeftIDs& leftIDs = iData.vLeftID();
   const RightIDs& rightIDs = iData.vRightID();

   //store the left and right ids
   iSink << sm_field( "leftIDs", sm_contents_builtin( leftIDs.begin(), 
						      leftIDs.end() ))
	 << sm_field( "rightIDs", sm_contents_builtin( rightIDs.begin(), 
						       rightIDs.end() ) )
      //store info from link data
	 << SM_VAR( iData, linkData()._var_name_ ) _var_loop_ 
      ;
}

SMLatticeLinkInfoBase< _lattice_name_ >* 
LatticeLink_lattice_name_StorageHelper::deliverV1( SMSourceStream& iSource )
{
   SMLatticeLinkInfoBase< _lattice_name_ >* link = 
      new SMLatticeLinkInfoIn< _lattice_name_>();

   //first read the left and right IDs
   _lattice_name_::VectorLeftID leftIDs;
   _lattice_name_::VectorRightID rightIDs;
   
   back_insert_iterator<LeftIDs> leftInsertIterator( leftIDs );
   back_insert_iterator<RightIDs> rightInsertIterator( rightIDs );

   iSource >> sm_fill_contents( leftInsertIterator )
	   >> sm_fill_contents( rightInsertIterator ) ;

   //now read data for the LinkData
   //NOTE: variable type must match type used to store data
   _var_type_ _var_name_; TEST_RETURN_TYPE(_lattice_name_::LinkData,_var_name_); _var_loop_

   iSource 
      >> _var_name_ _var_loop_
      ;
   _lattice_name_::LinkData linkData = 
      _lattice_name_::LinkData( 
	 _var_name_,  _var_most_loop_ 
	 _var_name_  _var_end_loop
	 );
   //Add all the information to the link
   link->set( leftIDs, linkData, rightIDs );
   return link;
}

//
// const member functions
//
const SMLatticeLinkInfoBase< _lattice_name_ >& 
LatticeLink_lattice_name_StorageHelper::getDefault() const
{
   static const SMLatticeLinkInfoDefault< _lattice_name_ > 
      temp(  LeftIDs(1,LeftIDs::value_type(1)),
	     _lattice_name_::LinkData(
		_var_type_ ( _var_index_ ), // _var_name_ _var_most_loop_
		_var_type_ ( _var_index_ )  // _var_name_ _var_end_loop
		),
	     RightIDs(1,RightIDs::value_type(1)) );
   return temp;
}

DABoolean 
LatticeLink_lattice_name_StorageHelper::compare( 
   const SMLatticeLinkInfoBase< _lattice_name_ >* iNewData, 
   const SMLatticeLinkInfoBase< _lattice_name_ >& iOldData ) const
{
   //need to compare contents
   return ( 
            (iNewData->linkData() == iOldData.linkData() ) &&
// comment out the line above and uncomment the lines below if operator==
// does not exist for the link data
      //    (iNewData->linkData()._var_name_() == iOldData.linkData()._var_name_() ) && _var_loop_
	    (iNewData->vLeftID() == iOldData.vLeftID() ) &&
	    (iNewData->vRightID() == iOldData.vRightID() ) );
}

//
// static member functions
//

//------------------------------------------------------------------------
// DO NOT DELETE
SM_REGISTER_STORAGE( LatticeLink_lattice_name_StorageHelper );

//this is done to create a TypeTag and its name
#include "FrameAccess/instantiate_macros.h"
typedef SMLatticeLinkInfoBase< _lattice_name_ > _lattice_name_Link;
INSTANTIATE_ONE( _lattice_name_Link )
#include "StorageManagement/instantiate_one_typetag.h"

#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( LatticeLink_lattice_name_StorageHelper, SMLatticeLinkInfoBase< _lattice_name_ > )

typedef _lattice_name_ _lattice_element_;
#include "StorageManagement/instantiate_latticelinkhelper.h"



