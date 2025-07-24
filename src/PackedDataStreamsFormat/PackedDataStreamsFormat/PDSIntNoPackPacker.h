#if !defined(PACKEDDATASTREAMSFORMAT_PDSINTNOPACKPACKER_H)
#define PACKEDDATASTREAMSFORMAT_PDSINTNOPACKPACKER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      PDSIntNoPackPacker
// 
/**\class PDSIntNoPackPacker PDSIntNoPackPacker.h PackedDataStreamsFormat/PDSIntNoPackPacker.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Sep 15 20:09:26 EDT 2000
// $Id: PDSIntNoPackPacker.h,v 1.1.1.1 2000/09/29 17:46:15 cdj Exp $
//
// Revision history
//
// $Log: PDSIntNoPackPacker.h,v $
// Revision 1.1.1.1  2000/09/29 17:46:15  cdj
// imported
//

// system include files

// user include files
#include "PackedDataStreamsFormat/PDSPackerTemplate.h"
#include "StorageManagement/Compression/SMIntNoPackPacker.h"
#include "StorageManagement/SMPackInfo.h"

// forward declarations

template< class T>
class PDSIntNoPackPacker : public PDSPackerTemplate<T>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ///used when writing data out
      PDSIntNoPackPacker( const SMPackInfo& iPackInfo ) {}

      ///used when reading data back
      PDSIntNoPackPacker( const UInt32*& , unsigned char& ) {}

      //virtual ~PDSIntNoPackPacker();

      // ---------- member functions ---------------------------
      SMPackerTemplate<T>& packer() { return m_packer;}
      const SMIntNoPackPacker<T>& packerTrueType() const { return m_packer;}

      // ---------- const member functions ---------------------
      PDSPacking::Strategies strategy() const { return PDSPacking::kNoPacking; }
      const SMIntNoPackPacker<T>& packerTrueType() const { return m_packer;}

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
      PDSIntNoPackPacker( const PDSIntNoPackPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSIntNoPackPacker& operator=( const PDSIntNoPackPacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      SMIntNoPackPacker<T> m_packer;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsFormat/Template/PDSIntNoPackPacker.cc"
//#endif

#endif /* PACKEDDATASTREAMSFORMAT_PDSINTNOPACKPACKER_H */
