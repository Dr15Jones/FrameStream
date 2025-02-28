#if !defined(STORAGEMANAGEMENT_SMPACKERTEMPLATE_H)
#define STORAGEMANAGEMENT_SMPACKERTEMPLATE_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMPackerTemplate
// 
/**\class SMPackerTemplate SMPackerTemplate.h StorageManagement/SMPackerTemplate.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Sun Mar 26 12:09:20 EST 2000
// $Id: SMPackerTemplate.h,v 1.4 2003/01/30 15:51:09 cleo3 Exp $
//
// Revision history
//
// $Log: SMPackerTemplate.h,v $
// Revision 1.4  2003/01/30 15:51:09  cleo3
// explicitly use global namespace versions of frexp and log
//
// Revision 1.3  2000/07/13 21:14:38  mkl
// properly handle 0 bit packing
//
// Revision 1.2  2000/07/12 21:22:38  mkl
// fix up in number of bit calculation
//
// Revision 1.1  2000/04/04 18:56:44  cdj
// added Compression and compression testing code
//

// system include files

// user include files
#include "StorageManagement/Compression/SMPackerBase.h"

// forward declarations

template < class T>
class SMPackerTemplate : public SMPackerBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMPackerTemplate(unsigned int iNumberOfBits ) :
	 SMPackerBase( iNumberOfBits ) {}
      //virtual ~SMPackerTemplate();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual void pack( T iValue,
			 UInt32& ioStartWord,
			 UInt32& oOverflowWord,
			 unsigned char& ioStartBit ) const = 0;

      virtual T unpack( const UInt32 iStartWord,
			const UInt32 iOverflowWord,
			unsigned char& ioStartBit ) const = 0 ;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

      /** calculate the number of bits that would be needed to store
	  the value iValue to a precision of iPrecision.  iValue is
	  assumed to be positive.
       */
      static unsigned int calcNumberOfBitsNeeded( T iValue,
						  T iPrecision ) {
	 // The algorithm is functionally the same as
         //   ( log( iValue ) - log( iPrecision ) ) / log(2) +1;
	 // but much faster

	 // NOTE:
         //     f = frexp( x, n )
         //   returns
         //       0.5<= |f| < 1.0 and f*2^n = x
         // or
         //       ln_2( x ) = ln_2( f ) + n

	 int n_value, n_prec;
	 double f_value = ::frexp( iValue, &n_value ); 
	 double f_prec = ::frexp( iPrecision, &n_prec );
	 int nExtraBits = 0;
	 if( f_value >= f_prec ) {
	    //need an extra bit to store the difference between 
	    // f_diff and f_prec
	    nExtraBits = 1;
	 }
	 if( (n_value+nExtraBits) < n_prec ) {
	    // avoid negative number, resulting in very large positive number
	    return 0;
	 }
	 return (n_value - n_prec) + nExtraBits;
      }

   private:
      // ---------- Constructors and destructor ----------------
      //SMPackerTemplate( const SMPackerTemplate& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMPackerTemplate& operator=( const SMPackerTemplate& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMPackerTemplate.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMPACKERTEMPLATE_H */
