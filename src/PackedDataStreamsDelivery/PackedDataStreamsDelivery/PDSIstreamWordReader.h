#if !defined(PACKEDDATASTREAMSDELIVERY_PDSISTREAMWORDREADER_H)
#define PACKEDDATASTREAMSDELIVERY_PDSISTREAMWORDREADER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSIstreamWordReader
// 
/**\class PDSIstreamWordReader PDSIstreamWordReader.h PackedDataStreamsDelivery/PDSIstreamWordReader.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Oct  6 14:25:47 EDT 2000
// $Id: PDSIstreamWordReader.h,v 1.4 2002/11/21 21:16:59 cleo3 Exp $
//
// Revision history
//
// $Log: PDSIstreamWordReader.h,v $
// Revision 1.4  2002/11/21 21:16:59  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.3  2001/04/10 19:48:13  cdj
// can now store strings
//
// Revision 1.2  2001/01/15 21:08:01  cdj
// Now properly reads Tags when doing byteSwapping
//
// Revision 1.1  2000/10/07 18:24:28  cdj
// can now read files that were written from a different endian machine
//

// system include files
#include "C++Std/fstream.h"

// user include files

// forward declarations

class PDSIstreamWordReader
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSIstreamWordReader( istream& iIstream ) : m_stream(iIstream) {}
      virtual ~PDSIstreamWordReader();

      // ---------- member functions ---------------------------
      //returns false if reached end of file
      // if an error occurs, an exception is thrown
      virtual DABoolean readWords( UInt32* iBuffer, 
				   unsigned int iNumberOfWords,
				   const char* iActivity );

      //stops swapping when it sees a iNumberOfStrings 0 chars
      virtual void unswapString( UInt32* iBegin, UInt32 iNumberOfStrings);
      virtual void unswapStringArray( UInt32* iBegin,
				      UInt32* iEnd );

      void skipWords( unsigned int iNumberOfWordsToSkip );

      istream& stream() { return m_stream; }
      // ---------- const member functions ---------------------
      virtual DABoolean isByteSwapping() const { return false; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSIstreamWordReader( const PDSIstreamWordReader& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSIstreamWordReader& operator=( const PDSIstreamWordReader& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      istream& m_stream;
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSIstreamWordReader.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSISTREAMWORDREADER_H */
