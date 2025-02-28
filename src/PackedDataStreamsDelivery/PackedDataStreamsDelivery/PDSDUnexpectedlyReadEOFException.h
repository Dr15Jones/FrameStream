#if !defined(PACKEDDATASTREAMSDELIVERY_PDSDUNEXPECTEDLYREADEOFEXCEPTION_H)
#define PACKEDDATASTREAMSDELIVERY_PDSDUNEXPECTEDLYREADEOFEXCEPTION_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSDUnexpectedlyReadEOFException
// 
/**\class PDSDUnexpectedlyReadEOFException PDSDUnexpectedlyReadEOFException.h PackedDataStreamsDelivery/PDSDUnexpectedlyReadEOFException.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Tue Oct  3 14:48:05 EDT 2000
// $Id: PDSDUnexpectedlyReadEOFException.h,v 1.1 2000/10/04 18:50:27 cdj Exp $
//
// Revision history
//
// $Log: PDSDUnexpectedlyReadEOFException.h,v $
// Revision 1.1  2000/10/04 18:50:27  cdj
// first submission
//

// system include files
#include <string>

// user include files
#include "PackedDataStreamsDelivery/PDSDExceptionBase.h"

// forward declarations

class PDSDUnexpectedlyReadEOFException : public PDSDExceptionBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSDUnexpectedlyReadEOFException( const char* iHappenedWhile ) :
	 PDSDExceptionBase( (string("Read EOF while ") + 
			     string(iHappenedWhile) ).c_str() ) {}
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSDUnexpectedlyReadEOFException.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSDUNEXPECTEDLYREADEOFEXCEPTION_H */
