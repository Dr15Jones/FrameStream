#if !defined(PACKEDDATASTREAMSDELIVERY_PDSSOURCESTREAMFACTORY_H)
#define PACKEDDATASTREAMSDELIVERY_PDSSOURCESTREAMFACTORY_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSSourceStreamFactory
// 
/**\class PDSSourceStreamFactory PDSSourceStreamFactory.h PackedDataStreamsDelivery/PDSSourceStreamFactory.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Tue Sep 19 14:17:43 EDT 2000
// $Id: PDSSourceStreamFactory.h,v 1.2 2001/04/10 19:48:14 cdj Exp $
//
// Revision history
//
// $Log: PDSSourceStreamFactory.h,v $
// Revision 1.2  2001/04/10 19:48:14  cdj
// can now store strings
//
// Revision 1.1.1.1  2000/09/29 17:48:05  cdj
// imported
//

// system include files

// user include files
#include "PackedDataStreamsFormat/pds_packing_enums.h"

// forward declarations
class PDSUnpackingSourceStreamBase;

class PDSSourceStreamFactory
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSSourceStreamFactory();
      //virtual ~PDSSourceStreamFactory();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      PDSUnpackingSourceStreamBase* 
      createStream( const UInt32*& ioBuffer,
		    unsigned char& ioStartBit,
		    DABoolean iSwappedBytes ) const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSSourceStreamFactory( const PDSSourceStreamFactory& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSSourceStreamFactory& operator=( const PDSSourceStreamFactory& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSSourceStreamFactory.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSSOURCESTREAMFACTORY_H */
