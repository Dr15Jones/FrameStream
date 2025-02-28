#if !defined(PACKEDDATASTREAMSDELIVERY_PDSRECORDREADBUFFER_H)
#define PACKEDDATASTREAMSDELIVERY_PDSRECORDREADBUFFER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSRecordReadBuffer
// 
/**\class PDSRecordReadBuffer PDSRecordReadBuffer.h PackedDataStreamsDelivery/PDSRecordReadBuffer.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Sep 25 14:32:07 EDT 2000
// $Id: PDSRecordReadBuffer.h,v 1.2 2000/10/07 18:24:29 cdj Exp $
//
// Revision history
//
// $Log: PDSRecordReadBuffer.h,v $
// Revision 1.2  2000/10/07 18:24:29  cdj
// can now read files that were written from a different endian machine
//
// Revision 1.1.1.1  2000/09/29 17:48:05  cdj
// imported
//

// system include files

// user include files
#include "PackedDataStreamsDelivery/PDSProxyBuffer.h"

// forward declarations
class PDSIstreamWordReader;

class PDSRecordReadBuffer
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      class const_iterator {
	 public:
	    const_iterator( const UInt32* iStart ) : m_start(iStart) {}
	    DABoolean operator!=( const const_iterator& iRHS ) {
	       return m_start != iRHS.m_start; }
	    PDSProxyBuffer operator*() { return m_start; }
	    const_iterator& operator++() { m_start += operator*().size(); 
	    return *this;}
	 private:
	    const UInt32* m_start;
      };

      // ---------- Constructors and destructor ----------------
      PDSRecordReadBuffer();
      virtual ~PDSRecordReadBuffer();

      // ---------- member functions ---------------------------
      //Throws PDSDExceptionBase if problem arrises
      void read( PDSIstreamWordReader& iReader , UInt32 iWordsToRead );

      // ---------- const member functions ---------------------
      const UInt32* begin() const { return m_buffer;}
      const UInt32* end() const { return m_buffer+m_wordsInBuffer; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSRecordReadBuffer( const PDSRecordReadBuffer& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSRecordReadBuffer& operator=( const PDSRecordReadBuffer& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------
      UInt32* m_buffer;
      UInt32 m_sizeOfBuffer;
      UInt32 m_wordsInBuffer;
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSRecordReadBuffer.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSRECORDREADBUFFER_H */
