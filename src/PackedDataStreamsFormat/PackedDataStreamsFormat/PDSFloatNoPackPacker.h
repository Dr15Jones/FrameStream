#if !defined(PACKEDDATASTREAMSFORMAT_PDSFLOATNOPACKPACKER_H)
#define PACKEDDATASTREAMSFORMAT_PDSFLOATNOPACKPACKER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      PDSFloatNoPackPacker
// 
/**\class PDSFloatNoPackPacker PDSFloatNoPackPacker.h PackedDataStreamsFormat/PDSFloatNoPackPacker.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Sep 15 20:09:19 EDT 2000
// $Id: PDSFloatNoPackPacker.h,v 1.1.1.1 2000/09/29 17:46:15 cdj Exp $
//
// Revision history
//
// $Log: PDSFloatNoPackPacker.h,v $
// Revision 1.1.1.1  2000/09/29 17:46:15  cdj
// imported
//

// system include files

// user include files
#include "PackedDataStreamsFormat/PDSPackerTemplate.h"
#include "StorageManagement/Compression/SMFloatNoPackPacker.h"

// forward declarations

template< class T>
class PDSFloatNoPackPacker : public PDSPackerTemplate<T> 
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ///used when writing data out
      PDSFloatNoPackPacker( const SMPackInfo& iPackInfo ) {}

      ///used when reading data back
      PDSFloatNoPackPacker( const UInt32*&, unsigned char& ) {}
      //virtual ~PDSFloatNoPackPacker();

      // ---------- member functions ---------------------------
      SMPackerTemplate<T>& packer() { return m_packer;}

      // ---------- const member functions ---------------------
      PDSPacking::Strategies strategy() const { return PDSPacking::kNoPacking; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      void storeStrategyInfo( UInt32& ioPackedWord,
			     unsigned char& ioStartBit,
			     std::vector<UInt32>& iContainer ) const {
	 //No additional info needs to be saved
      }

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSFloatNoPackPacker( const PDSFloatNoPackPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSFloatNoPackPacker& operator=( const PDSFloatNoPackPacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      SMFloatNoPackPacker<T> m_packer;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsFormat/Template/PDSFloatNoPackPacker.cc"
//#endif

#endif /* PACKEDDATASTREAMSFORMAT_PDSFLOATNOPACKPACKER_H */



