#if !defined(HETEROCONTAINER_HCMETHODS_CC)
#define HETEROCONTAINER_HCMETHODS_CC
// -*- C++ -*-
//
// Package:     <HeteroContainer>
// Module:      HCMethods
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D. Jones
// Created:     Sun Sep 20 16:03:32 EDT 1998
// $Id: HCMethods.cc,v 1.3 2002/06/04 18:23:17 cleo3 Exp $
//
// Revision history
//
// $Log: HCMethods.cc,v $
// Revision 1.3  2002/06/04 18:23:17  cleo3
// replaced SUNCC switch with STATIC_LOCAL_VARIABLE_IN_TEMPLATE_FUNC_BUG
//
// Revision 1.2  1998/10/20 18:06:36  cdj
// modified so .cc file can not be multiply included
//
// Revision 1.1.1.1  1998/09/23 14:13:12  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "HeteroContainer/HCMethods.h"
#include "HeteroContainer/HCTypeTagTemplate.h"

// STL classes

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
//HCMethods::HCMethods()
//{
//}

// HCMethods::HCMethods( const HCMethods& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//HCMethods::~HCMethods()
//{
//}

//
// assignment operators
//
// const HCMethods& HCMethods::operator=( const HCMethods& rhs )
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
template< class Type, class ItemType, class Storage, class Key, class IdTag >
Key
HCMethods< Type, ItemType, Storage, Key, IdTag >::makeKey( const IdTag& iIdTag)
{
#if !defined(STATIC_LOCAL_VARIABLE_IN_TEMPLATE_FUNC_BUG)
   static HCTypeTag< Key > typeTag = HCTypeTagTemplate<Type, Key>();
   return Key( typeTag, iIdTag );
#else
   return Key( HCTypeTagTemplate<Type, Key>(), iIdTag );
#endif
}

template< class Type, class ItemType, class Storage, class Key, class IdTag >
DABoolean
HCMethods< Type, ItemType, Storage, Key, IdTag >::insert(
   Storage& iStorage, ItemType* iItem, const IdTag& iIdTag )
{
   return iStorage.insert( makeKey( iIdTag ) , iItem );
}

template< class Type, class ItemType, class Storage, class Key, class IdTag >
ItemType*
HCMethods< Type, ItemType, Storage, Key, IdTag >::find(
   const Storage& iStorage, const IdTag& iIdTag )
{
   //The cast should be safe since the Key tells us the type
   return ( ItemType* ) iStorage.find( makeKey( iIdTag ) );
}
#endif /* HETEROCONTAINER_HCMETHODS_CC */
