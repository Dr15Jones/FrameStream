#if !defined(STORAGEMANAGEMENT_SMINTNOPACKPACKER_H)
#define STORAGEMANAGEMENT_SMINTNOPACKPACKER_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMIntNoPackPacker
// 
/**\class SMIntNoPackPacker SMIntNoPackPacker.h StorageManagement/SMIntNoPackPacker.h

 Description: Does no compression when doing packing.  Only works with integral
              types.

 Usage:
    Each integer type will be stored using the minimal number of bits that
    C++ demands for that type.  This is necessary to allow us to read
    the data back on different machines.
    
    type                    size
    char,  unsigned char     8
    short, unsigned short   16
    int,   unsigned int     32
    long,  unsigned long    32

*/
//
// Author:      Chris D Jones
// Created:     Fri Mar 31 08:56:28 EST 2000
// $Id: SMIntNoPackPacker.h,v 1.2 2001/09/07 17:30:18 cleo3 Exp $
//
// Revision history
//
// $Log: SMIntNoPackPacker.h,v $
// Revision 1.2  2001/09/07 17:30:18  cleo3
// use proper template specialization syntax
//
// Revision 1.1  2000/04/04 18:56:42  cdj
// added Compression and compression testing code
//

// system include files

// user include files
#include "StorageManagement/Compression/SMPackerTemplate.h"

// forward declarations

template<class T>
class SMIntNoPackPacker : public SMPackerTemplate<T>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMIntNoPackPacker() : SMPackerTemplate<T>(sizeOf() ) {}
      //virtual ~SMIntNoPackPacker();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      void pack( T iValue,
		 UInt32& ioStartWord,
		 UInt32& oOverflowWord,
		 unsigned char& ioStartBit ) const {
	 UInt32 compressedValue ;
	 if( iValue < minValue() ) {
	    compressedValue = T(0);
	 } else {
	    compressedValue = iValue - minValue();
	 }

	 doBitShifting( compressedValue,
			ioStartWord,
			oOverflowWord,
			ioStartBit );
      }

      virtual T unpack( const UInt32 iStartWord,
			const UInt32 iOverflowWord,
			unsigned char& ioStartBit ) const {
	 UInt32 compressedValue = undoBitShifting( iStartWord,
						   iOverflowWord,
						   ioStartBit );
	 return compressedValue + minValue();
      }

      // ---------- static member functions --------------------
      static T minValue() ;
      static UInt8 sizeOf() ;

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMIntNoPackPacker( const SMIntNoPackPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMIntNoPackPacker& operator=( const SMIntNoPackPacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

const Int32 kSmallestInt32 = 0 - (1<<30) - ((1<<30) -1);
const Int32 kSmallestInt16 = 0 - (1<<14) - ((1<<14) -1);

// inline function definitions
#define SMINTNOPACKPACKER_DEF( type_, nbits_, min_ ) \
template<> inline type_ SMIntNoPackPacker<type_>::minValue() { return min_; } \
template<> inline UInt8 SMIntNoPackPacker<type_>::sizeOf() { return nbits_; }

SMINTNOPACKPACKER_DEF( char, 8, CHAR_MIN )
SMINTNOPACKPACKER_DEF( unsigned char, 8, 0 )

SMINTNOPACKPACKER_DEF( short, 16, kSmallestInt16  )
SMINTNOPACKPACKER_DEF( unsigned short, 16, 0 )

//NOTE: C++ standard says that int must be at least 16 bits, but in 
// discussions w/ dsr we determined that all platforms we are going to
// use have int as at least 32 bits and our users might be unpleasantly
// surprised if we stored ints only to 16 bit precision.
SMINTNOPACKPACKER_DEF( int, 32, kSmallestInt32  )
SMINTNOPACKPACKER_DEF( unsigned int, 32, 0 )

SMINTNOPACKPACKER_DEF( long, 32, kSmallestInt32  )
SMINTNOPACKPACKER_DEF( unsigned long, 32, 0 )

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMIntNoPackPacker.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMINTNOPACKPACKER_H */
