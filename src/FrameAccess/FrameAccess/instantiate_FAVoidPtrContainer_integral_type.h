#if !defined(FRAMEACCESS_INSTANTIATE_FAVOIDPTRCONTAINER_INTEGRAL_TYPE_H)
#define FRAMEACCESS_INSTANTIATE_FAVOIDPTRCONTAINER_INTEGRAL_TYPE_H
// -*- C++ -*-
//
// Package:     <FrameAccess>
// Module:      instantiate_FAVoidPtrContainer
// 
/**\class instantiate_FAVoidPtrContainer instantiate_FAVoidPtrContainer.h FrameAccess/instantiate_FAVoidPtrContainer.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Thu Nov  2 14:07:20 EST 2000
// $Id: instantiate_FAVoidPtrContainer_integral_type.h,v 1.3 2002/06/04 18:31:55 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_FAVoidPtrContainer_integral_type.h,v $
// Revision 1.3  2002/06/04 18:31:55  cleo3
// changed SUNCC cpp switch to AUTO_INSTANTIATE_TEMPLATE_BUG
//
// Revision 1.2  2000/12/27 20:57:35  cdj
// workaround for Solaris auto template instantiation bug
//
// Revision 1.1  2000/11/02 21:30:50  cdj
// first submission
//

// system include files


// user include files
#include "FrameAccess/FAVoidPtrContainer.h"

typedef pair<_favoidptrcontainer_integral_type_, void*> _vector_contents_;
#include "STLUtility/instantiate_vector.h"

#if defined(AUTO_INSTANTIATE_TEMPLATE_BUG)
template class pair<_favoidptrcontainer_integral_type_,void*>;
template class allocator<pair<_favoidptrcontainer_integral_type_,void*> >;
#endif

typedef STD_PREFIX vector< STD_PREFIX pair<_favoidptrcontainer_integral_type_, void*> >::iterator _lower_bound_iterator_;
typedef FAVoidPtrIntegralIdContainer<_favoidptrcontainer_integral_type_>::PairFirstCompare _lower_bound_compare_;
#include "STLUtility/instantiate_lower_bound_with_compare.h"


#endif /* FRAMEACCESS_INSTANTIATE_FAVOIDPTRCONTAINER_INTEGRAL_TYPE_H */
