#if !defined(PACKEDDATASTREAMSDELIVERY_PDSISTREAMSWAPBYTESWORDREADER_H)
#define PACKEDDATASTREAMSDELIVERY_PDSISTREAMSWAPBYTESWORDREADER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSIstreamSwapBytesWordReader
// 
/**\class PDSIstreamSwapBytesWordReader PDSIstreamSwapBytesWordReader.h PackedDataStreamsDelivery/PDSIstreamSwapBytesWordReader.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Oct  6 14:33:11 EDT 2000
// $Id: PDSIstreamSwapBytesWordReader.h,v 1.3 2001/04/10 19:48:13 cdj Exp $
//
// Revision history
//
// $Log: PDSIstreamSwapBytesWordReader.h,v $
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

// user include files
#include "PackedDataStreamsDelivery/PDSIstreamWordReader.h"
// forward declarations

class PDSIstreamSwapBytesWordReader : public PDSIstreamWordReader
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSIstreamSwapBytesWordReader( std::istream& iStream ) :
	 PDSIstreamWordReader( iStream ) {}
      //virtual ~PDSIstreamSwapBytesWordReader();

      // ---------- member functions ---------------------------
      DABoolean readWords( UInt32* iBuffer, 
			   unsigned int iNumberOfWords,
			   const char* iActivity );

      void unswapString( UInt32* iBegin, UInt32 iNumberOfStrings);
      void unswapStringArray( UInt32* iBegin,
			      UInt32* iEnd );

      // ---------- const member functions ---------------------
      DABoolean isByteSwapping() const { return true; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSIstreamSwapBytesWordReader( const PDSIstreamSwapBytesWordReader& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSIstreamSwapBytesWordReader& operator=( const PDSIstreamSwapBytesWordReader& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSIstreamSwapBytesWordReader.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSISTREAMSWAPBYTESWORDREADER_H */
