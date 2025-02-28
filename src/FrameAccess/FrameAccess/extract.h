#if !defined(FRAMEACCESS_EXTRACTOR_H)
#define FRAMEACCESS_EXTRACTOR_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      extract
// 
// Description: Template for standard extract
//
// Usage:
//    <usage>
//
// Author:      Simon Patton
// Created:     Mon Apr 14 11:22:11 EDT 1997
// $Id: extract.h,v 1.5 1998/04/09 23:19:37 cleo3 Exp $
//
// Revision history
//
// $Log: extract.h,v $
// Revision 1.5  1998/04/09 23:19:37  cleo3
// port to egcs
//
// Revision 1.4  1997/12/20 20:04:17  cleo3
// now use Producer label for insert/extract
//
// Revision 1.3  1997/12/12 21:04:49  mkl
// changed const*const to const* for extract and insert labels -- why necessary to get working?
//
// Revision 1.2  1997/12/11 23:10:10  mkl
// bug fixes to new files extract, insert etc.
//
// Revision 1.1  1997/12/09 01:13:57  mkl
// Extractor --> extract
//
// Revision 1.1  1997/12/05 03:03:57  mkl
// moved sources from DataHandler
//
// Revision 1.7  1997/08/06 15:27:38  sjp
// Updated documentation to deal with Proxies
//
// Revision 1.6  1997/08/06 14:58:53  sjp
// Changed to handle Records, rather than Frames
//
// Revision 1.5  1997/07/11 16:44:53  sjp
// Added INCLUDE_TEMPLATE_DEFINITIONS flag
//
// Revision 1.4  1997/07/09 17:59:48  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.3  1997/05/12 15:32:32  sjp
// Modified to handle extracts with Labels
//
// Revision 1.2  1997/04/20 18:37:35  sjp
// Renamed DD handling classes to FA classes
//
// Revision 1.1  1997/04/14 19:50:09  sjp
// Standard extractor for normal DataFields
//


// system include files

// user include files

// forward declarations
class Record ;

//
// This extract should only be used when you KNOW that the label and
//   Proxy's are consistant.  There is (currently) no way to check
//   the label against the type.
//
template < class FAContainer > 
void extract( const Record& aRecord ,
	      FAContainer& aContainer ,
	      const char* aUseLabel );

template < class FAContainer > 
void extract( const Record& aRecord ,
	      FAContainer& aContainer ,
	      const char* aUseLabel ,
	      const char* aProducerLabel );

//
// The following extractor should be used in most cases, as it is more
//   "typesafe" that the preceeding one.
//
template < class FAContainer > 
void extract( const Record& aRecord ,
	      FAContainer& aContainer ) ;


#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// function definitions
# include "FrameAccess/Template/extract.cc"
#endif

#endif /* FRAMEACCESS_EXTRACTOR_H */

