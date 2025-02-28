#if !defined(STORAGEMANAGEMENT_SMCONTAINERSIZEPACKER_H)
#define STORAGEMANAGEMENT_SMCONTAINERSIZEPACKER_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMContainerSizePacker
// 
/**\class SMContainerSizePacker SMContainerSizePacker.h StorageManagement/SMContainerSizePacker.h

 Description: Compresses the size of a container into as few as 5 bits and
              a maximum of 32 bits.  Fails if container size is more than
	      2^27 ~= 140 million entries.

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Sat Sep 23 14:14:23 EDT 2000
// $Id: SMContainerSizePacker.h,v 1.1 2000/09/24 16:10:55 cdj Exp $
//
// Revision history
//
// $Log: SMContainerSizePacker.h,v $
// Revision 1.1  2000/09/24 16:10:55  cdj
// first submission
//

// system include files
#include <assert.h>

// user include files
#include "StorageManagement/Compression/SMPackerTemplate.h"

// forward declarations

class SMContainerSizePacker : public SMPackerTemplate<UInt32>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      enum {kNumberOfHeaderBits = 5, kBitsPerWord = 32 };

      // ---------- Constructors and destructor ----------------
      SMContainerSizePacker() : SMPackerTemplate<UInt32>(kNumberOfHeaderBits){}
      //virtual ~SMContainerSizePacker();

      // ---------- member functions ---------------------------
      void pack( UInt32 iValue,
		 UInt32& ioStartWord,
		 UInt32& oOverflowWord,
		 unsigned char& ioStartBit ) const {
	 //determine number of bits needed
	 unsigned char numberOfBitsForValue = 0;
	 unsigned int temp = iValue;
	 while( temp != 0 ) {
	    temp >>= 1;
	    ++numberOfBitsForValue;
	 }
	 const_cast<SMContainerSizePacker*>(this)->setNumberOfBits( numberOfBitsForValue + kNumberOfHeaderBits );

	 assert( iValue < (2 << (kBitsPerWord - kNumberOfHeaderBits)) );
	 
	 //first do compression
	 UInt32 compressedValue = iValue << kNumberOfHeaderBits;
	 compressedValue |= numberOfBitsForValue;

	 doBitShifting( compressedValue,
			ioStartWord,
			oOverflowWord,
			ioStartBit );
      }

      UInt32 unpack( const UInt32 iStartWord,
		const UInt32 iOverflowWord,
		unsigned char& ioStartBit ) const {
	 //First read how many bits we used to store the value
	 const_cast<SMContainerSizePacker*>(this)->setNumberOfBits(kNumberOfHeaderBits);

	 UInt32 numberOfBitsForValue = undoBitShifting( iStartWord,
							iOverflowWord,
							ioStartBit );

	 if( 0 == numberOfBitsForValue ) {
	    return 0;
	 }

	 //check to see if we have used up all of the iStartWord
	 DABoolean rolledOver = false;
	 UInt32 startWord = iStartWord;
	 UInt32 overflowWord = iOverflowWord;
	 if( ioStartBit >= kBitsPerWord ) { 
	    ioStartBit -= kBitsPerWord;
	    startWord = iOverflowWord;
	    overflowWord = 0;
	    rolledOver = true;
	 }
	 //now read the value of the size
	 const_cast<SMContainerSizePacker*>(this)->setNumberOfBits(numberOfBitsForValue);
	 UInt32 value = undoBitShifting( startWord,
					 overflowWord,
					 ioStartBit );
	 if( rolledOver ) {
	    ioStartBit += kBitsPerWord;
	 }
	 
	 return value;
      }

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMContainerSizePacker( const SMContainerSizePacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMContainerSizePacker& operator=( const SMContainerSizePacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMContainerSizePacker.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMCONTAINERSIZEPACKER_H */
