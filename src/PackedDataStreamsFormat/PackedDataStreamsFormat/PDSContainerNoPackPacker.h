#if !defined(PACKEDDATASTREAMSFORMAT_PDSCONTAINERNOPACKPACKER_H)
#define PACKEDDATASTREAMSFORMAT_PDSCONTAINERNOPACKPACKER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      PDSContainerNoPackPacker
// 
/**\class PDSContainerNoPackPacker PDSContainerNoPackPacker.h PackedDataStreamsFormat/PDSContainerNoPackPacker.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Sun Sep 17 13:24:01 EDT 2000
// $Id: PDSContainerNoPackPacker.h,v 1.2 2002/04/04 19:12:30 cdj Exp $
//
// Revision history
//
// $Log: PDSContainerNoPackPacker.h,v $
// Revision 1.2  2002/04/04 19:12:30  cdj
// speed optimization: use SMPackerBase instead of PDSPackerBase when reading back
//
// Revision 1.1.1.1  2000/09/29 17:46:15  cdj
// imported
//

// system include files

// user include files
#include "PackedDataStreamsFormat/PDSPackerBase.h"

// forward declarations

class PDSContainerNoPackPacker : public PDSPackerBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ///used when writing data out
      PDSContainerNoPackPacker() {}

      ///used when reading data in
      PDSContainerNoPackPacker(const UInt32*& , unsigned char& ) {}
      //virtual ~PDSContainerNoPackPacker();

      // ---------- member functions ---------------------------
      PDSPacking::Types type() const {
	 return PDSPacking::kClassContainerType; }
      PDSPacking::Strategies strategy() const {
	 return PDSPacking::kNoPacking; }

      SMPackerBase* smPacker() { return reinterpret_cast<SMPackerBase*>(0);}
      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      void storeStrategyInfo( UInt32& ioPackedWord,
			      unsigned char& ioStartBit,
			      STL_VECTOR(UInt32)& ) const {
	 //no additional data needs to be stored
      }

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSContainerNoPackPacker( const PDSContainerNoPackPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSContainerNoPackPacker& operator=( const PDSContainerNoPackPacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsFormat/Template/PDSContainerNoPackPacker.cc"
//#endif

#endif /* PACKEDDATASTREAMSFORMAT_PDSCONTAINERNOPACKPACKER_H */
