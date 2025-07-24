// -*- C++ -*-
//
// Package:     <package>
// Module:      T_vector_bool
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D. Jones
// Created:     Wed Nov 18 11:15:20 EST 1998
// $Id: T_vector_bool.cc,v 1.2 1998/11/18 19:37:22 cdj Exp $
//
// Revision history
//
// $Log: T_vector_bool.cc,v $
// Revision 1.2  1998/11/18 19:37:22  cdj
// cxx 6.1 only works if instantiate helper templates
//
// Revision 1.1  1998/11/18 16:24:16  cdj
// first submission (needed for cxx 6.1)
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"

// STL classes

#if !defined(BOOL_NOT_DEFINED_BUG)
typedef bool _vector_contents_ ;
#include <vector>
#include <vector>
//#include "STLUtility/instantiate_vector.h"

#if ( defined(NO_IMPLICIT_INSTANTIATION) && defined(__DECCXX) )

#define vec_iterator std::vector< _vector_contents_ >::iterator

template vec_iterator std::copy( vec_iterator, 
				 vec_iterator, 
				 vec_iterator );

template vec_iterator std::copy_backward( vec_iterator ,  
					  vec_iterator ,
					  vec_iterator );
template void std::fill( vec_iterator ,  
		         vec_iterator ,
		    _vector_contents_ const& );

template void std::fill_n( vec_iterator, 
			   unsigned long, 
			   _vector_contents_ const& );
#endif

#endif
