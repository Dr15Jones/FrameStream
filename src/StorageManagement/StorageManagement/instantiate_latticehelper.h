#if !defined(STORAGEMANAGEMENT_INSTANTIATE_LATTICEHELPER_H)
#define STORAGEMANAGEMENT_INSTANTIATE_LATTICEHELPER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      instantiate_latticehelper
// 
// Description: instantiate all the templates needed to store a Lattice
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Tue Sep 14 18:18:53 EDT 1999
// $Id: instantiate_latticehelper.h,v 1.3 2002/06/12 20:09:13 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_latticehelper.h,v $
// Revision 1.3  2002/06/12 20:09:13  cleo3
// updated to new template specialization syntax
//
// Revision 1.2  1999/10/18 18:27:33  cdj
// updated to work with new design of its class
//
// Revision 1.1  1999/10/11 22:00:44  cdj
// added Lattice storage code
//

// system include files

// user include files


#include "StorageManagement/Template/SMLatticeStorageHelper.cc"
template class SMLatticeStorageHelper< _lattice_element_ >;

//forward decleration to stop autoinstantiation
template<>
_lattice_element_*
SMStorageHelper<_lattice_element_>::make( const _lattice_element_& iData ) const {
   //copy one to the other
   return new _lattice_element_ (
      ( iData.isLNodeMulti() ? _lattice_element_::LNodeMulti :
	_lattice_element_::Default ),
      ( iData.isRNodeMulti() ? _lattice_element_::RNodeMulti :
	_lattice_element_::Default ),
      ( iData.isLLinkMulti() ? _lattice_element_::LLinkMulti :
	_lattice_element_::Default ),
      ( iData.isRLinkMulti() ? _lattice_element_::RLinkMulti :
	_lattice_element_::Default )
      );
}

#if defined(SUNCC)
# if !defined(CANNOT_STOP_AUTOINSTANTIATION)
#  define CANNOT_STOP_AUTOINSTANTIATION
# endif 
#endif
#if defined(CANNOT_STOP_AUTOINSTANTIATION)
//need to include this to avoid autoinstantiation of default function
template<>
SMLatticeLinkInfoBase< _lattice_element_ >*
SMStorageHelper<SMLatticeLinkInfoBase< _lattice_element_ > >::make( const SMLatticeLinkInfoBase< _lattice_element_ >& iTable ) const {
   //copy one to the other
   assert(false);
   return new SMLatticeLinkInfoIn<_lattice_element_>;
}
#endif

#include "StorageManagement/Template/SMStorageHelper.cc"
template class SMStorageHelper<_lattice_element_ >;

#include "StorageManagement/Template/SMStorageProxyHelper.cc"
template class SMStorageProxyHelper<_lattice_element_ >;

#include "StorageManagement/Template/SMProxyWriter.cc"
template class SMProxyWriter<_lattice_element_ >;

#include "StorageManagement/Template/SMContents.cc"
template class SMContents<LatticeOutputItr<_lattice_element_> >;

template<>
const TypeTag&
SMFillContents<LatticeInsertItr<_lattice_element_> >::getTypeTag()
{
   static const TypeTag tag = RecordMethods< 
      SMLatticeLinkInfoBase<_lattice_element_> >::makeKey("","").type() ;
   return tag;
}

#include "StorageManagement/Template/SMMakeContents.cc"
template class SMMakeContents<LatticeInsertItr<_lattice_element_> >;

#endif /* STORAGEMANAGEMENT_INSTANTIATE_LATTICEHELPER_H */
