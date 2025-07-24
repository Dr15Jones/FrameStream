#if !defined(PACKEDDATASTREAMSDELIVERY_PDSUNPACKINGSOURCESTREAMBASE_H)
#define PACKEDDATASTREAMSDELIVERY_PDSUNPACKINGSOURCESTREAMBASE_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSUnpackingSourceStreamBase
//
/**\class PDSUnpackingSourceStreamBase PDSUnpackingSourceStreamBase.h PackedDataStreamsDelivery/Sources/PDSUnpackingSourceStreamBase.h

 Description: Base class for SourceStreams that only know how to unpack one way

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Apr 14 11:04:08 EDT 2003
// $Id$
//
// Revision history
//
// $Log$

// system include files

// user include files
#include "Experiment/Experiment.h"
#include "StorageManagement/SMSourceStream.h"

// forward declarations

class PDSUnpackingSourceStreamBase : public SMSourceStream
{
   // ---------- friend classes and functions ---------------

public:
   // ---------- constants, enums and typedefs --------------

   // ---------- Constructors and destructor ----------------
   PDSUnpackingSourceStreamBase() : m_nextSource(endSource()),
                                    m_startWord(0),
                                    m_startBit(0) {}

   virtual ~PDSUnpackingSourceStreamBase()
   {
      if (m_nextSource != endSource())
      {
         delete m_nextSource;
      }
   }

   // ---------- member functions ---------------------------
   void setNextSource(PDSUnpackingSourceStreamBase *iSource)
   {
      if (m_nextSource != endSource() &&
          m_nextSource != iSource)
      {
         delete m_nextSource;
      }
      m_nextSource = iSource;
   }

   void setBufferInfo(const UInt32 *iStartWord,
                      unsigned char iStartBit)
   {
      m_startWord = iStartWord;
      m_startBit = iStartBit;
   }

   // ---------- const member functions ---------------------
   const UInt32 *startWord() const { return m_startWord; }
   unsigned char startBit() const { return m_startBit; }
   PDSUnpackingSourceStreamBase *nextSource() const { return m_nextSource; }

   // ---------- static member functions --------------------
   static PDSUnpackingSourceStreamBase *endSource();

protected:
   // ---------- protected member functions -----------------
   PDSUnpackingSourceStreamBase &gotoNext()
   {
      m_nextSource->setBufferInfo(m_startWord, m_startBit);
      m_startWord = 0;
      return *m_nextSource;
   }

   void advanceStartWordIfNeeded()
   {
      if (m_startBit >= 32)
      {
         m_startBit -= 32;
         ++m_startWord;
      }
   }

   // ---------- protected const member functions -----------

private:
   // ---------- Constructors and destructor ----------------
   PDSUnpackingSourceStreamBase(const PDSUnpackingSourceStreamBase &); // stop default

   // ---------- assignment operator(s) ---------------------
   const PDSUnpackingSourceStreamBase &operator=(const PDSUnpackingSourceStreamBase &); // stop default

   // ---------- private member functions -------------------

   // ---------- private const member functions -------------

   // ---------- data members -------------------------------
   PDSUnpackingSourceStreamBase *m_nextSource;
   const UInt32 *m_startWord;
   unsigned char m_startBit;

   // ---------- static data members ------------------------
};

// inline function definitions

#endif /* PACKEDDATASTREAMSDELIVERY_PDSUNPACKINGSOURCESTREAMBASE_H */
