#if !defined(PACKEDDATASTREAMSDELIVERY_PDSDEXCEPTIONBASE_H)
#define PACKEDDATASTREAMSDELIVERY_PDSDEXCEPTIONBASE_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSDExceptionBase
// 
/**\class PDSDExceptionBase PDSDExceptionBase.h PackedDataStreamsDelivery/PDSDExceptionBase.h

 Description: Base exception class for any PackedDataStreamsDelivery specific
              exceptions.

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Tue Oct  3 14:30:00 EDT 2000
// $Id: PDSDExceptionBase.h,v 1.1 2000/10/04 18:50:26 cdj Exp $
//
// Revision history
//
// $Log: PDSDExceptionBase.h,v $
// Revision 1.1  2000/10/04 18:50:26  cdj
// first submission
//

// system include files

// user include files
#include "DAException/DAException.h"

// forward declarations

class PDSDExceptionBase : public DAException
{

   public:
      // ---------- Constructors and destructor ----------------
      PDSDExceptionBase(const char* iMessage, DABoolean iOwnMemory=true) :
	 DAException(iMessage, iOwnMemory ) {}
      //virtual ~PDSDExceptionBase();
};

#endif /* PACKEDDATASTREAMSDELIVERY_PDSDEXCEPTIONBASE_H */
