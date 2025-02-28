#if !defined(FRAMEACCESS_INSTANTIATE_MANY_H)
#define FRAMEACCESS_INSTANTIATE_MANY_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate a "Many" Data element
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Sat May 25 14:32:44 EDT 1996
// $Id: instantiate_many.h,v 1.12 2002/04/03 19:08:33 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_many.h,v $
// Revision 1.12  2002/04/03 19:08:33  cleo3
// provide more control on extactly what gets instantiated
//
// Revision 1.11  1998/09/30 15:44:48  cdj
// includes HCTypeTagTemplate.cc
//
// Revision 1.10  1998/09/25 19:57:57  cdj
// no longer use ProxyDict
//
// Revision 1.9  1998/04/22 20:24:01  mkl
// extracted out FAItem/Table instantiations into their own file
//
// Revision 1.8  1998/03/06 15:27:04  mkl
// added insert instantiations for multiply-occuring items
//
// Revision 1.7  1998/02/06 20:39:04  mkl
// left-over edits for switch to STLUtility
//
// Revision 1.6  1998/01/16 21:08:22  mkl
// added DataHandler to list of instantiables
//
// Revision 1.5  1997/12/21 17:33:33  cleo3
// typo fix
//
// Revision 1.4  1997/12/20 20:04:19  cleo3
// now use Producer label for insert/extract
//
// Revision 1.3  1997/12/12 22:55:38  mkl
// changed const*const to const* for label in extract
//
// Revision 1.2  1997/12/09 01:13:58  mkl
// Extractor --> extract
//
// Revision 1.1  1997/12/05 03:04:11  mkl
// moved sources from DataHandler
//
// Revision 1.3  1997/09/10 14:14:49  sjp
// Changed FAItr to be FATableItr
//
// Revision 1.2  1997/08/14 11:42:58  sjp
// Mods to run under CW Pro 1
//
// Revision 1.1  1997/08/06 15:01:28  sjp
// New file is instantiate multiple items
//

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */

#include "FrameAccess/Template/FAItem.cc"
#include "FrameAccess/Template/FATableItr.cc"
#include "FrameAccess/Template/FAPtrTable.cc"
#include "FrameAccess/Template/FATable.cc"

#include "HeteroContainer/Template/HCTypeTagTemplate.cc"
#include "DataHandler/Template/ProxyTemplate.cc"
#include "DataHandler/Template/RecordMethods.cc"
#include "HeteroContainer/Template/HCMethods.cc"

#include "FrameAccess/Template/extract.cc"
#if !defined(DO_NOT_INSTANTIATE_INSERT)
#include "FrameAccess/Template/insert.cc"
#include "FrameAccess/Template/ValueProxy.cc"
#endif

#include "DataHandler/DataField.h"

typedef FAPtrTable< _many_element_ > _ptrTable_element_ ;
typedef FATable< _many_element_ > _table_element_ ;

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP
#  pragma define_template HCTypeTagTemplate< _ptrTable_element_, DataKey >
#  pragma define_template ProxyTemplate< _ptrTable_element_ >
#  pragma define_template DataField< _ptrTable_element_ >
#  pragma define_template RecordMethods< _ptrTable_element_ >
#  pragma define_template HCMethods< _ptrTable_element_ , ProxyTemplate< _ptrTable_element_ >, Record, DataKey, IdTags >
#  pragma define_template extract< _table_element_ >

#if !defined(DO_NOT_INSTANTIATE_INSERT)
#  pragma define_template ValueProxy< _ptrTable_element_ >
#  pragma define_template insert< _ptrTable_element_ >
#endif
#else
template class HCTypeTagTemplate< _ptrTable_element_ , DataKey > ;
template class ProxyTemplate< _ptrTable_element_ > ;
template class DataField< _ptrTable_element_ > ;
template class RecordMethods< _ptrTable_element_ > ;
template class HCMethods< _ptrTable_element_, ProxyTemplate< _ptrTable_element_>, Record, DataKey, IdTags > ;

#if !defined(DO_NOT_INSTANTIATE_INSERT)
template class ValueProxy< _ptrTable_element_ > ;
#endif

#if defined(NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG)
template void extract< _table_element_ >( const Record& aRecord ,
					  _table_element_& aContainer ) ;
template void extract< _table_element_ >( const Record& aRecord ,
					  _table_element_& aContainer ,
					  const char* aUseLabel ) ;
template void extract< _table_element_ >( const Record& aRecord ,
					  _table_element_& aContainer ,
					  const char* aUseLabel ,
					  const char* aProducerLabel ) ;

#if !defined(DO_NOT_INSTANTIATE_INSERT)
template DABoolean 
insert< _ptrTable_element_ >( Frame& aFrame,
			      const _ptrTable_element_* aValue ,
			      const char* aUseLabel,
			      const char* aProducerLabel );
#endif
// not used for now because of Producer dependencies
//template DABoolean insert< _ptrTable_element_ >( Frame& aFrame,
//					    _ptrTable_element_* aValue,
//					    const char* const aUseLabel, 
//					    const Producer& producer );
#else
template void extract( const Record& aRecord ,
		       _table_element_& aContainer ) ;
template void extract( const Record& aRecord ,
		       _table_element_& aContainer ,
		       const char* aUseLabel ) ;
template void extract( const Record& aRecord ,
		       _table_element_& aContainer ,
		       const char* aUseLabel ,
		       const char* aProducerLabel ) ;

#if !defined(DO_NOT_INSTANTIATE_INSERT)
template DABoolean insert( Frame& aFrame,
			   const _ptrTable_element_* aValue ,
			   const char* aUseLabel,
			   const char* aProducerLabel );
#endif
// not used for now because of Producer dependencies
//template DABoolean insert( Frame& aFrame,
//			   _ptrTable_element_* aValue,
//			   const char* aUseLabel, 
//			   const Producer& producer );
#endif /* NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG */

#endif /* (defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX)) */


// --- and last but not least the FATable instantiations ---
#include "FrameAccess/instantiate_FATable.h"

#endif /* FRAMEACCESS_INSTANTIATE_MANY_H */
