#if !defined(PACKEDDATASTREAMSDELIVERY_PDSPROXYBUFFER_H)
#define PACKEDDATASTREAMSDELIVERY_PDSPROXYBUFFER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSProxyBuffer
// 
/**\class PDSProxyBuffer PDSProxyBuffer.h PackedDataStreamsDelivery/PDSProxyBuffer.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Sep 27 13:47:20 EDT 2000
// $Id: PDSProxyBuffer.h,v 1.1.1.1 2000/09/29 17:48:05 cdj Exp $
//
// Revision history
//
// $Log: PDSProxyBuffer.h,v $
// Revision 1.1.1.1  2000/09/29 17:48:05  cdj
// imported
//

// system include files

// user include files

// forward declarations

class PDSProxyBuffer
{
   public:
      // ---------- Constructors and destructor ----------------
      PDSProxyBuffer(const UInt32* iBuffer ) : m_buffer(iBuffer) {}
      //virtual ~PDSProxyBuffer();

      // ---------- const member functions ---------------------
      UInt32 index() const { return *m_buffer;}
      UInt32 size() const { return *(m_buffer+1) + 2;}
      const UInt32* buffer() const { return m_buffer;}
   private:
      // ---------- Constructors and destructor ----------------
      //PDSProxyBuffer( const PDSProxyBuffer& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const PDSProxyBuffer& operator=( const PDSProxyBuffer& ); // stop default

      // ---------- data members -------------------------------
      const UInt32* m_buffer;
};

#endif /* PACKEDDATASTREAMSDELIVERY_PDSPROXYBUFFER_H */
