#if !defined(PACKEDDATASTREAMSFORMAT_PDSSTRINGPACKER_H)
#define PACKEDDATASTREAMSFORMAT_PDSSTRINGPACKER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      PDSStringPacker
// 
/**\class PDSStringPacker PDSStringPacker.h PackedDataStreamsFormat/PDSStringPacker.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Sep 15 20:09:39 EDT 2000
// $Id: PDSStringPacker.h,v 1.3 2002/04/04 19:12:31 cdj Exp $
//
// Revision history
//
// $Log: PDSStringPacker.h,v $
// Revision 1.3  2002/04/04 19:12:31  cdj
// speed optimization: use SMPackerBase instead of PDSPackerBase when reading back
//
// Revision 1.2  2001/04/10 19:47:33  cdj
// can now store strings
//
// Revision 1.1.1.1  2000/09/29 17:46:15  cdj
// imported
//

// system include files

// user include files
#include "PackedDataStreamsFormat/PDSPackerBase.h"

// forward declarations

class PDSStringPacker : public PDSPackerBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      enum {kByteSwapped, kNotByteSwapped};

      // ---------- Constructors and destructor ----------------
      PDSStringPacker(DABoolean iSwappedBytes ) : m_byteSwapped(iSwappedBytes){}
      //virtual ~PDSStringPacker();

      // ---------- member functions ---------------------------
      SMPackerBase* smPacker() {
         return (m_byteSwapped? reinterpret_cast<SMPackerBase*>(kByteSwapped):
                reinterpret_cast<SMPackerBase*>(kNotByteSwapped) );
      }

      // ---------- const member functions ---------------------
      PDSPacking::Types type() const {
	 return PDSPacking::kStringType; }
      PDSPacking::Strategies strategy() const {
	 return PDSPacking::kNoPacking; }

      // ---------- static member functions --------------------
      DABoolean bytesSwapped() { return m_byteSwapped; }
      void setByteSwapped(DABoolean iSwap) { m_byteSwapped = iSwap;}

   protected:
      // ---------- protected member functions -----------------
      void storeStrategyInfo( UInt32& ioPackedWord,
			      unsigned char& ioStartBit,
			      std::vector<UInt32>& ) const {
	 //no additional data needs to be stored
      }

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSStringPacker( const PDSStringPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSStringPacker& operator=( const PDSStringPacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------
      DABoolean m_byteSwapped;

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsFormat/Template/PDSStringPacker.cc"
//#endif

#endif /* PACKEDDATASTREAMSFORMAT_PDSSTRINGPACKER_H */
