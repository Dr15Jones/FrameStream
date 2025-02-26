#if !defined(FRAMEACCESS_INSTANTIATE_ONE_H)
#define FRAMEACCESS_INSTANTIATE_ONE_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate a "One" Data element
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Sat May 25 14:32:44 EDT 1996
// $Id: instantiate_one.h,v 1.12 1998/09/30 15:44:48 cdj Exp $
//
// Revision history
//
// $Log: instantiate_one.h,v $
// Revision 1.12  1998/09/30 15:44:48  cdj
// includes HCTypeTagTemplate.cc
//
// Revision 1.11  1998/09/25 19:57:59  cdj
// no longer use ProxyDict
//
// Revision 1.10  1998/04/22 21:27:17  mkl
// fix for wrong file inclusion
//
// Revision 1.9  1998/04/22 20:24:02  mkl
// extracted out FAItem/Table instantiations into their own file
//
// Revision 1.8  1998/03/06 15:28:10  mkl
// correction of (commented out) insert instantiations involving producer label
//
// Revision 1.7  1998/02/14 21:42:03  mkl
// merge insert instantiations with extract
//
// Revision 1.6  1998/01/13 23:45:09  mkl
// added DataField instantiation
//
// Revision 1.5  1997/12/20 20:04:19  cleo3
// now use Producer label for insert/extract
//
// Revision 1.4  1997/12/12 22:55:39  mkl
// changed const*const to const* for label in extract
//
// Revision 1.3  1997/12/11 23:10:12  mkl
// bug fixes to new files extract, insert etc.
//
// Revision 1.2  1997/12/09 01:13:59  mkl
// Extractor --> extract
//
// Revision 1.1  1997/12/05 03:04:14  mkl
// moved sources from DataHandler
//
// Revision 1.2  1997/08/14 11:43:00  sjp
// Mods to run under CW Pro 1
//
// Revision 1.1  1997/08/06 15:01:11  sjp
// New file is instantiate single items
//

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */

#include "FrameAccess/Template/FAItem.cc"

#include "HeteroContainer/Template/HCTypeTagTemplate.cc"
#include "DataHandler/Template/ProxyTemplate.cc"
#include "DataHandler/Template/RecordMethods.cc"
#include "HeteroContainer/Template/HCMethods.cc"

#include "FrameAccess/Template/extract.cc"
#include "FrameAccess/Template/insert.cc"
#include "FrameAccess/Template/ValueProxy.cc"

#include "DataHandler/DataField.h"

typedef FAItem< _one_element_ > _item_element_ ;

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP

#  pragma define_template HCTypeTagTemplate< _one_element_, DataKey >
#  pragma define_template ProxyTemplate< _one_element_ >
#  pragma define_template DataField< _one_element_ >
#  pragma define_template RecordMethods< _one_element_ >
#  pragma define_template HCMethods< _one_element_ , ProxyTemplate< _one_element_ > , Record, DataKey, IdTags >

#  pragma define_template extract< _item_element_ >

#  pragma define_template ValueProxy< _one_element_ >
#  pragma define_template insert< _one_element_ >
#else

template class HCTypeTagTemplate< _one_element_ , DataKey  > ;
template class ProxyTemplate< _one_element_ > ;
template class DataField< _one_element_ > ;
template class RecordMethods< _one_element_ > ;
template class HCMethods< _one_element_,
                          ProxyTemplate< _one_element_ >,
                          Record,
                          DataKey,
                          IdTags > ;

template class ValueProxy< _one_element_ > ;

#if defined(NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG)
template void extract< _item_element_ >( const Record& aRecord ,
					 _item_element_& aContainer ) ;
template void extract< _item_element_ >( const Record& aRecord ,
					 _item_element_& aContainer ,
					 const char* aUseLabel );
template void extract< _item_element_ >( const Record& aRecord ,
					 _item_element_& aContainer ,
					 const char* aUseLabel ,
					 const char* aProducerLabel );

template DABoolean insert< _one_element_ >( Frame& aFrame,
					    const _one_element_* aValue ,
					    const char* aUseLabel,
					    const char* aProducerLabel );

// not used for now because of Producer dependencies
//template DABoolean insert< _one_element_ >( Frame& aFrame,
//					    _one_element_* aValue,
//					    const char* const aUseLabel, 
//					    const Producer& producer );
#else
template void extract( const Record& aRecord ,
		       _item_element_& aContainer ) ;
template void extract( const Record& aRecord ,
		       _item_element_& aContainer ,
		       const char* aUseLabel );
template void extract( const Record& aRecord ,
		       _item_element_& aContainer ,
		       const char* aUseLabel ,
		       const char* aProducerLabel );

template DABoolean insert( Frame& aFrame,
			   const _one_element_* aValue ,
			   const char* aUseLabel,
			   const char* aProducerLabel );

// not used for now because of Producer dependencies
//template DABoolean insert( Frame& aFrame,
//			   _one_element_* aValue,
//			   const char* aUseLabel, 
//			   const Producer& producer );
#endif /* NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG */

#endif /* (defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX)) */


// --- and last but not least the FAItem instantiations ---
#include "FrameAccess/instantiate_FAItem.h"

#endif /* FRAMEACCESS_INSTANTIATE_ONE_H */
