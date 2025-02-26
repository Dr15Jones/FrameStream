#if !defined(FRAMEACCESS_VALUEPROXY_CC)
#define FRAMEACCESS_VALUEPROXY_CC
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      ValueProxy
// 
// Description: Templated implementation of Proxy for holding a value.
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Thu Dec 11 15:49:54 EDT 1997
// $Id: ValueProxy.cc,v 1.3 1998/09/25 19:58:10 cdj Exp $
//
// Revision history
//
// $Log: ValueProxy.cc,v $
// Revision 1.3  1998/09/25 19:58:10  cdj
// no longer use ProxyDict
//
// Revision 1.2  1998/09/16 21:36:33  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.1  1997/12/11 23:11:03  mkl
// new files insert and ValueProxy
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>  // For 'exit'

// user include files
#include "Experiment/report.h" // For error report
#include "DataHandler/Record.h"

#include "FrameAccess/ValueProxy.h"

// STL classes

//
// constants, enums and typedefs
//

FILESCOPE_IN_TEMPLATE_CC_BUG string kValueProxyFacilityString 
= "FrameAccess.ValueProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//

template < class T >
ValueProxy< T >::ValueProxy( const T* value )
   : m_ptr( value )
{
}

template < class T >
ValueProxy< T >::~ValueProxy()
{
   // have to cast const away to be able to delete it
   delete (T*)m_ptr ;
}

//
// member functions
//

template < class T >
void
ValueProxy< T >::invalidateCache()
{
   delete (T*)m_ptr ;
   m_ptr = 0 ;
}

template < class T >
const T*
ValueProxy< T >::faultHandler( const Record& aDict ,
			       const DataKey& )
{
   return( m_ptr );
}

//
// const member functions
//

//
// static member functions
//

#endif /* FRAMEACCESS_VALUEPROXY_CC */
