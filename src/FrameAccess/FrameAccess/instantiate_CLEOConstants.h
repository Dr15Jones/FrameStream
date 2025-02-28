#if !defined(FRAMEACCESS_INSTANTIATE_CLEOCONSTANTS_H)
#define FRAMEACCESS_INSTANTIATE_CLEOCONSTANTS_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate a templates needed
//               to read a CLEOConstants<> from the Frame 
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris Jones
// Created:     Sat May 25 14:32:44 EDT 1996
// $Id: instantiate_CLEOConstants.h,v 1.1 1999/05/07 01:26:31 cdj Exp $
//
// Revision history
//
// $Log: instantiate_CLEOConstants.h,v $
// Revision 1.1  1999/05/07 01:26:31  cdj
// Added smart pointers for Constants access
//
//

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */

#include "FrameAccess/FAConstants.h"

#include "HeteroContainer/Template/HCTypeTagTemplate.cc"
#include "DataHandler/Template/ProxyTemplate.cc"
#include "DataHandler/Template/RecordMethods.cc"
#include "HeteroContainer/Template/HCMethods.cc"

#include "FrameAccess/Template/ValueProxy.cc"
#include "FrameAccess/Template/insert.cc"
#include "DataHandler/DataField.h"

typedef CLEOConstants< _constant_element_ > _cleoConstants_element_ ;

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP
#  pragma define_template HCTypeTagTemplate< _cleoConstants_element_, DataKey >
#  pragma define_template ProxyTemplate< _cleoConstants_element_ >
#  pragma define_template DataField< _cleoConstants_element_ >
#  pragma define_template RecordMethods< _cleoConstants_element_ >
#  pragma define_template HCMethods< _cleoConstants_element_ , ProxyTemplate< _cleoConstants_element_ >, Record, DataKey, IdTags >

#  pragma define_template ValueProxy< _cleoConstants_element_ >
#  pragma define_template insert< _cleoConstants_element_ >
#else
template class HCTypeTagTemplate< _cleoConstants_element_ , DataKey > ;
template class ProxyTemplate< _cleoConstants_element_ > ;
template class DataField< _cleoConstants_element_ > ;
template class RecordMethods< _cleoConstants_element_ > ;
template class HCMethods< _cleoConstants_element_, ProxyTemplate< _cleoConstants_element_>, Record, DataKey, IdTags > ;

template class ValueProxy< _cleoConstants_element_ > ;

#if defined(NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG)

template DABoolean 
insert< _cleoConstants_element_ >( Frame& aFrame,
			      const _cleoConstants_element_* aValue ,
			      const char* aUseLabel,
			      const char* aProducerLabel );
// not used for now because of Producer dependencies
//template DABoolean insert< _cleoConstants_element_ >( Frame& aFrame,
//					    _cleoConstants_element_* aValue,
//					    const char* const aUseLabel, 
//					    const Producer& producer );
#else

template DABoolean insert( Frame& aFrame,
			   const _cleoConstants_element_* aValue ,
			   const char* aUseLabel,
			   const char* aProducerLabel );

// not used for now because of Producer dependencies
//template DABoolean insert( Frame& aFrame,
//			   _cleoConstants_element_* aValue,
//			   const char* aUseLabel, 
//			   const Producer& producer );
#endif /* NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG */

#endif /* (defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX)) */

#endif /* FRAMEACCESS_INSTANTIATE_CLEOCONSTANTS_H */
