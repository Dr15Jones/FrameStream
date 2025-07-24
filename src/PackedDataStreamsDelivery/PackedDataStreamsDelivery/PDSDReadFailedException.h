#if !defined(PACKEDDATASTREAMSDELIVERY_PDSDREADFAILEDEXCEPTION_H)
#define PACKEDDATASTREAMSDELIVERY_PDSDREADFAILEDEXCEPTION_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSDReadFailedException
// 
/**\class PDSDReadFailedException PDSDReadFailedException.h PackedDataStreamsDelivery/PDSDReadFailedException.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Tue Oct  3 14:49:42 EDT 2000
// $Id: PDSDReadFailedException.h,v 1.1 2000/10/04 18:50:27 cdj Exp $
//
// Revision history
//
// $Log: PDSDReadFailedException.h,v $
// Revision 1.1  2000/10/04 18:50:27  cdj
// first submission
//

// system include files
#include <string>

// user include files
#include "PackedDataStreamsDelivery/PDSDExceptionBase.h"

// forward declarations

class PDSDReadFailedException : public PDSDExceptionBase
{

   public:
      // ---------- Constructors and destructor ----------------
      PDSDReadFailedException( const char* iHappenedWhile ) :
	 PDSDExceptionBase( (std::string("Read failed ") + 
			     std::string(iHappenedWhile) ).c_str() ) {}

};

#endif /* PACKEDDATASTREAMSDELIVERY_PDSDREADFAILEDEXCEPTION_H */
