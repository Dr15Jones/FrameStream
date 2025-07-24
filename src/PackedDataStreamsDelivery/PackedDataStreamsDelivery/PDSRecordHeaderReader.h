#if !defined(PACKEDDATASTREAMSDELIVERY_PDSRECORDHEADERREADER_H)
#define PACKEDDATASTREAMSDELIVERY_PDSRECORDHEADERREADER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSRecordHeaderReader
// 
/**\class PDSRecordHeaderReader PDSRecordHeaderReader.h PackedDataStreamsDelivery/PDSRecordHeaderReader.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Sep 25 10:55:06 EDT 2000
// $Id: PDSRecordHeaderReader.h,v 1.3 2002/11/21 21:17:00 cleo3 Exp $
//
// Revision history
//
// $Log: PDSRecordHeaderReader.h,v $
// Revision 1.3  2002/11/21 21:17:00  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.2  2000/10/07 18:24:29  cdj
// can now read files that were written from a different endian machine
//
// Revision 1.1.1.1  2000/09/29 17:48:05  cdj
// imported
//

// system include files
//#include <fstream>

// user include files
#include "DataHandler/SyncValue.h"
#include "PackedDataStreamsFormat/pds_record_header.h"

// forward declarations
class PDSIstreamWordReader;

class PDSRecordHeaderReader : public PDSRecordHeader
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSRecordHeaderReader() : m_recordType(0), m_bodyLength(0) {}
      //virtual ~PDSRecordHeaderReader();

      // ---------- member functions ---------------------------
      ///returns false when reaches end of file. On error throws exception
      DABoolean read( PDSIstreamWordReader& iFStream ) ;

      // ---------- const member functions ---------------------
      const SyncValue& syncValue() const { return m_syncValue; }
      UInt32 recordType() const { return m_recordType; }
      UInt32 bodyLength() const { return m_bodyLength; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSRecordHeaderReader( const PDSRecordHeaderReader& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSRecordHeaderReader& operator=( const PDSRecordHeaderReader& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      SyncValue m_syncValue;
      UInt32 m_recordType;
      UInt32 m_bodyLength;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSRecordHeaderReader.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSRECORDHEADERREADER_H */
