#if !defined(STORAGEMANAGEMENT_SMPACKERBASE_H)
#define STORAGEMANAGEMENT_SMPACKERBASE_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMPackerBase
// 
/**\class SMPackerBase SMPackerBase.h StorageManagement/SMPackerBase.h

 Description: Base class for all classes that compress data

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Sun Mar 26 12:09:28 EST 2000
// $Id: SMPackerBase.h,v 1.4 2002/08/15 18:08:25 cleo3 Exp $
//
// Revision history
//
// $Log: SMPackerBase.h,v $
// Revision 1.4  2002/08/15 18:08:25  cleo3
// added missing virtual destructor to SMPackerBase
//
// Revision 1.3  2002/04/01 19:04:11  cdj
// optimized doBitShift used while unpacking
//
// Revision 1.2  2000/09/24 16:11:50  cdj
// added setNumberOfBits method
//
// Revision 1.1  2000/04/04 18:56:43  cdj
// added Compression and compression testing code
//

// system include files

// user include files

// forward declarations

class SMPackerBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      virtual ~SMPackerBase();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      unsigned int numberOfBits() const { return m_numberOfBits; }

      // ---------- static member functions --------------------

      enum { kBitsPerWord=32};
   protected:
      // ---------- protected member functions -----------------
      SMPackerBase( unsigned char iNumberOfBits ) :
	 m_numberOfBits(iNumberOfBits),
         m_bitMask( (~UInt32(0)) >> (kBitsPerWord - iNumberOfBits)){}

      // ---------- protected const member functions -----------
      void doBitShifting( UInt32 iCompressedValue,
			  UInt32& ioStartWord,
			  UInt32& oOverflowWord,
			  unsigned char& ioStartBit ) const {

	 // do necessary bit manipulation to put iCompressedValue into
	 // ioStartWord and oOverflowWord
	 ioStartWord |= iCompressedValue << ioStartBit ;
	 unsigned char newStartBit = ioStartBit + numberOfBits();
	 if( newStartBit  > kBitsPerWord ) {
	    //need to use overflow
	    //  shift over by the number of bits written to ioStartWord
	    oOverflowWord = 
	       iCompressedValue >> (kBitsPerWord - ioStartBit );
	 }
	 ioStartBit = newStartBit;
      }

      UInt32 undoBitShifting( UInt32 iStartWord,
			      UInt32 iOverflowWord,
			      unsigned char& ioStartBit ) const {
	 UInt32 compressedValue = iStartWord >> ioStartBit;
	 unsigned char newStartBit = ioStartBit + m_numberOfBits;
	 if(  kBitsPerWord < newStartBit ) {
	    //need to get info from iOverflowWord
	    compressedValue |= iOverflowWord << 
	       (kBitsPerWord - ioStartBit);
	 } 
	 //need to mask off the bits we do not need
	 compressedValue &= m_bitMask;
	 ioStartBit = newStartBit;

	 return compressedValue;
      }

      /**if compression uses variable number of bits, 
	set this value before calling bit shift operations */
      void setNumberOfBits( unsigned char iNumberOfBits ) {
	 m_numberOfBits = iNumberOfBits ;
         m_bitMask = ( (~UInt32(0)) >> (kBitsPerWord - iNumberOfBits));
      }
   private:
      // ---------- Constructors and destructor ----------------
      //SMPackerBase( const SMPackerBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMPackerBase& operator=( const SMPackerBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      unsigned char m_numberOfBits;
      unsigned int m_bitMask;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMPackerBase.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMPACKERBASE_H */
