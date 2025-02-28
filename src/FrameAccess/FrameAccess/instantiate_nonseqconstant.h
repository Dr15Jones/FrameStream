#if !defined(FRAMEACCESS_INSTANTIATE_NONSEQCONSTANT_H)
#define FRAMEACCESS_INSTANTIATE_NONSEQCONSTANT_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      Instantiation
// 
// Description: Code required to extract using a FANonSeqConstants
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Sat May 25 14:32:44 EDT 1996
// $Id: instantiate_nonseqconstant.h,v 1.1 1999/05/07 01:26:33 cdj Exp $
//
// Revision history
//
// $Log: instantiate_nonseqconstant.h,v $
// Revision 1.1  1999/05/07 01:26:33  cdj
// Added smart pointers for Constants access
//
//

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */

#include "FrameAccess/FANonSeqConstants.h"

#include "FrameAccess/Template/extract.cc"

typedef FANonSeqConstants< _constant_element_ > _nonseqconstants_element_ ;


#if defined(NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG)
template void extract< _nonseqconstants_element_ >( const Record& aRecord ,
					  _nonseqconstants_element_& aContainer ) ;
template void extract< _nonseqconstants_element_ >( const Record& aRecord ,
					  _nonseqconstants_element_& aContainer ,
					  const char* aUseLabel ) ;
template void extract< _nonseqconstants_element_ >( const Record& aRecord ,
					  _nonseqconstants_element_& aContainer ,
					  const char* aUseLabel ,
					  const char* aProducerLabel ) ;

#else
template void extract( const Record& aRecord ,
		       _nonseqconstants_element_& aContainer ) ;
template void extract( const Record& aRecord ,
		       _nonseqconstants_element_& aContainer ,
		       const char* aUseLabel ) ;
template void extract( const Record& aRecord ,
		       _nonseqconstants_element_& aContainer ,
		       const char* aUseLabel ,
		       const char* aProducerLabel ) ;

#endif /* NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG */

//also instantiate all the stuff that knows about CLEOConstants
#include "FrameAccess/instantiate_CLEOConstants.h"

#endif /* FRAMEACCESS_INSTANTIATE_NONSEQCONSTANT_H */
